
#ifndef ARD_MPU6050_H
#define ARD_MPU6050_H

#include "Arduino.h"

// bits in hex
#define ARD_MPU6050_BIT_0  0x01
#define ARD_MPU6050_BIT_1  0x02
#define ARD_MPU6050_BIT_2  0x04
#define ARD_MPU6050_BIT_3  0x08
#define ARD_MPU6050_BIT_4  0x10
#define ARD_MPU6050_BIT_5  0x20
#define ARD_MPU6050_BIT_6  0x40
#define ARD_MPU6050_BIT_7  0x80

// IMU definitions.
#define ARD_MPU6050_ADDRESS 0x68

// Configuration Registers //
// ----------------------- //

// sample rate divider SMPLRT_DIV
// DLPF enabled,  rate (Hz) = 1000/(value + 1)
#define ARD_MPU6050_SAMPLERATE_REGISTER 0x19
#define ARD_MPU6050_SAMPLERATE_VALUE_1000HZ 0x00
#define ARD_MPU6050_SAMPLERATE_VALUE_500HZ  0x01
#define ARD_MPU6050_SAMPLERATE_VALUE_250HZ  0x03
#define ARD_MPU6050_SAMPLERATE_VALUE_200HZ  0x04
#define ARD_MPU6050_SAMPLERATE_VALUE_125HZ  0x07
#define ARD_MPU6050_SAMPLERATE_VALUE_100HZ  0x09
#define ARD_MPU6050_SAMPLERATE_VALUE_50HZ   0x13
#define ARD_MPU6050_SAMPLERATE_VALUE_40HZ   0x18
#define ARD_MPU6050_SAMPLERATE_VALUE_25HZ   0x27
// DLPF disabled, rate (Hz) = 8000/(value + 1)
#define ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_8000HZ 0x00
#define ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_4000HZ 0x01
#define ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_2000HZ 0x03
#define ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_1600HZ 0x04
#define ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_1000HZ 0x07
#define ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_800HZ  0x09
#define ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_400HZ  0x13
#define ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_320HZ  0x18
#define ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_200HZ  0x27

// low pass filter bandwidth DLPF_CFG
#define ARD_MPU6050_LOWPASSFILTER_REGISTER 0x1A
#define ARD_MPU6050_LOWPASSFILTER_VALUE_260Hz 0x00
#define ARD_MPU6050_LOWPASSFILTER_VALUE_184Hz 0x01
#define ARD_MPU6050_LOWPASSFILTER_VALUE_94Hz  0x02
#define ARD_MPU6050_LOWPASSFILTER_VALUE_44Hz  0x03
#define ARD_MPU6050_LOWPASSFILTER_VALUE_21Hz  0x04
#define ARD_MPU6050_LOWPASSFILTER_VALUE_10Hz  0x05
#define ARD_MPU6050_LOWPASSFILTER_VALUE_5Hz   0x06

// gyro scale FS_SEL
#define ARD_MPU6050_GYROCONFIG_REGISTER 0x1B
#define ARD_MPU6050_GYROCONFIG_VALUE_RANGE250  0x00
#define ARD_MPU6050_GYROCONFIG_VALUE_RANGE500  ARD_MPU6050_BIT_3
#define ARD_MPU6050_GYROCONFIG_VALUE_RANGE1000 ARD_MPU6050_BIT_4
#define ARD_MPU6050_GYROCONFIG_VALUE_RANGE2000 (ARD_MPU6050_BIT_4 | ARD_MPU6050_BIT_3)

// accelerometer scale AFS_SEL
#define ARD_MPU6050_ACCELCONFIG_REGISTER 0x1C
#define ARD_MPU6050_ACCELCONFIG_VALUE_RANGE2G  0x00
#define ARD_MPU6050_ACCELCONFIG_VALUE_RANGE4G  ARD_MPU6050_BIT_3
#define ARD_MPU6050_ACCELCONFIG_VALUE_RANGE8G  ARD_MPU6050_BIT_4
#define ARD_MPU6050_ACCELCONFIG_VALUE_RANGE16G (ARD_MPU6050_BIT_4 | ARD_MPU6050_BIT_3)

// signal reset SIGNAL_PATH_RESET
#define ARD_MPU6050_SIGRESET_REGISTER 0x68
#define ARD_MPU6050_SIGRESET_VALUE_TEMP  ARD_MPU6050_BIT_0
#define ARD_MPU6050_SIGRESET_VALUE_ACCEL ARD_MPU6050_BIT_1
#define ARD_MPU6050_SIGRESET_VALUE_GYRO  ARD_MPU6050_BIT_2
#define ARD_MPU6050_SIGRESET_VALUE_ALL   (ARD_MPU6050_SIGRESET_VALUE_TEMP  | \
                                          ARD_MPU6050_SIGRESET_VALUE_ACCEL | \
                                          ARD_MPU6050_SIGRESET_VALUE_GYRO)

