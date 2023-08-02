#include "rcc_stdlib.h"
using namespace std;

int main(void){

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

    float desired = 200;
    float actual;
    float error;
    uint16_t lidar_reading; 
    float kp = 1;
    float power;


    while(true){
        lidar_reading = getFastReading(&lidar);

        actual = static_cast<float>(lidar_reading);

        error= desired - actual;

        power = kp*error;

        power = max(min(power, 100.f), -100.f);

        int power_int = static_cast<int>(power*-1);

        MotorPower(&motors, .95*power_int, power_int);

        cout << "des: " << desired << "act:" << actual << "err:" << error << "power:" << power_int << '\n';


    }
}