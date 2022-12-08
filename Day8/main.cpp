#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int treeView(std::vector<std::vector<int>>& forestView, int posI, int posJ, int len) {
    int view = 1;
    int count = 0;
    int target = forestView[posI][posJ];

    // Left
    for(int i = posI-1; i >= 0; --i){
        count++;
        if(forestView[i][posJ] >= target)
            break;
    }

    view *= count;
    count = 0;

    // Right
    for(int i = posI+1; i < len; ++i){
        count++;
        if(forestView[i][posJ] >= target)
            break;
    }

    view *= count;
    count = 0;

    // Top
    for(int j = posJ-1; j >= 0; --j){
        count++;
        if(forestView[posI][j] >= target)
            break;
    }

    view *= count;
    count = 0;
    // Down
    for(int j = posJ+1; j < len; ++j){
        count++;
        if(forestView[posI][j] >= target)
            break;
    }

    return view * count;
}




bool checkVisibility(std::vector<std::vector<int>>& forestView, int posI, int posJ, int len) {
    int target = forestView[posI][posJ];
    bool visible = true;

    // Check left
    for(int i = 0; i < posI; ++i)
        if(forestView[i][posJ] >= target)
            visible = false;

    if(visible) return true;
    visible = true;

    // Check right
    for(int i = posI + 1; i < len; ++i){
        if(forestView[i][posJ] >= target)
            visible = false;
    }

    if(visible) return true;
    visible = true;

    // Check top
    for(int j = 0; j < posJ; ++j)
        if(forestView[posI][j] >= target)
            visible = false;

    if(visible) return true;
    visible = true;

    // Check bottom.
    for(int j = posJ + 1; j < len; ++j)
        if(forestView[posI][j] >= target)
            visible =  false;

    return visible;
}


void bruteForce(std::vector<std::vector<int>>& forestView, int size){
    int visible = size * 4 - 4; // Initialize visible to outer trees.
    int scenic = 0;

    for(int i = 1; i < size -1; ++i)
        for(int j = 1; j < size-1; ++j){
            if(checkVisibility(forestView, i, j, size))
                visible++;

            scenic = std::max(treeView(forestView, i,j,size), scenic);
        }

    std::cout << "Visible trees: " << visible << std::endl;
    std::cout << "Scenic score:  " << scenic << std::endl;
}


int main(int argc, char *argv[]) {
    std::ifstream input(argv[1]);
    std::string line;
    getline(input, line);
    int len = line.length();
    auto forest = std::vector<std::vector<int>>(len, std::vector<int>(len));

    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j)
            forest[i][j] = line[j] - '0';
        getline(input,line);
    }

    bruteForce(forest, len);

    return 0;
}
