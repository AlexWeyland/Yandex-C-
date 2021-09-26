#include <iostream>
#include <vector>
#include <chrono>


template <typename T>
class Stack {
private:
    std::vector<T> array;
public:
    void push(const T);
    T pop();
    T getTop();
    bool isempty();
};


template <typename T>
void Stack<T>::push(const T val) {
    array.push_back(val);
}


template <typename T>
T Stack<T>::pop() {
    if (not array.empty()) {
        array.pop_back();
        return true;
    }
    else {
        return false;
    }
}


template <typename T>
T Stack<T>::getTop() {
    if (not array.empty()) {
        return array[array.size() - 1];
    }
    else {
        return '*';
    }
}


template <typename T>
bool Stack<T>::isempty() {
    return array.empty();
}


std::string ReadString() {
    std::string Mystr;
    std::cin >> Mystr;
    return Mystr;
}


bool isopen(char val) {
    if (val == '(' or val == '{' or val == '[') {
        return true;
    }
    else {
        return false;
    }
}


bool ispair(char val_1, char val_2) {
    if ((val_1 == '(' and val_2 == ')') or (val_1 == '[' and val_2 == ']') or (val_1 == '{' and val_2 == '}')) {
        return true;
    }
    else {
        return false;
    }
}


void answer(std::string Mystr) {
    Stack<char> symbols;
    size_t ans = 0;
    bool ind = true;
    for (size_t i = 0; i < Mystr.size(); ++i) {
        ans = i + 1;
        if (isopen(Mystr[i])) {
            symbols.push(Mystr[i]);
        }
        else {
            if (ispair(symbols.getTop(), Mystr[i])) {
                symbols.pop();
            }
            else {
                ans = i;
                ind = false;
                break;
            }
        }
    }
    if (ind) {
        std::cout << "CORRECT" << std::endl;
    }
    else {
        std::cout << ans << std::endl;
    }
}


void UnitTests() {
    answer("(((((((((((]");
    answer("(([])){}[[]]((())){}{}{}[]");
    answer("");
    answer("[}");
    answer("()()()()()()()()()()()()()()()()()()()()");
    answer("[(]())]{}");
    answer("]())(");
    answer("()){()()}");
}


void StressTest() {
    auto begin = std::chrono::steady_clock::now();
    std::string str_1(500000, '(');
    std::string str_2(500000, ')');
    answer(str_1 + str_2);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
}


int main() {
    std::ios_base::sync_with_stdio(false);
    //auto data = ReadString();
    //answer(data);
    //UnitTests();
    StressTest();
    return 0;
}
