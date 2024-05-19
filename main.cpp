#include <iostream>
#include <string>
#include <utility>
#include "TicketSystem.hpp"
//#define aaa
using namespace std;

template<typename aaaaa>
class A {
private:
public:
    string aaa;
public:
    A(std::string  filePath) : aaa(std::move(filePath)) {}
};
//class B : public A {
//public:
//#ifdef aaa
//    int b;
//#endif
//};

int main() {
    freopen("test.out", "w", stdout);
//    A<int> s("jferuhf    ioj");
//    cout<<s.aaa;
    clearFile();
//    std::cout<<0b11111110<<std::endl;
//    string str,str1;
//    cin>>str1;
//    fstream f1(str1,ios::out|ios::binary);
//    remove(str1.c_str());
//    f1.close();
//    getline(cin, str);
//    cout<<str1<<endl<<str;
//    sjtu::vector<string> v;
//    splitString(str, v);
//    for (auto &i : v) {
//        cout << i << endl;
//    }
    TicketSystem ticketSystem;
    ticketSystem.run();
//    B aa;
//    aa.b=0;
//    string s;
//    cin >> s;
//    cout << s << endl;
    return 0;
}
