
    #include "rcc_stdlib.h"
    using namespace std;
    
    //setup instance of config struct
    PID_control_config_t config;
    
    int main(){
        stdio_init_all();
        cyw43_arch_init();
        sleep_ms(1500);
    
        //init i2c first
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
    
        //set values for config
        config.kp = .57; 
        config.ki = .05;
        config.kd = 0;
        config.ts = 0.01; // 1ms
        config.sigma = 0.1;
        config.lowerLimit = -20;
        config.upperLimit = 20;
        config.antiWindupEnabled = true;
    

        float angle = 0;
        //create controller class based on config
        PID_control controller(config);
    
        //motor power variables setup
        int base_power = 80;
        int output; 
    
        //timing variables setup
        uint32_t current_time, previous_time;
        current_time = time_us_32();
    
        //pico led on when done setup
        cyw43_arch_gpio_put(0,1); 

        while(true){
            //update current time
            current_time = time_us_32();



            //if config's timestep has passed
            if((current_time - previous_time) >= config.ts*1e6){
    
                //get data from sensors
                imu.update_pico();
                //calculate controller output:
                    //first input is desired value
                    //second input is actual value

                angle += imu.getAngVelZ() * config.ts;

                output = controller.pid(0.0, angle);
    
                //set motor power based on controller output
                MotorPower(&motors, (base_power - output), (base_power + output));

                //reset previous time
                previous_time = current_time;
            }
        }
    }
