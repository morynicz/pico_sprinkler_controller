#include "hw/hw.hpp"

void setOuts(const std::vector<uint> &outs) {
  for (auto out : outs) {
    gpio_init(out);
    gpio_set_dir(out, GPIO_OUT);
  }
}

void blinkLed(uint out) {
  gpio_put(out, 1);
  sleep_ms(250);
  gpio_put(out, 0);
}

void blinkMany(std::vector<uint> &outs) {
  for (auto out : outs)
    gpio_put(out, 1);
  sleep_ms(250);
  for (auto out : outs)
    gpio_put(out, 0);
}