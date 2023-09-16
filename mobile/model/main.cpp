#include <iostream>
#include <vector>
#include<cmath>
#include <utility>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;


struct Point
{
    std::vector<double> cood;
    // int label;
};

// Fonction pour calculer la distance euclienne entre 2 points

double distance(const Point& p1,const Point& p2 ){
    double sum = 0.0;
    for (size_t i = 0; i < p1.cood.size();++i){
        double diff = p1.cood[i] - p2.cood[i];
        sum += diff * diff;
    }
    return (std::sqrt(sum));
}

std::vector<std::pair<double, int>> KNN(const std::vector<Point> &data, const Point &item){
    std::vector<std::pair<double, int>> distances;

    for (size_t i = 0; i < data.size();++i){
        double dist = distance(data[i], item);
        distances.emplace_back(dist, i);
    }
    return distances;
}

bool compareByDouble(const std::pair<double, int> &a, const std::pair<double, int> &b)
{
    return a.first < b.first;
}

int main(){
    // std::cout << "hello World" << std::endl;
    // std::vector<Point> data = {
    //     {{2.0, 3.8, 4.8, 9.1}},
    //     {{9.0, 3.8, 4.5, 9.3}},
    //     {{2.0, 3.8, 4.8, 9.1}},
    //    { {2.0, 3.8, 4.0, 9.5}},
    //     {{2.0, 3.8, 4.4, 9.8}},
    // };

    // Point index = {{2.9, 4.0, 5.3, 3.9}};

    // std::vector<std::pair<double, int>> result = KNN(data, index);
    // std::cout << "Observer Notre Matrice de distance "  << std::endl;

    // std::sort(result.begin(), result.end(), compareByDouble);

    // for (const auto &element : result)
    // {
    //     std::cout << "distance: " << element.first << ", index: " << element.second << std::endl;
    // }

    // Open the CSV file
    std::ifstream file("num.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open file!" << std::endl;
        return -1;
    }

    std::vector<Point> train;
    std::string line;

    while(std::getline(file,line)){

        Point row; // Initialize a vector to store the numerical columns of the row
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ','))
        {
            try
            {
                double value = std::stod(cell);
                row.cood.push_back(value); // Store the numerical value in the row vector
            }
            catch (const std::exception &e)
            {
                // Ignore non-numerical cells
            }
        }
        train.push_back(row);
    }

    for (const auto &row : train)
    {
         for (const auto &value : row.cood)
        {
             std::cout << value << " ";
         }
         std::cout << std::endl;
        // std::cout << row.cood
    }

    Point pred = {{13116, 3, 0.835, 0.782, 8 - 4.256, 0.102, 0.228, 0, 0.108, 0.645, 128.021, 230435}};

    std::vector<std::pair<double, int>> result2 = KNN(train, pred);

    std::sort(result2.begin(), result2.end(), compareByDouble);

    int k = 10;
    int i = 0;
    for (const auto &element : result2)
    {
        if(i<k){
             std::cout << "distance: " << element.first << ", index: " << element.second << std::endl;
             i = i + 1;
        }
    }
}