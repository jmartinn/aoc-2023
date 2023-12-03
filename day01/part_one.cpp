#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream file("calibration_values.txt");
  std::string line;
  int sum = 0;

  if (file.is_open()) {
    while (getline(file, line)) {
      int firstDigit = '0';
      int lastDigit = '0';

      bool foundFirst = false;

      for (char c : line) {
        if (std::isdigit(c)) {
          firstDigit = c;
          foundFirst = true;
          break;
        }
      }

      if (foundFirst) {
        for (auto it = line.rbegin(); it != line.rend(); it++) {
          if (std::isdigit(*it)) {
            lastDigit = *it;
            break;
          }
        }
      }

      if (foundFirst) {
        int value = (firstDigit - '0') * 10 + (lastDigit - '0');
        sum += value;
      }
    }
    file.close();
  } else {
    std::cout << "Failed to open the input file" << std::endl;
    return -1;
  }

  std::cout << "Total sum: " << sum << std::endl;

  return 0;
}
