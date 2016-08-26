
#include <stdint.h>

#include "ard_i2c.h"
#include "ard_mpu6050.h"


extern uint8_t ard_mpu6050_configure_select_samplerate(eArdMpu6050SampleRate choice);
extern uint8_t ard_mpu6050_configure_select_lpf_cutoff(eArdMpu6050LpfCutoff choice);
extern uint8_t ard_mpu6050_configure_select_gyrorange(eArdMpu6050GyroRange choice);
extern uint8_t ard_mpu6050_configure_select_accrange(eArdMpu6050AccRange choice);

extern int  ard_mpu6050_configure(ArdMpu6050Config config);
extern size_t ard_mpu6050_read(uint16_t *out);
extern void ard_mpu6050_stop(void);
