/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "timers.h"

TimerHandle_t xTimer;
int32_t i = 0;
char name[] = "Ryan Willard";

DRV_USART_INIT              usartInit;
SYS_MODULE_OBJ              objectHandle;
DRV_HANDLE handle;

#define MY_BUFFER_SIZE 6
#define NUM_LINES 3

//MY_APP_OBJ myAppObj;    
uint8_t mybuffer[NUM_LINES][MY_BUFFER_SIZE] = {{"Ryan"},{"James"},{"Adam"}};
DRV_USART_BUFFER_HANDLE bufferHandle;

void vTimerCallback()
{
   
//    char test = 'a';
    //DRV_USART_Write(handle, &mybuffer, 1);
    int i;
    for (i = 0; i < 3; i++)
    {
        DRV_USART_BufferAddWrite(handle, &bufferHandle, mybuffer[i], strlen(mybuffer[i]));
    }

//    if(DRV_USART_BUFFER_HANDLE_INVALID == bufferHandle)
//    {
//        // Error handling here
//    }
    

}


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback funtions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
    
    // uart initialization
    // The following code snippet shows an example USART driver initialization.
    // The driver is initialized for normal mode and a baud of 300. The
    // receive queue size is set to 2 and transmit queue size is set to 3.
    


    usartInit.baud  = 57600;
    usartInit.mode  = DRV_USART_OPERATION_MODE_NORMAL;
    usartInit.flags = DRV_USART_INIT_FLAG_NONE;
    usartInit.usartID   = USART_ID_1;
    usartInit.brgClock  = 80000000;
    usartInit.handshake = DRV_USART_HANDSHAKE_NONE;
    usartInit.lineControl       = DRV_USART_LINE_CONTROL_8NONE1;
    usartInit.interruptError    = INT_SOURCE_USART_1_ERROR;
    usartInit.interruptReceive  = INT_SOURCE_USART_1_RECEIVE;
    usartInit.queueSizeReceive  = 2;
    usartInit.queueSizeTransmit = 3;
    usartInit.interruptTransmit = INT_SOURCE_USART_1_TRANSMIT;
    usartInit.moduleInit.value  = SYS_MODULE_POWER_RUN_FULL;

//    objectHandle = DRV_USART_Initialize(DRV_USART_INDEX_1, (SYS_MODULE_INIT*)&usartInit);
//    if (SYS_MODULE_OBJ_INVALID == objectHandle)
//    {
//        // Handle error
//    }
    
    handle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_NONBLOCKING | DRV_IO_INTENT_WRITE);
    if (DRV_HANDLE_INVALID == handle)
    {
        // Unable to open the driver
        // May be the driver is not initialized or the initialization
        // is not complete.
    }
    
    
    // timer setup
    xTimer = xTimerCreate("Timer", 10, pdTRUE, 0, vTimerCallback);
    xTimerStart(xTimer, 0);
    vTaskStartScheduler();
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            break;
        }

        /* TODO: implement your application state machine.*/

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
 

/*******************************************************************************
 End of File
 */
