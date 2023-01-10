#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "BigInt.h"

using namespace std;

bool testSum(string answer, BigInt first, BigInt second) {
    if (string(first + second) == answer) return true;
    else return false;
}

bool testSub(string answer, BigInt first, BigInt second) {
    if (string(first - second) == answer) return true;
    else return false;
}

bool testDiv(string answer, BigInt first, BigInt second) {
    if (string(first / second) == answer) return true;
    else return false;
}

bool testMul(string answer, BigInt first, BigInt second) {
    if (string(first * second) == answer) return true;
    else return false;
}

bool testMod(string answer, BigInt first, BigInt second) {
    if (string(first % second) == answer) return true;
    else return false;
}

void testing(string file, bool mod = false) {
    ifstream fin;
    fin.open(file, ios::in);
    string answer, test, f, s;
    BigInt first, second;
    int i = 1;
    while (true) {
        getline(fin, test);
        if (test == "") break;
        getline(fin, answer);
        getline(fin, f);
        getline(fin, s);
        first = f;
        second = s;
        cout << "Test #" << i++ << endl;
        if (test == "Sum") {
            clock_t start = clock();
            if (testSum(answer, first, second)) cout << "Good! ";
            else cout << "Bad! ";
            double duration = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
            cout << "time: " << duration << endl;
            if (mod) cout << "first: " << f << endl << "Sum" << endl << "second: " + s << "\nanswer: " + answer << "\n\n";
        } else if (test == "Sub") {
            clock_t start = clock();
            if (testSub(answer, first, second)) cout << "Good! ";
            else cout << "Bad! ";
            double duration = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
            cout << "time: " << duration << endl;
            if (mod) cout << "first: " << f << endl << "Sub" << endl << "second: " + s << "\nanswer: " + answer << "\n\n";
        } else if (test == "Mul") {
            clock_t start = clock();
            if (testMul(answer, first, second)) cout << "Good! ";
            else cout << "Bad! ";
            double duration = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
            cout << "time: " << duration << endl;
            if (mod) cout << "first: " << f << endl << "Mul" << endl << "second: " + s << "\nanswer: " + answer << "\n\n";
        } else if (test == "Div") {
            clock_t start = clock();
            if (testDiv(answer, first, second)) cout << "Good! ";
            else cout << "Bad! ";
            double duration = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
            cout << "time: " << duration << endl;
            if (mod) cout << "first: " << f << endl << "Div" << endl << "second: " + s << "\nanswer: " + answer << "\n\n";
        } else if (test == "Mod") {
            clock_t start = clock();
            if (testMod(answer, first, second)) cout << "Good! ";
            else cout << "Bad! ";
            double duration = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
            cout << "time: " << duration << endl;
            if (mod) cout << "first: " << f << endl << "Mod" << endl << "second: " + s << "\nanswer: " + answer << "\n\n";
        }
        test = "";
    }
}

int main() {
    testing("tests.txt", true);
    return 0;
}
