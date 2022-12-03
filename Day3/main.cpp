#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

#define UPPERFACTOR 38
#define LOWERFACTOR 96
#define itemVal(x) (std::isupper(x) ? (int)x - UPPERFACTOR : (int) x - LOWERFACTOR)

int checkSack(const std::string sack){
    for(int i = 0; i < sack.size()/2; ++i)
            for(int j = sack.size()/2; j < sack.size(); ++j)
                if (sack[i] == sack[j])
                    return itemVal(sack[i]);

    return 0;
}

void part1(std::ifstream& input){
    std::string sack;
    int value = 0;

    while(std::getline(input, sack))
        value += checkSack(sack);

    std::cout << "Value: " << value << std::endl;
}

void part2(std::ifstream& input){
    std::string elf1, elf2, elf3;
    int badgeValue = 0;

    while(input >> elf1 >> elf2 >> elf3){
        std::set<char> elf1Set(elf1.begin(), elf1.end());
        std::set<char> elf2Set(elf2.begin(), elf2.end());
        std::set<char> elf3Set(elf3.begin(), elf3.end());

        std::set<char> badge, badge2;

        std::set_intersection(elf1Set.begin(), elf1Set.end(),
                              elf2Set.begin(), elf2Set.end(),
                              std::inserter(badge, badge.begin()));

        std::set_intersection(badge.begin(), badge.end(),
                              elf3Set.begin(), elf3Set.end(),
                              std::inserter(badge2, badge2.begin()));

        const char badgeChar = *(badge2.begin());
        badgeValue += itemVal(badgeChar);
    }

    std::cout << "Badge values: " << badgeValue << std::endl;
}

int main(int argc, char *argv[]) {
    std::ifstream input(argv[1]);


    part1(input);

    input.clear();
    input.seekg(0);
    part2(input);

    return 0;
}
