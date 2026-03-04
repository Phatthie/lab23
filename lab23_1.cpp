#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream source(filename);
    string line;
    while(getline(source, line)){
        size_t pos = line.find(':');
        if(pos == string::npos) continue;
        string name = line.substr(0, pos);
        while(!name.empty() && name.back() == ' ')
            name.pop_back();
        const char* scorePart = line.substr(pos + 1).c_str();
        int a,b,c;
        if(sscanf(scorePart,"%d %d %d",&a,&b,&c) == 3){
            int total = a + b + c;
            names.push_back(name);
            scores.push_back(total);
            grades.push_back(score2grade(total));
        }
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    string line;
    getline(cin >> ws, line);
    size_t pos = line.find(' ');
    if(pos == string::npos){
        command = line;
        key = "";
    }else{
        command = line.substr(0, pos);
        key = line.substr(pos + 1);
    }
}

void searchName(vector<string> &name,vector<int> &score,vector<char> &grade,const string &key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned int i=0;i<name.size();i++){
        if(toUpperStr(name[i]) == toUpperStr(key)){
            cout << name[i] << "'s score = " << score[i] << endl;
            cout << name[i] << "'s grade = " << grade[i] << endl;
            found = true;
            break;
        }
    }
    if(!found) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned int i=0;i<grades.size();i++){
        if(grades[i]==key[0]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }
    if(!found) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}