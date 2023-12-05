#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Función para comprobar si un carácter es un número
bool esNumero(char c) { return c >= '0' && c <= '9'; }

// Función para comprobar si un carácter es un símbolo (no es un punto ni un
// número)
bool esSimbolo(char c) { return c != '.' && !esNumero(c); }

// Función para sumar los números adyacentes a símbolos
int sumaNumerosAdyacentes(const std::vector<std::string> &esquema) {
  int suma = 0;

  // Recorre cada carácter del esquema
  for (int i = 0; i < esquema.size(); i++) {
    for (int j = 0; j < esquema[i].length(); j++) {
      if (esNumero(esquema[i][j])) {
        // Comprobar los caracteres adyacentes (incluyendo diagonales)
        // Si alguno es un símbolo, suma el número

        // Rellena aquí tu lógica para comprobar los adyacentes y sumar
      }
    }
  }
  return suma;
}

int main() {
  std::ifstream file("input.test");
  std::vector<std::string> schema;
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Failed to open the input file" << std::endl;
    return 1;
  }

  while (std::getline(file, line)) {
    schema.push_back(line);
  }

  int counter = 0;
  for (auto &line : schema) {
    std::cout << "[" << counter << "]" << line << std::endl;

    counter++;
  }

  file.close();

  return 0;
}
