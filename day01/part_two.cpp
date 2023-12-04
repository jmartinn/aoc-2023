#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Array of digit representations
const std::string digits[] = {
    "0",   "1",   "2",     "3",    "4",    "5",   "6",     "7",     "8",   "9",
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

// Convert string to digit
int64_t to_digit(const std::string &str) {
  for (size_t i = 0; i < std::size(digits); ++i) {
    if (str.find(digits[i]) == 0) {
      return (i >= 10) ? i - 9 : i;
    }
  }
  return -1;
}

// Main function to process the document
int64_t spelled_out(const std::string &document) {
  int64_t total = 0;
  std::istringstream iss(document);
  std::string line;

  while (std::getline(iss, line)) {
    int64_t first = -1, last = -1;

    for (size_t i = 0; i < line.length(); ++i) {
      for (size_t j = 1; j <= line.length() - i; ++j) {
        int64_t digit = to_digit(line.substr(i, j));
        if (digit != -1) {
          if (first == -1)
            first = digit;
          last = digit;
        }
      }
    }

    if (first != -1 && last != -1) {
      total += first * 10 + last;
    }
  }

  return total;
}

int main() {
  // File input
  std::ifstream file("calibration_values.txt");
  if (!file) {
    std::cerr << "Error opening file 'input.txt'" << std::endl;
    return 1;
  }

  std::string document((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());

  std::cout << "Total: " << spelled_out(document) << std::endl;

  return 0;
}

