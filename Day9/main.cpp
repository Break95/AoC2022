#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

template<typename I>
std::pair<I,I> operator-(const std::pair<I,I>& l, const std::pair<I,I>& r){
    return {l.first-r.first, l.second-r.second};
}

template<typename I>
std::pair<I,I> operator*(const std::pair<I,I>&l, const std::pair<I,I>& r){
    return {l.first*r.first, l.second * r.second};
}

std::pair<int,int> pairSign(const std::pair<int,int>& p){
    return {(0 < p.first) - (p.first < 0), (0 < p.second) - (p.second < 0)};
}

void solve(std::ifstream& input, int ropeL){
    std::string line;
    std::set<std::pair<int,int>> tailVisits;

    // Initialize rope.
    std::vector<std::pair<int,int>> rope;
    for(int i = 0; i < ropeL; ++i)
        rope.push_back(std::pair<int,int>(0,0));

    tailVisits.insert(rope[ropeL - 1]);

    char dir; int move;
    while(getline(input, line)){
        std::istringstream ss(line);
        ss >> dir >> move;

        for(int j = 0; j < move; ++j){
            // Move head
            if      (dir == 'L') --rope[0].first;
            else if (dir == 'R') ++rope[0].first;
            else if (dir == 'U') ++rope[0].second;
            else if (dir == 'D') --rope[0].second;

            // Followup movement.
            for(int i = 1; i < ropeL; ++i){
                std::pair<int, int> dist = rope[i-1] - rope[i];

                // Diag move.
                if(std::abs(dist.first) + std::abs(dist.second) == 4)
                    rope[i] = rope[i-1] - std::pair<int,int>(1,1) * pairSign(dist);
                else{ // Row move.
                    if(dist.first == -2) {rope[i].first = rope[i-1].first + 1; rope[i].second = rope[i-1].second;}
                    if(dist.first ==  2) {rope[i].first = rope[i-1].first - 1; rope[i].second = rope[i-1].second;}
                    if(dist.second ==  2){rope[i].first = rope[i-1].first; rope[i].second = rope[i-1].second - 1;}
                    if(dist.second == -2){rope[i].first = rope[i-1].first; rope[i].second = rope[i-1].second + 1;}
                }
            }
            tailVisits.insert(rope[ropeL-1]);
        }
    }
    std::cout << "Tail visited: " << tailVisits.size() << std::endl;
}

int main(int argc, char *argv[]) {
    std::ifstream input(argv[1]);
    solve(input, atoi(argv[2]));
    input.close();
    return 0;
}
