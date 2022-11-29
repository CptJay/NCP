#include <iostream>
#include "TuringMachine.h"

int main() {
    TuringMachine t("../exampleTM.json");
    cout << boolalpha << t.accepts({"A","A"});
    return 0;
}