#pragma once
#include "sam.h"
#include <sys/types.h>

void dcmotor_init();

void dc_motor_reset();

int dc_motor_read();

void motor_PWM_init();

void motor_PWM_set(u_int32_t value, char dir_left);