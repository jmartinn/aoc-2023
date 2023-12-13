#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int64_t process_line(const std::string &line) {
  std::stringstream ss(line);
  std::string word;
  std::string token;
  char pipe;
  int64_t number;
  int64_t card_id;

  std::vector<int> winning_numbers;
  std::vector<int> my_numbers;

  std::getline(ss, token, ':');

  std::stringstream token_stream(token);

  token_stream >> word >> card_id;

  while (ss >> number) {
    if (ss.peek() == '|') {
      ss >> pipe;
      break;
    }
    std::cout << "[0]: " << number << std::endl;
    winning_numbers.push_back(number);
  }

  while (ss >> number) {
    std::cout << "[1]: " << number << std::endl;
    my_numbers.push_back(number);
  }

  std::set<int> my_numbers_set(my_numbers.begin(), my_numbers.end());

  int score = 0;
  int match_count = 0;

  for (int num : winning_numbers) {
    if (my_numbers_set.find(num) != my_numbers_set.end()) {
      if (match_count == 0) {
        score++;
      } else {
        score *= 2;
      }
      match_count++;
    }
  }

  // std::cout << "[" << card_id << "]: " << score << std::endl;
  return score;
}

int main(int argc, char *argv[]) {
  std::ifstream file("input.test");
  std::string line;

  int sum = 0;

  if (file.is_open()) {
    while (getline(file, line)) {
      sum += process_line(line);
    }
    file.close();
  } else {
    std::cerr << "Failed to open the input file" << std::endl;
    return 1;
  }

  std::cout << "Total sum: " << sum << std::endl;

  return 0;
}
