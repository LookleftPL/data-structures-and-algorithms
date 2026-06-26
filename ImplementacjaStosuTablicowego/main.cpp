#include <limits.h>
#include <iostream>
const int maxlength=100;
typedef int elementtype;
typedef int position;
class Stos
{
    int S[maxlength] ;
    position Top;//szczyt stosu
public:
    Stos() {
        Top=-1;
    }
    void Push(elementtype x) {
        if (Top==maxlength-1) {
            return;
        }
        Top++;
        S[Top]=x;
    }
    void Pop() {
        if (Empty()) {
            return;
        }
        Top = Top - 1;

    }
    bool Empty() {
        return Top==-1;
    }
    elementtype TopElem() {
        if (Empty()) {
            return INT_MIN;
        }
        return S[Top];
    }
    void Makenull() {
        Top=-1;
    }
};
using namespace std;
int main() {
    Stos stos;
    cout<<stos.Empty()<<endl;    // powinno byc 1 prawda
    stos.Push(5);
    cout<<stos.TopElem()<<endl;    // powinna byc 5
    cout<<stos.Empty()<<endl;     // powinno byc 0 falsz
    stos.Pop();
    cout<<stos.Empty()<<endl;     // powinna byc prawda 1
    stos.Push(2);
    stos.Push(3);
    cout<<stos.TopElem()<<endl; // powinna byc 3
    stos.Push(4);
    cout<<stos.TopElem()<<endl;
    stos.Makenull();
    cout<<stos.Empty()<<endl;  // powinna byc prawda 1
    return 0;
}
