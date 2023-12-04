#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <utility>

std::map<std::string, char> word_to_digit = {
    {"one", '1'}, {"two", '2'},   {"three", '3'}, {"four", '4'}, {"five", '5'},
    {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};

std::pair<char, char> findDigits(const std::string &line) {
  if (line.empty()) {
    return {'0', '0'}; // Return default values if the string is empty
  }

  char firstDigit = line.front();
  char lastDigit = line.back();

  return {firstDigit, lastDigit};
}

std::pair<char, char> replaceWordsWithNumbers(const std::string &input) {
  std::string result;
  std::string currentWord;

  for (char ch : input) {
    if (std::isalpha(ch)) {
      currentWord += ch;
      if (word_to_digit.find(currentWord) != word_to_digit.end()) {
        result += word_to_digit[currentWord];
        currentWord.clear();
      }
    } else {
      if (!currentWord.empty() &&
          word_to_digit.find(currentWord) != word_to_digit.end()) {
        result += word_to_digit[currentWord];
      }
      currentWord.clear();
      if (std::isdigit(ch)) {
        result += ch;
      }
    }
  }

  if (!currentWord.empty() &&
      word_to_digit.find(currentWord) != word_to_digit.end()) {
    result += word_to_digit[currentWord];
  }

  std::pair<char, char> digits = findDigits(result);

  std::cout << "[" << digits.first << "," << digits.second << "]" << std::endl;

  return digits;
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
