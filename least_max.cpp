#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<size_t> vector;

size_t FindMinMax(const vector& sort_asc, const vector& sort_desc, size_t length) {
    size_t position = 0;
    size_t curr_maximum = std::max(sort_asc[position], sort_desc[position]);
    size_t left = 0, right = length;
    size_t previous_left = left, previous_right = right;

    while (left < right - 1) {
        size_t new_position = left + (right - left) / 2;
        size_t new_maximum = std::max(sort_asc[new_position], sort_desc[new_position]);
        if (new_maximum < curr_maximum) {
            position = new_position;
            curr_maximum = new_maximum;
        }
        if (sort_asc[new_position] == sort_desc[new_position]) {
            return position;
        }
        if (new_maximum == sort_asc[new_position]) {
            right = new_position + 1;
        } else {
            left = new_position;
        }
        if (left == previous_left && right == previous_right) {
            ++left;
        }
        previous_left = left;
        previous_right = right;
    }
    return position;
}

void ReadVector(std::vector<vector>* container, size_t rows, size_t columns) {
    container->resize(rows);
    for (auto& line : *container) {
        line.resize(columns);
        for (auto& element : line) {
            std::cin >> element;
        }
    }
}

void SolveTask() {
    size_t sort_asc_n, sort_desc_m, length;
    std::cin >> sort_asc_n >> sort_desc_m >> length;
    std::vector<vector> sort_asc, sort_desc;

    ReadVector(&sort_asc, sort_asc_n, length);
    ReadVector(&sort_desc, sort_desc_m, length);

    size_t q_count;
    std::cin >> q_count;

    while (q_count--) {
        size_t asc, desc;
        std::cin >> asc >> desc;
        std::cout << FindMinMax(sort_asc[asc - 1], sort_desc[desc - 1], length) + 1 << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    SolveTask();
    return 0;
}
