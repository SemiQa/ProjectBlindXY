#pragma once

#include "arm_math.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct MathMock {
  MathMock();
  ~MathMock();

  MOCK_METHOD(double, sqrtf, (double));
  MOCK_METHOD(arm_status, arm_dct4_init_f32,
              (arm_dct4_instance_f32 *, arm_rfft_instance_f32 *,
               arm_cfft_radix4_instance_f32 *, uint16_t, uint16_t, float32_t));
  MOCK_METHOD(void, arm_dct4_f32,
              (const arm_dct4_instance_f32 *, float32_t *, float32_t *));
  MOCK_METHOD(void, arm_std_f32, (const float *, uint32_t, float *));
};