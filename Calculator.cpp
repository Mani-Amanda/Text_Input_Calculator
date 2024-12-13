#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include<sstream>
#include<fstream>
#include<iomanip>

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}
string infixToPostfix(const string& infix) {
    string postfix = "";
    stack<char> operatorStack;

    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];

        if (isspace(c)) {
            continue; // Ignore spaces
        }
        else if (isdigit(c)) {
            string operand = "";
            operand += c;
            while (i + 1 < infix.size() && isdigit(infix[i + 1])) {
                operand += infix[++i];
            }
            postfix += operand;
            postfix += ' '; // Separate operands with a space
        }
        else if (c == '(') {
            operatorStack.push(c);
        }
        else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                postfix += ' ';
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '(') {
                operatorStack.pop(); // Remove the '('
            }
            else {
                return "";
            }
        }
        else if (c == '[') {
            operatorStack.push(c);
        }
        else if (c == ']') {
            while (!operatorStack.empty() && operatorStack.top() != '[') {
                postfix += operatorStack.top();
                postfix += ' ';
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '[') {
                operatorStack.pop(); // Remove the '['
            }
            else {
                return "";
            }
        }
        else if (isOperator(c)) {
            while (!operatorStack.empty() &&
                precedence(c) <= precedence(operatorStack.top())) {
                postfix += operatorStack.top();
                postfix += ' ';
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
        else {
            return "";
        }
    }

    while (!operatorStack.empty()) {
        if (operatorStack.top() == '(' || operatorStack.top() == ')') {
            return "";
        }
        postfix += operatorStack.top();
        postfix += ' ';
        operatorStack.pop();
    }

    return postfix;
}
int main() {
    ifstream inputFile("formulas.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open 'formulas.txt'" << endl;
        return 1;
    }

    ofstream outputFile("result.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open 'result.txt'" << endl;
        inputFile.close();
        return 1;
    }
    outputFile << "(-1) means the errors in the equation" << endl;
    string formula;
    while (!inputFile.eof()) {
        
        getline(inputFile, formula);
        outputFile<< formula << "=";
        string postFix = infixToPostfix(formula);
    }
    

    inputFile.close();


    return 0;
}