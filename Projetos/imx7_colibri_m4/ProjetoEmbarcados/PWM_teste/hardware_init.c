/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "gpio_pins.h"
#include "board.h"

void hardware_init(void)
{
    /* Board specific RDC settings */
    BOARD_RdcInit();
    /* Board specific clock settings */
    BOARD_ClockInit();
    /* initialize debug uart */
    dbg_uart_init();

    /* In this demo, we need to grasp board GPT exclusively */
    RDC_SetPdapAccess(RDC, BOARD_GPTA_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);
    RDC_SetPdapAccess(RDC, BOARD_GPTB_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* In this demo, we need to access RDC SEMAPHORE1 on this board */
    RDC_SetPdapAccess(RDC, rdcPdapSemaphore1, 0xFF, false, false);

    /* In this demo, we need to share board GPIO, we can set sreq argument to true
     * when the peer core could also access GPIO with RDC_SEMAPHORE, or the peer
     * core doesn't access the GPIO at all */
    RDC_SetPdapAccess(RDC, BOARD_GPIO_ENCODER_RDC_PDAP, 0xFF, false/*true*/, false);

    /* Enable PLL PFD0 for GPTA */
    CCM_ControlGate(CCM, ccmPllGateSys, ccmClockNeededRunWait);
    CCM_ControlGate(CCM, ccmPllGatePfd0, ccmClockNeededRunWait);
	
	
	///* Select GPTA clock derived from PLL PFD0 clock divide 4 (pre=2 post=2) */
    //CCM_UpdateRoot(CCM, BOARD_GPTA_CCM_ROOT, ccmRootmuxGptSysPllPfd0, 1, 1);

	/* Select GPTA clock derived from PLL PFD0 */
    CCM_UpdateRoot(CCM, BOARD_GPTA_CCM_ROOT, ccmRootmuxGptSysPllPfd0, 0, 0);

    /* Select GPTB clock derived from OSC 24M */
    CCM_UpdateRoot(CCM, BOARD_GPTB_CCM_ROOT, ccmRootmuxGptOsc24m, 0, 0);
 
    
    /* Enable clock used by GPTA */
    CCM_EnableRoot(CCM, BOARD_GPTA_CCM_ROOT);
    CCM_ControlGate(CCM, BOARD_GPTA_CCM_CCGR, ccmClockNeededRunWait);
    /* Enable clock used by GPTB */
    CCM_EnableRoot(CCM, BOARD_GPTB_CCM_ROOT);
    CCM_ControlGate(CCM, BOARD_GPTB_CCM_CCGR, ccmClockNeededRunWait);


    /* Enable RDC SEMAPHORE GATE needed in this demo */
    CCM_ControlGate(CCM, ccmCcgrGateSema1, ccmClockNeededRunWait);

    /* Enable gpio clock gate, led and key share same CCGR on this board */
    CCM_ControlGate(CCM, BOARD_GPIO_ENCODER_CCM_CCGR, ccmClockNeededRunWait);

    /* Configure gpio pin IOMUX */
    configure_gpio_pin(BOARD_GPIO_ENCODER_CONFIG);
    
    //----------------------------------------- PWM -----------------------------------------------------
    
    //RDC_SetPdapAccess(RDC, BOARD_PWM1_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Enable PWM1 clock */
    //CCM_ControlGate(CCM, BOARD_PWM1_CCM_CCGR, ccmClockNeededRunWait);
    
    /* Configure PWM1 pin IOMUX */
    //configure_pwm_pins(BOARD_PWM1_BASEADDR);
    
    //-----------------------------------------------------------------------------------------------------------------
    
    RDC_SetPdapAccess(RDC, BOARD_PWM2_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Enable PWM2 clock */
    CCM_ControlGate(CCM, BOARD_PWM2_CCM_CCGR, ccmClockNeededRunWait);
    
    /* Configure PWM2 pin IOMUX */
    //configure_pwm_pins(BOARD_PWM2_BASEADDR);
    
    //-----------------------------------------------------------------------------------------------------------------
    
    //RDC_SetPdapAccess(RDC, BOARD_PWM3_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Enable PWM3 clock */
    //CCM_ControlGate(CCM, BOARD_PWM3_CCM_CCGR, ccmClockNeededRunWait);
    
    /* Configure PWM3 pin IOMUX */
    //configure_pwm_pins(BOARD_PWM3_BASEADDR);
    
    //-----------------------------------------------------------------------------------------------------------------
    
    //RDC_SetPdapAccess(RDC, BOARD_PWM4_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Enable PWM4 clock */
    //CCM_ControlGate(CCM, BOARD_PWM4_CCM_CCGR, ccmClockNeededRunWait);
    
    /* Configure PWM4 pin IOMUX */
    //configure_pwm_pins(BOARD_PWM4_BASEADDR);
    
    
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
