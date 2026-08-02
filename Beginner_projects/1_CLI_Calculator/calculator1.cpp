#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <vector>

double toDouble(const std::string& s) {
    try {
        size_t charsUsed;
        double value = std::stod(s, &charsUsed);
        if (charsUsed != s.size()) {
            throw std::runtime_error("'" + s + "' is not a valid number");
        }
        return value;
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("'" + s + "' is not a valid number");
    }
}

std::vector<std::string> tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::string current;

    for (char c : expression) {
        if (std::isspace(c)) {
            if (!current.empty()) { tokens.push_back(current); current.clear(); }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (!current.empty()) { tokens.push_back(current); current.clear(); }
            tokens.push_back(std::string(1, c));
        } else {
            current += c;
        }
    }
    if (!current.empty()) tokens.push_back(current);
    return tokens;
}
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("division by zero");
            return a / b;
        default:
            throw std::runtime_error("unknown operator");
    }
}

double evaluate(const std::string& expression) {
    std::vector<std::string> tokens = tokenize(expression);

    std::stack<double> numbers;
    std::stack<char> operators;

    for (const std::string& t : tokens) {
        if (t == "+" || t == "-" || t == "*" || t == "/") {
            char op = t[0];
            while (!operators.empty() && precedence(operators.top()) >= precedence(op)) {
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                char prevOp = operators.top(); operators.pop();
                numbers.push(applyOp(a, b, prevOp));
            }
            operators.push(op);
        } else {
            numbers.push(toDouble(t));
        }
    }

    while (!operators.empty()) {
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        char op = operators.top(); operators.pop();
        numbers.push(applyOp(a, b, op));
    }

    return numbers.top();
}

int main() {
    std::cout << "Expression Calculator (type 'q' to quit)" << std::endl;
    std::cout << "Example: 3 + 4 * 2 - 1" << std::endl;

    while (true) {
        std::string line;
        std::cout << "\n> ";
        std::getline(std::cin, line);

        if (line == "q") break;
        if (line.empty()) continue;

        try {
            double result = evaluate(line);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}