#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

typedef std::vector<int> Vector;

void ReadVector(Vector* container) {
    size_t length;
    std::cin >> length;

    container->resize(length);
    for (auto& element : *container) {
        std::cin >> element;
        std::cerr << element << " ";
    }
    std::cerr << "\n";
}

auto SolveTask(const std::vector<Vector>& sequences) {
    size_t i_size = sequences[0].size() + 1;
    size_t j_size = sequences[1].size() + 1;
    size_t k_size = sequences[2].size() + 1;

    std::vector<std::vector<std::vector<int> > > dynamic(i_size);

    for (size_t i_ndex = 0; i_ndex < i_size; ++i_ndex) {
        dynamic[i_ndex].resize(j_size);
        for (size_t j_ndex = 0; j_ndex < j_size; ++j_ndex) {
            dynamic[i_ndex][j_ndex].resize(k_size);
        }
    }

    for (size_t i_ndex = 1; i_ndex < i_size; ++i_ndex) {
        for (size_t j_ndex = 1; j_ndex < j_size; ++j_ndex) {
            for (size_t k_ndex = 1; k_ndex < k_size; ++k_ndex) {
                bool i_j_eq = sequences[0][i_ndex - 1] == sequences[1][j_ndex - 1];
                bool j_k_eq = sequences[1][j_ndex - 1] == sequences[2][k_ndex - 1];
                if (i_j_eq && j_k_eq) {
                    dynamic[i_ndex][j_ndex][k_ndex]= dynamic[
                        i_ndex - 1][j_ndex - 1][k_ndex - 1] + 1;
                } else {
                    dynamic[i_ndex][j_ndex][k_ndex] = std::max(
                        std::max(dynamic[i_ndex - 1][j_ndex][k_ndex],
                            dynamic[i_ndex][j_ndex - 1][k_ndex]),
                        dynamic[i_ndex][j_ndex][k_ndex - 1]);
                }
            }
        }
    }

    std::stack<int> result;

    size_t i_ndex = i_size - 1;
    size_t j_ndex = j_size - 1;
    size_t k_ndex = k_size - 1;

    while ((i_ndex > 0) && (j_ndex > 0) && (k_ndex > 0)) {
        bool i_j_eq = sequences[0][i_ndex - 1] == sequences[1][j_ndex - 1];
        bool j_k_eq = sequences[1][j_ndex - 1] == sequences[2][k_ndex - 1];
        bool eq_ijk = (dynamic[i_ndex][j_ndex][k_ndex]
            == dynamic[i_ndex - 1][j_ndex - 1][k_ndex - 1] + 1);

        if (i_j_eq && j_k_eq && eq_ijk) {
            result.push(sequences[0][i_ndex - 1]);
            --i_ndex;
            --j_ndex;
            --k_ndex;
        } else if (dynamic[i_ndex][j_ndex][k_ndex] == dynamic[i_ndex - 1][j_ndex][k_ndex]) {
            --i_ndex;
        } else if (dynamic[i_ndex][j_ndex][k_ndex] == dynamic[i_ndex][j_ndex - 1][k_ndex]) {
            --j_ndex;
        } else if (dynamic[i_ndex][j_ndex][k_ndex] == dynamic[i_ndex][j_ndex][k_ndex - 1]) {
            --k_ndex;
        }
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<Vector> sequences(3);
    ReadVector(&sequences[0]);
    ReadVector(&sequences[1]);
    ReadVector(&sequences[2]);

    auto result = SolveTask(sequences);

    std::cout << result.size() << "\n";
    while (!result.empty()) {
        std::cout << result.top() << " ";
        result.pop();
    }

    return 0;
}
