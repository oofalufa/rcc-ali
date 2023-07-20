#include "rcc_stdlib.h"
using namespace std;

#define WHEEL_RADIUS 0.04 //meters
#define COUNTS_PER_ROTATION 40 
#define IMU_FREQ 500 //Hz
float distanceM;

int distanceToCounts(float distance){
    /*
    converts distance in meters [m] to encoder counts 
    takes in distance as a float
    returns integer
    */
   float rotations = distance/(2*3.14*WHEEL_RADIUS);
   float counts_f = rotations*COUNTS_PER_ROTATION;
   int counts = (int)counts_f;
   return counts;

    //converts distance to number of rotations
    //converts number of rotations to number of counts
    //round to whole counts
    //return counts as an integer
}


float countsTodistance(int counts){
    //takes in counts //

    distanceM = counts * .0062
    //converts distance to number of rotations
    //converts number of rotations to number of counts
    //round to whole counts
    //return counts as an integer
}


int main()
{   
      Left_Odom left;
    Right_Odom right;

    stdio_init_all();
    sleep_ms(100);
    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }
    
     Motor motors;
    MotorInit(&motors, RCC_ENB, RCC_ENA, 1000);
    MotorsOn(&motors);

    cyw43_arch_gpio_put(0, 1); //turns on led
    // This example will use i2c1 on the default SDA and SCL pins (4, 5 on a Pico)
    rcc_init_i2c();

    VL53L0X lidar;
    rcc_init_lidar(&lidar);

    while(true)
    {
        uint16_t dist = getFastReading(&lidar);
        printf("Distance (mm): %hu\n", dist);
        cout << lidar.timeoutOccurred() << '\n';
        sleep_ms(100);

        if(dist > 300){
            MotorPower(&motors, 67, 70);
        }
    }
}