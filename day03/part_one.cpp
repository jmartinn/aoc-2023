#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

bool is_number(char c) { return c >= '0' && c <= '9'; }

bool is_dot(char c) { return c == '.'; }

const std::pair<int, int> dirs[] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

char get_char(const std::vector<std::string> &schema, int y, int x) {

  if (y < 0 || y >= schema.size() || x < 0 || x >= schema[y].size()) {
    return '\0';
  }
  return schema[y][x];
}

std::string get_full_number(const std::vector<std::string> &schema, int y, int x) {
  std::string number;
  int i = x;
  // Buscar hacia atrás para encontrar el inicio del número
  while (i >= 0 && is_number(schema[y][i])) {
    i--;
  }
  i++; // Volver al inicio del número
  // Recoger todos los dígitos del número
  while (i < schema[y].size() && is_number(schema[y][i])) {
    number += schema[y][i];
    i++;
  }
  return number;
}

int main() {
  std::ifstream file("input.test");
  std::vector<std::string> schema;
  std::string line;
  int sum = 0;

  if (!file.is_open()) {
    std::cerr << "Failed to open the input file" << std::endl;
    return 1;
  }

  while (std::getline(file, line)) {
    schema.push_back(line);
  }

  file.close();

  std::set<int> processedStarts;
  for (int y = 0; y < schema.size(); ++y) {
    for (int x = 0; x < schema[y].size(); ++x) {
      if (is_number(schema[y][x])) {
        bool isAdjacentToSymbol = false;
        for (const auto &dir : dirs) {
          char adjacentChar = get_char(schema, y + dir.first, x + dir.second);
          if (!is_dot(adjacentChar) && !is_number(adjacentChar) &&
              adjacentChar != '\0') {
            isAdjacentToSymbol = true;
            break;
          }
        }
        if (isAdjacentToSymbol) {
          int numberStart = x;
          while (numberStart > 0 && is_number(schema[y][numberStart - 1])) {
            numberStart--;
          }
          if (processedStarts.find(numberStart) == processedStarts.end()) {
            std::string fullNumber = get_full_number(schema, y, numberStart);
            sum += std::stoi(fullNumber);
            processedStarts.insert(numberStart);
          }
        }
      }
    }
  }

  std::cout << "Sum of all valid numbers:" << sum << std::endl;

  return 0;
}
