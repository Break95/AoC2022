#include <fstream>
#include <iostream>
#include <deque>

void day6(int step, std::ifstream& input){
    std::deque<char> signal;
    std::string line;
    int start = 0, preSig = 0;
    getline(input, line);

    for(int i = 0; i < line.length(); ++i){
        preSig++;
        signal.push_back(line[i]);

        int invalid = 0;
        for(auto it = signal.begin(); it != signal.end()-1; ++it){
            invalid++;
            if(line[i] == *it){
                for(int i = 0; i < invalid; ++i)
                    signal.pop_front();
                preSig -= invalid;
                break;
            }
        }

        if(preSig == step){ start = i; break; }
    }

    std::cout << "Solution: " << start << std::endl;
}

int main(int argc, char *argv[]) {
    std::ifstream input(argv[1]);
    day6(atoi(argv[2]), input);
    return 0;
}
