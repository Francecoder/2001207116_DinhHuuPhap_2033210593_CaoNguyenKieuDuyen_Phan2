#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;

struct City {
    string name;
    double x;
    double y;


    double distanceTo(const City& other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

bool readData(const string& filename, vector<City>& cities, string& startCity) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file" << endl;
        return false;
    }

    int numCities;
    inFile >> numCities;
    inFile.ignore();

    cities.resize(numCities);
    for (int i = 0; i < numCities; ++i) {
        inFile >> cities[i].name >> cities[i].x >> cities[i].y;
    }

    inFile >> startCity;
    inFile.close();

    return true;
}

void calculateDistances(const vector<City>& cities, vector<vector<double>>& dist) {
    int numCities = cities.size();
    dist.resize(numCities, vector<double>(numCities));

    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            dist[i][j] = cities[i].distanceTo(cities[j]);
        }
    }
}

void greedyTSP(const vector<vector<double>>& dist, int startCityIndex, vector<int>& tour, double& totalDistance) {
    int numCities = dist.size();
    vector<bool> visited(numCities, false);
    int currentCity = startCityIndex;
    visited[currentCity] = true;
    tour.push_back(currentCity);

    for (int i = 1; i < numCities; ++i) {
        double minDist = numeric_limits<double>::max();
        int nextCity = -1;
        for (int j = 0; j < numCities; ++j) {
            if (!visited[j] && dist[currentCity][j] < minDist) {
                minDist = dist[currentCity][j];
                nextCity = j;
            }
        }
        visited[nextCity] = true;
        tour.push_back(nextCity);
        currentCity = nextCity;
    }

    tour.push_back(startCityIndex);

    totalDistance = 0.0;
    for (int i = 0; i < numCities; ++i) {
        totalDistance += dist[tour[i]][tour[i + 1]];
    }
}

void outputResults(const vector<City>& cities, const vector<int>& tour, double totalDistance) {
    cout << "Tour order: ";
    for (int i = 0; i < tour.size(); ++i) {
        cout << cities[tour[i]].name;
        if (i < tour.size() - 1) {
            cout << "-";
        }
    }
    cout << endl;
    cout << "Total distance: " << fixed << setprecision(2) << totalDistance << endl;

    ofstream outFile("output_bai1.txt");
    if (!outFile) {
        cerr << "Error opening file for writing" << endl;
        return;
    }
    outFile << "Tour order: ";
    for (int i = 0; i < tour.size(); ++i) {
        outFile << cities[tour[i]].name;
        if (i < tour.size() - 1) {
            outFile << "-";
        }
    }
    outFile << endl;
    outFile << "Total distance: " << fixed << setprecision(2) << totalDistance << endl;
    outFile.close();
}

int main() {
    vector<City> cities;
    string startCity;
    if (!readData("input_bai1.txt", cities, startCity)) {
        return 1;
    }

    int startCityIndex = -1;
    for (int i = 0; i < cities.size(); ++i) {
        if (cities[i].name == startCity) {
            startCityIndex = i;
            break;
        }
    }

    if (startCityIndex == -1) {
        cerr << "Start city not found in the list" << endl;
        return 1;
    }

    vector<vector<double>> dist;
    calculateDistances(cities, dist);

    vector<int> tour;
    double totalDistance;
    greedyTSP(dist, startCityIndex, tour, totalDistance);

    outputResults(cities, tour, totalDistance);

    return 0;
}

