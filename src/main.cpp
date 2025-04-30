#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <future>
#include <cctype>
#include "funkcja.hpp"
using namespace std;

int obliczONP(queue<string> ONP) {
    stack<int> wartosci;
    while (!ONP.empty()) {
        string token = ONP.front();
        ONP.pop();
        if (isdigit(token[0]) || token.size() > 1) {
            wartosci.push(stoi(token));
        }
        else {
            int a = wartosci.top(); wartosci.pop();
            int b = wartosci.top(); wartosci.pop();
            switch (token[0]) {
	            case '+': wartosci.push(a + b); break;
	            case '-': wartosci.push(a - b); break;
	            case '*': wartosci.push(a * b); break;
	            case '/': wartosci.push(a / b); break;
            }
        }
    }
    return wartosci.top();
}

int main(){
    string wyrazenie;
    cout << "Podaj wyrazenie: ";
    getline(cin, wyrazenie);

    queue<string> ONP = wyrnaonp(wyrazenie);

	cout << "Odwrotna notacja polska: ";
    queue<string> temp = ONP;
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;

    future<int> przyszlyWynik = async(launch::async, obliczONP, ONP);

    int wynik = przyszlyWynik.get();

    cout << "Wynik: " << wynik << endl;

    return 0;
}