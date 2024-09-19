// SimpleCalculator.cpp
#include "SimpleCalculator.h"
#include <iostream>
#include <cctype>  // for isdigit function
#include <sstream> // for istringstream
#include <stdexcept> // for exception handling
#include <stack>    // Include stack header to use the stack class


using namespace std;

SimpleCalculator::SimpleCalculator() {}

bool SimpleCalculator::isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
    // Student Task: Implement the isOperator function
    // This function should return true if the character 'ch' is one of the arithmetic operators.
    // Supported operators are: +, -, *, /, %
    // Use a simple comparison to check if 'ch' matches any of these operators.
}

int SimpleCalculator::precedence(char op) {
    // Student Task: Implement the precedence function
    // This function should return the precedence of the operator 'op'.
    // Precedence rules:
    if (op == '+' || op == '-') return 1; // Lowest precedence
    if (op == '*' || op == '/' || op == '%') return 2; // Higher precedence
    return 0; // Non-operator characters

    // - Return 1 for + and -
    // - Return 2 for *, /, and %
    // - Return 0 for any other character (default case)
}

double SimpleCalculator::applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero");
        return a / b;
        case '%':
            // Convert to integers to handle modulus operation
                if (b == 0) throw runtime_error("Division by zero");
        return static_cast<int>(a) % static_cast<int>(b);
        default:
            throw runtime_error("Invalid operator");
    }
    // Student Task: Implement the applyOperation function
    // This function should perform arithmetic operations based on the operator 'op'.
    // Steps:
    // - Use a switch statement to handle each operator: +, -, *, /, %
    // - For each case, perform the corresponding arithmetic operation on 'a' and 'b'
    // - If 'op' is '/', check if 'b' is 0 to prevent division by zero; if so, throw a runtime_error
    // - If 'op' is '%', convert 'a' and 'b' to integers before applying the modulus operation
    // - Return the result of the operation
}

string SimpleCalculator::infixToPostfix(const string& infix) {
    stack<char> operators;
    string postfix;
    stringstream ss;

    for (size_t i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (isdigit(ch) || ch == '.') {
            ss << ch;
            if (i == infix.length() - 1 || !isdigit(infix[i + 1]) && infix[i + 1] != '.') {
                postfix += ss.str() + " ";
                ss.str("");
            }
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.pop();
        } else if (isOperator(ch)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        postfix += ' ';
        operators.pop();
    }

    return postfix;
}


    // - Use a stack to store operators and parentheses during the conversion
    // - Iterate over each character in the input string 'infix'
    // - If the character is a digit, append it to the postfix string
    // - If the character is '(', push it onto the stack
    // - If the character is ')', pop from the stack to the postfix string until '(' is found
    // - If the character is an operator, pop from the stack to the postfix string while the top of the stack has higher or equal precedence
    // - After the loop, pop any remaining operators in the stack to the postfix string


double SimpleCalculator::evaluatePostfix(const string& postfix) {
    stack<double> operands; // Stack to hold the operands during evaluation
    istringstream iss(postfix); // Stream to handle space-separated tokens
    string token;

    // Split the postfix string into tokens
    while (iss >> token) {
        if (isdigit(token[0])) {
            // If the token is a number, convert it to double and push it onto the stack
            operands.push(stod(token));
        } else if (isOperator(token[0]) && token.size() == 1) {
            // If the token is an operator, pop two numbers and apply the operator
            double right = operands.top();
            operands.pop();
            double left = operands.top();
            operands.pop();
            double result = applyOperation(left, right, token[0]);
            operands.push(result); // Push the result back onto the stack
        } else {
            throw runtime_error("Invalid token in postfix expression");
        }
    }

    if (operands.size() != 1) {
        throw runtime_error("Invalid postfix expression");
    }

    return operands.top();
    // Student Task: Implement the evaluatePostfix function
    // This function should evaluate a postfix expression and return its result.
    // Steps:
    // - Use a stack to store numerical values during evaluation
    // - Split the postfix string into tokens using a string stream
    // - For each token:
    //   - If it is a number, convert it to double and push it onto the stack
    //   - If it is an operator, pop two numbers from the stack, apply the operator, and push the result back onto the stack
    // - The final result should be the only number left on the stack
}

void SimpleCalculator::calculate(const string& infix) {
    // This function is already implemented for you.
    // It handles input/output and coordinates the conversion from infix to postfix and the evaluation of the postfix expression.
    try {
        cout << "Input the infix expression: " << infix << endl;
        string postfix = infixToPostfix(infix);
        cout << "Postfix expression is: " << postfix << endl;
        double result = evaluatePostfix(postfix);
        cout << " The result is: " << result << endl;
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}