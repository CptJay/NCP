//
// Created by nr1sl on 12/1/2022.
//

#include "Objects.h"

Objects::Objects(){}

Objects::Objects(bool t, string N): terminal(t), Naam(N)  {}

void Objects::SetProducts(vector<Objects*> O){
    products.push_back(O);
}

const vector<vector<Objects*>> &Objects::getProducts() const {
    return products;
}

string Objects::getnaam(){
    return Naam;
}

bool Objects::HelperSearch(string str){
    ////Hier wordt gekeken of de string door een var wordt geproduceert of niet
    bool True = false;
    if(Naam == "Function"){
        string word;
        if(str.size()<4){
            return false;
        }
        word = str.substr(0,3);
        if(!FunctionHelper(word)){
            return false;
        }
        word.clear();
        word += str[3];
        if(!FunctionHelper(word)){
            return false;
        }
        word = str.substr(4,str.size()-1);
        word.pop_back();
        if(!FunctionHelper(word)){
            return false;
        }
        word = str.substr(str.size()-1,str.size()-1);
        return FunctionHelper(word);
    }
    else if(Naam == "Variable"){
        if(str.size()<4){
            return  false;
        }
        string word;
        bool WentInside = false;
        for(auto i:str){
            if(i == '(' || i == ')'){
                WentInside = true;
                string temp;
                temp+= i;
                if(!products[0][0]->HelperSearch(word)){
                    return false;
                }
                if(!FunctionHelper(temp)){
                    return false;
                }
                word.clear();
                continue;
            }
            word += i;
        }
        if(WentInside){
            return true;
        }
        return false;
    }
    else if(Naam == "Var"){
        for(auto i:str){
            if(i == str[0]){
                string letter;
                letter.push_back(i);
                True = Alhphabet(letter);
                if(!True){
                    return false;
                }
            }
            else{
                True = VarHelper(str.substr(1,str.size()-1));
            }
        }
        return True;
    }
    else if(Naam == "Getal"){
        for(auto i:str){
            string letter;
            letter.push_back(i);
            True = Nummer(letter);
        }
        return True;
    }
    else if(Naam == "Komma"){
        bool komma = false;
        string getal1;
        string getal2;
        for(int i=0;i<str.size();i++){
            if(str[i] == '.'){
                komma = true;
                getal1 = str.substr(0,i);
                getal2 = str.substr(i+1,str.size()-1);
                for(auto j:getal1){
                    string g;
                    g.push_back(j);
                    if(!NummerKomma(g)){
                        return false;
                    }
                }
                for(auto k:getal2){
                    string g;
                    g.push_back(k);
                    if(!NummerKomma(g)){
                        return false;
                    }
                }
            }
        }
        return komma;
    }
    for(auto i:products){
        for(auto j:i){
            if(j->Naam == str){
                 return true;
             }
        }
    }
    return false;
}

bool Objects::FunctionHelper(string str){
    bool erin = false;
    for(auto i:products){
        for(auto j:i){
            if(str == j->Naam){
                return true;
            }
            else if(str == j->Naam){
                return true;
            }
            else if(!j->terminal){
                erin = j->HelperSearch(str);
            }
            if(erin){
                return erin;
            }
        }
    }
    return false;
}

bool Objects::VarHelper(string str) {
    for(auto i:products){
        for(auto j:i){
            if(j->Naam == "Getal"){
                return j->FunctionHelper(str);
            }
        }
    }
    return false;
}

bool Objects::Alhphabet(string str){
    for(auto l:products[0][0]->products){
        for(auto j:l){
            if(j->Naam == str){
                return true;
            }
        }
    }
    return false;
}

bool Objects::Nummer(string str){
    for(auto i:products[0][0]->products){
        for(auto j:i){
            if(j->Naam == str){
                return true;
            }
        }
    }
    return false;
}

bool Objects::NummerKomma(string str){
    for(auto i:products[0][0]->products[0][0]->products){
        for(auto j:i){
            if(j->Naam == str){
                return true;
            }
        }
    }
    return false;
}

bool Objects::getterminal(){
    return terminal;
}