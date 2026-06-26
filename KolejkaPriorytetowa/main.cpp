#include <iostream>
#include <vector>
using namespace std;

class Container{
protected:
    Container (){};
public:
    virtual unsigned int Count () const = 0;
    virtual bool IsEmpty () const {return Count()==0;};
    virtual bool IsFull () const = 0;
    virtual void MakeNull() = 0;
};


template <typename T>
class PriorityQueue : public Container
{
public:
    virtual void Enqueue (T element) = 0;
    virtual T  FindMin () const = 0;
    virtual T DequeueMin () = 0;
};

template <typename T>
class BinaryHeap : public PriorityQueue<T>
{
protected:
    int count;
    std::vector<T> data;

public:

    BinaryHeap (unsigned int n): count(0), data(n){};
    BinaryHeap (): count(0), data(10) {};
    ~BinaryHeap (){;};
    void MakeNull() {
        count = 0;
    }
    void Enqueue (T element) {
        if (count == data.size()) {
            data.resize(count + 1);
        }
        count++;
        int i = count - 1;
        while (i != 0 && data[(i-1)/2] > element) {
            data[i] = data[(i-1)/2]; // przesiewanie
            i = (i-1)/2;
        }
        data[i] = element;
    }
    T FindMin () const {
        if (count > 0)
            return data[0];
        return T();
    }
    T DequeueMin () {
        if (IsEmpty()) {
            return T();
        }
        T min = FindMin();
        T last = data[count - 1];
        count--;
        int i = 0;
        while (2 * i + 1 < count) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallerChild = left; // zakladamy
            if ( right < count && data[right] < data[left]) {
                smallerChild = right;
            }

            if (last <= data[smallerChild]) {
                break;
            }
            data[i] = data[smallerChild];
            i = smallerChild;
        }
        data[i] = last;
        return min;
    }
    bool IsEmpty () const {
        return count == 0;
    }
    bool IsFull () const {
        return false;
    }
    void Wypisz() const {
        cout<<"KOPIEC:"<<endl;
        if (count == 0) {
            cout << "Pusty" << endl;
            return;
        }
        int elementsInLevel = 1; // Ile elementów powinno być na obecnym poziomie
        int elementsPrinted = 0; // Ile elementów wydrukowaliśmy na obecnym poziomie

        for (int i = 0; i < count; i++) {
            cout << data[i] << " ";
            elementsPrinted++;

            // Gdy wydrukujemy wszystkie węzły dla danego poziomu, przechodzimy do nowej linii
            if (elementsPrinted == elementsInLevel) {
                cout << endl;
                elementsInLevel *= 2; // Na kolejnym poziomie będzie 2x więcej węzłów
                elementsPrinted = 0;  // Zerujemy licznik dla nowego poziomu
            }
        }
        cout << endl<< "----------";
    }
    unsigned int Count() const {
        return count;
    }

};

int main() {
    cout <<boolalpha;


    BinaryHeap<int> heap(10);     // tworzymy kolejke
    cout << heap.IsEmpty() << endl;  // sprawdzamy czy jest pusta
    heap.Enqueue(5);         // wstawiamy 5
    cout << heap.IsEmpty() << endl; // sprawdzamy czy jest pusta
    heap.Wypisz();                 // wypisujemy tablice
    cout <<endl;                // endl
    cout << "Korzen: "<<heap.FindMin() << endl;  // wypisujemy Min
    heap.Enqueue(6);
    heap.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap.FindMin() << endl;
    heap.Enqueue(8);
    heap.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap.FindMin() << endl;
    heap.Enqueue(3);
    heap.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap.FindMin() << endl;
    heap.Enqueue(9);
    heap.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap.FindMin() << endl;
    heap.Enqueue(2);
    heap.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap.FindMin() << endl;

    heap.Enqueue(1);
    heap.Wypisz();
    cout << endl;

    heap.DequeueMin();
    heap.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap.FindMin() << endl;
    heap.DequeueMin();
    heap.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap.FindMin() << endl;
    cout << heap.IsEmpty() << endl;

    cout << endl;
    cout << "Teraz dla data[2]"<<endl;
    cout << endl;

    BinaryHeap<int> heap2(2);     // tworzymy kolejke
    cout << heap2.IsEmpty() << endl;  // sprawdzamy czy jest pusta
    heap2.Enqueue(5);         // wstawiamy 5
    cout << heap2.IsEmpty() << endl; // sprawdzamy czy jest pusta
    heap2.Wypisz();                 // wypisujemy tablice
    cout <<endl;                // endl
    cout << "Korzen: "<<heap2.FindMin() << endl;  // wypisujemy Min
    heap2.Enqueue(6);
    heap2.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap2.FindMin() << endl;
    heap2.Enqueue(8);
    heap2.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap2.FindMin() << endl;
    heap2.Enqueue(9);
    heap2.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap2.FindMin() << endl;
    heap2.Enqueue(2);
    heap2.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap2.FindMin() << endl;
    heap2.Enqueue(1);
    heap2.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap2.FindMin() << endl;

    heap2.DequeueMin();
    heap2.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap2.FindMin() << endl;
    heap2.DequeueMin();
    heap2.Wypisz();
    cout << endl;
    cout << "Korzen: "<< heap2.FindMin() << endl;
    cout << heap2.IsEmpty() << endl;

}