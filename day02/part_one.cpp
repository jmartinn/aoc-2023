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
};

int64_t extract_number(const std::string &round_info, const std::string &color) {
  size_t pos = round_info.find(color);
  if (pos != std::string::npos) {
    // Find the start of the number preceding the color
    int i = pos - 1;
    while (i >= 0 && std::isspace(round_info[i])) {
      --i;
    }

    // Now find the end of the number (which is the start of our search)
    int start = i;
    while (start >= 0 && std::isdigit(round_info[start])) {
      --start;
    }

    // Extract the number
    std::string number_str = round_info.substr(start + 1, i - start);
    int number = std::stoi(number_str);

    return number;
  }
  return 0;
}

void process_line(const std::string &line) {
  std::stringstream ss(line);
  std::string token;
  std::string word;
  int game_ID;

  std::getline(ss, token, ':');

  std::stringstream tokenStream(token);

  tokenStream >> word >> game_ID;

  Game current_game(game_ID);

  while (std::getline(ss, token, ';')) {
    int red = extract_number(token, "red");
    int green = extract_number(token, "green");
    int blue = extract_number(token, "blue");

    Round round(red, green, blue);

    current_game.rounds.push_back(round);
  }

  // Print the current game object in a legible way
  current_game.print_game_details();

  // Ahora, currentGame contiene toda la información de este juego
  // Puedes hacer algo con currentGame, como agregarlo a un vector de juegos o
  // procesarlo más
}

int main(int argc, char *argv[]) {
  std::ifstream file("input.test");
  std::string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      process_line(line);
    }
  }
}
