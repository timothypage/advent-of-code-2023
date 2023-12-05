#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <utility>

// TODO not handling this case
// .........
// ....*....
// .123.123.

int getNumber(std::string line, int pos) {
  std::string num;

  while (pos > 0 && line.at(pos - 1) >= '0' && line.at(pos - 1) <= '9') {
    pos--;
  }

  auto chr = line.at(pos);
  while (chr >= '0' && chr <= '9') {
    num += chr;
    if (pos == line.size() - 1) break;
    chr = line.at(++pos);
  }

  return std::stoi(num);
}


int main() {
  auto filename = std::string{ "input" };
  std::ifstream input{ filename };

  std::vector<std::string> schematic;
  std::string line;

  while(std::getline(input, line)) {
    schematic.push_back(line);
  }

  int sum = 0;

  for (size_t lineNumber = 0; lineNumber < schematic.size(); lineNumber++) {
    line = schematic[lineNumber];

    size_t gearPos = line.find("*");
    while (gearPos != std::string::npos) {
      std::vector<int> numbers;

      std::cout << "Line " << (lineNumber + 1) << ": Found * at " << gearPos << std::endl;

      int positionBefore = std::max<int>(gearPos - 1, 0);
      int positionAfter = std::min<int>(gearPos + 2, line.size()); // position + length of '*'

      // line before
      if (lineNumber > 0) {
        for (int dx = positionBefore; dx < positionAfter; dx++) {
          auto chr = schematic[lineNumber - 1].at(dx);
          if (chr >= '0' && chr <= '9') {
            numbers.push_back( getNumber(schematic[lineNumber - 1], dx));
            // std::cout << "Found number " << getNumber(schematic[lineNumber - 1], dx) << std::endl;
            

            //handling this case
            // .123.123.
            // ....*....
            // .........
            if (dx == positionBefore && schematic[lineNumber - 1].at(dx + 1) == '.') {
              dx++;
            } else {
              break;
            }
          }
        }
      }

      // line after
      if (lineNumber < schematic.size() - 2) {
        for (int dx = positionBefore; dx < positionAfter; dx++) {
          auto chr = schematic[lineNumber + 1].at(dx);
          if (chr >= '0' && chr <= '9') {
            numbers.push_back( getNumber( schematic[lineNumber + 1], dx));

            // handling this case
            // .........
            // ....*....
            // .123.123.
            if (dx == positionBefore && schematic[lineNumber + 1].at(dx + 1) == '.') {
              dx++;
            } else {
              break;
            }
          }
        }
      }

      // position before
      {
        auto chr = schematic[lineNumber].at(positionBefore);
        if (chr >= '0' && chr <= '9') {
          numbers.push_back( getNumber( schematic[lineNumber], positionBefore));
        }
      }

      // position after
      {
        auto chr = schematic[lineNumber].at(positionAfter - 1);
        if (chr >= '0' && chr <= '9') {
          numbers.push_back( getNumber( schematic[lineNumber], positionAfter - 1));
        }
      }

      std::cout << "Found numbers " << std::endl;
      for (auto num : numbers) {
        std::cout << num << std::endl;
      }

      if (numbers.size() == 2) {
        sum += numbers.at(0) * numbers.at(1);
      }



      std::cout << std::endl;

      gearPos = line.find("*", gearPos + 1);
    }
  }

  std::cout << std::endl << "Sum: " << sum << std::endl;
}
