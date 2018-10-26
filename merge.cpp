#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

typedef std::vector<int> Vector;

void ReadVector(Vector* container, size_t length) {
    container->resize(length);
    for (auto& element : *container) {
        std::cin >> element;
    }
}

Vector Merge(const Vector& first, const Vector& last) {
    Vector result;
    size_t first_i = 0;
    size_t last_i = 0;
    while (first_i < first.size() && last_i < last.size()) {
        if (first[first_i] <= last[last_i]) {
            result.push_back(first[first_i]);
            ++first_i;
        } else {
            result.push_back(last[last_i]);
            ++last_i;
        }
    }
    while (first_i < first.size()) {
        result.push_back(first[first_i]);
        ++first_i;
    }
    while (last_i < last.size()) {
        result.push_back(last[last_i]);
        ++last_i;
    }
    return result;
}

void SolveTask(std::queue<Vector>* queue) {
    while (queue->size() > 1) {
        auto first = queue->front();
        queue->pop();
        auto last = queue->front();
        queue->pop();
        queue->push(Merge(first, last));
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t rows_number;
    size_t length;
    std::cin >> rows_number >> length;

    std::queue<Vector> queue;
    Vector data;
    for (size_t line = 0; line < rows_number; ++line) {
        ReadVector(&data, length);
        queue.push(data);
    }

    SolveTask(&queue);

    for (const auto& element : queue.front()) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    return 0;
}
