from esphome import pins
import esphome.codegen as cg
from esphome.components import output
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_PIN

from .. import gpio_ns

GPIOTristateOutput = gpio_ns.class_("GPIOTristateOutput", output.FloatOutput, cg.Component)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(GPIOTristateOutput),
        cv.Required(CONF_PIN): pins.gpio_output_pin_schema,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await output.register_output(var, config)
    await cg.register_component(var, config)

    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))