// power management PWR_MGMT_1
#define ARD_MPU6050_PWR1_REGISTER 0x6B
// clock source CLKSEL
#define ARD_MPU6050_PWR1_VALUE_CLK_INT8MHZ  0x00
#define ARD_MPU6050_PWR1_VALUE_CLK_PLLGYROX 0x01
#define ARD_MPU6050_PWR1_VALUE_CLK_PLLGYROY 0x02
#define ARD_MPU6050_PWR1_VALUE_CLK_PLLGYROZ 0x03
#define ARD_MPU6050_PWR1_VALUE_CLK_EXT32KHZ 0x04
#define ARD_MPU6050_PWR1_VALUE_CLK_EXT19MHZ 0x05
#define ARD_MPU6050_PWR1_VALUE_CLK_STOP     0x07
// reset DEVICE_RESET
#define ARD_MPU6050_PWR1_VALUE_DEVICE_RESET ARD_MPU6050_BIT_7
// sleep SLEEP
#define ARD_MPU6050_PWR1_VALUE_CLK_SLEEP ARD_MPU6050_BIT_6
// enable/disable temperature DIS_TEMP
#define ARD_MPU6050_PWR1_VALUE_DISABLE_TEMP ARD_MPU6050_BIT_3

// Read Registers //
// -------------- //

// read registers
#define ARD_MPU6050_READ_ACC_TEMP_GYR 0x3B
#define ARD_MPU6050_READ_ACCEL 0x3B
#define ARD_MPU6050_READ_TEMP  0x41
#define ARD_MPU6050_READ_GYRO  0x43
#define ARD_MPU6050_READ_EXT   0x49

