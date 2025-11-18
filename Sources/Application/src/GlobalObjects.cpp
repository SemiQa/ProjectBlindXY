#include "BGT60TRXX.hpp"
#include "BMI270.hpp"
#include "GPIOInternal.hpp"
#include "HelpSignaler.hpp"
#include "I2CInternal.hpp"
#include "LoopbackThread.hpp"
#include "MotionThread.hpp"
#include "PWMDrivenDevice.hpp"
#include "PWMInternal.hpp"
#include "RadarThread.hpp"
#include "SPIInternal.hpp"
#include "USBThread.hpp"

static Wrappers::I2CInternal i2c;
static Wrappers::SPIInternal spi;
static Wrappers::PWMInternal vibratingMotorPwm{P9_7};
static Wrappers::PWMInternal noiseMakerPwm{P9_6};
static Wrappers::GPIOInternal helpDiode{P9_4};

static Threads::LoopbackThread loopbackThread{
    MessageSystem::NodeID::LOOPBACK_THREAD};

static Threads::USBThread usbThread{MessageSystem::NodeID::USB_THREAD};

static Drivers::BMI270 motionSensor{i2c,
                                    static_cast<mtb_bmi270_address_t>(0x68)};
static Threads::MotionThread motionThread{motionSensor,
                                          MessageSystem::NodeID::MOTION_THREAD};

static Drivers::BGT60TRXX radarSensor{spi};
static Drivers::PWMDrivenDevice vibratingMotor{vibratingMotorPwm};
static Drivers::PWMDrivenDevice noiseMaker{noiseMakerPwm, 100.0f, 500.0f};
std::vector<std::reference_wrapper<Drivers::PWMDrivenDevice>> obstacleSignalers{
    vibratingMotor, noiseMaker};
static Drivers::HelpSignaler helpSignaler{helpDiode, 500};
static Threads::RadarThread radarThread{radarSensor, obstacleSignalers,
                                        helpSignaler,
                                        MessageSystem::NodeID::RADAR_THREAD};
