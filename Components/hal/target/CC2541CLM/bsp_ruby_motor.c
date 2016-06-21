/**************************************************************************************************
  Filename:       bsp_ruby_led.c
  Revised:        $Date: 2015/9/10 $
  Revision:       $Revision: 1 $

  Description:    This file contains the interface to the bsp ruby capacity measurement.

  Copyright 2015 - 2016 QijiTek. All rights reserved.
**************************************************************************************************/

/***************************************************************************************************
 *                                             INCLUDES
 ***************************************************************************************************/
#include "hal_mcu.h"
#include "hal_defs.h"
#include "hal_types.h"
#include "hal_drivers.h"
#include "osal.h"
#include "hal_board.h"
#include "bsp_ruby_motor.h"
#include "bsp_smart_cover.h"
#include "stdio.h"

#if defined POWER_SAVING
#include "bsp_power.h"
#include "OSAL_PwrMgr.h"
#endif


/***************************************************************************************************
 *                                             CONSTANTS
 ***************************************************************************************************/

/***************************************************************************************************
 *                                              MACROS
 ***************************************************************************************************/

/***************************************************************************************************
 *                                              TYPEDEFS
 ***************************************************************************************************/


/***************************************************************************************************
 *                                           GLOBAL VARIABLES
 ***************************************************************************************************/
uint8 pwm_change_value = 50;
//uint8 BspScDelegateState  = BSP_SC_INT_IDLE;
uint8 BspMotorDelegateTaskID = BSP_SC_INT_NO_TASK;
uint16 BspMotorDelegateEvent = BSP_SC_INT_NO_EVENT;

/***************************************************************************************************
 *                                            LOCAL FUNCTION
 ***************************************************************************************************/

/***************************************************************************************************
 *                                            FUNCTIONS - API
 ***************************************************************************************************/
/***************************************************************************************************
 * @fn      BspRubyMotorInit
 *
 * @brief   
 *
 * @param   None
 *          
 *          
 *                    
 *
 * @return  None
 ***************************************************************************************************/
void BspRubyMotorInit( void )
{
  P1DIR |= (1 << 4);
  P1SEL |= (1 << 4);
  P2SEL |= (1 << 5);
  T3CTL = 0x82;
  T3CCTL1 = 0x24;
  T3CC0 = 100;
  T3CC1 = 50;
  T3CTL |= (1 << 4);
}

/***************************************************************************************************
 * @fn      BspRubyMotorInit
 *
 * @brief   
 *
 * @param   None
 *          
 *          
 *                    
 *
 * @return  None
 ***************************************************************************************************/
uint8 BspRubyMotorInitDelegate(uint8 task_id, uint16 event)
{
  if ( BspMotorDelegateTaskID == BSP_SC_INT_NO_TASK )
  {
    BspMotorDelegateTaskID = task_id;
    BspMotorDelegateEvent = event;
    
    return ( true );
  }
  else
    return ( false );
}/**/
/***************************************************************************************************
 * @fn      BspRubyMotorOpen
 *
 * @brief   
 *
 * @param   None
 *          
 *          
 *                    
 *
 * @return  None
 ***************************************************************************************************/
void BspRubyMotorOpen(uint8 pwm)
{
  P1DIR |= (1 << 4);
  P1SEL |= (1 << 4);
  P2SEL |= (1 << 5);
  T3CTL = 0x82;
  T3CCTL1 = 0x24;
  T3CC0 = 100;
  T3CC1 = pwm;
  T3CTL |= (1 << 4);}

/***************************************************************************************************
 * @fn      BspRubyMotorClose
 *
 * @brief   
 *
 * @param   None
 *          
 *          
 *                    
 *
 * @return  None
 ***************************************************************************************************/
void BspRubyMotorClose(void)
{
  P1DIR &= ~(1 << 4);
  P1SEL &= ~(1 << 4);
  P1INP |= 0x01;
  //osal_pwrmgr_task_state( BspMotorDelegateTaskID, PWRMGR_CONSERVE );
}


void BspRubyMotorTimer(void)
{
  BspRubyMotorOpen(pwm_change_value);
  
  osal_start_timerEx( BspMotorDelegateTaskID, BspMotorDelegateEvent, 50 );
}
/***************************************************************************************************
 * @fn      BspRubyMotorChangePwm
 *
 * @brief   
 *
 * @param   None
 *          
 *          
 *                    
 *
 * @return  None
 ***************************************************************************************************/
void BspRubyMotorChangePwm( uint8 pwm )
{
  //T3CTL &= ~(1 << 4);
  //T3CC1 = pwm;
  P1DIR |= (1 << 4);
  P1SEL |= (1 << 4);
  P2SEL |= (1 << 5);
  T3CTL = 0x82;
  T3CCTL1 = 0x24;
  T3CC0 = 100;
  T3CC1 = pwm;
  T3CTL |= (1 << 4);
}


/***************************************************************************************************
***************************************************************************************************/