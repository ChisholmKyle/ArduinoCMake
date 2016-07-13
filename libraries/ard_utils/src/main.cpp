#include <Arduino.h>
#include <string.h>
#include <stdbool.h>

#include "ard_timing.h"
#include "ard_mpu6050.h"
#include "ard_pid.h"
#include "ard_crc.h"
#include "ard_serial.h"

// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }


// ********** //
// parameters //
// ********** //

#define ARD_PARAM_TIMESTEP 0.1

#define ARD_PID_GAIN_KP 1.0
#define ARD_PID_GAIN_KI 0.0
#define ARD_PID_GAIN_KD 0.1
#define ARD_PID_GAIN_TF 0.01

#define ARD_PID_LIMITS_UMAX 1.e6
#define ARD_PID_LIMITS_UMIN -1.e6


#define ARD_IMU_SAMPLE_RATE EARD_MPU6050_SAMPLERATE_1000HZ
#define ARD_IMU_LPF_CUTOFF EARD_MPU6050_LPF_CUTOFF_260HZ
#define ARD_IMU_GYRO_RANGE EARD_MPU6050_GYRORANGE_250
#define ARD_IMU_ACC_RANGE EARD_MPU6050_ACCRANGE_4G

#define ARD_SERIAL_BAUD_RATE 115200
#define ARD_SERIAL_SIZE 14
#define ARD_SERIAL_DELIMITER '|'

#define ARD_TOGGLE_PIN 13

// ******* //
// globals //
// ******* //

// mpu
ArdMpu6050Config mpu_config;

// timing
ArdTiming timing;

// serial stream
ArdSerialPacket serial_data;

// pid
ArdPidState pidState;
ArdPidParam pidParam;

// spline
#define ARD_SPLINE_BREAKS 20
const static double roast_spline_breaks[ARD_SPLINE_BREAKS] = {0.0000000e+00, 5.2631579e-02, 1.0526316e-01, 1.5789474e-01, 2.1052632e-01, 2.6315789e-01, 3.1578947e-01, 3.6842105e-01, 4.2105263e-01, 4.7368421e-01, 5.2631579e-01, 5.7894737e-01, 6.3157895e-01, 6.8421053e-01, 7.3684211e-01, 7.8947368e-01, 8.4210526e-01, 8.9473684e-01, 9.4736842e-01, 1.0000000e+00};
const static double roast_spline_coefs[ARD_SPLINE_BREAKS * 4] = {5.2108479e+02, 0.0000000e+00, -1.0297011e+01, 9.5595026e-01, -3.7397668e+02, 8.2276546e+01, -5.9666666e+00, 4.8997326e-01, -1.2244561e+02, 2.3227597e+01, -4.1381703e-01, 3.4932754e-01, -9.6892593e+00, 3.8940802e+00, 1.0136397e+00, 3.7403826e-01, -2.3883498e+01, 2.3641971e+00, 1.3430227e+00, 4.3676200e-01, -2.6524506e+00, -1.4068814e+00, 1.3934077e+00, 5.1051436e-01, 5.9410915e+00, -1.8256894e+00, 1.2232724e+00, 5.7956772e-01, 2.8198265e+00, -8.8762233e-01, 1.0804665e+00, 6.3975934e-01, -3.8491739e+00, -4.4238656e-01, 1.0104661e+00, 6.9457833e-01, -9.6692473e-01, -1.0501509e+00, 9.3191146e-01, 7.4597412e-01, 2.3295931e+00, -1.2028232e+00, 8.1333388e-01, 7.9197211e-01, 1.0500035e+00, -8.3499269e-01, 7.0608041e-01, 8.3178688e-01, 9.8544614e-01, -6.6920267e-01, 6.2691223e-01, 8.6678909e-01, 4.3551102e-01, -5.1360591e-01, 5.6465915e-01, 8.9807440e-01, -4.9771266e+00, -4.4484101e-01, 5.1421458e-01, 9.2643406e-01, 1.6811048e+00, -1.2307031e+00, 4.2602804e-01, 9.5154011e-01, 2.5421453e+00, -9.6526550e-01, 3.1045075e-01, 9.7079858e-01, -3.7393888e+00, -5.6387415e-01, 2.2996972e-01, 9.8483486e-01, 7.3105917e+00, -1.1543040e+00, 1.3953929e-01, 9.9483137e-01};

// pins
bool pintoggle;

int main(void)
{
    init();
    initVariant();

    // ********** //
    // initialize //
    // ********** //

    // timing at period of 1e6 microseconds (1s, 1Hz)
    ard_timing_reset(&timing, ARD_PARAM_TIMESTEP);

    // serial stream
    ard_serial_alloc(&serial_data, ARD_SERIAL_SIZE, ARD_SERIAL_DELIMITER);
    ard_serial_begin(ARD_SERIAL_BAUD_RATE);

    // pid
    pidParam.kp = ARD_PID_GAIN_KP;
    pidParam.ki = ARD_PID_GAIN_KI;
    pidParam.kd = ARD_PID_GAIN_KD;
    pidParam.tf = ARD_PID_GAIN_TF;
    pidParam.umin = ARD_PID_LIMITS_UMIN;
    pidParam.umax = ARD_PID_LIMITS_UMAX;
    ard_pid_reset(&pidState);

    // IMU
    mpu_config.sample_rate = ARD_IMU_SAMPLE_RATE;
    mpu_config.lpf_cutoff = ARD_IMU_LPF_CUTOFF;
    mpu_config.gyro_range = ARD_IMU_GYRO_RANGE;
    mpu_config.acc_range = ARD_IMU_ACC_RANGE;
    ard_mpu6050_configure(mpu_config);

    // pins
    pintoggle = false;
    pinMode(ARD_TOGGLE_PIN, OUTPUT);
    digitalWrite(ARD_TOGGLE_PIN, LOW);    // Set the LED off

    // *************** //
    //   run forever   //
    // *************** //

    for (;;) {
        loop();
    }

    ard_mpu6050_stop();
    return 0;
}

// ******** //
//   loop   //
// ******** //

void loop() {

    if (ard_timing_step(&timing)) {
        // toggle state
        // if (pintoggle) {
        //     serial_data.data[5] = 'n';
        //     serial_data.data[6] = '\0';
        //     digitalWrite(ARD_TOGGLE_PIN, HIGH);   // Set the LED on
        // } else {
        //     serial_data.data[5] = 'f';
        //     serial_data.data[6] = 'f';
        //     digitalWrite(ARD_TOGGLE_PIN, LOW);    // Set the LED off
        // }
        ard_mpu6050_read((uint16_t *) serial_data.data);
        ard_serial_write_packet(&serial_data);
        // toggle
        pintoggle = !pintoggle;
    }

}

