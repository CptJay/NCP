//
// Created by nr1sl on 1/26/2023.
//

#include "Calculator.h"



void Calculator::Bereken() {

}



pair<int,string> Calculator::Haakjes(int index, vector<string>Vector,string type){
    int x;
    vector<string> temp = {};
    for(int i = 0; i< index;i++){
        temp.emplace_back(Vector[i]);
    }
    vector<string> tem = {};
    for(int i = index+1; i < Vector.size();i++){
        if(Vector[i] == ")"){
            x = i;
            break;
        }
        tem.emplace_back(Vector[i]);
    }
    return {x,Double_Oefening(type,tem)[0]};
}

vector<string> Change_vector(int begin, int end, vector<string> V, const string &new_value){
    vector<string> temp = {};
    for(int i=0; i < begin; i++){
        temp.emplace_back(V[i]);
    }

    temp.emplace_back(new_value);
    for(int i=end+1;i<V.size();i++){
        temp.emplace_back(V[i]);
    }
    return temp;
}

// 9 + 5 + 40 + 9
vector<string> Calculator::Double_Oefening(string type, vector<string>V) {
    int tempNames {};
    vector<string>a {};
    vector<string>b {};
    int new_value {};
    string Wat_is_het = "niks";
    int n = 1;
    while(V.size() != n){
        int index = 0;
        while(true){
            if(V[index] == "("){
                //int1 geeft sluitend haakje
                //int2 is de value
                pair<int,string> new_values = Haakjes(index,V,type);
                V.erase(V.begin()+index, V.begin() + new_values.first);
                V.insert(V.begin()+index, V.begin(), V.end());
                //V = Change_vector(index,new_values.first,V, new_values.second);
                index = 0;
            }
            if(index == V.size()-1){
                break;
            }
            index++;
        }
        index = 0;
        while(true){
            if(V[index] =="*" or V[index] == "/"){
                string Before = V[index-1];
                string After = V[index+1];
                int x;
                int y;

                if(Map_Vriable.contains(Before)){
                    if(Map_Vriable[Before].second == "Matrix"){
                        // matrices kunnen niet delen
                        if (V[index] == "/"){ // el1 * el2
                            cout << "Error: Matrices kunnen niet delen";
                        }
                        a = Map_Vriable[Before].first;
                        Wat_is_het = "Matrix";
                    }
                    else if(Map_Vriable[Before].second == "Vector"){

                    }
                    else{
                        x = stoi(Map_Vriable[Before].first[0]);
                    }
                }
                else{
                    x = stoi(Before);
                }

                if(Map_Vriable.contains(After)){
                    if(Map_Vriable[After].second == "Matrix"){
                        b = Map_Vriable[After].first;
                        Wat_is_het = "Matrix";
                    }
                    else if(Map_Vriable[After].second == "Vector"){

                    }
                    else{
                        y = stoi(Map_Vriable[After].first[0]);
                    }
                }
                else{
                    y = stoi(After);
                }
                if (Wat_is_het == "Matrix"){
                    vector<string> newMatrix = evaluateMatrixExpression(helper_vecString_to_Matrix(a),helper_vecString_to_Matrix(b),V[index][0]);
                    Map_Vriable.insert({"_" + to_string(tempNames),{newMatrix, "Matrix"}});
                    V = Change_vector(index-1,index+1,V, "_" + to_string(tempNames));
                    tempNames++;
                }
                else if (Wat_is_het == "Vector"){
                    vector<string> newVector = EvaluateVectorExpression(helper_Vector_to_String(a),helper_Vector_to_String(b),V[index][0]);
                    Map_Vriable.insert({"_" + to_string(tempNames),{newVector, "Vector"}});
                    V = Change_vector(index-1,index+1,V, "_" + to_string(tempNames));
                    tempNames++;
                }
                else {
                    new_value = evaluateExpression(x,y,V[index][0]);
                    V = Change_vector(index-1,index+1,V, to_string(new_value));
                }
                index = 0;
            }
            if(index == V.size()-1){
                break;
            }
            index++;
        }
        index = 0;
        while(true){
            if (V[index] == "+" || V[index] == "-"){
                string Before = V[index-1];
                string After = V[index+1];
                int x;
                int y;
                if(Map_Vriable.contains(Before)){
                    if(Map_Vriable[Before].second == "Matrix"){
                        a = Map_Vriable[Before].first;
                        Wat_is_het = "Matrix";
                    }
                    else if(Map_Vriable[Before].second == "Vector"){

                    }
                    else{
                        x = stoi(Map_Vriable[Before].first[0]);
                    }
                }
                else{
                    x = stoi(Before);
                }
                if(Map_Vriable.contains(After)){
                    if(Map_Vriable[After].second == "Matrix"){
                        b = Map_Vriable[Before].first;
                        Wat_is_het = "Matrix";
                    }
                    else if(Map_Vriable[After].second == "Vector"){

                    }
                    else{
                        y = stoi(Map_Vriable[After].first[0]);
                    }
                }
                else{
                    y = stoi(After);
                }
                if(Wat_is_het == "Matrix"){
                    vector<string> newMatrix = evaluateMatrixExpression(helper_vecString_to_Matrix(a),helper_vecString_to_Matrix(b),V[index][0]);
                }
                else if(Wat_is_het == "Vector"){

                }
                else{
                    new_value = evaluateExpression(x,y,V[index][0]);
                }
                V = Change_vector(index-1,index+1,V, to_string(new_value));
                index = 0;
            }
            if(V.size() == 1){
                break;
            }
            index++;
        }
    }
    return V;
}




