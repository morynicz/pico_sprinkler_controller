#pragma once
#include "pico/stdlib.h"
#include <vector>

void setOuts(const std::vector<uint> &outs);

void blinkLed(uint out);

void blinkMany(std::vector<uint> &outs);