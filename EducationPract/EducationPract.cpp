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

void Raschoska(vector<string>& Words) {
    int step = Words.size() - 1;
    for (step; step >= 1; step /= 1.2473309) {
        for (int i = 0; i + step < Words.size(); i++) {
            if (Words[i] < Words[i + step])
                swap(Words[i], Words[i + step]);
        }
    }
}

void PrintWords(vector<string>& Words, ofstream& fresult) {
    for (int i = 0; i < Words.size(); i++) {
        if (i != 0) {
            if (Words[i][0] != Words[i - 1][0]) {
                fresult << endl << Words[i] << " ";
            }
            else {
                fresult << Words[i] << " ";
            }
        }
        else {
            fresult << Words[i] << " ";
        }
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
    ofstream fresult("result.txt");
    ofstream fanalysts("analysts.txt");

    input(S, fin);
    vector <string> Words;
    FindWords(S, Words);
    Raschoska(Words);
    PrintWords(Words, fresult);

}

int main() {
    setlocale(LC_ALL, "ru");
    Run();
}