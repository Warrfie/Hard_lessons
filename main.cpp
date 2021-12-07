#include <iostream>
#include <list>
#include <vector>

using namespace std;

void avg_list(list<int> &n){
    int av=0,j=0;
    for(auto i:n){
        av+=i;
        j++;
    }
    av=av/j;
    n.push_back(av);
}



class Matrix {
public:
    vector<vector<int>> matr;

    bool check_list (const initializer_list<initializer_list<int>> &list){
        if (list.size()>3) {
            cout<<"Matrix > 3";
            return false;
        }
        for(auto i:list){

            if (list.size()!=i.size()){
                cout<<"Matrix ne kvadrat";
                return false;
            }
        }
        cout<<"Matrix is OK"<<endl;
        return  true;
    }

    Matrix(const initializer_list<initializer_list<int>> &list){
        check_list(list);
        vector<int> buf;

        for(auto col:list){
            for(auto row:col){
               buf.push_back(row);
            }
           matr.push_back(buf);
            buf.clear();

    }

    }
    void print(){
for(auto i:matr){
    for(auto j:i){
        cout<<j<<":";
    }
    cout<<endl;
}
    }

    int determ(){
        switch (matr.size()) {
            case 1:
                return matr[0][0];
                break;
            case 2:
                return matr[0][0]*matr[1][1]-matr[0][1]*matr[1][0];
                break;
            case 3:
                // Тут можно было сделать рекурсивную функцию, разбивающую матрицу на матрицы 2-го порядка, но нет времени на красивое выполнение задания
                return matr[0][0]*matr[1][1]*matr[2][2]-matr[0][0]*matr[1][2]*matr[2][1]-matr[0][1]*matr[1][0]*matr[2][2]+matr[0][1]*matr[1][2]*matr[2][0]+matr[0][2]*matr[1][0]*matr[2][1]-matr[0][2]*matr[1][1]*matr[2][0];
        }
    }

};


class OwnIterator: public std::iterator<std::input_iterator_tag, vector<int>>
{
    friend class OwnContainer;
private:
    OwnIterator(vector<int>* p);
public:
    OwnIterator(const OwnIterator &it);

    bool operator!=(OwnIterator const& other) const;
    bool operator==(OwnIterator const& other) const; //need for BOOST_FOREACH
    typename OwnIterator::reference operator*() const;
    OwnIterator& operator++();
private:
    vector<int>* p;
};


class Iterator {
    vector<int> vec;
    int* _begin;
    int* _end;

public:

    Iterator(vector<int>& ivec):vec(ivec){
        _begin = &vec.front();
        _end=_begin+vec.size();
    }
    int* begin(){
        return _begin;
    }
    int* end(){
        return _end;
    }
};


int main() {
    Matrix x{{1,2,3},
             {4,5,6},
             {7,8,9}} ;
    x.print();
    cout<<"Det="<<x.determ()<<endl;
    vector<int> vec{1,2,3,4,5};
    Iterator mi(vec);
    for(auto i:mi){
        cout<<i<<endl;
    }

}
