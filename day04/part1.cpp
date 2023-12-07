#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>

int main() {
    auto filename = std::string("input");

    std::ifstream input{ filename };
    std::string line;

    int sum = 0;

    while(std::getline(input, line)) {
        std::cout << line << std::endl;

        std::set<int> cardNumbers{};
        std::set<int> winningNumbers{};

        auto loc = line.find(":"); // at :
        auto cardDelimiterLoc = line.find("|");
        loc += 2; // move to first number;
        
        while (loc < cardDelimiterLoc) {
            auto num = std::stoi(line.substr(loc, 2));
            cardNumbers.emplace(num);

            loc += 3;
        }

        // std::cout << "Card Numbers:" << std::endl;
        for (const auto num : cardNumbers) {
            // std::cout << num << std::endl;
        }

        loc += 2; // skip over |

        while (loc < line.length()) {
            auto num = std::stoi(line.substr(loc, 2));
            winningNumbers.emplace(num);
            loc += 3;
        }

        // std::cout << "Winning Numbers:" << std::endl;
        for (const auto num : winningNumbers) {
            // std::cout << num << std::endl;

        }

        int cardPoints = 0;
        for (const auto num : cardNumbers) {
            // c++20
            if (!winningNumbers.contains(num)) continue;

            if (cardPoints == 0) {
                cardPoints = 1;
            } else {
                cardPoints *= 2;
            }
        }

        std::cout << "Card Points: " << cardPoints << std::endl;

        sum += cardPoints;
    }

    std::cout << "Sum: " << sum << std::endl;
}