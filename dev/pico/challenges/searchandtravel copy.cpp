#include "rcc_stdlib.h"
using namespace std;

#define WHEEL_RADIUS 0.04 //meters
#define COUNTS_PER_ROTATION 40 
#define IMU_FREQ 500 //Hz



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



float hertz_to_s(int hertz) {
    /*
    converts sampling frequency (hertz) to seconds
    returns as a float
    */
   return 1/(float)hertz;
}

int64_t hertz_to_us(int hertz){
    /*
    converts sampling frequency (hertz) to microseconds
    returns as integer
    */
   return 1e6/hertz;
}



int main(void){

    int servocount = 0;
    int bestservo = 0;
    int testval = 10000;
    int bestval = 10000;
    float DegreeOfObject = 0;
    int bool_move = 0;
    stdio_init_all();
    rcc_init_potentiometer();
    sleep_ms(1000);
    Servo s3;
    VL53L0X lidar;
    rcc_init_lidar(&lidar);


    stdio_init_all();
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1); //turns on led

    rcc_init_i2c(); //setup i2c
    rcc_init_pushbutton(); //setup button

    Motor motors; //struct setup
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); //setup 
    MotorsOn(&motors); //enable PWM

    MPU6050 imu; //class setup
    imu.begin(i2c1); //adds to i2c1
    imu.calibrate(); //hold robot still
    sleep_ms(200); //wait a bit

    float angle_pos = 0.0; //angular position of robot
    float angvel_z; //imu returns a float
    float dt_s = hertz_to_s(IMU_FREQ); //seconds
    int dt_us = hertz_to_us(IMU_FREQ); //microseconds

    //track time since pico started
    int64_t current_time = time_us_64(); 
    int64_t previous_time = time_us_64(); 


    //use bool to stop until RESET
    bool stop = false; 


    ServoInit(&s3, 18, false, 50); 
    ServoOn(&s3);
    ServoPosition(&s3, 0);
    sleep_ms(2000);
    // compares servo postions on lidar to find shotest distance 
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
        cout<< dist << testval << bestval << '\n';
    }

    DegreeOfObject = bestservo * 1.8 -90;
    float deg_spin = DegreeOfObject;
    bool_move = 1; 

    while(bool_move = 1) 
    {
        cout<<deg_spin << deg_spin << DegreeOfObject << '\n';
        MotorPower(&motors, 50, 0); 
    
        //update current time
        current_time = time_us_64();
        if((current_time - previous_time)>= dt_us){
            imu.update_pico();
            angvel_z = imu.getAngVelZ();
            angle_pos += angvel_z*dt_s;
            previous_time = current_time;
        }
        //if difference between current time and previous time is long enough
            //get IMU data
            //sum area of rectangles aka integrate (units are seconds)
            //make previous time the same as current time
        //check if we spun long enough
        if(angle_pos >= deg_spin){
            stop = true;
        }

        if(stop){
            MotorPower(&motors, 0,0); //stop until RESET
        }
}
}


