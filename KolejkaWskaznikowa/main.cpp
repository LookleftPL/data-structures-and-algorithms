#include <iostream>
#include <limits.h>
#include <stdio.h>
typedef int elementtype;
struct celltype
{
    elementtype element;
    celltype * next;
};
typedef celltype * position;
class Queue
{
protected:
    position Front; // wskaźnik do głowy listy
    position Rear; // wskaźnik do ostatniego elementu
public:
    Queue() {
        position l = new celltype;
        l->next = NULL;
        Rear = l;
        Front = l;
    }
    ~Queue() {
        while (!Empty()) {
            Dequeue();
        }
        delete Front;
    }
    void Enqueue(elementtype x) {
        Rear->next = new celltype; // tworzymy nowa komorke
        Rear->next->element = x; // wstawiamy tam x
        Rear = Rear->next; // ustawiawmy rear na nowy element
        Rear->next = NULL;  // ustawiamy nexta rear'a na NULL

    }
    void Dequeue() {
        if (Empty()) {
            return;
        }
        position tmp = Front;
        Front = Front->next;
        delete tmp;
    }
    elementtype FrontElem() {
        if (Empty()) {
            return INT_MIN;
        }
        return Front->next->element;
    }
    bool Empty() {
        return Front == Rear;
    }
    void Makenull() {
        while (!Empty()) {
            Dequeue();
        }
    }
};


using namespace std;


int main() {
    Queue q;
    cout<< q.Empty()<<endl;  // 1
    q.Enqueue(5);
    cout<<q.Empty()<< endl; // 0
    cout<<q.FrontElem()<<endl; //5
    q.Dequeue();
    cout<<q.Empty()<<endl; // 1
    q.Enqueue(4);
    q.Enqueue(3);
    q.Enqueue(2);
    cout<<q.FrontElem()<<endl; // 4
    q.Enqueue(1);
    cout<<q.FrontElem()<<endl; // 4
    q.Dequeue();
    cout<<q.FrontElem()<<endl;  // 3
    q.Enqueue(6);
    cout<<q.FrontElem()<< endl; // 3
    q.Dequeue();
    q.Dequeue();
    cout<<q.FrontElem()<< endl;  // 1
    q.Makenull();
    cout<<q.Empty()<< endl;  // 1
    return 0;
}