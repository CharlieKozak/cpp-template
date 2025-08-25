#include <fibonacci/fibonacci.h>

#include <stdexcept>
#include <vector>

namespace fibonacci {

// Compute first n Fibonacci numbers (0-indexed series: 0, 1, 1, 2, 3, 5, ...)
std::vector<unsigned long long> generate(std::size_t n) {
  std::vector<unsigned long long> seq;
  seq.reserve(n);
  if (n == 0) return seq;
  seq.push_back(0);
  if (n == 1) return seq;
  seq.push_back(1);
  for (std::size_t i = 2; i < n; ++i) {
    seq.push_back(seq[i - 1] + seq[i - 2]);
  }
  return seq;
}

// Return F(n) for n>=0
unsigned long long nth(std::size_t n) {
  if (n == 0) return 0ULL;
  if (n == 1) return 1ULL;
  unsigned long long a = 0, b = 1;
  for (std::size_t i = 2; i <= n; ++i) {
    auto next = a + b;
    a = b;
    b = next;
  }
  return b;
}

} // namespace fibonacci
