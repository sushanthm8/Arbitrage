#include <iostream>
#include <fstream>
#include <vector>
#include <tgmath.h>
#include <limits>
using namespace std;

//conversion rate is relative to 1 USD

struct Currency {
    string symbol = "";
    float rate = 0.0;
    int index = 0;
};

int main() {
    //read data file
    std::ifstream data_file;
    data_file.open("data/data.txt");
    int counter = 0;
    vector<Currency> currencies(161);
    while(counter < 161){
        data_file >> currencies[counter].symbol >> currencies[counter].rate;
        currencies[counter].index = counter;
        counter++;
    }
    data_file.close();
    //make 2d vector with all currencies exchange rates
    vector< vector<float> > conversions(161, vector<float>(161));
    for (int i = 0; i < currencies.size(); i++) {
        for (int j = 0; j < currencies.size(); j++) {
            conversions[i][j] = -1*log(currencies[i].rate/currencies[j].rate);
            // cout << conversions[i][j] << " ";
        }
        // cout << endl;
    }

    //perform bellman-ford
    vector<float> distance(161);
    vector<float> previous(161);
    for(int i = 0; i < 161; i++) {
        distance[i] = std::numeric_limits<double>::infinity();
        previous[i] = -1;
    }
    int source = 0;
    distance[source] = 0;

    //Relax edges
    for (int i = 0; i < 161; i++) {
        for (int j = 0; j < 161; j++) {
            for (int k = 0; k < 161; k++) {
                if(distance[k] > distance[j] + conversions[j][k]) {
                    distance[k] = distance[j] + conversions[j][k];
                    previous[k] = j;
                }
            }
        }
    }

    //check if it's possible to still relax edges
    std::ofstream out_file;
    out_file.open("out.txt");
    out_file << "Arbitrage Opportunity: \n";
    // vector<vector<int>> opportunities;
    for (int j = 0; j < 161; j++) {
        for (int k = 0; k < 161; k++) {
            if(distance[k] > distance[j] + conversions[j][k]) {
                //We have a cycle
                vector<int> cycle;
                cycle.push_back(j);
                cycle.push_back(k);
                while(find(cycle.begin(),cycle.end(),previous[j]) != cycle.end()) {
                    cycle.push_back(previous[j]);
                    j = previous[j];
                }
                cycle.push_back(previous[j]);
                for (int i = cycle.size()-1; i > -1; i--) {
                    out_file << currencies[cycle[i]].symbol << " ";
                }
                out_file << endl;
            }
        }
    }
    out_file.close();
    return 0;
}