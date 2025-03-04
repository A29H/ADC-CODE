# ADC-CODE
ADC Code for EE318 Project 2025



#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
# include "MCXN947_cm33_core0.h"
#include "fsl_spc.h"
#include "fsl_clock.h"
//#define TEST_WITHOUT_MOTOR

void Motor_Spin(void)
{

CLOCK_AttachClk(kFRO_HF_to_ADC0);

CLOCK_SetClkDiv(kCLOCK_DivAdc0Clk, 1U);

CLOCK_EnableClock(kCLOCK_Adc0);

SPC_EnableActiveModeAnalogModules(SPC0, kSPC_controlVref);

ADC0->CFG  |= 0xa0;

ADC0->TCTRL[0] = (0b001 << ADC_TCTRL_TCMD_SHIFT);

ADC0->CTRL |= 0x01;

}

void delay_ms(uint32_t ms)
{
    SDK_DelayAtLeastUs(ms * 1000, CLOCK_GetCoreSysClkFreq());
}


float MotorReadVoltage()
{
    uint32_t result;

//#ifdef TEST_WITHOUT_MOTOR
       // return 5.0f;  // Simulated 5V for testing without motor
   // #else

    // Start ADC conversion
    ADC0->SWTRIG = 0x01;

    // Wait for conversion to complete
    while ((ADC0->FCTRL[0] & 0x1F) == 0);

    // Read ADC value
    result = ADC0->RESFIFO[0] & 0xFFFFu;

    // Convert ADC value back to motor voltage
    float voltage = (result / 1023.0) * 7.2;

    return voltage;

//#endif

}



int main()
{

    Motor_Spin();


    while (1)
    {
        float motorVoltage = MotorReadVoltage();
        printf("Motor Voltage: %.2fV\n", motorVoltage);

        SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    }
}
