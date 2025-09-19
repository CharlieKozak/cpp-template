#include <cmath>
#include <iostream>
#include <string>

#include "calculator/calculate.h"

namespace calculator {

void calculate(std::istream& in, std::ostream& out) {
  std::string Equation;
  out << "Type your equation\n";
  in >> Equation;

  std::string Operation;

  double Num_1;
  double Num_2;

  out << "Enter first number: ";
  in >> Num_1;
  out << "Enter operation(+, -, /, *): ";
  in >> Operation;
  out << "Enter second number: ";
  in >> Num_2;

  if (Operation == "+") {
    out << (Num_1 + Num_2);
  } else if (Operation == "-") {
    out << (Num_1 - Num_2);
  } else if (Operation == "*") {
    out << (Num_1 * Num_2);
  } else if (Operation == "/") {
    if (Num_2 == 0) {
      out << "Error: Division by zero!";
    } else {
      out << (Num_1 / Num_2);
    }
  } else {
    out << "Error: Invalid operation!";
  }
}

}  // namespace calculator
