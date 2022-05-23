#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <map>

using namespace std;

//Разбиение текста на слова
void FindWords(string S, vector<string>& Words) {
    istringstream stream(S);
    string word;
    bool check;
    while (stream >> word) {
        check = true;
        for (int i = 0; i < word.length(); i++) {
            check = true;
            if (((word[i] >= -64 && word[i] <= -33) || (word[i] >= -32 && word[i] <= -1) || (word[i] >= '0' && word[i] <= '9'))) {
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

//Сортировка расчёской
void Raschoska(vector<string>& Words) {
    int step = Words.size() - 1;
    for (step; step >= 1; step /= 1.2473309) {
        for (int i = 0; i + step < Words.size(); i++) {
            if (Words[i] < Words[i + step])
                swap(Words[i], Words[i + step]);
        }
    }
}

//Вывод отсортированных слов
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

//Для статистики (количество слов на букву алфавита)
void Analysts(vector<string>& Words, map<char, int>& statistics) {
    for (int i = 0; i < Words.size(); i++) {
        statistics[Words[i][0]] = statistics[Words[i][0]] + 1;
    }
}

//Вывод статистикии
void PrintAnalysts(map<char, int>& statistics, ofstream& fanalysts) {
    map <char, int> ::iterator it = statistics.begin();
    for (int i = 0; it != statistics.end(); it++, i++) {
        fanalysts << it->first << " - " << it->second << endl;
    }
}

//Входной текст
void Input(string& S, ifstream& fin) {
    bool Transfer = false;
    string line;
    while (getline(fin, line)) {
        if (Transfer)
            S += '\n';
        S += line;
        Transfer = true;
    }
}

//Основная функция для работы программы
void Run() {
    string S;
    /*string way;
    cout << "Enter name of input file: ";
    getline(cin, way);
    ifstream fin(way);*/ //Открытие файла для чтения текста
    ifstream fin("input.txt"); //Открытие файла для чтения текста
    ofstream fresult("result.txt"); //Открытие файла для записи отсортированных слов
    ofstream fanalysts("analysts.txt"); //Открытие файла для записи статистики
    Input(S, fin); //Вызов функции Input для считывания входного текста
    fin.close();//Закрытие файла 
    vector <string> Words;
    map<char, int> statistics;
    FindWords(S, Words); //Вызов функции FindWords для разбиения исходного текста на слова

    auto begin = chrono::steady_clock::now(); // Время начала отсчёта времени сортировки
    Raschoska(Words); //Вызов функции Raschoska для сортировки расчёской вектора слов. По возрастанию 
    auto end = chrono::steady_clock::now(); // Конечное время сортировки
    auto time = chrono::duration_cast<chrono::microseconds>(end - begin).count();//Время сортировки

    if (fresult.is_open()) {
        fresult << "Слова, отсортированные по алфавиту и по возрастанию:" << endl;
        PrintWords(Words, fresult); // Вызов функции PrintWords для вывода отсортированных слов
    }
    fresult.close();// Закрытие файла для записи отсортированных слов

    if (fanalysts.is_open()) {
        fanalysts << "Исходный текст: " << endl;
        fanalysts << S << endl << endl;
        fanalysts << "Вариант 20: Кирилица, по алфавиту, по возрастанию, учитывать числа, сортировка расчёской." << endl;
        fanalysts << "Количество слов: " << Words.size() << endl;
        fanalysts << "Время сортировки: " << time << " микросек." << endl;
        fanalysts << "Статистика (количество слов на букву алфавита):" << endl;
        Analysts(Words, statistics); //Вызов функции Analysts для статистики (количество слов на букву алфавита)
        PrintAnalysts(statistics, fanalysts); //Вызов функции PrintAnalysts для вывода в файл статистики
    }
    fanalysts.close();// Закрытие файла для записи статистики 
}

int main() {
    setlocale(LC_ALL, "ru");
    Run(); // Вызов функции Run, для начала работы программы
}