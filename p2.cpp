#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <future>
#include <cctype>
using namespace std;

int priorytet(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

queue<string> wyrnaONP(const string& wyrazenie) {
    stack<char> operatory;
    queue<string> wyjscie;
    istringstream iss(wyrazenie);
    char token;
    while (iss >> token) {
        if (isdigit(token)) {
            string number(1, token);
            while (iss.peek() != EOF && isdigit(iss.peek())) {
                char next = iss.get();
                number += next;
            }
            wyjscie.push(number);
        }
        else if (token == '(') {
            operatory.push(token);
        }
        else if (token == ')') {
            while (!operatory.empty() && operatory.top() != '(') {
                wyjscie.push(string(1, operatory.top()));
                operatory.pop();
            }
            if (!operatory.empty() && operatory.top() == '(') {
                operatory.pop();
            }
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
        	while (!operatory.empty() && priorytet(operatory.top()) >= priorytet(token)) {
                wyjscie.push(string(1, operatory.top()));
                operatory.pop();
            }
            operatory.push(token);
        }
    }

    while (!operatory.empty()) {
        wyjscie.push(string(1, operatory.top()));
        operatory.pop();
    }

    return wyjscie;
}

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

int main() {
    string wyrazenie;
    cout << "Podaj wyrazenie: ";
    getline(cin, wyrazenie);

    queue<string> ONP = wyrnaONP(wyrazenie);

    /*
	cout << "Odwrotna notacja polska: ";
    queue<string> temp = ONP;
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
	*/

    future<int> przyszlyWynik = async(launch::async, obliczONP, ONP);

    int wynik = przyszlyWynik.get();

    cout << "Wynik: " << wynik << endl;

    return 0;
}