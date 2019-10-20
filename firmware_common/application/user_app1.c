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
static u8 UserApp_au8MyName[] ="   PLEASE CHOOSE !    ";
void UserApp1Initialize(void)
{
  LCDMessage(LINE1_START_ADDR, UserApp_au8MyName);
  LCDMessage(LINE2_START_ADDR, "1");
  LCDMessage(LINE2_START_ADDR + 6, "2");
  LCDMessage(LINE2_START_ADDR + 13, "3");
  LCDMessage(LINE2_END_ADDR - 2, "off");

  /* All discrete LEDs to off */
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
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
  if( WasButtonPressed(BUTTON3) )
{ 
  
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
  PWMAudioOff(BUZZER1);
  PWMAudioOff(BUZZER2);
  
  ButtonAcknowledge(BUTTON3);
  ButtonAcknowledge(BUTTON2);
  ButtonAcknowledge(BUTTON1);
  ButtonAcknowledge(BUTTON0);
   
}
else
{
  //1 
  if(!(IsButtonPressed(BUTTON1) || IsButtonPressed(BUTTON2) ) ) 
  {if( WasButtonPressed(BUTTON0) )
   {
    LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
    static u16 au16NotesLeft[]    = {F4, F4, A4, A4, D4, D4, F4, F4, A3S, A3S, D4, D4, C4, C4};
  static u16 au16DurationLeft[] = {HN, HN, HN, HN, HN, HN, HN, HN, HN,  HN,  HN, HN, HN, HN};
  static u16 au16NoteTypeLeft[] = {RT, RT, RT, RT, RT, RT, RT, RT, RT,  RT,  RT, RT, RT, RT};
  static u8 u8IndexLeft = 0 ,  u8CurrentIndex;
  static u32 u32LeftTimer = 0;
  static u16 u16CurrentDurationLeft = 0;
  static u16 u16NoteSilentDurationLeft = 0;
  static bool bNoteActiveNextLeft = TRUE;
  
  /* Left Hand */
  if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft))
  {
    u32LeftTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexLeft;
    
    /* Set up to play current note */
    if(bNoteActiveNextLeft)
    {
      if(au16NoteTypeLeft[u8CurrentIndex] == RT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationLeft = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextLeft = FALSE;
      }
    
      else if(au16NoteTypeLeft[u8CurrentIndex] == ST)
      {
        u16CurrentDurationLeft = STACCATO_NOTE_TIME;
        u16NoteSilentDurationLeft = au16DurationLeft[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextLeft = FALSE;
      }

      else if(au16NoteTypeLeft[u8CurrentIndex] == HT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex];
        u16NoteSilentDurationLeft = 0;
        bNoteActiveNextLeft = TRUE;

        u8IndexLeft++;
        if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
        {
          u8IndexLeft = 0;
        }
      }

      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesLeft[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER2, au16NotesLeft[u8CurrentIndex]);
        PWMAudioOn(BUZZER2);
      }
      else
      {                
        PWMAudioOff(BUZZER2);
      }
    }
    else
    {
      PWMAudioOff(BUZZER2);
      u32LeftTimer = G_u32SystemTime1ms;
      u16CurrentDurationLeft = u16NoteSilentDurationLeft;
      bNoteActiveNextLeft = TRUE;
      
      u8IndexLeft++;
      if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
      {
        u8IndexLeft = 0;
      }
    } /* end else if(bNoteActiveNextLeft) */
  } /* end if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft)) */
    if(au16NotesLeft[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER2, au16NotesLeft[u8CurrentIndex]);
        PWMAudioOn(BUZZER2);
        
        /* LED control */
        switch(au16NotesLeft[u8CurrentIndex])
        {
          case F4:
            LedOn(WHITE);
            break;
            
          case E5:
            LedOn(PURPLE);
            break;
            
          case A4:
            LedOn(BLUE);
            break;
            
          case D4:
            LedOn(CYAN);
            break;
            
          case A3S:
            LedOn(GREEN);
            break;
            
          case C4:
            LedOn(YELLOW);
            break;
            
          case D5:
            LedOn(ORANGE);
            break;
            
          case A5:
            LedOn(RED);
            break;
            
          default:
            break;
            
        } /* end switch */
      }
      else
      {                
        PWMAudioOff(BUZZER2);
        LedOff(WHITE);
        LedOff(PURPLE);
        LedOff(BLUE);
        LedOff(CYAN);
        LedOff(GREEN);
        LedOff(YELLOW);
        LedOff(ORANGE);
        LedOff(RED);
      }/* end if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft)) */
   }
  
 } 
 else
 {
   PWMAudioOff(BUZZER2);
   PWMAudioOff(BUZZER1);
        LedOff(WHITE);
        LedOff(PURPLE);
        LedOff(BLUE);
        LedOff(CYAN);
        LedOff(GREEN);
        LedOff(YELLOW);
        LedOff(ORANGE);
        LedOff(RED);
   ButtonAcknowledge(BUTTON0);
 }
 
  //2
  if(!(IsButtonPressed(BUTTON1) || IsButtonPressed(BUTTON0) ) ) 
  {if( WasButtonPressed(BUTTON2) )
   {
     LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
    static u16 au16NotesLeft[]    = {E4, E4, B4, B4, C5S, C5S, B4, A4, A4, G4S, G4S, F4S, F4S, E4};
  static u16 au16DurationLeft[] = {EN, EN, EN, EN, EN, EN, EN, EN, EN,  EN,  EN, EN, EN, EN};
  static u16 au16NoteTypeLeft[] = {RT, RT, RT, RT, RT, RT, RT, RT, RT,  RT,  RT, RT, RT, RT};
  static u8 u8IndexLeft = 0 ,  u8CurrentIndex;
  static u32 u32LeftTimer = 0;
  static u16 u16CurrentDurationLeft = 0;
  static u16 u16NoteSilentDurationLeft = 0;
  static bool bNoteActiveNextLeft = TRUE;
  
  /* Left Hand */
  if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft))
  {
    u32LeftTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexLeft;
    
    /* Set up to play current note */
    if(bNoteActiveNextLeft)
    {
      if(au16NoteTypeLeft[u8CurrentIndex] == RT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationLeft = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextLeft = FALSE;
      }
    
      else if(au16NoteTypeLeft[u8CurrentIndex] == ST)
      {
        u16CurrentDurationLeft = STACCATO_NOTE_TIME;
        u16NoteSilentDurationLeft = au16DurationLeft[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextLeft = FALSE;
      }

      else if(au16NoteTypeLeft[u8CurrentIndex] == HT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex];
        u16NoteSilentDurationLeft = 0;
        bNoteActiveNextLeft = TRUE;

        u8IndexLeft++;
        if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
        {
          u8IndexLeft = 0;
        }
      }

      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesLeft[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER2, au16NotesLeft[u8CurrentIndex]);
        PWMAudioOn(BUZZER2);
      }
      else
      {                
        PWMAudioOff(BUZZER2);
      }
    }
    else
    {
      PWMAudioOff(BUZZER2);
      u32LeftTimer = G_u32SystemTime1ms;
      u16CurrentDurationLeft = u16NoteSilentDurationLeft;
      bNoteActiveNextLeft = TRUE;
      
      u8IndexLeft++;
      if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
      {
        u8IndexLeft = 0;
      }
    } /* end else if(bNoteActiveNextLeft) */
  } /* end if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft)) */
    if(au16NotesLeft[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER2, au16NotesLeft[u8CurrentIndex]);
        PWMAudioOn(BUZZER2);
        
        /* LED control */
        switch(au16NotesLeft[u8CurrentIndex])
        {
          case D5S:
            LedOn(WHITE);
            break;
            
          case E5:
            LedOn(PURPLE);
            break;
            
          case A4:
            LedOn(RED);
            break;
            
          case B4:
            LedOn(CYAN);
            break;
            
          case F4S:
            LedOn(GREEN);
            break;
            
          case E4:
            LedOn(YELLOW);
            break;
            
          case D5:
            LedOn(ORANGE);
            break;
            
          case G4S:
            LedOn(BLUE);
            break;
            
          default:
            break;
            
        } /* end switch */
      }
      else
      {                
        PWMAudioOff(BUZZER2);
        LedOff(WHITE);
        LedOff(PURPLE);
        LedOff(BLUE);
        LedOff(CYAN);
        LedOff(GREEN);
        LedOff(YELLOW);
        LedOff(ORANGE);
        LedOff(RED);
      }/* end if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft)) */
   
   }
  }
  else
 {
   PWMAudioOff(BUZZER2);
   PWMAudioOff(BUZZER1);
        LedOff(WHITE);
        LedOff(PURPLE);
        LedOff(BLUE);
        LedOff(CYAN);
        LedOff(GREEN);
        LedOff(YELLOW);
        LedOff(ORANGE);
        LedOff(RED);
   ButtonAcknowledge(BUTTON2);
 }
 
  //3
 if(!(IsButtonPressed(BUTTON0) || IsButtonPressed(BUTTON2) ) ) 
  {if( WasButtonPressed(BUTTON1) )
   {  
    
     LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  

     
    static u16 au16NotesLeft[]    = {D5S, E5, A4, F5S, A4, F5S, A5, E4, D5S, D5, D5S, E5, F5S};
  static u16 au16DurationLeft[] = {HN, FN, HN, HN, HN, FN, FN, HN, FN,  HN,  HN, FN, HN};
  static u16 au16NoteTypeLeft[] = {RT, RT, RT, RT, RT, RT, RT, RT, RT,  RT,  RT, RT, RT};
  static u8 u8IndexLeft = 0 ,  u8CurrentIndex;
  static u32 u32LeftTimer = 0;
  static u16 u16CurrentDurationLeft = 0;
  static u16 u16NoteSilentDurationLeft = 0;
  static bool bNoteActiveNextLeft = TRUE;
  
  /* Left Hand */
  if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft))
  {
    u32LeftTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexLeft;
    
    /* Set up to play current note */
    if(bNoteActiveNextLeft)
    {
      if(au16NoteTypeLeft[u8CurrentIndex] == RT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationLeft = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextLeft = FALSE;
      }
    
      else if(au16NoteTypeLeft[u8CurrentIndex] == ST)
      {
        u16CurrentDurationLeft = STACCATO_NOTE_TIME;
        u16NoteSilentDurationLeft = au16DurationLeft[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextLeft = FALSE;
      }

      else if(au16NoteTypeLeft[u8CurrentIndex] == HT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex];
        u16NoteSilentDurationLeft = 0;
        bNoteActiveNextLeft = TRUE;

        u8IndexLeft++;
        if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
        {
          u8IndexLeft = 0;
        }
      }

      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesLeft[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER2, au16NotesLeft[u8CurrentIndex]);
        PWMAudioOn(BUZZER2);
      }
      else
      {                
        PWMAudioOff(BUZZER2);
      }
    }
    else
    {
      PWMAudioOff(BUZZER2);
      u32LeftTimer = G_u32SystemTime1ms;
      u16CurrentDurationLeft = u16NoteSilentDurationLeft;
      bNoteActiveNextLeft = TRUE;
      
      u8IndexLeft++;
      if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
      {
        u8IndexLeft = 0;
      }
    } /* end else if(bNoteActiveNextLeft) */
  } 
  if(au16NotesLeft[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER2, au16NotesLeft[u8CurrentIndex]);
        PWMAudioOn(BUZZER2);
        
        /* LED control */
        switch(au16NotesLeft[u8CurrentIndex])
        {
          case D5S:
            LedOn(RED);
            break;
            
          case E5:
            LedOn(BLUE);
            break;
            
          case A4:
            LedOn(PURPLE);
            break;
            
          case F5S:
            LedOn(CYAN);
            break;
            
          case A5:
            LedOn(GREEN);
            break;
            
          case E4:
            LedOn(YELLOW);
            break;
            
          case D5:
            LedOn(ORANGE);
            break;
            
          case D6:
            LedOn(WHITE);
            break;
            
          default:
            break;
            
        } /* end switch */
      }
      else
      {                
        PWMAudioOff(BUZZER2);
        LedOff(WHITE);
        LedOff(PURPLE);
        LedOff(BLUE);
        LedOff(CYAN);
        LedOff(GREEN);
        LedOff(YELLOW);
        LedOff(ORANGE);
        LedOff(RED);
      }/* end if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft)) */
   }
  /* Set the buzzer frequency and LED for the note (handle NO special case) */
  }
  else
 {
        PWMAudioOff(BUZZER2);
        PWMAudioOff(BUZZER1);
        LedOff(WHITE);
        LedOff(PURPLE);
        LedOff(BLUE);
        LedOff(CYAN);
        LedOff(GREEN);
        LedOff(YELLOW);
        LedOff(ORANGE);
        LedOff(RED);
   ButtonAcknowledge(BUTTON1);
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
