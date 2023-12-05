#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Round {
  int red, green, blue;
  Round(int r, int g, int b) : red(r), green(g), blue(b) {}
};

struct Game {
  int id;
  std::vector<Round> rounds;

  Game(int id) : id(id){};

  void print_game_details() {
    std::cout << "Game ID: " << id << std::endl;
    for (size_t i = 0; i < rounds.size(); ++i) {
      std::cout << "Round " << (i + 1) << ": "
                << "Red: " << rounds[i].red << ", "
                << "Green: " << rounds[i].green << ", "
                << "Blue: " << rounds[i].blue << std::endl;
    }
  }

  int64_t is_game_possible(int max_red, int max_green, int max_blue) {
    for (auto &round : rounds) {
      if (round.red > max_red || round.green > max_green ||
          round.blue > max_blue) {
        return 0;
      }
    }
    return id;
  }
};

int64_t extract_number(const std::string &round_info, const std::string &color) {
  size_t pos = round_info.find(color);
  if (pos != std::string::npos) {
    int i = pos - 1;
    while (i >= 0 && std::isspace(round_info[i])) {
      --i;
    }

    int start = i;
    while (start >= 0 && std::isdigit(round_info[start])) {
      --start;
    }

    std::string number_str = round_info.substr(start + 1, i - start);
    int number = std::stoi(number_str);

    return number;
  }
  return 0;
}

int64_t process_line(const std::string &line) {
  std::stringstream ss(line);
  std::string token;
  std::string word;
  int game_id;

  std::getline(ss, token, ':');

  std::stringstream token_stream(token);

  token_stream >> word >> game_id;

  Game current_game(game_id);

  while (std::getline(ss, token, ';')) {
    int red = extract_number(token, "red");
    int green = extract_number(token, "green");
    int blue = extract_number(token, "blue");

    Round round(red, green, blue);

    current_game.rounds.push_back(round);
  }

  return current_game.is_game_possible(12, 13, 14);
}

int main(int argc, char *argv[]) {
  std::ifstream file("input.prod");
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
