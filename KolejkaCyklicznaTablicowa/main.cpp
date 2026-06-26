#include <iostream>
#include <climits>
const int maxlength = 50;
typedef int elementtype;
typedef int position;

class Kolejka {
    protected:
        elementtype Queue[maxlength];  // indeksy od 0 do 49 , ale mozemy zmiescisc max 49 elementow
        position Front;   // indeks elementu czołowego
        position Rear;    // indeks ostaniego elementu
    public:
        Kolejka() {                             // done
            Front = 0;
            Rear = maxlength-1;
        };
        int AddOne(int i) {                         // done
            return (i+1)%maxlength;
        }
        void Enqueue(elementtype x) {              // done
            if (AddOne(AddOne(Rear)) == Front) {
                return;
            }
            Rear = AddOne(Rear);
            Queue[Rear] = x;

        }
        void Dequeue() {
            if (Empty()) {               // done
                return;
            }
            Front = AddOne(Front);
        }
        elementtype FrontElem() {      // done
            if (Empty()) {
                return INT_MIN;
            }
            return Queue[Front];
        }
        void Makenul() {            //done
            Front = 0;
            Rear = maxlength-1;
        }
        bool Empty() {                  // done
            return Front==AddOne(Rear);
        }
};


using namespace std;

int main() {
    Kolejka kolejka;

    cout<<kolejka.Empty()<<endl;   // true    printuje
    kolejka.Enqueue(5);           //
    cout<<kolejka.Empty()<<endl;   // false
    cout<<kolejka.FrontElem()<<endl; // 5
    kolejka.Dequeue();                //
    cout<<kolejka.Empty()<<endl;   // true
    kolejka.Enqueue(4);           // 4
    kolejka.Enqueue(3);           // 4 3
    kolejka.Enqueue(2);           // 4 3 2
    cout<<kolejka.FrontElem()<<endl; // 4
    kolejka.Enqueue(1);           // 4 3 2 1
    cout<<kolejka.FrontElem()<<endl; // 4
    kolejka.Dequeue();            // 3 2 1
    cout<<kolejka.FrontElem()<<endl; // 3
    kolejka.Enqueue(6);        // 3 2 1 6
    cout<<kolejka.FrontElem()<<endl; // 3
    kolejka.Dequeue();   // 2 1 6
    kolejka.Dequeue();   //  1 6
    cout<<kolejka.FrontElem()<<endl; // 1
    kolejka.Makenul();   //
    cout<<kolejka.Empty()<<endl;  // true

    return 0;
}

