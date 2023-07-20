//includes libary that they made 
#include "rcc_stdlib.h"
using namespace std;

// main entry point to the program 
// standard code 

// function declaeration 
void printing(int val, int n){
    int i = 0; 
    while(i < n){
        cout << "val: " << val << "\n";
        i++;
    }
}


int main(void){

    stdio_init_all();

    if(!cyw43_arch_init()) {cout << "CYW43 init failed!" << "\n";}
    cyw43_arch_gpio_put(0, true);

    // code stuff to run once // 

    int x_loc = 0 ;
    int y_loc = 20;
    // set code to run for ever // 

    while(true){
        cout << "Print N times: " << x_loc << " | ";
        printing(x_loc,x_loc);
        x_loc = x_loc + 1;
        sleep_ms(500);
    }
}