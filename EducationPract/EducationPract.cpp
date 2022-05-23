#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;
void FindWords(string S, vector<string>& Words) {
    istringstream stream(S);
    string word;
    bool check;
    while (stream >> word) {
        check = true;
        for (int i = 0; i < word.length(); i++) {
            check = true;
            if (((word[i] >= 'А' && word[i] <= 'Я') || (word[i] >= 'а' && word[i] <= 'я') || (word[i] >= '0' && word[i] <= '9'))) {
                check = false;
            }
            if (check) {
                word.erase(i, 1);
                i--;
            }
        }
        if (!word.empty())
            Words.push_back(word);
    }
}

void PrintWords(vector<string>& Words, ofstream& result) {
    for (int i = 0; i < Words.size(); i++) {
        result << Words[i] << endl;
    }
}

void input(string& S, ifstream& fin) {
    bool Transfer = false;
    string line;
    while (getline(fin, line)) {
        if (Transfer)
            S += '\n';
        S += line;
        Transfer = true;
    }
}

void Run() {
    string S;
    ifstream fin("input.txt");
    ofstream result("result.txt");
    ofstream analysts("analysts.txt");

    input(S, fin);
    vector <string> Words;
    FindWords(S, Words);
    PrintWords(Words, result);

}

int main() {
    setlocale(LC_ALL, "ru");
    Run();
}