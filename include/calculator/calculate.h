#pragma once

#include <istream>
#include <ostream>

namespace calculator {

// Runs the interactive calculation by reading prompts from `in` and writing
// prompts and results to `out`.
// Expected input sequence:
//   <equation token>\n
//   <first number>\n
//   <operation +|-|*|/>\n
//   <second number>\n
// Outputs prompts and either the computed result or an error message.
void calculate(std::istream& in, std::ostream& out);

}
