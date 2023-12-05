#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Round {
  int red, green, blue;
};

struct Game {
  int id;
  std::vector<Round> rounds;
};

void process_line(const std::string &line) {
  std::stringstream ss(line);
  std::string token;

  // Obtener ID del juego
  std::getline(ss, token, ':');

  int game_ID = std::stoi(token);

  Game current_game;
  current_game.id = game_ID;

  // Procesar cada ronda
  while (std::getline(ss, token, ';')) {
    std::stringstream roundStream(token);
    int red, green, blue;

    // Aquí necesitas extraer los números de red, green, blue de 'roundStream'
    // Por ejemplo, puedes buscar 'red', 'green', 'blue' en la cadena y extraer
    // los números antes de estos Supongamos que tienes una función
    // extractNumber que hace esto

    Round round;
    round.red = /* extraer número de red */;
    round.green = /* extraer número de green */;
    round.blue = /* extraer número de blue */;

    current_game.rounds.push_back(round);
  }

  // Ahora, currentGame contiene toda la información de este juego
}

int main(int argc, char *argv[]) {
  std::ifstream file("input.test");
  std::string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      // Parsear el ID del juego y los datos de las rondas.
      // Crear un objeto Game y almacenar la informacion.

      // Verificar si el juego es posible con las cantidades dadas de cubos.
      // Si es posible, sumar el ID a un acumulador.
    }
  }

  // Imprime la suma total de los ID de los juegos validos.
}
