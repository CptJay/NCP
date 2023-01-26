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

    ////Hier maak ik alle varaibles aan

    for(auto l:j["Variable"]){
        Objects* ob = new Objects(false,l);
        V[l] = ob;
        if(l == "Var"){
            Variable_Object = &*ob;
        }
    }

    ////Hier geef ik al de variable hun eigen productie
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

    ////Start symbol

    if(V.contains(j["Start"][0])){
        S = V[j["Start"][0]];
    }
}

void EarleyParser::accepting(EarleyParser& second, string str){
    ////Open de file
    ifstream newfile(str);
    string lines;
    if (!newfile.is_open()){
        cout << "Unable to open file";
        exit(0);
    }
    while(getline(newfile,lines)){
        map<string,bool> twotime;
        int state =0;                                                                   // verschillende state voor elk dot beweging
        int chart = 0;                                                                  // chart zegt in welk fase wij zitten
        bool Break = false;     // als er foute input is
        Equal_sign = false;
        map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>> Tabel;             //Hie hou ik alles bij van dots verplaatsing
        TabelVullenSecond(second,second.S,Tabel,state,chart);
        stringstream ss(lines);
        string word;

        ////Als het # of \r is moet je die lijn skippen
        if(lines == "\r" or lines[0] == '#'){
            continue;
        }

        /////String word verdeelt in kleinere stukken
        while(getline(ss,word,' ')){
            if(word == "="){
                Equal_sign = true;
            }
            if(word[0] == '#' or word == "\r"){
                ////Na #heb jij commentaren
                break;
            }
            if(!Equal_sign and !Bestaand_Variable.contains(word)){
                Bestaand_Variable[word] = true;
            }

            if(word[word.size()-1] == '\r'){
                ////Bij de laaste woord van de zin heb jij \r aan het uiteinde
                word.pop_back();
            }
            ////Woorden dat beginnen met [ worden onderbroken
            if(word[0] == '['){
                string BeginChar = {word[0]};
                Break = !Search(BeginChar,Tabel,second,state,chart,twotime);
                if(Break){
                    break;
                }
                chart++;
                word.erase(word.begin());
                Break = !Search(word,Tabel,second,state,chart,twotime);
                if(Break){
                    break;
                }
                Break = !Variable_check(word);
                if(Break){
                    break;
                }
            }
            ////Woorden dat begint met ( wordt in drie stukken verddelt. (, midden en )
            else if(word[0] == '(' && word[word.size()-1] == ')'){
                string dotkomma = word.substr(word.size()-1, word.size()-1);
                word.pop_back();

                string st = word.substr(word.size()-1,word.size()-1);
                word.pop_back();
                Break = !Search(word,Tabel,second,state,chart,twotime);
                if(Break){
                    break;
                }
                chart++;
                word = st;
                Break = !Search(word,Tabel,second,state,chart,twotime);
                if(Break){
                    break;
                }
                Break = Variable_check(word);
                if(Break){
                    break;
                }

                chart++;
                Break = !Search(dotkomma,Tabel,second,state,chart,twotime);
                if(Break){
                    break;
                }
            }
            ////Woorden dat eindigen met ; moet in stukken gekeken worden
            else if((word[word.size()-1] == ';') && word.size() != 1){          // door deze else if mogen mensen ';' plakken op het einde
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

            ////normale woorden zoals 2,2x,a,+ etc worden hier gekeken
            else if(!Search(word,Tabel,second,state,chart,twotime)){
                Break =true;
                break;
            }
            chart++;
        }

        ////Break wilt zeggen als er geen enkel Variable is die de woord heeft als productie
        ////LastChart Kijkt of de dot op het einde is gekomen
        if(Break or !LastChart(Tabel,chart-1)){
            cout<<"Er is een foutje in lijn: " + word <<endl;
            exit(0);
        }
        cout<<lines<<endl;
        Contains.clear();
    }
}

bool EarleyParser::Variable_check(string word){
    if(Equal_sign and !Bestaand_Variable.contains(word) and Variable_Object->HelperSearch(word)){
        return false;
    }
    return true;
}

void EarleyParser::TabelVullenSecond(EarleyParser& second, Objects* ob,map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel, int& state,int& chart){
    ////Hier wordt de tabel voor eerst ingevult door produtie van de startsymbol
    ////Het wordt later gebruikt als wij produtie van bepaalte variable in tabel moeten doen
    for(auto i:ob->getProducts()){
        state++;
        Tabel[{{ob,chart},state}] = {0,i};
        Contains[{0,i}] = true;
        if(second.V.contains(i[0]->getnaam()) and i[0] != ob){
            ////Het wordt recursive gedaan want als de eerst symbol van de proudtie een variable is, dan moet men de productie van die variable ook in de tabel doen
            TabelVullenSecond(second,i[0],Tabel,state,chart);
        }
    }
}

bool EarleyParser::Search(string str,map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel,EarleyParser& second, int& state, int& chart,map<string,bool>& twotime){
    ////Deze funtie doorzoekt Variables om te zien of een van de vraible de gegeven string produceert
    bool Erin = false;
    for(auto i:V){
        if(i.second->HelperSearch(str)){
            if(OneDotAhead(i.first,Tabel,second,state,chart,twotime)){
                Erin = true;
            }
        }
    }
    return Erin;
}

bool EarleyParser::OneDotAhead(string str,map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel,EarleyParser& second, int& state, int& chart, map<string,bool>& twotime){
    ////Hiet wordt de dot een plaats naar rechts vertplaats als wij een Variable hebben gevonden die de string produceert.
    ////Het Gevonden variable moet het variable zijn waar de dot zich bevind in de tabel met producties
    map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>> temporary = Tabel;
    bool erin = false;
    for(auto i:Tabel){
        ////Wij loopen door alle producties in tabel
        int j = i.second.first;
        if(i.second.first >= i.second.second.size()){
            ////Als het dot al op einde bevind, dan moet jij niet naar die productie kijken
            continue;
        }
        else if(i.second.second[j]->getnaam() == str ){
            if(Contains.contains({j+1,i.second.second})){
                erin = true;
            }
            ////Als wij een productie hebben gevonden die de variable heeft kijken wij of de nieuwe productie die wij gaan maken door de dot naar rechts te doen al bestaat of niet
            if(!Contains.contains({j+1,i.second.second})){
                erin = true;
                state++;
                temporary[{{i.first.first.first,chart},state}] = {j+1,i.second.second};
                Contains[{j+1,i.second.second}] = true;
            }
            if(j+1 == i.second.second.size()){
                erin = true;
                ////Als het dot naar recht doen en wij zijn bij de einde, Dan moeten wij de Variable van de productie pakken
                ////Wij zullen dan weer in de tabel moeten zoeken maar deze keer met de nieuwe variable
                OneDotAhead(i.first.first.first->getnaam(),temporary,second,state,chart,twotime);

            }
            if(j+1 != i.second.second.size() and !i.second.second[j+1]->getterminal() and !twotime.contains(i.second.second[j+1]->getnaam())){
                ////Als wij een een dot naar recht doen en komen een variable tegen, Dan moeten wij al de productie van die var in de tabel doen
                TabelVullenSecond(second,i.second.second[j+1],temporary,state,chart);
                twotime[i.second.second[j+1]->getnaam()] = true;
                erin = true;
            }
        }
    }
    if(!erin){
        return false;
    }
    Tabel = temporary;
    return true;
}

bool EarleyParser::LastChart(map<pair<pair<Objects*,int>,int>,pair<int,vector<Objects*>>>& Tabel, int chart){
    ////Hier wordt gekeken of wij echter de laaste punt hebben bereikt en dat de zin juist werd gelezsen
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