#pragma once

#include <cstddef>
#include <vector>

namespace fibonacci {

// We provide both a generator and a single-value accessor:
// - generate(n) returns the first n Fibonacci numbers, useful for iteration and printing.
// - nth(n) returns F(n), useful for direct assertions in tests and algorithmic reuse.
// Keeping a small header allows multiple programs (CLI, tests) to share the interface without
// depending on private implementation details.

std::vector<unsigned long long> generate(std::size_t n);
unsigned long long nth(std::size_t n);

} // namespace fibonacci
