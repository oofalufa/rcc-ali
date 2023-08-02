#include "rcc_stdlib.h"
using namespace std;

typedef enum{
    //Use commas to separate words
    ON,
    OF,

    //put rest here...
} state_t;

int main(){
    stdio_init_all();
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1); //turns on led
    time_us_32(); 
    uint32_t previous_time;
    uint32_t current_time;
    printf("hello");

    //rename state_name to something more informative
    state_t state_name = ON;

    while(true){

        current_time = time_us_32();

        switch(state_name){
            case ON:
            cyw43_arch_gpio_put(0, 1);    //do something in each state
                //check transition conditions
                if(current_time - current_time >= 400){
                  state_name = OF;
                  previous_time = time_us_32();
                  printf("on");
                }
                break;
            case OF://PUT REST HERE
            cyw43_arch_gpio_put(0, 0); //turns on led
            if(current_time - previous_time >= 400){
                state_name = ON;
                previous_time = time_us_32();
                printf("of");
                }
                break; 
        }
    }
}