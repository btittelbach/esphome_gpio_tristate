# esphome Tristate Output Component

This is a custom component for [ESPHome](https://esphome.io/) that allows you switch a GPIO output between HIGH, LOW and HIGH-Z (aka high-impedance INPUT-PinMode)

This allows e.g. to share physical pins with other electrical drivers.

It might also allow you to read the GPIO state when you are not driving it HIGH or LOW but some external hardware is driving it HIGH or LOW. (possibly needs lambda code to directly read the pin)

## Basic usage and premisses

The pin state is set with a float value.

- value 0.0: LOW  (really: any value from 0.0 and smaller than 0.4)
- value 0.5: high-Z (really: any value from 0.4 to 0.6)
- value 1.0: HIGH (really: any value from above 0.6 and to 1.0)

## Usage in esphome yaml and example

Include the following into your esphome yaml file:


```yaml
external_components:
  - source:
      type: git
      url: https://github.com/btittelbach/esphome_tristate_output
      ref: main
    components: [ "gpio_tristate" ]

## define Tristate Output
output:
  - platform: gpio_tristate
    pin:
      number: 4
      mode: input
    id: my_tristate_gpio

```


see [examples/](./examples/) for full examples.

## Copyright and License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.


# TODO

- [x] test on esp32
- [x] ensure it works on esp-idf and arduino
- [ ] make compile with rp2040
- [ ] make compile with esp8266
