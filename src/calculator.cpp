// main delegates to calculator::calculate so the logic can be unit tested
#include <iostream>

#include "calculator/calculate.h"

int main() {
  calculator::calculate(std::cin, std::cout);
  return 0;
}