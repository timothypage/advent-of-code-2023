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

    cardTotal++;
  }

  return cardTotal;

}

int main() {
  auto filename = std::string("input");

  std::ifstream input{ filename };
  std::string line;
  int sum = 0;

  int cardCounts[196];

  std::fill_n(cardCounts, 196, 1);

  int* cardCountPtr = cardCounts;

  while (std::getline(input, line)) {
    int currentCardScore = calculateCardScore(line);

    std::cout << line << std::endl;
    std::cout << "Card Score: " << currentCardScore << std::endl;

    for (int i = 1; i <= currentCardScore; i++) {
      // for the next "i" cards increment the total count at that index by 1 
      // times the value of the current card being evaluated
      //
      //   cartCountPtr + i - pointer arithmetic to get next position in array
      // *(cardCountPtr + i) - dereferences pointer, allowing to set the value at that position
      *(cardCountPtr + i) += 1 * *cardCountPtr;
    }

    cardCountPtr++;
  }

  for (auto count : cardCounts) {
    sum += count;
  }

  std::cout << "Sum: " << sum << std::endl;
}
