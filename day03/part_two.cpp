#include <fstream>
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <set>

bool is_number(char c) { 
  return c >= '0' && c <= '9';
}

bool is_star(char c) {
  return c == '*';
}

const std::pair<int, int> dirs[] = { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0},   {-1, 1}, {0, 1},  {1, 1} };

char get_char(const std::vector<std::string> &schema, int y, int x) {
  if (y < 0 || y >= schema.size() || x < 0 || x >= schema[y].size()) {
    return '\0';
  }
  return schema[y][x];
};

std::string get_full_number(const std::vector<std::string> &schema, int y, int x) {
  std::string number;
  int i = x;
  while (i >= 0 && is_number(schema[y][i])) {
    i--;
  }
  i++;
  while (i < schema[y].size() && is_number(schema[y][i])) {
    number += schema[y][i];
    i++;
  }
  return number;
}

int main (int argc, char *argv[]) {
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
  for (int y = 0; y < schema.size(); y++) {
    for (int x = 0; x < schema[y].size(); x++) {
      if (is_star(schema[y][x])) {
        std::vector<std::string> adjacent_numbers;
        for (const auto &dir :dirs) {
          char adjacent_char = get_char(schema, y + dir.first, x + dir.second);
          if (is_number(adjacent_char)) {
            int number_start = x + dir.second;
            while (number_start > 0 && is_number(schema[y + dir.first][number_start - 1])) {
              number_start--;
            }

            if (processed_starts.find(std::make_pair(y + dir.first, number_start)) == processed_starts.end()) {
              std::string full_number = get_full_number(schema, y + dir.first, x + dir.second);
              adjacent_numbers.push_back(full_number);
              processed_starts.insert(std::make_pair(y + dir.first, number_start));
            }
          }
        }

        if (adjacent_numbers.size() == 2) {
          int num1 = std::stoi(adjacent_numbers[0]);
          int num2 = std::stoi(adjacent_numbers[1]);

          sum += num1 * num2;
        }
      }
    }
  }

  std::cout << "Sum of all gear ratios: " << sum << std::endl;
  
  return 0;
}





















