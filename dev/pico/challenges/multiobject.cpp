#include "rcc_stdlib.h"
using namespace std;

int main()
{   
    // start up
    stdio_init_all();
    rcc_init_pushbutton();
    rcc_init_potentiometer();
    cyw43_arch_init();
    rcc_init_i2c(); 
    VL53L0X lidar;
    rcc_init_lidar(&lidar);
    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);
    MotorPower(&motors, 0, 0);
    cyw43_arch_gpio_put(0, true);

    while (servocount !=101) {
        ServoPosition(&s3, servocount);
        uint16_t dist = getFastReading(&lidar);
        testval = dist;
        if(testval < bestval){
            bestval = testval;
            bestservo = servocount;
        }
        sleep_ms(100); 
        servocount++;
        cout << "dist:" << dist << "testval:" << testval << "bestval:" << bestval << '\n';
    }






}