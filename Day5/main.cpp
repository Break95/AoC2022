#include <iostream>
#include <fstream>
#include <deque>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::deque<char>> parseInput(std::ifstream& input){
    std::vector<std::deque<char>> ship;
    std::string line;

    getline(input,line);
    ship.resize(line.length() / 4 + 1);

    // Get initial config.
    while(line[1] != '1') {
        for(int i = 1, j = 0; i < line.length(); i = i + 4, ++j){
            if(line[i] == ' ')
                continue;
            ship[j].push_front(line[i]);
        }
        getline(input,line);
    }

    // Read empty line.
    getline(input,line);

    return ship;
}


void part1Logic(std::vector<std::deque<char>>& ship, int amount, int src, int dst){
     for(int i = 0; i < amount; ++i){
            ship[dst - 1].push_back(ship[src-1].back());
            ship[src-1].pop_back();
    }
}

void part2Logic(std::vector<std::deque<char>>& ship, int amount, int src, int dst){
    std::vector<char> substack;
        for(auto it = ship[src-1].end()-amount; it != ship[src-1].end(); ++it){
           substack.push_back(*it);
        }

        for(auto& x: substack){
            ship[dst-1].push_back(x);
            ship[src-1].pop_back();
        }
}

int main(int argc, char *argv[]) {
    std::ifstream input(argv[1]);

    std::vector<std::deque<char>> ship1 = parseInput(input);
    std::vector<std::deque<char>> ship2 = ship1;
    std::string line, stub;
    int amount, src, dst;

    while(std::getline(input, line)){
        std::stringstream ss(line);
        ss >> stub >> amount >> stub >> src >> stub >> dst;
        part1Logic(ship1, amount, src, dst);
        part2Logic(ship2, amount, src, dst);
    }

    std::string tops1 = "";
    std::string tops2 = "";

    for(auto it1 = ship1.begin(), it2 = ship2.begin(); it1 != ship1.end(); ++it1, ++it2){
        tops1 += std::string(1, it1->back());
        tops2 += std::string(1, it2->back());
    }

    std::cout << "Tops Crane 9000: " << tops1 << std::endl;
    std::cout << "Tops Crane 9001: " << tops2 << std::endl;

    input.close();
    return 0;
}