#ifdef __cplusplus
extern "C" {
#endif

#include "ard_i2c.h"

// Selection enums //
// --------------- //

typedef enum eArdMpu6050SampleRate {
    EARD_MPU6050_SAMPLERATE_1000HZ,
    EARD_MPU6050_SAMPLERATE_500HZ,
    EARD_MPU6050_SAMPLERATE_250HZ,
    EARD_MPU6050_SAMPLERATE_200HZ,
    EARD_MPU6050_SAMPLERATE_125HZ,
    EARD_MPU6050_SAMPLERATE_100HZ,
    EARD_MPU6050_SAMPLERATE_50HZ,
    EARD_MPU6050_SAMPLERATE_40HZ,
    EARD_MPU6050_SAMPLERATE_25HZ,
    EARD_MPU6050_SAMPLERATE_NOFILT_8000HZ,
    EARD_MPU6050_SAMPLERATE_NOFILT_4000HZ,
    EARD_MPU6050_SAMPLERATE_NOFILT_2000HZ,
    EARD_MPU6050_SAMPLERATE_NOFILT_1600HZ,
    EARD_MPU6050_SAMPLERATE_NOFILT_1000HZ,
    EARD_MPU6050_SAMPLERATE_NOFILT_800HZ,
    EARD_MPU6050_SAMPLERATE_NOFILT_400HZ,
    EARD_MPU6050_SAMPLERATE_NOFILT_320HZ,
    EARD_MPU6050_SAMPLERATE_NOFILT_200HZ
} eArdMpu6050SampleRate;

typedef enum eArdMpu6050LpfCutoff {
    EARD_MPU6050_LPF_CUTOFF_260HZ,
    EARD_MPU6050_LPF_CUTOFF_184HZ,
    EARD_MPU6050_LPF_CUTOFF_94HZ,
    EARD_MPU6050_LPF_CUTOFF_44HZ,
    EARD_MPU6050_LPF_CUTOFF_21HZ,
    EARD_MPU6050_LPF_CUTOFF_10HZ,
    EARD_MPU6050_LPF_CUTOFF_5HZ
} eArdMpu6050LpfCutoff;

typedef enum eArdMpu6050GyroRange {
    EARD_MPU6050_GYRORANGE_250,
    EARD_MPU6050_GYRORANGE_500,
    EARD_MPU6050_GYRORANGE_1000,
    EARD_MPU6050_GYRORANGE_2000
} eArdMpu6050GyroRange;

typedef enum eArdMpu6050AccRange {
    EARD_MPU6050_ACCRANGE_2G,
    EARD_MPU6050_ACCRANGE_4G,
    EARD_MPU6050_ACCRANGE_8G,
    EARD_MPU6050_ACCRANGE_16G
} eArdMpu6050AccRange;

// Configuration struct //
// -------------------- //

typedef struct ArdMpu6050Config {
    eArdMpu6050SampleRate sample_rate;
    eArdMpu6050LpfCutoff lpf_cutoff;
    eArdMpu6050GyroRange gyro_range;
    eArdMpu6050AccRange acc_range;
} ArdMpu6050Config;

// selection functions //
// ------------------- //

inline uint8_t ard_mpu6050_configure_select_samplerate(eArdMpu6050SampleRate choice) {
    switch(choice) {
        case EARD_MPU6050_SAMPLERATE_1000HZ:        return ARD_MPU6050_SAMPLERATE_VALUE_1000HZ;
        case EARD_MPU6050_SAMPLERATE_500HZ:         return ARD_MPU6050_SAMPLERATE_VALUE_500HZ;
        case EARD_MPU6050_SAMPLERATE_250HZ:         return ARD_MPU6050_SAMPLERATE_VALUE_250HZ;
        case EARD_MPU6050_SAMPLERATE_200HZ:         return ARD_MPU6050_SAMPLERATE_VALUE_200HZ;
        case EARD_MPU6050_SAMPLERATE_125HZ:         return ARD_MPU6050_SAMPLERATE_VALUE_125HZ;
        case EARD_MPU6050_SAMPLERATE_100HZ:         return ARD_MPU6050_SAMPLERATE_VALUE_100HZ;
        case EARD_MPU6050_SAMPLERATE_50HZ:          return ARD_MPU6050_SAMPLERATE_VALUE_50HZ;
        case EARD_MPU6050_SAMPLERATE_40HZ:          return ARD_MPU6050_SAMPLERATE_VALUE_40HZ;
        case EARD_MPU6050_SAMPLERATE_25HZ:          return ARD_MPU6050_SAMPLERATE_VALUE_25HZ;
        case EARD_MPU6050_SAMPLERATE_NOFILT_8000HZ: return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_8000HZ;
        case EARD_MPU6050_SAMPLERATE_NOFILT_4000HZ: return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_4000HZ;
        case EARD_MPU6050_SAMPLERATE_NOFILT_2000HZ: return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_2000HZ;
        case EARD_MPU6050_SAMPLERATE_NOFILT_1600HZ: return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_1600HZ;
        case EARD_MPU6050_SAMPLERATE_NOFILT_1000HZ: return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_1000HZ;
        case EARD_MPU6050_SAMPLERATE_NOFILT_800HZ:  return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_800HZ;
        case EARD_MPU6050_SAMPLERATE_NOFILT_400HZ:  return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_400HZ;
        case EARD_MPU6050_SAMPLERATE_NOFILT_320HZ:  return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_320HZ;
        case EARD_MPU6050_SAMPLERATE_NOFILT_200HZ:  return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_200HZ;
        default: return ARD_MPU6050_SAMPLERATE_VALUE_NOFILT_8000HZ;
    }
}

inline uint8_t ard_mpu6050_configure_select_lpf_cutoff(eArdMpu6050LpfCutoff choice) {
    switch(choice) {
        case EARD_MPU6050_LPF_CUTOFF_260HZ: return ARD_MPU6050_LOWPASSFILTER_VALUE_260Hz;
        case EARD_MPU6050_LPF_CUTOFF_184HZ: return ARD_MPU6050_LOWPASSFILTER_VALUE_184Hz;
        case EARD_MPU6050_LPF_CUTOFF_94HZ:  return ARD_MPU6050_LOWPASSFILTER_VALUE_94Hz;
        case EARD_MPU6050_LPF_CUTOFF_44HZ:  return ARD_MPU6050_LOWPASSFILTER_VALUE_44Hz;
        case EARD_MPU6050_LPF_CUTOFF_21HZ:  return ARD_MPU6050_LOWPASSFILTER_VALUE_21Hz;
        case EARD_MPU6050_LPF_CUTOFF_10HZ:  return ARD_MPU6050_LOWPASSFILTER_VALUE_10Hz;
        case EARD_MPU6050_LPF_CUTOFF_5HZ:   return ARD_MPU6050_LOWPASSFILTER_VALUE_5Hz;
        default: return ARD_MPU6050_LOWPASSFILTER_VALUE_260Hz;
    }
}

inline uint8_t ard_mpu6050_configure_select_gyrorange(eArdMpu6050GyroRange choice) {
    switch(choice) {
        case EARD_MPU6050_GYRORANGE_250:  return ARD_MPU6050_GYROCONFIG_VALUE_RANGE250;
        case EARD_MPU6050_GYRORANGE_500:  return ARD_MPU6050_GYROCONFIG_VALUE_RANGE500;
        case EARD_MPU6050_GYRORANGE_1000: return ARD_MPU6050_GYROCONFIG_VALUE_RANGE1000;
        case EARD_MPU6050_GYRORANGE_2000: return ARD_MPU6050_GYROCONFIG_VALUE_RANGE2000;
        default: return ARD_MPU6050_GYROCONFIG_VALUE_RANGE250;
    }
}

inline uint8_t ard_mpu6050_configure_select_accrange(eArdMpu6050AccRange choice) {
    switch(choice) {
        case EARD_MPU6050_ACCRANGE_2G:  return ARD_MPU6050_ACCELCONFIG_VALUE_RANGE2G;
        case EARD_MPU6050_ACCRANGE_4G:  return ARD_MPU6050_ACCELCONFIG_VALUE_RANGE4G;
        case EARD_MPU6050_ACCRANGE_8G:  return ARD_MPU6050_ACCELCONFIG_VALUE_RANGE8G;
        case EARD_MPU6050_ACCRANGE_16G: return ARD_MPU6050_ACCELCONFIG_VALUE_RANGE16G;
        default: return ARD_MPU6050_ACCELCONFIG_VALUE_RANGE2G;
    }
}

inline int ard_mpu6050_configure(ArdMpu6050Config config) {

    // check if config is ok
    if (config.lpf_cutoff == EARD_MPU6050_LPF_CUTOFF_260HZ && config.sample_rate < EARD_MPU6050_SAMPLERATE_NOFILT_8000HZ) {
        // if no digital low pass filter (cutoff 260Hz, samplerate scaled from 1000Hz)
        return -1;
    }

    // reset device
    if (ard_i2c_master_write_register(ARD_MPU6050_ADDRESS,
                                      ARD_MPU6050_PWR1_REGISTER,
                                      ARD_MPU6050_PWR1_VALUE_DEVICE_RESET) != 0) return -1;
    delay(100);

    // select clock source and clear sleep bit
    if (ard_i2c_master_write_register(ARD_MPU6050_ADDRESS,
                                      ARD_MPU6050_PWR1_REGISTER,
                                      ARD_MPU6050_PWR1_VALUE_CLK_PLLGYROY) != 0) return -1;

    // select low pass filter
    if (ard_i2c_master_write_register(ARD_MPU6050_ADDRESS,
                                      ARD_MPU6050_LOWPASSFILTER_REGISTER,
                                      ard_mpu6050_configure_select_lpf_cutoff(config.lpf_cutoff)) != 0) return -1;

    // select sample rate
    if (ard_i2c_master_write_register(ARD_MPU6050_ADDRESS,
                                      ARD_MPU6050_SAMPLERATE_REGISTER,
                                      ard_mpu6050_configure_select_samplerate(config.sample_rate)) != 0) return -1;

    // Gyroscope and accelerometer range configuration
    if (ard_i2c_master_write_register(ARD_MPU6050_ADDRESS,
                                      ARD_MPU6050_GYROCONFIG_REGISTER,
                                      ard_mpu6050_configure_select_gyrorange(config.gyro_range)) != 0) return -1;
    if (ard_i2c_master_write_register(ARD_MPU6050_ADDRESS,
                                      ARD_MPU6050_ACCELCONFIG_REGISTER,
                                      ard_mpu6050_configure_select_accrange(config.acc_range)) != 0) return -1;

    // reset sensor paths
    if (ard_i2c_master_write_register(ARD_MPU6050_ADDRESS,
                                      ARD_MPU6050_SIGRESET_REGISTER,
                                      ARD_MPU6050_SIGRESET_VALUE_ALL) != 0) return -1;
    delay(100);

    return 0;
}

inline size_t ard_mpu6050_read(uint16_t *out) {
    // order is AcX (uint16_t) | 2 bytes | index 0-1
    //          AcY (uint16_t) | 2 bytes | index 2-3
    //          AcZ (uint16_t) | 2 bytes | index 4-5
    //          Tmp (uint16_t) | 2 bytes | index 6-7
    //          GyX (uint16_t) | 2 bytes | index 8-9
    //          GyY (uint16_t) | 2 bytes | index 10-11
    //          GyZ (uint16_t) | 2 bytes | index 12-13
    size_t retval = ard_i2c_master_read_begin(ARD_MPU6050_ADDRESS, ARD_MPU6050_READ_ACC_TEMP_GYR);
    if (retval == 0) {
        return ard_i2c_master_read_16swap(ARD_MPU6050_ADDRESS, out, 7);
    }
    return retval;
}

inline void ard_mpu6050_stop(void) {
    ard_i2c_master_end_transmission();
}

#ifdef __cplusplus
}
#endif

#endif
