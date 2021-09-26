#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <algorithm>

size_t LowerBound(const std::vector<int>& data, int elem) {
    size_t left = 0, right = data.size();
    while (left < right) {
        size_t middle = left + (right - left) / 2;
        if (data[middle] < elem) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

void UnitTests() {
    assert(LowerBound({}, 8) == 0);
    assert(LowerBound({2}, 0) == 0);
    assert(LowerBound({2}, 2) == 0);
    assert(LowerBound({2}, 3) == 1);
    assert(LowerBound({0, 3}, 2) == 1);
    assert(LowerBound({0, 3}, 4) == 2);
}

size_t LowerBoundLinear(const std::vector<int>& data, int elem) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] >= elem) {
            return i;
        }
    }
    return data.size();
}

std::vector<int> GenRandomArray(std::mt19937 *gen, size_t count, int from, int to) {
    std::uniform_int_distribution<int> dist(from, to);
    std::vector<int> data(count);
    for (int& cur : data) {
        cur = dist(*gen);
    }
    return data;
}

void StressTest() {
    std::mt19937 generator(72874);
    const int max_value = 100;
    const int max_size = 10;
    std::uniform_int_distribution<int> dist(0, max_value);
    for (int iter = 1; iter <= 100; ++iter) {
        std::cerr << "Test " << iter << "... ";
        auto data = GenRandomArray(&generator, max_size, 0, max_value);
        std::sort(data.begin(), data.end());
        int element = dist(generator);
        auto ok_answer = LowerBoundLinear(data, element);
        auto my_answer = LowerBound(data, element);
        if (ok_answer == my_answer) {
            std::cerr << "OK\n";
        } else {
            std::cerr << "Fail\n";
            for (auto cur : data) {
                std::cerr << cur << " ";
            }
            std::cerr << "\n";
            std::cerr << "Searching " << element << "\n";
            std::cerr << "Ok ans " << ok_answer << ", my ans " << my_answer << "\n";
            break;
        }
    }
}

std::vector<int> ReadArray() {
    size_t count;
    std::cin >> count;
    std::vector<int> data(count);
    for (int& cur : data) {
        std::cin >> cur;
    }
    return data;
}

int main() {
    // UnitTests();
    // StressTest();
    std::ios_base::sync_with_stdio(false);
    auto data = ReadArray();
    auto queries = ReadArray();

    for (int query : queries) {
        std::cout << LowerBound(data, query) << "\n";
    }
    return 0;
}