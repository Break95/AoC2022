#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

    std::cout << maxCalories << std::endl;

}

void part2_a(std::ifstream& input){
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

    std::cout << low + mid + high << std::endl;
}

bool compare(int a, int b){ return a > b; }

void part2_b(std::ifstream& input){
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

    std::cout << calorieList[0] + calorieList[1] + calorieList[2] << std::endl;
}

int main(int argc, char *argv[]) {
    std::ifstream input(argv[1]);

    part1(input);

    input.clear();
    input.seekg(0);
    part2_a(input);

    input.clear();
    input.seekg(0, std::ios::beg);
    part2_b(input);

    input.close();

    return 0;
}
