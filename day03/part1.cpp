#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <utility>

int main() {
  auto filename = std::string("input");

  std::ifstream input{ filename };

  std::vector<std::string> schematic;
  std::string line;

  while(std::getline(input, line)) {
    schematic.push_back(line);
  }

  std::regex partNumberPattern("[0-9]+");

  int sum = 0;

  for (size_t lineNumber = 0; lineNumber < schematic.size(); lineNumber++) {
    // std::cout << schematic[lineNumber] << std::endl;

    line = schematic[lineNumber];

    // for each number
    for ( auto iterator = std::sregex_iterator(line.begin(), line.end(), partNumberPattern); iterator != std::sregex_iterator(); iterator++) {

      std::smatch match = *iterator;
      std::string match_str = match.str();

      std::string surrounding_characters = "";


      int positionBefore = std::max<int>( iterator->position() - 1, 0);
      int positionAfter = std::min<int>( iterator->position() + match_str.size(), line.size() - 1);

      auto take = positionAfter - positionBefore + 1;

      // check line before
      if (lineNumber > 0) {
        surrounding_characters.append( schematic[lineNumber - 1].substr(positionBefore, take) );
      }

      // check char before
      if (iterator->position() > 0) {
        surrounding_characters.append( line.substr( positionBefore, 1 ) );
      }

      // check char after
      if (iterator->position() + match_str.size() < line.size()) {
        surrounding_characters.append( line.substr( positionAfter, 1 ) ) ;
      }

      // check line after
      if (lineNumber < schematic.size() - 2) {
        surrounding_characters.append( schematic[lineNumber + 1].substr(positionBefore, take) );
      }

      for (char& c : surrounding_characters) {
        if ( c == '.') continue;

        // std::cout << "adding " << match_str << " because " << c << std::endl;
        sum += std::stoi(match_str); 
        break;
      }
    }

  }

  std::cout << std::endl << "Sum: " << sum << std::endl;
}
