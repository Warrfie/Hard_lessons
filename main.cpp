#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() -m_beg).count();
    }

public:
    Timer() : m_beg(clock_t::now()) { }
    Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }

    void start(std::string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};


template <typename T>
void Swap (T &a,T &b){
    T temp;
    temp=a;
    a=b;
    b=temp;
}


template <typename T>
void SortPointers (vector<T> &a){
    sort(a.begin(),a.end(),
         [](T a1,T a2)
         {return(*a1>*a2);});
}


bool find_let (char a){
    string s;
    s.push_back(a);
    return ((s.find('a') != string::npos)||(s.find('e') != string::npos)||(s.find('o') != string::npos));// не стал писать прям все гласные, не вижу смысла для теста
}


int main() {
    setlocale(LC_ALL, "Russian");
int *a,*b;
a=new int(1);
b=new int(2);
cout<<"a="<<*a<<"b="<<*b<<endl;
cout<<"&a="<<a<<"&b="<<b<<endl;
Swap(a,b);
cout<<"a="<<*a<<"b="<<*b<<endl;
cout<<"&a="<<a<<"&b="<<b<<endl;

vector<int*> vec;

for (int i=0;i<10;i++){
    vec.push_back(new int(i));
}

    for (auto out:vec){
        cout<<*out<<endl;
    }
    SortPointers(vec);
    for (auto out:vec){
        cout<<*out<<endl;
    }

    string test="a";
    cout<<(test.find('a')!=string::npos)<<endl;

    ifstream file("War and peace.txt");
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0);
    string s(size, ' ');
    file.read(&s[0], size);
    {
        Timer timer("count_if and find");
        cout << count_if(s.begin(), s.end(), find_let);
        timer.print();
    }
    {
        Timer timer("count_if and for");
        cout << count_if(s.begin(), s.end(), []
                (auto a)
        {
            vector<char> vec = {'e','a','o'};
            for(auto l:vec){
                if (l==a) return true;
            }
            return false;
        });
        timer.print();
    }
    {
        Timer timer("for and find");
        int i=0;
        for (auto a:s)
        {

            if(find_let(a) ) i++;
        };
        cout << i;
        timer.print();
    }
    {
        Timer timer("for and for");
        int i=0;
        vector<char> vec = {'e','a','o'};
        for (auto a:s)
        {

            for(auto l:vec){
                if (l==a) i++;
            }

        };
        cout << i;
        timer.print();
    }
    return 0;
}
