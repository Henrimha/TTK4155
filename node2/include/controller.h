#pragma once
#include "sam.h"
#include <stdint.h>
#include "sam/sam3x/include/sam3x8e.h"
#include "sam/sam3x/include/component/component_pwm.h"
#include "sam/sam3x/include/instance/instance_pwm.h"
#include "sam/sam3x/include/component/component_pmc.h"
#include "sam/sam3x/include/instance/instance_pmc.h"
#include "sam/sam3x/include/pio/pio_sam3x8e.h"
#include "sam/sam3x/include/instance/instance_piob.h"
void timer_init();

void calculate_thrust();