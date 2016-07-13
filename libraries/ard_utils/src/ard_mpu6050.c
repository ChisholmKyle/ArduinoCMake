
#include <stdint.h>

#include "ard_i2c.h"
#include "ard_mpu6050.h"

extern int  ard_mpu6050_configure(ArdMpu6050Config config);
extern size_t ard_mpu6050_read(uint16_t *out);
extern void ard_mpu6050_stop(void);
