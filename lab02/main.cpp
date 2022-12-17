#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <map>
#include <chrono>
#include <fstream>

using namespace std;

using domain_t = vector<double>;
random_device rd;
mt19937 mt_generator(rd());

auto brute_force = [](auto f, auto domain_generator, int iterations) {
    auto start = chrono::high_resolution_clock::now();
    auto current_p = domain_generator();
    auto best_point = current_p;

    for (int i = 0; i < iterations; ++i) {
        if (f(current_p) < f(best_point)) {
            best_point = current_p;
        }
        current_p = domain_generator();
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    return pair(best_point, elapsed_time);
};

int main(int argc, char **argv) {
    map<string, function<double(vector<double>)>> operations;
    vector<string> arguments(argv, argc + argv);

    operations["Himmelblau"] = [](domain_t x) { return pow((pow(x[0],2) + x[1] - 11),2) + pow((x[0] + pow(x[1],2) - 7),2); };
    operations["Beale"] = [](domain_t x) {return pow((1.5-x[0]+x[0]*x[1]),2) + pow(2.25-x[0]+x[0]*x[1]*x[1],2) + pow(2.265-x[0]+x[0]*x[1]*x[1]*x[1],2);};
    operations["Booth"] = [](domain_t x) {return pow((x[0]+ 2*x[1] - 7),2) + pow((2*x[0]+x[1]-5),2);};

    auto getPoint = [=]() -> domain_t {
        uniform_real_distribution<double>distr(stod(arguments.at(2)), stod(arguments.at(3)));
        return {distr(mt_generator), distr(mt_generator)};
    };

    try {
        vector<pair<domain_t, long long>> results;

        for (int i = 0; i < 20; ++i) {
            auto result = brute_force(operations.at(arguments.at(1)), getPoint, 1000);
            results.push_back(result);
        }

        ofstream output_file("/Users/maciejdubowik/Desktop/NAI/lab02/results.txt");

        for (const auto& result : results) {
            output_file << result.second << " " << result.first[0] << " " << result.first[1] << endl;
            cout << result.second << " " << result.first[0] << " " << result.first[1] << endl;
        }

        output_file.close();
    }
    catch (bad_function_call e){
        cout << "Błąd - zła nazwa funkcji" << endl;
    }

    return 0;
}