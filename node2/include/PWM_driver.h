#pragma once

#include <stdint.h>
#include "sam/sam3x/include/sam3x8e.h"
#include "sam/sam3x/include/component/component_pwm.h"
#include "sam/sam3x/include/instance/instance_pwm.h"
#include "sam/sam3x/include/component/component_pmc.h"
#include "sam/sam3x/include/instance/instance_pmc.h"





void PWM_init();

void PWM_set(uint8_t value);