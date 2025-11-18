#pragma once

#include "I2CI.hpp"
#include "bmi270.h"
#include "mtb_bmi270.h"
#include <array>

namespace Drivers {

class BMI270 {
public:
  struct DataSegment {
    float x;
    float y;
    float z;
  };

  struct MotionData {
    DataSegment accData;
    DataSegment gyroData;
  };

  BMI270(Wrappers::I2CI &i2c, mtb_bmi270_address_t address);
  ~BMI270() = default;

  BMI270(const BMI270 &) = delete;
  BMI270(BMI270 &&) = delete;
  BMI270 &operator=(const BMI270 &) = delete;
  BMI270 &operator=(BMI270 &&) = delete;

  void init();
  void readData();

  MotionData getData();

private:
  typedef uint8_t SensorType;

  void configure();
  void configureSensor(SensorType type);
  void setConfiguration(bmi2_sens_config &config, SensorType type);
  void enableDevice();
  void convertData();

  float getAccSI(int16_t rawValue) const;
  float getGyroSI(int16_t rawValue) const;
  float getHalfScale() const;

  Wrappers::I2CI &m_i2c;
  mtb_bmi270_address_t m_address;
  mtb_bmi270_t m_deviceInfo;
  mtb_bmi270_data_t m_rawData;
  MotionData m_data;
  std::array<SensorType, 2> m_sensors{BMI2_ACCEL, BMI2_GYRO};
  float m_gyroRange = 2000.0f;
  float m_accRange = 16.0f;
};
} // namespace Drivers