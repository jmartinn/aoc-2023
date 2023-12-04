#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream file("input.test");
  std::string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      std::cout << line << std::endl;
    }
  }
}
