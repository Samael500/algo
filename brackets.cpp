#include <iostream>
#include <stack>
#include <string>

bool IsOpen(char bracket) {
    return bracket == '(' || bracket == '[' || bracket == '{';
}

bool CloseCorrect(char prev, char next) {
    switch (prev) {
        case '(': return next == ')';
        case '[': return next == ']';
        case '{': return next == '}';
    }
    return false;
}

void Checkrackets() {
    std::string input;
    std::stack<char> stack;
    size_t prefix = 0;

    std::cin >> input;
    for (const auto& chr : input) {
        if (IsOpen(chr)) {
            ++prefix;
            stack.push(chr);
        } else if (!stack.empty() && CloseCorrect(stack.top(), chr)) {
            ++prefix;
            stack.pop();
        } else {
            break;
        }
    }

    if (stack.empty() && (prefix == input.size())) {
        std::cout << "CORRECT";
    } else {
        std::cout << prefix;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Checkrackets();
    return 0;
}
