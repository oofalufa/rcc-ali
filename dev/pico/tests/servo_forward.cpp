#include "rcc_stdlib.h"
using namespace std;

int main(void)
{
    stdio_init_all();
    sleep_ms(1000);

    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }
    
    cyw43_arch_gpio_put(0, true);

    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);
    
    while(true)
    {   
        ServoPosition(&s3, 50);
        sleep_ms(100);
        ServoPosition(&s3, 0);
        sleep_ms(1000);

    }
}