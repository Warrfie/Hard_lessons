#include <iostream>
#include<tuple>
#include<vector>
#include<optional>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct Person {
    string last, first, pat;
public:
    Person(string ilast, string ifirst, string ipat) :last(ilast), first(ifirst) {
        if (ipat == "-") {
            pat = "No Patronymic";
        }
        else {
            pat = ipat;
        }
    }


    Person& operator= (const Person& right) {
        last = right.last;
        first = right.first;
        pat = right.pat;
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Person& person);

    bool operator< (const Person& right) {

        return tie(last, first, pat) < tie(right.last, right.first, right.pat);
    }

    bool operator== (const Person& right) {

        return tie(last, first, pat) == tie(right.last, right.first, right.pat);
    }

};

ostream& operator<<(ostream& out, const Person& person) {
    out << "|| Last Name: " << person.last << " || First Name: " << person.first << " || Patronymic: " << person.pat << " || ";
    return out;
}

struct PhoneNumber {
    int country, city;
    string number;
    optional<int> add;

public:
    PhoneNumber(int icountry, int icity, string inumber, string iadd) : country(icountry), city(icity), number(inumber) {
        if (iadd == "-") {
            add = nullopt;
        }
        else {
            add = stoi(iadd);
        }
    }


    friend ostream& operator<<(ostream& out, const PhoneNumber& phone_number);

    bool operator< (const PhoneNumber& right) {
        if (add.has_value() && right.add.has_value()) {
            return tie(country, city, number, add) < tie(right.country, right.city, right.number, right.add);
        }
        else {
            return tie(country, city, number) < tie(right.country, right.city, right.number);
        }
    }

    bool operator== (const PhoneNumber& right) {

        if (add.has_value() && right.add.has_value()) {
            return tie(country, city, number, add) < tie(right.country, right.city, right.number, right.add);
        }
        else {
            return tie(country, city, number) < tie(right.country, right.city, right.number);
        }
    }
};

ostream& operator<<(ostream& out, const PhoneNumber& phone_number) {
    out << "PhoneNumber: +" << phone_number.country << "(" << phone_number.city << ")" << phone_number.number;
    if (phone_number.add.has_value())out << " " << phone_number.add.value();
    out << endl;
    return out;
}

pair<Person, PhoneNumber> parse(string line) {
    int id = 0;
    string c;

    string country = "", city = "", number = "", add = "";

    string last = "", first = "", pat = "";

    for (int i = 0; i < line.size(); i++) {
        c = line[i];

        if (c == " ") {
            id++;
            continue;
        }
        switch (id) {

            case 0:
                last += c;
                break;
            case 1:
                first += c;
                break;
            case 2:
                pat += c;
                break;
            case 3:
                country += c;
                break;
            case 4:
                city += c;
                break;
            case 5:
                number += c;
                break;
            case 6:
                add += c;
                break;

        }
    }

    Person person(last, first, pat);
    PhoneNumber phone_number(stoi(country), stoi(city), number, add);
    pair<Person, PhoneNumber> out(person, phone_number);
    return out;


}

bool NameSort(pair<Person, PhoneNumber> first, pair<Person, PhoneNumber> second) {
    return first.first < second.first;
}

bool PhoneSort(pair<Person, PhoneNumber> first, pair<Person, PhoneNumber> second) {
    return first.second < second.second;
}

struct PhoneBook {
    vector<pair<Person, PhoneNumber>> book;

    PhoneBook(ifstream& file) {
        string line;
        while (getline(file, line)) {

            book.push_back(parse(line));
        }
    }

    friend ostream& operator<<(ostream& out, const PhoneBook& phone_book);

    void SortByName() {
        sort(book.begin(), book.end(), NameSort);
    }

    void SortByPhone() {
        sort(book.begin(), book.end(), PhoneSort);
    }

    tuple<string, string>  GetPhoneNumber(const string& surname) {
        int id, count = 0;
        stringstream ss;
        string phone;

        for (int i = 0; i < book.size(); i++) {
            if (book[i].first.first == surname) {
                id = i;
                count++;
            }
        }
        if (count == 0) {
            return tie(surname, "not found");
        }
        else if (count == 1) {
            ss << book[id].second;
            phone = ss.str();
            return tie(surname, phone);
        }
        else if (count > 1) {
            return tie(surname, "found more than 1");
        }
    }

    void  ChangePhoneNumber(const Person& person, PhoneNumber phone) {
        for (int i = 0; i < book.size(); i++) {
            if (book[i].first == person) {
                book[i].second = phone;
            }
        }
    }
};

ostream& operator<<(ostream& out, const PhoneBook& phone_book) {
    for (const auto& [person, phone_book] : phone_book.book) {
        out << person << phone_book << endl;
    }

    return out;
}

int main()
{

    ifstream file("book.txt");
    PhoneBook book(file);
    cout << book;
    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;

    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;
    auto print_phone_number = [&book](const string& surname) {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer);
        else
            cout << get<0>(answer);
        cout << endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", "-" });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", "13" });
    cout << book;
}
