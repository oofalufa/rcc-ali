#include "rcc_stdlib.h"
using namespace std;

int main(void){

      if(!cyw43_arch_init()) {cout << "CYW43 init failed!" << "\n";}
    cyw43_arch_gpio_put(0, true);


    while (true)
    {
        cyw43_arch_gpio_put(0, true);
        sleep_ms(600);
        cyw43_arch_gpio_put(0, false);
        sleep_ms(600);
    }
    



    
}