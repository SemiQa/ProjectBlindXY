#include "BMI270.hpp"

namespace Drivers {

BMI270::BMI270(Wrappers::I2CI &i2c, mtb_bmi270_address_t address)
    : m_i2c(i2c), m_address(address) {}

void BMI270::setConfiguration(bmi2_sens_config &config, SensorType type) {
  switch (type) {
  case BMI2_ACCEL:
    config.type = BMI2_ACCEL;
    config.cfg.acc.odr = BMI2_ACC_ODR_100HZ;
    config.cfg.acc.range = BMI2_ACC_RANGE_16G;
    config.cfg.acc.bwp = BMI2_ACC_OSR4_AVG1;
    config.cfg.acc.filter_perf = BMI2_PERF_OPT_MODE;
    break;
  case BMI2_GYRO:
    config.type = BMI2_GYRO;
    config.cfg.gyr.odr = BMI2_GYR_ODR_100HZ;
    config.cfg.gyr.range = BMI2_GYR_RANGE_2000;
    config.cfg.gyr.bwp = BMI2_GYR_NORMAL_MODE;
    config.cfg.gyr.noise_perf = BMI2_POWER_OPT_MODE;
    config.cfg.gyr.filter_perf = BMI2_PERF_OPT_MODE;
    break;
  default:
    break;
  }
}

void BMI270::configureSensor(SensorType type) {
  struct bmi2_sens_config config = {0};
  auto sensorData = &(m_deviceInfo.sensor);

  bmi2_get_sensor_config(&config, 1, sensorData);
  setConfiguration(config, type);
  bmi2_set_sensor_config(&config, 1, sensorData);
}

void BMI270::enableDevice() {

  struct bmi2_sens_config config = {0};
  auto sensorData = &(m_deviceInfo.sensor);

  bmi2_get_sensor_config(&config, 1, sensorData);
  bmi2_sensor_enable(m_sensors.data(), 2, sensorData);
}

void BMI270::configure() {
  for (auto type : m_sensors)
    configureSensor(type);
  enableDevice();
}

void BMI270::init() {
  Lock lock{m_i2c.getMutex()};
  mtb_bmi270_init_i2c(&m_deviceInfo, m_i2c.getHandle(), m_address);
  configure();
}

float BMI270::getHalfScale() const {
  auto resolution = m_deviceInfo.sensor.resolution;
  return static_cast<float>((pow(2.0, static_cast<double>(resolution)) / 2.0f));
}

float BMI270::getAccSI(int16_t rawValue) const {
  const float g = 9.80665f;
  return (g * rawValue * m_accRange) / getHalfScale();
}

float BMI270::getGyroSI(int16_t rawValue) const {
  return m_gyroRange / getHalfScale() * rawValue;
}

void BMI270::convertData() {
  m_data.accData.x = getAccSI(m_rawData.sensor_data.acc.x);
  m_data.accData.y = getAccSI(m_rawData.sensor_data.acc.y);
  m_data.accData.z = getAccSI(m_rawData.sensor_data.acc.z);
  m_data.gyroData.x = getGyroSI(m_rawData.sensor_data.gyr.x);
  m_data.gyroData.y = getGyroSI(m_rawData.sensor_data.gyr.y);
  m_data.gyroData.z = getGyroSI(m_rawData.sensor_data.gyr.z);
}

void BMI270::readData() {
  Lock lock{m_i2c.getMutex()};
  mtb_bmi270_read(&m_deviceInfo, &m_rawData);
}

BMI270::MotionData BMI270::getData() {
  convertData();
  return m_data;
}

} // namespace Drivers
