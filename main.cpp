#include <iostream>
#include <list>

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


int main() {
    
}
