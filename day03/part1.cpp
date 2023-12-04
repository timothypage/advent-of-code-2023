#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <utility>
#include <regex>
#include <algorithm>

int main() {
    std::ifstream input{ "input" };
    std::string prevLine;
    std::string line;
    std::string nextLine;

    int total{ 0 };

    std::regex matcher{ "[0-9]+" };

    do {
        if (line.length() == 0) {
            prevLine = line;
            line = nextLine;

            continue;
        }

        std::cout << line << '\n';

        for (
            auto it = std::sregex_iterator(line.begin(), line.end(), matcher); 
            it != std::sregex_iterator(); 
            it++
        ) {
            std::smatch match = *it;
            std::string match_str = match.str();

            std::cout << std::endl;

            std::cout << "matched: " << match_str << " at: " << it->position() << std::endl;

            // find symbol on same line
            if (it->position() > 0) {
                auto chr = line.at(it->position() - 1);
                std::cout << " before: " << chr;
                if (chr != '.') {
                    std::cout << std::endl << "adding " << match_str << std::endl;
                    total += std::stoi(match_str);
                    continue;
                }
            }

            if (it->position() + match_str.length() < line.length()) {
                auto chr = line.at(it->position() + match_str.length());
                std::cout << " after: " << chr << ' ';
                if (chr != '.') {
                    std::cout << std::endl << "adding " << match_str << std::endl;

                    total += std::stoi(match_str);
                    continue;
                }
            }

            int start = std::max<int>(it->position() - 1, 0);
            int end = std::min<int>(it->position() + match_str.length() + 1, line.length() - 1);
            std::cout << "other line search from: " << start << " to " << end;

            // find symbol on prev line
            for (int i = start; i <= end; i++) {
                if (prevLine.length() > 0) {
                    auto chr = prevLine.at(i);

                    if(chr != '.' && !regex_match(prevLine.substr(i, 1), matcher)) {
                        std::cout << " found " << chr << std::endl;
                        std::cout << std::endl << "adding " << match_str << std::endl;
                        total += std::stoi(match_str);
                        break;
                    } 
                }

                if (nextLine.length() > 0) {
                    auto chr = nextLine.at(i);
                    if(chr != '.' && !regex_match(nextLine.substr(i, 1), matcher)) {
                        std::cout << " found " << chr << std::endl;
                        std::cout << std::endl << "adding " << match_str << std::endl;
                        total += std::stoi(match_str);
                        break;
                    } 
                }
            }

            std::cout << std::endl;

        }
        std::cout << std::endl;

        // bookkeeping
        prevLine = line;
        line = nextLine;

    } while( std::getline( input, nextLine ) );


    std::cout << "total: " << total << std::endl;

    return 0;
}
