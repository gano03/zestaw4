#include "singlelist.h"
#include <iostream>
#include <cstdlib>

int main (void)
{
    SingleList<int> obj;
    SingleList<int> L;
    obj.back();
    obj.front();
    
    std::cout << "Empty " << obj.empty() <<"\n";
    
    obj.insert(0,1);
    std::cout << "Rozmiar listy to " <<obj.size()<<"\n";
    obj.insert(1,3);
    obj.insert(2,7);
    std::cout << "Empty " << obj.empty() <<"\n";

    std::cout << obj.index(10) <<"\n";
    std::cout << obj.index(1) <<"\n";
    std::cout << obj.index(3) <<"\n";
    std::cout << obj.index(7) <<"\n";

    obj.push_front(12);
    obj.push_back(14);
    std::cout << obj.front() <<"\n";
    std::cout << obj.back() << "\n";
    obj[0] = 8;
    obj.display();

    L = obj;
    L.display();
    
    L[2] = 5;
    L.display();

    L.erase(2);
    std::cout << "last to " <<L.size() << "\n";
    L.display();

    std::cout << "Rozmiar listy to " <<L.size() <<"\n";

    L.pop_front();
    L.pop_back();
    L.display();
    obj.display();


    std::cout << "Rozmiar listy to " <<obj.size()<<"\n";
    L.insert(1,10);
    L.insert(2,12);
    L.insert(2,11);
    L.display();

    L.clear();
    L.display();
    std::cout << "test3\n";
    return 0;
}