void Calculator::Oefeningen(map<vector<string>, vector<string>>Mappen) {
    for(const auto &i:Mappen){
        Double_Oefening(i.first[0],i.second);
        cout<<i.first[1] <<"=";
        for(const auto &j:Map_Vriable[i.first[1]].first){
            cout<<j<<endl;
        }
    }
}

bool Calculator::sign_check(vector<string>v){
    for(auto i:v){
        if(i == "+" | i == "-" | i == "*" | i == "/"){
            return true;
        }
    }
    return false;
}

Calculator::Calculator(map<vector<string>, vector<string>> m) {
    for(const auto &i: m){
        if(i.second.size() == 1){
            Map_Vriable[i.first[1]] = {i.second,i.first[0]};
        }
        if((i.first[0] == "Vector" or i.first[0] == "Matrix") and !sign_check(i.second)){
            Map_Vriable[i.first[1]] = {i.second,i.first[0]};
        }
    }
    Oefeningen(m);

}


vector<string> Calculator::helper_Matrix_to_vecString(vector<std::vector<double>> temp){
    vector<string> return_string;
    for(auto i:temp){
        for(auto j:i){
            return_string.emplace_back(to_string(j));
        }
            return_string.emplace_back("|");
    }
    return return_string;
}

vector<vector<double>> Calculator::helper_vecString_to_Matrix(vector<string> temp){
    vector<vector<double>> return_double;
    vector<double> row;

    for (const auto& el : temp) {
        if (el == "[" || el == "]"){
            continue;
        }
        if (el == "|"){
            return_double.emplace_back(row);
            row.clear();
            continue;
        }
        row.emplace_back(stoi(el));
    }
    return return_double;
}

vector<string> Calculator::helper_vecString_to_Vector(vector<double> temp){
    vector<string> temporary_vec;
    for(auto i:temp){
        temporary_vec.emplace_back(to_string(i));
    }
    return temporary_vec;
}

vector<double> Calculator::helper_Vector_to_String(vector<string> temp){
    vector<double> temporary_vec;
    for(auto i:temp){
        temporary_vec.emplace_back(stoi(i));
    }
    return temporary_vec;
}





vector<string> Calculator::EvaluateVectorExpression(const std::vector<double> vec1, const std::vector<double> vec2,char op){
    switch(op){
        case '+':
            return helper_vecString_to_Vector(tm.add_vectors(vec1,vec2));
        case '-':
            return helper_vecString_to_Vector(tm.subtract_vectors(vec1, vec2));
        case '*':
            return helper_vecString_to_Vector(tm.multiply_vectors(vec1, vec2));
    }
}

vector<string> Calculator::evaluateMatrixExpression(const vector<std::vector<double>> &mat1, const vector<std::vector<double>> &mat2, char op){
    switch(op){
        case '+':
            return helper_Matrix_to_vecString(tm.add_matrices(mat1,mat2));
        case '-':
            return helper_Matrix_to_vecString(tm.subtract_matrices(mat1, mat2));
        case '*':
            return helper_Matrix_to_vecString(tm.multiply_matrices(mat1, mat2));
    }
}



int Calculator::evaluateExpression(int val1, int val2, char op) {
    switch (op) {
        case '+': return tm.add(val1, val2);
        case '-': return tm.subtract(val1, val2);
        case '*': return tm.multiply(val1, val2);
        case '/': return tm.divide(val1, val2);
    }
}

vector<string> Calculator::helper_poly_to_vecString(vector<double> temp) {
    // [2, 4, -1] -->  ["2x^2", "+", 4x^1, "+", -1]
    string delimiter = "x^";
    vector<string> result;

    for (int i = 0; i < temp.size()-1; i++) {
        //cout << temp[i] << delimiter << temp.size()-i-1 << " + ";
        result.push_back(to_string(temp[i]));
        result.emplace_back("+");
    }
    //cout << temp[temp.size()-1] << endl;
    result.push_back(to_string(temp[temp.size()-1]));
    return result;
}

vector<double> Calculator::helper_vecString_to_poly(vector<string> temp) {
    // ["2x^2", "+", 4x^1, "+", -1] --> [2, 4, -1]
    vector<double> result;
    string delimiter = "x^";
    string token;
    map<string,pair<vector<string>,string>>::iterator it;

    for (int i = 0; i < temp.size()-1; i++){
        if (temp[i] == "+" || temp[i] == "-"){ // niet zeker over "-"
            continue;
        }

        // wat als je een variabele gebruikt dat een polynomial is
        it = Map_Vriable.find(temp[i]);
        if (it != Map_Vriable.end()){ // niet 100%
            if (Map_Vriable[temp[i]].second == "Double"){
                result.emplace_back(stod(Map_Vriable[temp[i]].first[0]));
                continue;
            }
            // geen double

        }
        size_t found = temp[i].find(delimiter);
        if (found == string::npos){
            cout << "Error: Geen geldig getal in polynomial.";
            exit(0);
        }
        token = temp[i].substr(0, found);
        result.emplace_back(stod(token));
    }
    it = Map_Vriable.find(temp[temp.size()-1]);
    if (it != Map_Vriable.end()){
        if (Map_Vriable[temp[temp.size()-1]].second == "Double"){
            result.emplace_back(stod(Map_Vriable[temp[temp.size()-1]].first[0]));
        }
    } else{
        result.emplace_back(stod(temp[temp.size()-1]));
    }

    return result;
}

