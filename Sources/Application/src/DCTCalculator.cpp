#include "DCTCalculator.hpp"
#include <cstring>

DCTCalculator::DCTCalculator() {
  arm_dct4_init_f32(&m_dct, &m_rfft, &m_cfft, m_sampleCount, m_sampleCount / 2,
                    m_normalizeFactor);
  m_sampleQueue.reserve(m_queueSize + 1);
}

void DCTCalculator::push(
    std::array<float, DCTCalculator::m_sampleCount> const &samples) {
  std::memcpy(m_outputBuffer.data(), samples.data(),
              m_sampleCount * sizeof(float));
  executeDCT();
}

void DCTCalculator::executeDCT() {
  arm_dct4_f32(&m_dct, m_stateBuffer.data(), m_outputBuffer.data());
  m_sampleQueue.push_back(m_outputBuffer[0]);
  if (m_sampleQueue.size() > m_queueSize)
    m_sampleQueue.erase(m_sampleQueue.begin());
}

float DCTCalculator::computeSTD() const {
  float val;
  arm_std_f32(m_sampleQueue.data(), m_sampleQueue.size(), &val);
  return val;
}
