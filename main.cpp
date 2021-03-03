#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

class Cell{
public:
    int item;
    string name;
    string surname;
    string fname;
    string number;
    
    void print() {
        std:: cout << item << " " << surname << " " << name << " " << fname << " " << number << endl;
    }
    
};

bool comp (Cell x, Cell y) {
 
  return x.surname < y.surname;
 
}

class PhoneBook{
public:
    vector <Cell> entrys;
    
    void edit(int number) {
        entrys[number - 1].print();
        std:: cout << "Введите новое имя\n";
        std:: cin >> entrys[number - 1].name;
        std:: cout << "Введите новую фамилию\n";
        std:: cin >> entrys[number - 1].surname;
        std:: cout << "Введите новое отчество\n";
        std:: cin >> entrys[number - 1].fname;
        std:: cout << "Введите новый номер\n";
        std:: cin >> entrys[number - 1].number;
    }
    
    void print_all() {
        for (auto val: entrys)
            val.print();
    }
    
    void swap(int a, int b) {
        Cell temporary;
        int temp;
        temporary = entrys[a - 1];
        entrys[a - 1] = entrys[b - 1];
        entrys[b - 1] = temporary;
        temp = entrys[a - 1].item;
        entrys[a - 1].item = entrys[b - 1].item;
        entrys[b - 1].item = temp;
    }
    
    void exit() {
        ofstream fout("/Users/aleksandr/Desktop/output.txt");
        for (auto val: entrys)
            fout << val.item << " " << val.surname << " " << val.name << " " << val.fname << " " << val.number << endl;
        fout.close();
    }
    
    void add() {
        Cell new_contact;
        if (entrys.size() == 0) {
            new_contact.item = 1;
        } else {
            new_contact.item = entrys.back().item + 1;
        }
        std:: cout << "Введите имя нового контакта\n";
        std:: cin >> new_contact.name;
        std:: cout << "Введите фамилию нового контакта\n";
        std:: cin >> new_contact.surname;
        std:: cout << "Введите отчество нового контакта\n";
        std:: cin >> new_contact.fname;
        std:: cout << "Введите номер нового контакта\n";
        std:: cin >> new_contact.number;
        entrys.push_back(new_contact);
    }
    
    void
    del(int number) {
        entrys.erase(entrys.begin() + number - 1);
        for (int i = number - 1; i < entrys.size(); ++i)
            entrys[i].item = entrys[i].item - 1;
    }
    
    void transfer(int number, int place) {
        if (place <= entrys.size()) {
            Cell tem;
            if (number < place) {
                for (int i=number - 1; i < place - 1; ++i) {
                    Cell temporary;
                    int temp;
                    temporary = entrys[i];
                    entrys[i] = entrys[i+1];
                    entrys[i+1] = temporary;
                    temp = entrys[i].item;
                    entrys[i].item = entrys[i+1].item;
                    entrys[i+1].item = temp;
                }
            } else {
                for (int i=place - 1; i > number - 1; --i) {
                    Cell temporary;
                    int temp;
                    temporary = entrys[i];
                    entrys[i] = entrys[i-1];
                    entrys[i-1] = temporary;
                    temp = entrys[i].item;
                    entrys[i].item = entrys[i-1].item;
                    entrys[i-1].item = temp;
                }
            }
        }
        else{
            std:: cout << "Неверное место";
        }
    }
    
    void search(string given) {
        int p;
        for (auto val: entrys) {
            p = val.number.find(given);
            if (p == 0) {
                val.print();
            }
        }
    }
    
    void alf() {
        vector <Cell> dubl;
        dubl = entrys;
        sort (dubl.begin(), dubl.end(), comp);
        for (auto val: dubl)
            val.print();
    }
    
    void myadd(Cell newcont) {
        entrys.push_back(newcont);
    }
    
};

bool file_notempty(std::ifstream& pFile) {
    return pFile.peek() != std::ifstream::traits_type::eof();
}

int main() {
    PhoneBook book;
    string answer, c, d, s, word;
    int a, b, i;
    string words[5];
    std:: ifstream fin("/Users/aleksandr/Desktop/output.txt");
    if (file_notempty(fin)) {
        while (getline(fin, s)) {
            cout << s << endl;
            stringstream ss(s);
            i = 0;
            while (ss>>word) {
                words[i] = word;
                i ++;
            }
            Cell contact;
            i = std::stoi(words[0]);
            contact.item = i;
            contact.surname = words[1];
            contact.name = words[2];
            contact.fname = words[3];
            contact.number = words[4];
            book.myadd(contact);
        }
    }
    fin.close();
    for ( ; ;) {
        answer = "";
        std:: cout << "Выберите команду" << endl;
        std:: cout << "Доступные команды: add, print, edit, swap, alphabet, search, transfer, exit" << endl;
        cin >> answer;
        if (answer == "exit") {
            book.exit();
            break;
        }
        if (answer == "swap") {
            std:: cout << "Какие записи поменять местами?\n";
            cin >> a >> b;
            book.swap(a, b);
        }
        if (answer == "add") {
            book.add();
        }
        if (answer == "alphabet") {
            book.alf();
        }
        if (answer == "search") {
            std:: cout << "Введите номер или его часть\n";
            string phone;
            cin >> phone;
            book.search(phone);
        }
        if (answer == "transfer") {
            std:: cout << "Введите номей записи, которую хотите перенести\n";
            cin >> a;
            std:: cout << "Введите куда ее перенести\n";
            cin >> b;
            book.transfer(a, b);
        }
        if (answer == "print") {
            book.print_all();
        }
        if (answer == "edit") {
            std:: cout << "Введите номер записи для редактирования\n";
            cin >> a;
            book.edit(a);
        }
    }
    return 0;
}
