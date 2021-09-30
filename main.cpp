#include <iostream>
#include <vector>
#include <chrono>


std::vector<std::vector<int> > ReadData(int amount, int lenght) {
    std::vector<std::vector<int> > data(amount, std::vector<int> (lenght));
    for (auto &array : data) {
        for (auto &elem : array) {
            std::cin >> elem;
        }
    }
    return data;
}


int Search(std::vector<int> inc_array, std::vector<int> dec_array, int lenght) {
    int first = 0;
    int last = lenght - 1;
    while (last - first > 1) {
        int medium = (last - first) / 2 + first;
        if (dec_array[medium] > inc_array[medium]) {
            first = medium;
        } else {
            last = medium;
        }
    }
    if (dec_array[first] <= inc_array[last]) {
        return first;
    } else {
        return last;
    }
}


void answer(std::vector<std::vector<int> > inc_arrays, std::vector<std::vector<int> > dec_arrays, int lenght) {
    int cnt_question;
    int inc_number, dec_number;
    std::cin >> cnt_question;
    for (int number = 0; number < cnt_question; ++number) {
        std::cin >> inc_number >> dec_number;
        int ans = Search(inc_arrays[inc_number - 1], dec_arrays[dec_number - 1], lenght) + 1;
        std::cout << ans << std::endl;
    }
}


void UnitTests() {
    
}


void StressTest() {
   
}


int main() {
    std::ios_base::sync_with_stdio(false);
    int cnt_a, cnt_b, len;
    std::cin >> cnt_a >> cnt_b >> len;
    std::vector<std::vector<int> > data_1 = ReadData(cnt_a, len);
    std::vector<std::vector<int> > data_2 = ReadData(cnt_b, len);
    answer(data_1, data_2, len);
    return 0;
}
