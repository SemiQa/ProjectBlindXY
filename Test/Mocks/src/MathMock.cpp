#include "MathMock.hpp"
#include <functional>

static std::function<double(double)> _sqrtf;
static std::function<void(const arm_dct4_instance_f32 *, float32_t *,
                          float32_t *)>
    _arm_dct4_f32;
std::function<arm_status(arm_dct4_instance_f32 *, arm_rfft_instance_f32 *,
                         arm_cfft_radix4_instance_f32 *, uint16_t, uint16_t,
                         float32_t)>
    _arm_dct4_init_f32;
std::function<void(const float *, uint32_t, float *)> _arm_std_f32;

double sqrtf(double x) { return _sqrtf(x); }

void arm_dct4_f32(const arm_dct4_instance_f32 *S, float32_t *pState,
                  float32_t *pInlineBuffer) {
  return _arm_dct4_f32(S, pState, pInlineBuffer);
}

arm_status arm_dct4_init_f32(arm_dct4_instance_f32 *S,
                             arm_rfft_instance_f32 *S_RFFT,
                             arm_cfft_radix4_instance_f32 *S_CFFT, uint16_t N,
                             uint16_t Nby2, float32_t normalize) {
  return _arm_dct4_init_f32(S, S_RFFT, S_CFFT, N, Nby2, normalize);
}

void arm_std_f32(const float *values, uint32_t blockSize, float *output) {
  return _arm_std_f32(values, blockSize, output);
}

MathMock::MathMock() {
  _sqrtf = [this](double x) { return sqrtf(x); };
  _arm_dct4_f32 = [this](const arm_dct4_instance_f32 *S, float32_t *pState,
                         float32_t *pInlineBuffer) {
    return arm_dct4_f32(S, pState, pInlineBuffer);
  };
  _arm_dct4_init_f32 = [this](arm_dct4_instance_f32 *S,
                              arm_rfft_instance_f32 *S_RFFT,
                              arm_cfft_radix4_instance_f32 *S_CFFT, uint16_t N,
                              uint16_t Nby2, float32_t normalize) {
    return arm_dct4_init_f32(S, S_RFFT, S_CFFT, N, Nby2, normalize);
  };
  _arm_std_f32 = [this](const float *values, uint32_t blockSize,
                        float *output) {
    return arm_std_f32(values, blockSize, output);
  };
}

MathMock::~MathMock() {
  _sqrtf = {};
  _arm_dct4_f32 = {};
  _arm_dct4_init_f32 = {};
  _arm_std_f32 = {};
}