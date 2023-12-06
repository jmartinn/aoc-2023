#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

bool is_number(char c) { return c >= '0' && c <= '9'; }

bool is_dot(char c) { return c == '.'; }

const std::pair<int, int> dirs[] = { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0},   {-1, 1}, {0, 1},  {1, 1} };

// Get character from a given position
char get_char(const std::vector<std::string> &schema, int y, int x) {

  if (y < 0 || y >= schema.size() || x < 0 || x >= schema[y].size()) {
    return '\0';
  }
  return schema[y][x];
}

// Get the whole number by checking adjacent digits in the x axis
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
  std::ifstream file("input.prod");
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

  std::set<std::pair<int, int>> processed_starts;
  for (int y = 0; y < schema.size(); ++y) {
    for (int x = 0; x < schema[y].size(); ++x) {
      if (is_number(schema[y][x])) {
        bool is_adjacent_to_symbol = false;
        for (const auto &dir : dirs) {
          char adjacent_char = get_char(schema, y + dir.first, x + dir.second);
          if (!is_dot(adjacent_char) && !is_number(adjacent_char) && adjacent_char != '\0') {
            is_adjacent_to_symbol = true;
            break;
          }
        }
        if (is_adjacent_to_symbol) {
          int number_start = x;
          while (number_start > 0 && is_number(schema[y][number_start - 1])) {
            number_start--;
          }

          if (processed_starts.find(std::make_pair(y, number_start)) == processed_starts.end()) {
            std::string full_number = get_full_number(schema, y, number_start);
            sum += std::stoi(full_number);
            processed_starts.insert(std::make_pair(y, number_start));
          }
        }
      }
    }
  }

  std::cout << "Sum of all valid numbers:" << sum << std::endl;

  return 0;
}
