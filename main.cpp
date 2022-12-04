#include <iostream>
#include "UniversalTuringMachine.h"
using namespace std;

vector<string> stringToVector(const string& input) {
    vector<string> result {};
    for (auto i:input) {
        result.emplace_back(1,i);
    }
    return result;
}

int main() {
//    accepteert 0^(2^n) met n >= 0
    UniversalTuringMachine t("../TMtest1.json");
    cout << boolalpha << t.start(stringToVector("0000000000000000"));
    return 0;
}