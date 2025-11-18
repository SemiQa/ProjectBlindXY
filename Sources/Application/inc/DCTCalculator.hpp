#pragma once

#include "arm_math.h"
#include <array>
#include <stdint.h>
#include <vector>

class DCTCalculator {
private:
  static constexpr uint32_t m_sampleCount = 128;
  const float m_normalizeFactor = sqrtf(2.0f / m_sampleCount);
  const uint32_t m_queueSize = 20;

public:
  DCTCalculator();
  ~DCTCalculator() = default;

  DCTCalculator(const DCTCalculator &) = delete;
  DCTCalculator(DCTCalculator &&) = delete;
  DCTCalculator &operator=(const DCTCalculator &) = delete;
  DCTCalculator &operator=(DCTCalculator &&) = delete;

  void push(std::array<float, m_sampleCount> const &samples);
  float computeSTD() const;

#ifndef UT
private:
#endif
  void executeDCT();

  std::array<float, 2 * m_sampleCount> m_stateBuffer;
  std::array<float, m_sampleCount> m_outputBuffer;
  std::vector<float> m_sampleQueue;

  arm_dct4_instance_f32 m_dct;
  arm_rfft_instance_f32 m_rfft;
  arm_cfft_radix4_instance_f32 m_cfft;
};