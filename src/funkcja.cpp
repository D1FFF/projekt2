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

queue<string> wyrnaonp(const string& input) {
    stack<char> operatory;
    queue<string> wyjscie;
    istringstream iss(input);
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
