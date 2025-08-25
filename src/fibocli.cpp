#include <fibonacci/fibonacci.h>

#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: fibocli <N>\n";
    return 1;
  }
  std::size_t n = 0;
  try {
    n = static_cast<std::size_t>(std::stoul(argv[1]));
  } catch (...) {
    std::cerr << "Invalid N: " << argv[1] << "\n";
    return 1;
  }

  auto seq = fibonacci::generate(n);
  for (std::size_t i = 0; i < seq.size(); ++i) {
    if (i) std::cout << ' ';
    std::cout << seq[i];
  }
  if (!seq.empty()) std::cout << '\n';
  return 0;
}
