
#include "rcc_stdlib.h"
using namespace std;

// setup instance of config struct
PID_control_config_t config;
// define global constants
#define WHEEL_RADIUS 0.04 // meters
#define COUNTS_PER_ROTATION 40
#define IMU_FREQ 500 // Hz

int distanceToCounts(float distance)
{
    /*
    converts distance in meters [m] to encoder counts
    takes in distance as a float
    returns integer
    */

    // converts distance to number of rotations
    float rotations = distance / (2 * 3.14 * WHEEL_RADIUS);
    // converts number of rotations to number of counts
    float counts_f = rotations * COUNTS_PER_ROTATION;
    // round to whole counts
    int counts = (int)counts_f;
    // return counts as an integer
    return counts;
}

float hertz_to_s(int hertz)
{
    /*
    converts sampling frequency (hertz) to seconds
    returns as a float
    */
    return 1 / (float)hertz;
}

int64_t hertz_to_us(int hertz)
{
    /*
    converts sampling frequency (hertz) to microseconds
    returns as integer
    */
    return 1e6 / hertz;
}

int main()
{
    stdio_init_all();
    cyw43_arch_init();
    sleep_ms(1500);

    // init i2c first
    rcc_init_i2c();
    MPU6050 imu;
    imu.begin(i2c1);
    imu.calibrate();
    Left_Odom left;
    Right_Odom right;
    printf("AFTER ODOM");

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 20000);
    MotorsOn(&motors);

    float angle_pos = 0.0;             // angular position of robot
    float angvel_z;                    // imu returns a float
    float dt_s = hertz_to_s(IMU_FREQ); // seconds
    int dt_us = hertz_to_us(IMU_FREQ); // microseconds

    // track time since pico started
    int64_t current_time = time_us_64();
    int64_t previous_time = time_us_64();

    float deg_spin = -70.0;

    bool stop = false;
    // set values for config
    config.kp = .57;
    config.ki = 0.05;
    config.kd = 0;
    config.ts = 0.01; // 1ms
    config.sigma = 0.1;
    config.lowerLimit = -20;
    config.upperLimit = 20;
    config.antiWindupEnabled = true;

    float angle = 0;
    // create controller class based on config
    PID_control controller(config);

    // motor power variables setup
    int base_power = 80;
    int output;

    // timing variables setup
    current_time = time_us_32();

    int counter = 0;
    int turn_count = 39;

    // pico led on when done setup
    cyw43_arch_gpio_put(0, 1);

    while (counter != 3)
    {
        while ((left.getCount() < 160) && (right.getCount() < 160))
        {
            // update current time
            current_time = time_us_32();

            // if config's timestep has passed
            if ((current_time - previous_time) >= config.ts * 1e6)
            {

                // get data from sensors
                imu.update_pico();
                // calculate controller output:
                // first input is desired value
                // second input is actual value
                output = controller.pid(0.0, imu.getAngVelZ());

                // set motor power based on controller output
                MotorPower(&motors, (base_power - output), (base_power + output));

                // reset previous time
                previous_time = current_time;
            }
        }
        MotorPower(&motors, 0, 0);

        sleep_ms(300);
        imu.calibrate();
        left.setZero();
        right.setZero();
        sleep_ms(300);

        while (angle_pos >= deg_spin)
        {
            MotorPower(&motors, 80, 0); // spinnnnnn~~

            // update current time
            current_time = time_us_64();

            // if difference between current time and previous time is long enough
            if ((current_time - previous_time) >= dt_us)
            {
                // get IMU data
                imu.update_pico();
                angvel_z = imu.getAngVelZ(); // deg per sec
                // sum area of rectangles aka integrate (units are seconds)
                angle_pos += angvel_z * dt_s;
                // make previous time the same as current time
                previous_time = current_time;
            }

            // cout << "dt_s" << dt_s << " dt_us"<< dt_us<< " pos" <<angle_pos << '\n';

            // check if we spun long enough
        }
        MotorPower(&motors, 0, 0);

        sleep_ms(300);

        imu.calibrate();
        left.setZero();
        right.setZero();
        angle_pos = 0.0;
        counter++;
    }
}
