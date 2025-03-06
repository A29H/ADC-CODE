#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

int main(void) {
	Motor_Control();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    int forward = 0;
    int backward = 0;

    while(1){
    	if (GPIO_PinRead(button_forward_GPIO, button_forward_GPIO_PIN) == 1){
    		forward = 0;
    	}
    	else{
    		forward = 1;
    	}
    	if (GPIO_PinRead(button_backward_GPIO, button_backward_GPIO_PIN) == 1){
    		backward = 0;
    	}
    	else{
    		backward = 1;
    	}

    	while(forward == 1 && backward == 0){
    		GPIO_PinWrite(forward_GPIO,forward_PIN,1);
    		GPIO_PinWrite(backward_GPIO,backward_PIN,0);
    	}

    	while(forward == 0 && backward == 1){
        	GPIO_PinWrite(forward_GPIO,forward_PIN,0);
        	GPIO_PinWrite(backward_GPIO,backward_PIN,1);
    	}

    	while(forward == 0 && backward == 0){
        	GPIO_PinWrite(forward_GPIO,forward_PIN,0);
        	GPIO_PinWrite(backward_GPIO,backward_PIN,0);
    	}

    	while(forward == 1 && backward == 1){
        	GPIO_PinWrite(forward_GPIO,forward_PIN,0);
        	GPIO_PinWrite(backward_GPIO,backward_PIN,0);
    	}
    }
    return 0 ;
}
