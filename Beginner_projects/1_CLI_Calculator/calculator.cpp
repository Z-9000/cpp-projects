#include <iostream>
#include <string>

double toDouble(const std::string& s) {
    try {
        return std::stod(s);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("'" + s + "' is not a valid number");
    }
}

int main() {
    std::cout << "Simple C++ Calculator (type 'q' at any prompt to quit)" << std::endl;

    while (true) {
        std::string input;  // It will get initialised as an empty string ""
        double num1, num2;
        char op;
    
        std::cout << "Enter first number: ";
        std::cin >> input;
        if (input == "q") break;

        num1 = toDouble(input);

        std::cout << "Enter the operator (+, -, *, /): ";
        std::cin >> input;
        if (input == "q") break;
        op = input[0];
    
        std::cout << "Enter second number: ";
        std::cin >> input;
        if (input == "q") break;
        num2 = toDouble(input);

        double result = 0;

        if (op == '+') {
            result = num1 + num2;
        } else if (op == '-') {
            result = num1 - num2;
        } else if (op == '*') {
            result = num1 * num2;
        } else if (op == '/') {
            if (num2 == 0) {
                std::cout << "Error: division by zero!" << std::endl;
                return 1;
            }
            result = num1/num2;
        } else {
            std::cout << "Error: unknown operator." << std::endl;
            return 1;
        }

        std::cout << "Result: " << result << std::endl;

    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}