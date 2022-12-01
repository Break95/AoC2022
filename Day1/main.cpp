#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

void part1(std::ifstream& input){
    std::string calories;
    int currentCalories = 0;
    int maxCalories = 0;

    while (std::getline(input, calories)) {
        if (calories.size() != 0) {
            currentCalories += std::stoi(calories);
        } else {
            if (maxCalories < currentCalories)
                maxCalories = currentCalories;

            currentCalories = 0;
        }
    }

    std::cout << "Result part 1: " << maxCalories << std::endl;
}

int part2_a(std::ifstream& input){
    std::string calories;

    int low, mid, high = 0;
    int currentCalories = 0;

    while(std::getline(input, calories)) {
        if (calories.size() != 0) {
            currentCalories += std::stoi(calories);
        } else {
            if (currentCalories > high){
                low = mid;
                mid = high;
                high = currentCalories;
            } else if (currentCalories > mid) {
                low = mid;
                mid = currentCalories;
            } else if (currentCalories > low) {
                low = currentCalories;
            }
            currentCalories = 0;
        }
    }

    return low + mid + high;
}

bool compare(int a, int b){ return a > b; }

int part2_b(std::ifstream& input){
    std::string calories;
    std::vector<int> calorieList;
    int currentCalories = 0;

    while(std::getline(input, calories)) {
        if(calories.size() != 0)
            currentCalories += std::stoi(calories);
        else{
            calorieList.push_back(currentCalories);
            currentCalories = 0;
        }
    }

    std::sort(calorieList.begin(), calorieList.end(), compare);

    return calorieList[0] + calorieList[1] + calorieList[2];
}

int main(int argc, char *argv[]) {
    std::ifstream input(argv[1]);
    int loops = 1000;

    part1(input);


    int resA;
    int resB;
    auto timeA = std::chrono::duration<double, std::milli>::zero();
    auto timeB = std::chrono::duration<double, std::milli>::zero();

    for (int i = 0; i < loops; ++i){
        auto t1 = std::chrono::high_resolution_clock::now();
        input.clear();
        input.seekg(0);
        resA = part2_a(input);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> msDoubleA = t2 - t1;
        timeA += msDoubleA;
    }

    for (int i = 0; i < loops; ++i) {
        auto t1 = std::chrono::high_resolution_clock::now();
        input.clear();
        input.seekg(0, std::ios::beg);
        resB = part2_b(input);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> msDoubleB = t2 - t1;
        timeB += msDoubleB;
    }


    std::cout << "Result part 2: " << resA << " - " << resB << "\n\n";

    std::cout << "Part 2. 3 value approach: " << timeA.count()/loops << " ms\n";
    std::cout << "Part 2. List approach:    " << timeB.count()/loops << " ms\n";

    input.close();

    return 0;
}
