#include <cctype>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility> // Para std::pair

// Mapa de palabras a dígitos
std::unordered_map<std::string, int> word_to_digit = {
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

// Función para identificar y priorizar palabras numéricas en la cadena
std::vector<std::pair<size_t, std::string>>
findNumericWords(const std::string &line) {
  std::vector<std::pair<size_t, std::string>> positions;

  for (const auto &pair : word_to_digit) {
    size_t pos = line.find(pair.first);
    while (pos != std::string::npos) {
      positions.push_back({pos, pair.first});
      pos = line.find(pair.first, pos + 1);
    }
  }

  // Ordenar por posición y longitud de palabra
  std::sort(positions.begin(), positions.end(),
            [](const std::pair<size_t, std::string> &a,
               const std::pair<size_t, std::string> &b) {
              return a.first < b.first ||
                     (a.first == b.first && a.second.size() > b.second.size());
            });

  return positions;
}

// Función para buscar dígitos y palabras en la línea
std::pair<char, char> findDigits(const std::string &line) {
  auto numericWords = findNumericWords(line);

  char firstDigit = '0', lastDigit = '0';

  // Comprobar si el primer y último carácter son dígitos numéricos
  if (!numericWords.empty()) {
    // Si el primer carácter es un dígito, usarlo
    if (isdigit(line.front())) {
      firstDigit = line.front();
    } else {
      firstDigit = '0' + word_to_digit[numericWords.front().second];
    }

    // Si el último carácter es un dígito, usarlo
    if (isdigit(line.back())) {
      lastDigit = line.back();
    } else {
      lastDigit = '0' + word_to_digit[numericWords.back().second];
    }
  }

  return {firstDigit, lastDigit};
}

int main() {
  std::ifstream file("calibration_values.txt");
  std::string line;
  int sum = 0;

  if (file.is_open()) {
    int counter = 0;
    while (getline(file, line)) {
      auto [firstDigit, lastDigit] = findDigits(line);

      if (firstDigit != 0 && lastDigit != 0) {
      std::cout << "Pair number " << counter << " :" << firstDigit << ", " << lastDigit << std::endl;
        int value = (firstDigit - '0') * 10 + (lastDigit - '0');
        sum += value;
      }

      counter++;
    }
    file.close();
  } else {
    std::cout << "No se pudo abrir el archivo" << std::endl;
    return 1;
  }

  std::cout << "Suma total de valores de calibración: " << sum << std::endl;
  return 0;
}
