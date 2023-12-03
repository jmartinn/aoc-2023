#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <utility>

std::map<std::string, int> word_to_digit = {
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

std::pair<char, char> findDigits(const std::string &line) {
  char firstDigit = '0', lastDigit = '0';
  std::string result;
  size_t pos = 0;

  // Replace words with digits and form the result string
  while (pos < line.length()) {
    bool isReplaced = false;
    for (const auto &pair : word_to_digit) {
      if (line.compare(pos, pair.first.length(), pair.first) == 0) {
        result += std::to_string(pair.second);
        pos += pair.first.length();
        isReplaced = true;
        break;
      }
    }
    if (!isReplaced) {
      result += line[pos++];
    }
  }

  // Find the first digit
  for (char c : result) {
    if (std::isdigit(c)) {
      firstDigit = c;
      break;
    }
  }

  // Find the last digit
  for (auto it = result.rbegin(); it != result.rend(); ++it) {
    if (std::isdigit(*it)) {
      lastDigit = *it;
      break;
    }
  }

  std::cout << line << " --> " << "[" << firstDigit << "," << lastDigit << "]" << std::endl;

  return {firstDigit, lastDigit};
}

int main() {
  std::ifstream file("calibration_values.txt");
  if (!file.is_open()) {
    std::cerr << "Failed to open the input file" << std::endl;
    return 1;
  }

  std::string line;
  int sum = 0;

  while (getline(file, line)) {
    auto [firstDigit, lastDigit] = findDigits(line);
    if (firstDigit != '0' && lastDigit != '0') {
      int value = (firstDigit - '0') * 10 + (lastDigit - '0');
      sum += value;
    }
  }

  std::cout << "Total sum: " << sum << std::endl;
  return 0;
}

