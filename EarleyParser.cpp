//
// Created by nr1sl on 11/28/2022.
//

#include "EarleyParser.h"
#include <fstream>

EarleyParser::EarleyParser() {}

EarleyParser::EarleyParser(string str) {
    ifstream input(str);
    json j;
    input>>j;
    for(auto l:j["Variable"]){
        Objects* ob = new Objects(false,l);
        V[l] = ob;
    }
    for(auto i:j["Production"]){
        vector<Objects*> The_Productions;
        if(i["head"] == "Alphabet" || i["head"] == "Nummer"){
            for(auto k:i["body"]) {
                Objects *ob = new Objects(true, k);
                The_Productions.push_back(ob);
                V[i["head"]]->SetProducts(The_Productions);
                The_Productions.clear();
            }
            continue;
        }
        for(auto k:i["body"]){
            if(!V.contains(k)){
                Objects* ob = new Objects(true,k);
                The_Productions.push_back(ob);
            }
            else{
                The_Productions.push_back(V[k]);
            }
        }
        V[i["head"]]->SetProducts(The_Productions);
    }
    if(V.contains(j["Start"][0])){
        S = V[j["Start"][0]];
    }
}

void EarleyParser::accepting(EarleyParser& second, string str){
    ifstream newfile(str);
    string lines;
    while(getline(newfile,lines)){
        map<string,bool> twotime;
        cout<<lines;
        int state =0;                                                                   // verschillende state voor elk dot beweging
        int chart = 0;                                                                  // chart zegt in welk fase wij zitten
        bool Break = false;                                                             // als er foute input is
        map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>> Tabel;
        TabelVullenSecond(second,second.S,Tabel,state,chart);
        stringstream ss(lines);
        string word;
        if(lines == "\r" or lines[0] == '#'){
            continue;
        }
        while(getline(ss,word,' ')){
            if(word[0] == '#'){
                break;
            }
            if(word[word.size()-1] == '\r'){
                word.pop_back();
            }
            if(word[word.size()-1] == ';' or word[0] == '[' or word[0] == '('){  // door deze else if mogen mensen ';' plakken op het einde
                string dotkomma = word.substr(word.size()-1, word.size()-1);
                word.pop_back();
                if(word[word.size()-1] == ']' or (word[word.size()-1] == ')' and word.size() == 2)){
                    string st = word.substr(word.size()-1,word.size()-1);
                    word.pop_back();
                    Break = !Search(word,Tabel,second,state,chart,twotime);
                    if(Break){
                        break;
                    }
                    word = st;
                }
                Break = !Search(word,Tabel,second,state,chart,twotime);
                if(Break){
                    break;
                }
                chart++;
                Break = !Search(dotkomma,Tabel,second,state,chart,twotime);
            }
            else if(!Search(word,Tabel,second,state,chart,twotime)){
                Break =true;
                break;
            }
            chart++;
        }
        if(Break or !LastChart(Tabel,chart-1)){
            cout<<"Er is een foutje";
            break;
        }
        Contains.clear();
    }
}

void EarleyParser::TabelVullenSecond(EarleyParser& second, Objects* ob,map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel, int& state,int& chart){
    for(auto i:ob->getProducts()){
        state++;
        Tabel[{{ob,chart},state}] = {0,i};
        Contains[{0,i}] = true;
        if(second.V.contains(i[0]->getnaam()) and i[0] != ob){
            TabelVullenSecond(second,i[0],Tabel,state,chart);
        }
    }
}

bool EarleyParser::Search(string str,map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel,EarleyParser& second, int& state, int& chart,map<string,bool>& twotime){
    bool Erin = false;
    for(auto i:V){
        if(i.second->HelperSearch(str)){
            OneDotAhead(i.first,Tabel,second,state,chart,twotime);
            Erin = true;
        }
    }
    return Erin;
}

void EarleyParser::OneDotAhead(string str,map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel,EarleyParser& second, int& state, int& chart, map<string,bool>& twotime){
    if(twotime.contains(str)){
        return;
    }
    map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>> temporary = Tabel;
    for(auto i:Tabel){
        int j = i.second.first;
        if(i.second.first >= i.second.second.size()){
            continue;
        }
        else if(i.second.second[j]->getnaam() == str ){
            if(!Contains.contains({j+1,i.second.second})){
                state++;
                temporary[{{i.first.first.first,chart},state}] = {j+1,i.second.second};
                Contains[{j+1,i.second.second}] = true;
            }
            if(j+1 == i.second.second.size()){
                OneDotAhead(i.first.first.first->getnaam(),temporary,second,state,chart,twotime);
            }
            if(j+1 != i.second.second.size() and !i.second.second[j+1]->getterminal()){
                TabelVullenSecond(second,i.second.second[j+1],temporary,state,chart);
                twotime[i.second.second[j+1]->getnaam()] = true;
            }
        }
    }
    Tabel = temporary;
}

bool EarleyParser::LastChart(map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel, int chart){
    vector<pair<int,vector<Objects*>>> temporary;
    for(auto i:Tabel){
        if(i.first.first.second == chart){
            temporary.push_back(i.second);
        }
    }
    for(auto i:temporary){
        if(i.first != i.second.size()){
            return false;
        }
    }
    return true;
}