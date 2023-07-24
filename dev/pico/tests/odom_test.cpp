/*
#include "rcc_stdlib.h"
using namespace std;

int main()
{

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);

    stdio_init_all();
    sleep_ms(1000);
    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }
    
    cyw43_arch_gpio_put(0, 1); //turns on led

    cout << "Starting odom test!" << "\n";
    Left_Odom left;
// Find the distance traveled at time
// Find the distance    Right_Odom right;
    
    for(Left.getcount<200, Right.getCount<200)
    {
        sleep_ms(100);
        cout << left.getCount() << " | " << right.getCount() << "\n";
		MotorPower(&motors, 66, 70);
 }
}
*/
