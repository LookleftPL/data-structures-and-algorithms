#include <iostream>
#include <climits>

typedef int elementtype;
struct celltype {                  // typ komórka
    elementtype element;
    celltype* next;                // wskaznik na nastepnego typu celltype
};
typedef celltype* position;       // czyli position = celltype*
class Lista
{
protected :
    position l; // wskaźnik do głowy listy
public:
    Lista() {
        l = new celltype; // wskaźnik celltype* l przechowuje teraz adres, bo new zawiera adres (sterta)
        l->next = NULL;   // -> wyłuskuje pole next z l
    } //konstruktor
    ~Lista(){
        position p = l;
        while (p != NULL) {
            position nextNode = p->next;
            delete p;
            p = nextNode;
        }
    } //destruktor
    void Insert(elementtype x, position p) {
        position tmp = p->next;     // zapisujemy adres elementu za p
        p->next = new celltype;      // wstawiamy nowa komorke za p
        p->next->element = x;        // wstawiamy do tej komorki wartosc x
        p->next->next = tmp;        // łączymy teraz nowa komórkę z tą która była wczesniej za p
        
    }
    void Delete(position p) {
        if (p->next != NULL) {
            position tmp = p->next;    // zapisujemy tymczasowo adres komorki ktory chcemy usunac
            p->next = p->next->next;   // przepinamy zeby z p kolejnym elementym byl element po tym ktory chcemy usunac
            delete tmp;                 // usuwamy tmp
        }

    }
    elementtype Retrieve(position p) {
        if (p->next == NULL) {
            return INT_MIN;
        }
        return p->next->element;
    }
    position Locate(elementtype x) {
        position tmp = l;
        while (tmp->next != NULL && tmp->next->element != x) {
            tmp = tmp->next;
        }
        return tmp;
    }
    position First() {
        return l;
    }
    position Next(position p) {
        return p->next;
    }
    position Previous(position p) {
        position tmp = l;
        while (tmp-> next != p && tmp->next != NULL) {
            tmp = tmp->next;
        }
        return tmp;
    }
    position END() {
        position tmp = l;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        return tmp;
    }
};
using namespace std;

void print(Lista &lista) {
    position komorka = lista.Next(lista.First());
    while (komorka != NULL) {
        printf("%d ", komorka->element);
        komorka = lista.Next(komorka);
    }
    printf("\n");
}

int main() {
    Lista mojaLista;

    mojaLista.Insert(5,mojaLista.First());        // dodajemy 5 na poczatek
    cout << mojaLista.Retrieve(mojaLista.First())<<endl;   // wypisujemy ten element

    mojaLista.Insert(2,mojaLista.First());                 // dodajemy 2 na poczatek
    cout << mojaLista.Retrieve(mojaLista.First())<<" ";     // pierwszy element
    cout << mojaLista.Retrieve(mojaLista.Next(mojaLista.First()))<<endl;  // drugi element

    mojaLista.Insert(1,mojaLista.Next(mojaLista.First())); // wstawiamy 1 za pierwszym elementem
    print(mojaLista);                           // printujemy liste

    mojaLista.Insert(100,mojaLista.END());      // wstawiamy 100 na koncu
    print(mojaLista);                             // printujemy liste

    mojaLista.Delete(mojaLista.Previous(mojaLista.Locate(100))); // usuwamy element przed 100
    print(mojaLista);// printujemy liste
    mojaLista.Delete(mojaLista.Locate(1));
    print(mojaLista);

    return 0;
}