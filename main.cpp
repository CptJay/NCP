#include <iostream>
#include "UniversalTuringMachine.h"
#include "Track.h"
#include "EarleyParser.h"
using namespace std;

vector<string> stringToVector(const string& input) {
    vector<string> result {};
    for (auto i:input) {
        result.emplace_back(1,i);
    }
    return result;
}

int turingMachineProduct(UniversalTuringMachine& t, int x, int y) {
    vector<string> result = {};
    for (int i = 0; i < x; ++i) {
        result.emplace_back("1");
    }
    result.emplace_back("C");
    for (int i = 0; i < y; ++i) {
        result.emplace_back("1");
    }
    result = t.calculate(result, "MultiplicationTM.json");
    return (int) result.size();
}



int main() {
    /*
    TuringMachine t("../exampleTM.json");
    cout << boolalpha << t.accepts({"A","A"});
     */
    EarleyParser first("First_cfg.json");
    EarleyParser second("Second_cfg.json");
    first.accepting(second,"NCP_Input.txt");
//    accepteert 0^(2^n) met n >= 0
    UniversalTuringMachine t;
    cout << boolalpha << t.accepts(stringToVector("00000000000000000"), "TMtest1.json");
    return 0;
}