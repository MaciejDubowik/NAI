#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>

using namespace std;
using fun = function<double(vector<double>)>;
using operation = map<string,fun>;

void returnResult(map<string,fun> function, vector<string> arguments) {
    auto selectedFunction = function[arguments.at(1)];
    vector<double> vector;
    for(int i = 2 ; i < arguments.size() ; i++){
        vector.push_back(stod(arguments.at(i)));
    }
    cout << selectedFunction(vector);
}


int main(int argc, char **argv) {
    operation operations;

    operations["sin"] = [](vector<double> v) {return sin(v[0]);};
    operations["add"] = [](vector<double> v) {return v[0]+v[1];};
    operations["mod"] = [](vector<double> v) {return fmod(v[0],v[1]);};

    try {
        vector<string> arguments(argv, argv + argc);
        returnResult(operations, arguments);
    }
    catch (bad_function_call e){
        cout << "Błąd - zła nazwa funkcji" << endl;
    }

    return 0;
}
