/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
  
    LCDMessage(LINE1_START_ADDR, "      Groundhog     ");
  LCDMessage(LINE2_START_ADDR, "on");       /*开始按钮*/
  LCDMessage(LINE2_START_ADDR + 6, "1");    /*对应1号白灯*/
  LCDMessage(LINE2_START_ADDR + 13, "2");   /*对应2号紫灯*/
  LCDMessage(LINE2_END_ADDR - 2, "3");      /*对应3号蓝灯*/

  /* All discrete LEDs to off */
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
   LedOff(LCD_GREEN);
   LedOff(LCD_RED);

 
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
    if( IsButtonPressed(BUTTON0) )           /*游戏开始，lv 1（间隔1s）*/
   {
     u16 lv1=0,lv2=0,time=0;
     time++ ;
     if(time == 500)                     /*500ms亮第一个灯*/
     {
       LedOn(WHITE);
       if( IsButtonPressed(BUTTON1) && time<1500 )       /*1按键是否按下,同时防止时间内持续按下，导致多次计数*/
       {
          time=1499;
          LedOff(WHITE);
          lv1=lv1+1;
       }
     }
     
     if(time == 1500)                    /*1500ms亮第二个灯*/
     {
       LedOff(WHITE);
       LedOn(PURPLE);
       if( IsButtonPressed(BUTTON2) && time<2500)       /*2按键是否按下，同按键1*/
       {  
          time=2499;
          LedOff(PURPLE);
          lv1=lv1+1;
       }
     }
    
     if(time == 2500)                    /*2500ms亮第三个灯*/
     {
       LedOff(PURPLE);
       LedOn(BLUE);
       if( IsButtonPressed(BUTTON3) && time<3500 )       /*3按键是否按下，同按键1*/
       {
          time=3499;
          LedOff(BLUE);
          lv1=lv1+1;
       }
     }
     if(time == 3500)                   /*lv 1时间到，关灯*/
     {
       LedOff(BLUE);
     }  
     
     if( lv1 == 3 )                          /*如果3个灯全对，开启lv2，其余灯闪烁三秒过渡到lv2*/
     {
       LedBlink(RED, LED_2HZ);
       LedBlink(CYAN, LED_2HZ);
       LedBlink(GREEN, LED_2HZ);
       LedBlink(ORANGE, LED_2HZ);
       LedBlink(YELLOW, LED_2HZ);
      
       
        if(time == 6500)                /*3秒到，关灯，开启lv 2(间隔0.5s)*/               
        {
            LedOff(CYAN);
            LedOff(GREEN);
            LedOff(YELLOW);
            LedOff(ORANGE);
            LedOff(RED); 
            
            
            LedOn(WHITE);
            if( IsButtonPressed(BUTTON1) && time<7000 )       /*同lv 1*/
           {
               time=6999;
               LedOff(WHITE);
               lv2=lv2+1;
            }
        }  
            if(time == 7000)                                 /*同理 lv 1*/
           {
               LedOff(WHITE);
               LedOn(PURPLE);
               if( IsButtonPressed(BUTTON2) && time<7500)       
              {  
                time=7499;
                LedOff(PURPLE);
                lv2=lv2+1;
               }
           }
           
           if(time == 7500)                                   /*同理 lv 1*/
           {
               LedOff(PURPLE);
               LedOn(BLUE);
               if( IsButtonPressed(BUTTON3) && time<8000 )       
               {
                time=7999;
                LedOff(BLUE);
                lv2=lv2+1;
                }
            }
            if(time == 8000)                   /*lv 2时间到，关灯*/
           {
            LedOff(BLUE);
            }  
        
            if(lv2 == 3)             /*lv 2判定*/
            {
 
              LedOn(LCD_GREEN);
              
            }
            else
            {
                PWMAudioOn(BUZZER1);    
                LedOn(LCD_RED);
                if(time == 9000)
                {
                   PWMAudioOff(BUZZER1);
                }
            }
     }
     else                         /*lv 1 3次未成功，蜂鸣器响1s*/
     {
       PWMAudioOn(BUZZER1);  
       LedOn(LCD_RED);
       if(time == 4500)
       {
         PWMAudioOff(BUZZER1);
       }
     }
         
   }
} /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
