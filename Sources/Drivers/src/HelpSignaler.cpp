#include "HelpSignaler.hpp"

namespace Drivers {

HelpSignaler::HelpSignaler(Wrappers::GPIOI &diode, uint32_t periodMS)
    : m_diode(diode), m_periodMS(periodMS) {}

void HelpSignaler::init() const {
  m_diode.init(cyhal_gpio_direction_t::CYHAL_GPIO_DIR_OUTPUT,
               cyhal_gpio_drive_mode_t::CYHAL_GPIO_DRIVE_STRONG);
}

HelpSignaler::State HelpSignaler::getState() const { return m_state; }

void HelpSignaler::toggle() {
  if (m_state == State::ACTIVE)
    reset();
  else if (m_state == State::INACTIVE)
    set();
}

void HelpSignaler::evaluate() {
  if (m_state != State::ACTIVE)
    return;
  if (m_timeStamp.elapsed())
    m_diode.toggle();
}

void HelpSignaler::set() {
  m_timeStamp.set(m_periodMS);
  m_state = State::ACTIVE;
}

void HelpSignaler::reset() {
  m_diode.set();
  m_state = State::INACTIVE;
}

void HelpSignaler::disable() {
  m_diode.reset();
  m_state = State::DISABLED;
}

void HelpSignaler::enable() { reset(); }

} // namespace Drivers
