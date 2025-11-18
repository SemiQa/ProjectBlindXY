#include "BGT60TRXX.hpp"

namespace Drivers {
BGT60TRXX::BGT60TRXX(Wrappers::SPII &spi) : m_spi(spi) {};

void BGT60TRXX::init() {}
bool BGT60TRXX::readDataIfPossible() { return true; }
std::array<float, BGT60TRXX::m_sampleCount> &BGT60TRXX::getValues() {
  return m_processedData;
}

} // namespace Drivers