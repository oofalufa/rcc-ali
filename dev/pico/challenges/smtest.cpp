#include "rcc_stdlib.h"
using namespace std;

int main(void){

    stdio_init_all();
    rcc_init_pushbutton();
    rcc_init_potentiometer();

    if(!cyw43_arch_init()) {cout << "CYW43 init failed!" << "\n";}
    cyw43_arch_gpio_put(0, true);

    // make a state variable
    int state = 0;
    int val;
    uint32_t enter_time = time_us_32();


    while(true){
    //state 0
        if(state == 0){
            val = adc_read();
            // check if button pressed
            if(val < 2000){
            state = 1;
            } 
            if (val >= 2000 && val <= 3000){
                state = 2;
                enter_time = time_us_32();
            } 
            if (val > 3000){
                state = 3;
            }
        }
        if(state == 1){
            cout << "forwards\n";
            state = 0;
        }
        if(state == 2){
            cout << "stoped\n";
            if((time_us_32() - enter_time) > 1000000){
                state = 0;
            }
        }
        if(state == 3){
            cout << "backwards\n";
            state = 0;
        }
    }   
}