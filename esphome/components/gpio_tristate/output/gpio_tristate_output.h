#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/output/float_output.h"
#ifdef USE_ESP32
#include "esphome/components/esp32/gpio.h"
#endif
#ifdef USE_RP2040
#include "esphome/components/rp2040/gpio.h"
#endif
#ifdef USE_ESP8266
#include "esphome/components/esp8266/gpio.h"
#endif

namespace esphome {
namespace gpio_tristate {

class GPIOTristateOutput : public output::FloatOutput, public Component {
 public:
  void set_pin(GPIOPin *pin) { pin_ = pin; }

  void setup() override {
    this->turn_off();
#ifdef USE_ESP32
    static_cast<esp32::ESP32InternalGPIOPin*>(this->pin_)->set_flags(gpio::Flags::FLAG_INPUT);
#endif
#ifdef USE_RP2040
    static_cast<rp2040::RP2040GPIOPin*>(this->pin_)->set_flags(gpio::Flags::FLAG_INPUT);
#endif
#ifdef USE_ESP8266
    static_cast<esp8266::ESP8266GPIOPin*>(this->pin_)->set_flags(gpio::Flags::FLAG_INPUT);
#endif
    this->pin_->setup();
    // this->turn_off();
  }
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  void set_level(float state);

  void write_state(float state) override { this->set_level(state); }

  GPIOPin *pin_;
};

}  // namespace gpio
}  // namespace esphome
