#include <cstring>
#include <iostream>
const int B=65;
typedef char* elementtype;
struct celltype
{
    elementtype element;
    celltype * next;
};
typedef celltype* position; //
class dictionary
{
protected :
    position D[B];//tablica nagłówków list
public:
    dictionary() {
        for (int i = 0; i < B; i++) {
            D[i] = NULL;
        }
    }
    ~dictionary() {
        for (int i = 0; i < B; i++) {
            position p = D[i];
            while (p != NULL) {
                position temp = p;
                p = p->next;
                delete temp;
            }
            D[i] = NULL;
        }
    }
    void Makenul() {
        for (int i = 0; i < B; i++) {
            position p = D[i];
            while (p != NULL) {
                position temp = p;
                p = p->next;
                delete temp;
            }
            D[i] = NULL;
        }
    }
    bool Member(elementtype x) {
        int Hx = H(x);
        position p = D[Hx];
        while (p != NULL) {
            if (strcmp(p->element,x) == 0) {
                return true;
            }
            p = p->next;
        }
        return false;
    }
    void Insert(elementtype x) {
        if (!Member(x)) {
            int Hx = H(x);
            position p = new celltype;
            p->element = x;
            p->next = D[Hx];
            D[Hx] = p;
        }
    }
    void Delete(elementtype x) {
        int bucket  = H(x);
        position p = D[bucket];
        if (p == NULL) {
            return;
        }
        if (strcmp(p->element,x) == 0) {  // sprawdzamy pierwszy element
            D[bucket] = p->next;
            delete p;
            return;
        }
        position prev = p;
        p = p->next; // Przejdź do drugiego elementu

        while (p != NULL) {
            if (strcmp(p->element, x) == 0) {
                prev->next = p->next; // Omin usuwany element - przepnij wskaźnik
                delete p;             // Zwolnij pamięć
                return;
            }
            // wskaźniki o krok dalej
            prev = p;
            p = p->next;
        }
    }
    int H(elementtype x) {
        return int(x[0])%B;
    }
};
using namespace std;
int main() {
dictionary slownik;

    // Używamy rzutowania (char*), ponieważ elementtype jako char*,
    // a literały w C++ są stałymi (const char*).
    char* t1 = (char*)"Ala";
    char* t2 = (char*)"As";
    char* t3 = (char*)"Kita";

    // 1. Wstaw Ala
    slownik.Insert(t1);

    // 2. Wypisz Member Ala
    cout << slownik.Member(t1) << endl;

    // 3. Wypisz wartość hasz dla Ala
    cout << slownik.H(t1) << endl;

    // 4. Wstaw As
    slownik.Insert(t2);

    // 5. Wypisz Member As
    cout <<slownik.Member(t2) << endl;

    // 6. Wypisz wartość hasz dla As
    cout << slownik.H(t2) << endl;

    // 7. Wypisz Member Ala (sprawdzenie czy nadal istnieje)
    cout <<slownik.Member(t1) << endl;

    // 8. Wypisz wartość hasz dla Ala
    cout <<slownik.H(t1) << endl;

    // 9. Wstaw swoje nazwisko
    slownik.Insert(t3);

    // 10. Wypisz wartość hasz dla nazwiska
    cout << slownik.H(t3) << endl;

    // 11. Wypisz Member dla nazwiska
    cout <<slownik.Member(t3) << endl;

    // 12. Usuń Ala
    slownik.Delete(t1);

    // 13. Wypisz Member As (powinno być true(1))
    cout <<slownik.Member(t2)<< endl;

    // 14. Wypisz Member Ala (powinno być false(0))
    cout << slownik.Member(t1) << endl;

    // 15. Makenull
    slownik.Makenul();

    // 16. Wypisz Member As (powinno być false(0))
    cout <<slownik.Member(t2)<< endl;

    // 17. Wypisz Member dla nazwiska (powinno być false(0))
    cout <<slownik.Member(t3) << endl;



    return 0;
}