#include <iostream>
#include <fstream>
#include <string>
#include <utility>

// a contained in b.
inline bool contain(std::pair<int, int> a, std::pair<int, int> b) {
    return a.first >= b.first && a.second <= b.second;
}

// a overlapped by b.
inline bool overlap(std::pair<int, int> a, std::pair<int, int> b){
    return a.first >= b.first && a.first <= b.second;
}

inline std::pair<int, int> getElfJobs(std::string& elf) {
   int delimPos = elf.find("-");
   return std::pair<int, int>(std::stoi(elf.substr(0, delimPos)),
                              std::stoi(elf.substr(delimPos+1, elf.size())));
}

std::pair<std::pair<int,int>, std::pair<int,int>> parseJob(std::string& pairJob ) {
    int delimPos = pairJob.find(",");
    std::string elf1Jobs = pairJob.substr(0, delimPos);
    std::string elf2Jobs = pairJob.substr(delimPos+1, pairJob.size());

    return std::pair<std::pair<int,int>, std::pair<int,int>>(getElfJobs(elf1Jobs),
                                                             getElfJobs(elf2Jobs));
}

int main(int argc, char *argv[]) {
    std::ifstream input(argv[1]);

    std::string pairJob;
    int contPairs = 0;
    int overPairs = 0;

    while(std::getline(input, pairJob)){
        auto [elf1, elf2] = parseJob(pairJob);

        if (contain(elf1, elf2) || contain(elf2, elf1))
            contPairs += 1;

        if (overlap(elf1, elf2) || overlap(elf2, elf1))
            overPairs += 1;
    }

    std::cout << "Fully contained: " << contPairs << std::endl;
    std::cout << "Overlapped jobs: " << overPairs << std::endl;

    input.close();
    return 0;
}
