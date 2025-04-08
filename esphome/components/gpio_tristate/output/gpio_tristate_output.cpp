#include "gpio_tristate_output.h"
#include "esphome/core/log.h"

namespace esphome {
namespace gpio_tristate {

static const char *const TAG = "gpio.trioutput";

void GPIOTristateOutput::dump_config() {
  ESP_LOGCONFIG(TAG, "GPIO Tristate Output:");
  LOG_PIN("  Pin: ", this->pin_);
  LOG_FLOAT_OUTPUT(this);
}

 void GPIOTristateOutput::set_level(float state) {
    // state is the amount this output should be on, 0.0 for LOW, 0.5 for HIGH-IMPEDANCE, 1.0 for HIGH
    // int value = state * 10;
    int value = state * 10;
    if (value >= 3 && value <= 7) {
#ifdef USE_ESP32
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_INPUT);
      // gpio_set_direction(static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_), esp32::GPIO_MODE_INPUT_ONLY);
      // gpio_set_pull_mode(static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_), esp32::GPIO_FLOATING);
#endif
#ifdef USE_ESP8266
      static_cast<esp8266::ESP8266GPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_INPUT);
#endif
#ifdef USE_RP2040
      static_cast<rp2040::RP2040GPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_INPUT);
#endif
    } else if (value < 5) {
#ifdef USE_ESP32
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_OUTPUT);
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->set_inverted(false); //absolutely required, otherwise switching to output and LOW will enable inverted
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->set_drive_strength(GPIO_DRIVE_CAP_1);
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->digital_write(false);
      // gpio_set_direction(static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_), esp32::GPIO_MODE_OUTPUT);
      // gpio_set_level(pin_number, 0);
#endif
#ifdef USE_ESP8266
      static_cast<esp8266::ESP8266GPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_OUTPUT);
      static_cast<esp8266::ESP8266GPIOPin*>(this->pin_)->set_inverted(false); //absolutely required, otherwise switching to output and LOW will enable inverted
      static_cast<esp8266::ESP8266GPIOPin*>(this->pin_)->digital_write(false);
#endif
#ifdef USE_RP2040
      static_cast<rp2040::RP2040GPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_OUTPUT);
      static_cast<rp2040::RP2040GPIOPin*>(this->pin_)->set_inverted(false); //absolutely required, otherwise switching to output and LOW will enable inverted
      static_cast<rp2040::RP2040GPIOPin*>(this->pin_)->digital_write(false);
#endif
    } else {
#ifdef USE_ESP32
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_OUTPUT);
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->set_inverted(false); //absolutely required, otherwise switching to output and low will enable inverted
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->set_drive_strength(GPIO_DRIVE_CAP_1);
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->digital_write(true);
      // gpio_set_direction(dynamic_cast<esp32::ESP32InternalGPIOPin*>(this->pin_), esp32::GPIO_MODE_OUTPUT);
      // gpio_set_level(pin_number, 1);
#endif
#ifdef USE_ESP8266
      static_cast<esp8266::ESP8266GPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_OUTPUT);
      static_cast<esp8266::ESP8266GPIOPin*>(this->pin_)->set_inverted(false); //absolutely required, otherwise switching to output and low will enable inverted
      static_cast<esp8266::ESP8266GPIOPin*>(this->pin_)->digital_write(true);
#endif
#ifdef USE_RP2040
      static_cast<rp2040::RP2040GPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_OUTPUT);
      static_cast<rp2040::RP2040GPIOPin*>(this->pin_)->set_inverted(false); //absolutely required, otherwise switching to output and LOW will enable inverted
      static_cast<rp2040::RP2040GPIOPin*>(this->pin_)->digital_write(false);
#endif
    }
 }

}  // namespace gpio
}  // namespace esphome
