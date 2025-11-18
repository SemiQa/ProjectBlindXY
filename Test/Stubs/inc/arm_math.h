#pragma once

#include "stdint.h"

typedef struct {
} arm_dct4_instance_f32;

typedef struct {
} arm_rfft_instance_f32;

typedef struct {
} arm_cfft_radix4_instance_f32;

typedef struct {
} arm_status;

typedef float float32_t;

double sqrtf(double x);

void arm_dct4_f32(const arm_dct4_instance_f32 *S, float32_t *pState,
                  float32_t *pInlineBuffer);

void arm_std_f32(const float *values, uint32_t blockSize, float *output);

arm_status arm_dct4_init_f32(arm_dct4_instance_f32 *S,
                             arm_rfft_instance_f32 *S_RFFT,
                             arm_cfft_radix4_instance_f32 *S_CFFT, uint16_t N,
                             uint16_t Nby2, float32_t normalize);
