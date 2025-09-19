#include <cmath>
#include <iostream>

int main()
{

  std::string Equation;
  std::cout << "Type your equation\n";
  std::cin >> Equation;

  std::string Operation;

  double Num_1;
  double Num_2;

  std::cout << "Enter first number: ";
  std::cin >> Num_1;
  std::cout << "Enter operation(+, -, /, *): ";
  std::cin >> Operation;
  std::cout << "Enter second number: ";
  std::cin >> Num_2;

  if (Operation == "+")
  {
    std::cout << Num_1 + Num_2;
  }
  else if (Operation == "-")
  {
    std::cout << Num_1 - Num_2;
  }
  else if (Operation == "*")
  {
    std::cout << Num_1 * Num_2;
  }
  else if (Operation == "/")
  {
    if (Num_2 == 0)
    {
      std::cout << "Error: Division by zero!";
    }
    else
    {
      std::cout << Num_1 / Num_2;
    }
  }
  else
  {
    std::cout << "Error: Invalid operation!";
  }
  return 0;
}