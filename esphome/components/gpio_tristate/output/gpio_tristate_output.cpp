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
    if (value >= 4 && value <= 6) {
#ifdef USE_ESP32
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_INPUT);
      // gpio_set_direction(static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_), esp32::GPIO_MODE_INPUT_ONLY);
      // gpio_set_pull_mode(static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_), esp32::GPIO_FLOATING);
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
    } else {
#ifdef USE_ESP32
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->pin_mode(gpio::Flags::FLAG_OUTPUT);
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->set_inverted(false); //absolutely required, otherwise switching to output and low will enable inverted
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->set_drive_strength(GPIO_DRIVE_CAP_1);
      static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->digital_write(true);
      // gpio_set_direction(dynamic_cast<esp32::ESP32InternalGPIOPin*>(this->pin_), esp32::GPIO_MODE_OUTPUT);
      // gpio_set_level(pin_number, 1);
#endif
    }
 }

}  // namespace gpio
}  // namespace esphome
