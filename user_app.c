/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)
@brief
Initializes the application's variables.
Should only be called once in main init section.
Requires:
- NONE
Promises:
- NONE
*/
void UserAppInitialize(void)
{
    LATA = 0x80;
    T0CON1 = 0x54;
    T0CON0 = 0x90;
    
} /* end UserAppInitialize() */

/*---------------------------------------------------------------------------------------------------------------------
 void TimeXus(u16 u16Microseconds)
 Sets Timer0 to count u16Microseconds
 
 Requires:
 - Timer0 configured such that each timer tick is 1 microsecond
 - u16Microseconds is the value in microseconds to time from 1 to 65535
 
 Promises:
 - Pre-loads TMr0H:L to clock out desired period
 - TMR0IF cleared
 - Timer0 enabled
 */
void TimeXus(u16 u16Microseconds)
{
    T0CON0 &= 0x7F; //disabling timer
    u16 u16Timer = 0xFFFF - u16Microseconds;
    TMR0L = u16Timer & 0x00FF;
    TMR0H = (u8) ((u16Timer & 0xFF00) >> 8 );
    PIR3 &= 0x7F;
    T0CON0 |= 0x80;
}

/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)
@brief Application code that runs once per system loop
Requires:
- 
Promises:
- 
*/
void UserAppRun(void)
{
    static u16 u16Delay = 0x0000;
    static int stateofLED = 0;
    
    static u8 u8Pattern[22] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x21, 0x22, 0x24, 0x28, 0x30, 0x31, 0x32, 0x34, 0x38, 0x39, 0x3A, 0x3C, 0x3D, 0x3E, 0x3F};
    u16Delay++;
    
    if(u16Delay == 1000)
    {
       u16Delay = 0x0000;
       u8 u8var = LATA; 
       u8var &= 0x80;  
       u8var |= u8Pattern[stateofLED];
       LATA = u8var;
       stateofLED++;
       if(stateofLED == 22)
       {
           stateofLED = 0;
       }
    }
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
