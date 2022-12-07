#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>
#include <map>

struct dirNode {
    long size;
    std::map<std::string, dirNode*> subDirs;
};

void processFS(std::ifstream& input, dirNode* node, std::vector<int>& sizes){
    std::string line;
    while(std::getline(input, line)){
        if(line[2] == 'l') continue;  // $ ls
        if (line[0] == '$'){          // $ cd
            if(line[5] == '.') break; // Go up one level
            else {                    // Go down one level.
                std::string subDirName = line.substr(5, line.length()-5);
                processFS(input, node->subDirs[subDirName], sizes);
                node->size += node->subDirs[subDirName]->size;
            }
        }
        else { // In ls output.
            if(line[0] == 'd') // Found a new directory.
                node->subDirs[line.substr(4, line.size()-4)] = new dirNode{0, std::map<std::string, dirNode*>()};
            else { // Found new file.
                long tmp;
                std::istringstream(line) >> tmp;
                node->size += tmp;
            }
        }
    }

    sizes.push_back(node->size);
    return;
}

int main(int argc, char *argv[]) {
    const int totalDiskSpace = 70000000;
    const int neededSpace = 30000000;
    const int sizeLimit = 100000;

    std::ifstream input(argv[1]);
    std::vector<int> sizes;
    std::string a;
    getline(input , a);
    dirNode fileSystem = {0, std::map<std::string, dirNode*>()};

    processFS(input, &fileSystem, sizes);

    std::cout << "Part1. Sizes sum:    "
              << std::accumulate(sizes.begin(), sizes.end(), 0,
                                 [](int a, int b){ if (b < sizeLimit) return a+b; else return a; }) << std::endl;

    int freeReq = fileSystem.size - (totalDiskSpace - neededSpace);
    int minFound = totalDiskSpace;

    for(auto x : sizes)
        if(x >= freeReq && x < minFound) minFound = x;

    std::cout << "Part2. Smallest dir: " << minFound << std::endl;

    return 0;
}
