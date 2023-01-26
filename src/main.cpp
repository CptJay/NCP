#include <iostream>
#include "UniversalTuringMachine.h"
#include "Track.h"
#include "EarleyParser.h"
#include "Computing.h"
using namespace std;

vector<string> stringToVector(const string& input) {
    vector<string> result {};
    for (auto i:input) {
        result.emplace_back(1,i);
    }
    return result;
}

//int turingMachineProduct(UniversalTuringMachine& t, int x, int y) {
//    vector<string> result = {};
//    for (int i = 0; i < x; ++i) {
//        result.emplace_back("1");
//    }
//    result.emplace_back("C");
//    for (int i = 0; i < y; ++i) {
//        result.emplace_back("1");
//    }
//    result = t.calculate(result, "testing_files/MultiplicationTM.json");
//    return (int) result.size();
//}



int main() {
    /*
    TuringMachine t("testing_files/exampleTM.json");
    cout << boolalpha << t.accepts({"A","A"});
     */
    EarleyParser first("../testing_files/First_cfg.json");
    EarleyParser second("../testing_files/Second_cfg.json");
    first.accepting(second,"../testing_files/NCP_Input.txt");
//    accepteert 0^(2^n) met n >= 0
    UniversalTuringMachine t;
    Computing tm;
    cout << boolalpha << t.accepts(stringToVector("00000000000000000"), "../testing_files/TMtest1.json")<<endl;
    cout << t.divide(8,2).size() << endl;


    bool computingTests = true;
    if (computingTests){
        cout << endl << "Computing Tests" << endl << "---------------" << endl;

        cout << "*Adding Polynomials: " << endl;
        vector<double> res =  tm.addPolynomials({2, 4}, {3, 2});
        for (int i = 0; i < res.size()-1; i++) {
            cout << res[i] << "x^" << res.size()-i-1 << " + ";
        }
        cout << res[res.size()-1] << endl;

        cout << "*Subtracting Polynomials: " << endl;
        res =  tm.subtractPolynomials({2, 4}, {3, 2});
        for (int i = 0; i < res.size()-1; i++) {
            cout << res[i] << "x^" << res.size()-i-1 << " + ";
        }
        cout << res[res.size()-1] << endl;

        cout << "*Multiplying Polynomials: " << endl;
        res =  tm.multiplyPolynomials({2, 4}, {3, 2});
        for (int i = 0; i < res.size()-1; i++) {
            cout << res[i] << "x^" << res.size()-i-1 << " + ";
        }
        cout << res[res.size()-1] << endl;

        cout << "*Dividing Polynomials: " << endl;
        // hier klopts iets niet
        res =  tm.divide_polynomials({8, 9, 4}, {3, 2});
        for (int i = 0; i < res.size()-1; i++) {
            cout << res[i] << "x^" << res.size()-i-1 << " + ";
        }
        cout << res[res.size()-1] << endl;

        cout << "*Deriving Polynomial" << endl;
        res = tm.derive({10, 5, 2, 3});
        for (int i = 0; i < res.size()-1; i++) {
            cout << res[i] << "x^" << res.size()-i-1 << " + ";
        }
        cout << res[res.size()-1] << endl;

        cout << "*Integrating Polynomial" << endl;
        res = tm.integrate({5, 2, 3});
        for (int i = 0; i < res.size()-1; i++) {
            cout << res[i] << "x^" << res.size()-i << " + ";
        }
        cout << res[res.size()-1] << "x^1 + c" << endl;


    }

    return 0;
}