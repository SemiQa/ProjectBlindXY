#include "GPIOInternal.hpp"

namespace Wrappers {

GPIOInternal::GPIOInternal(cyhal_gpio_t gpio) : m_gpio(gpio) {}

void GPIOInternal::init(cyhal_gpio_direction_t direction,
                        cyhal_gpio_drive_mode_t mode) const {
  cyhal_gpio_init(m_gpio, direction, mode, false);
}

void GPIOInternal::set() const { cyhal_gpio_write(m_gpio, true); }

void GPIOInternal::reset() const { cyhal_gpio_write(m_gpio, false); }

void GPIOInternal::write(bool val) const { cyhal_gpio_write(m_gpio, val); }

void GPIOInternal::toggle() const { cyhal_gpio_toggle(m_gpio); }

} // namespace Wrappers
