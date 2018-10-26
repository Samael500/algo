#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>

typedef std::vector<int> vector;

void ReadVector(vector* container, size_t length) {
    container->resize(length);
    for (auto& element : *container) {
        std::cin >> element;
    }
}

struct AnswPosition {
    size_t length;
    size_t position;
};

const bool GREAT = 0, LEAST = 1;
const size_t MAX = -1;

template <class T>
inline bool operator<(const std::vector<T>& master, const std::vector<T>& slave) {
    if (slave.empty()) {
        return true;
    }
    if (master.size() == slave.size()) {
        for (size_t index = 0; index < master.size(); ++index) {
            if (master[index] < slave[index]) {
                return true;
            }
            if (master[index] > slave[index]) {
                return false;
            }
        }
    }
    // > for collect longest
    return master.size() > slave.size();
}

std::vector<size_t> RecoverTrack(
        size_t max_length, bool x_flag, size_t index,
        const std::vector<std::vector<AnswPosition>>& dynamic) {
    std::vector<size_t> candidat(max_length);
    size_t cursor = max_length - 1;
    bool flag = x_flag;
    size_t next = index;
    while (cursor < max_length) {
        candidat[cursor] = next;
        next = dynamic[flag][next].position;
        flag = !flag;
        --cursor;
    }
    return candidat;
}

size_t CheckTrack(
        const std::vector<std::vector<AnswPosition>>& dynamic,
        size_t j_index, size_t position, bool flag) {

    auto candidat_p = RecoverTrack(dynamic[flag][position].length, flag, position, dynamic);
    auto candidat_j = RecoverTrack(dynamic[flag][position].length, flag, j_index, dynamic);
    if (candidat_j < candidat_p) {
        return j_index;
    }
    return position;
}

void SolveTask(const vector& data) {
    std::vector<std::vector<AnswPosition>> dynamic(2);
    dynamic[GREAT].resize(data.size(), {1, 0});
    dynamic[LEAST].resize(data.size(), {1, 0});

    size_t max_length = 1;
    for (size_t i_index = 1; i_index < data.size(); ++i_index) {
        for (size_t j_index = 0; j_index < i_index; ++j_index) {
            if (data[j_index] < data[i_index]) {
                // .. from_j_min .. to_i_max
                if (dynamic[GREAT][i_index].length <= dynamic[LEAST][j_index].length) {
                    dynamic[GREAT][i_index].length = dynamic[LEAST][j_index].length + 1;
                    dynamic[GREAT][i_index].position = j_index;
                    max_length = std::max(max_length, dynamic[GREAT][i_index].length);
                } else if (
                        dynamic[GREAT][i_index].length - 1 == dynamic[LEAST][j_index].length) {
                    dynamic[GREAT][i_index].position = CheckTrack(
                        dynamic, j_index, dynamic[GREAT][i_index].position, LEAST);
                }
            }
            if (data[j_index] > data[i_index]) {
                // .. from_j_max .. to_i_min
                if (dynamic[LEAST][i_index].length <= dynamic[GREAT][j_index].length) {
                    dynamic[LEAST][i_index].length = dynamic[GREAT][j_index].length + 1;
                    dynamic[LEAST][i_index].position = j_index;
                    max_length = std::max(max_length, dynamic[LEAST][i_index].length);
                } else if (
                        dynamic[LEAST][i_index].length - 1 == dynamic[GREAT][j_index].length) {
                    dynamic[LEAST][i_index].position = CheckTrack(
                        dynamic, j_index, dynamic[LEAST][i_index].position, GREAT);
                }
            }
        }
    }

    std::vector<size_t> best_vector;

    for (size_t index = data.size() - 1; index < data.size(); --index) {
        for (size_t x_flag = 0; x_flag <= 1; ++x_flag) {
            if (dynamic[x_flag][index].length == max_length) {
                auto candidat = RecoverTrack(max_length, x_flag, index, dynamic);
                if (candidat < best_vector) {
                    best_vector = candidat;
                }
            }
        }
    }

    for (auto iterator = best_vector.begin(); iterator != best_vector.end(); ++iterator) {
        std::cout << data[*iterator] << " ";
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
