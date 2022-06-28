#pragma once
#include <iostream>
#include <vector>

template <typename T>
std::vector<T> numToDisp(const std::vector<T> &outs, char in) {
  std::vector<T> result;
  for (int i = 0; i < outs.size(); i++) {
    if (in & 1 << i) {
      result.push_back(outs.at(i));
    }
  }
  return result;
}

// 16 + 8 + 2 + 0