//Evaluates a single Reverse Polish Notation (RPN) expression. Prints INVALID when input is not a valid RPN expresion

#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

class Stack {
private:
    vector<int> elements;

public:
    void push(int x) {
        elements.push_back(x);
    }

    int top() {
        if (!elements.empty()) {
            return elements.back();
        }
        throw runtime_error("Empty Stack");
    }

    void pop() {
        if (!elements.empty()) {
            elements.pop_back();
        } else {
            throw runtime_error("Empty Stack");
        }
    }

    int size() {
        return elements.size();
    }
};

int main() {
    Stack S;
    string expr;
    int op1, op2, result;
    string item;

    //Reads line containing RPN
    getline(cin, expr);
    stringstream ss(expr);
    
    //process each item in the expression
    while (ss >> item) {
        //if item is number
        if ((item.length() > 1 && item[0] == '-') or isdigit(item[0])) {
            S.push(stoi(item));
          //if item is an operator
        } else if (item == "+" or item == "-" or item == "*" or item == "/") {
            if (S.size() < 2) {
                cout << "INVALID" << endl;
                return 0;
            }
            op2 = S.top();
            S.pop();
            op1 = S.top();
            S.pop();

          //Perform operation
            if (item == "+") result = op1 + op2;
            else if (item == "-") result = op1 - op2;
            else if (item == "*") result = op1 * op2;
            else if (item == "/") {
                if (op2 == 0) {
                    cout << "INVALID" << endl;
                    return 0;
                }
                result = op1 / op2;
            }

            S.push(result);
        } else {
            cout << "INVALID" << endl;
            return 0;
        }
    }

    if (S.size() == 1) {
        cout << S.top() << endl;
    } else {
        cout << "INVALID\n";
    }

    return 0;
}
