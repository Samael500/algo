#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>

typedef std::vector<int> vector;

class QueueMax {
private:
    std::stack<std::pair<int, int>> back_, front_;

public:
    QueueMax() {}

    void Push(int value) {
        back_.push({value, std::max(value, back_.empty() ? value : back_.top().second)});
    }

    void Pop() {
        if (front_.empty()) {
            while (!back_.empty()) {
                auto value = back_.top().first;
                front_.push({value, std::max(value, front_.empty() ? value : front_.top().second)});
                back_.pop();
            }
        }
        front_.pop();
    }

    int Max() const {
        if (back_.empty() && front_.empty()) {
            return 0;
        }
        if (back_.empty()) {
            return front_.top().second;
        }
        if (front_.empty()) {
            return back_.top().second;
        }
        return std::max(front_.top().second, back_.top().second);
    }
};

void ReadVector(vector* container, size_t length) {
    container->resize(length);
    for (auto& element : *container) {
        std::cin >> element;
    }
}

void SolveTask(const vector& data) {
    size_t questions;
    size_t cursor = 0;
    std::cin >> questions;
    QueueMax queue;
    queue.Push(data[0]);
    while (questions--) {
        char command;
        std::cin >> command;
        switch (command) {
            case 'R': {
                queue.Push(data[++cursor]);
                break;
            }
            case 'L': {
                queue.Pop();
                break;
            }
        }
        std::cout << queue.Max() << " ";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    vector data;
    size_t length;
    std::cin >> length;
    ReadVector(&data, length);

    SolveTask(data);
    return 0;
}
