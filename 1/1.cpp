#include <cstddef>
#include <iostream>
#include <vector>
#include <cstdint>

int main(int argc, char* argv[]) {

  std::vector<uint32_t> input;
  for(;;) {
    std::uint32_t num;
    std::cin >> num;
    if (std::cin.eof()) {
      break;
    }
    input.push_back(num);
  }

  // Part 1
  #if 0
  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t j = 0; j < input.size(); ++j) {
      if (i != j) {
        if (2020 == (input[i] + input[j]) ) {
          std::cout << input[i] * input[j] << std::endl;
          return 0;
        }
      }
    }
  }
  // Part 2
  #else
  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t j = 0; j < input.size(); ++j) {
      if (i != j) {
        for (size_t k = 0; k < input.size(); ++k) {
          if (k != i && k != j) {
            if (2020 == (input[i] + input[j] + input[k]) ) {
              std::cout << i << " " << input[i] << std::endl;
              std::cout << j << " " << input[j] << std::endl;
              std::cout << k << " " << input[k] << std::endl;
              std::cout << input[i] * input[j] * input[k] << std::endl;
              return 0;
            }
          }
        }
      }
    }
  }
  #endif

  std::cout << "Error: No match" << std::endl;
  return 1;
}
