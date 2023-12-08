#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>

int calculateCardScore(std::string line) {
  std::set<int> cardNumbers{};
  std::set<int> winningNumbers{};

  auto loc = line.find(":");
  auto cardDelimiterLoc = line.find("|");
  loc += 2;

  while (loc < cardDelimiterLoc) {
    auto num = std::stoi(line.substr(loc, 2));
    cardNumbers.emplace(num);

    loc += 3;
  }

  loc += 2; // move to first winning number

  while (loc < line.length()) {
    auto num = std::stoi(line.substr(loc, 2));
    winningNumbers.emplace(num);
    loc += 3;
  }


  int cardTotal = 0;
  for (const auto num : cardNumbers) {
    if (!winningNumbers.contains(num)) continue;

    if (cardTotal == 0) {
        cardTotal = 1;
    } else {
        cardTotal *= 2;
    }
  }

  return cardTotal;

}

int main() {
  auto filename = std::string("example_input");

  std::ifstream input{ filename };
  std::string line;

  int cardCounts[195] = { 0 };

  int* cardCountPtr = cardCounts;

  while (std::getline(input, line)) {
    int currentCardScore = calculateCardScore(line);

    *cardCountPtr = currentCardScore;

    std::cout << *cardCountPtr << std::endl;

    cardCountPtr++;

  }
}
