#include <iostream>
#include <map>
#include <fstream>

std::map<char,  int> values = {
    {'A',1}, {'B',2}, {'C',3},
    {'X',1}, {'Y',2}, {'Z',3}
};

void part1(std::ifstream& input){
    int score = 0;
    std::string game;

    while(std::getline(input, game)){
       auto myVal  = values[game[2]];
       auto elfVal = values[game[0]];
       auto tmp = myVal - elfVal;

       if (tmp == 1 || tmp == -2) // Win
           score += myVal + 6;
       else if (tmp == 0) // Draw
           score += myVal + 3;
       else  //Lose
           score += myVal;
    }

    std::cout << "Score A: " << score << std::endl;
}

void part2(std::ifstream& input){
    int score = 0;
    std::string game;

    while(std::getline(input, game)){
        auto elfVal = values[game[0]];
        auto action = values[game[2]];

        if (action == 1) { // Lose
            auto myVal = (elfVal == 1) ? 3 : elfVal - 1;
            score += myVal;
        } else if (action == 2) { // Draw
            score += elfVal + 3;
        } else if (action == 3) { // Win
            auto myVal = (elfVal == 3) ? 1 : elfVal + 1;
            score += myVal + 6;
        }
    }

    std::cout << "Score B: " << score << std::endl;
}

int main(int argc, char *argv[]) {
    std::ifstream input(argv[1]);

    part1(input);

    input.clear();
    input.seekg(0);
    part2(input);

    return 0;
}
