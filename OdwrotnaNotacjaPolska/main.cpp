#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

vector<string> zOdpowiedziDoListy(string odpowiedz) {
    string bufor = "";
    vector<string> listaElementow;
    for (int i = 0; i < odpowiedz.length(); i++) {
        if (odpowiedz[i] == ' ') {
            listaElementow.push_back(bufor); // dodawanie elementu
            bufor = "";
        }
        else {
            bufor += odpowiedz[i];
        }
    }
    if (!bufor.empty()) {
        listaElementow.push_back(bufor);
    }
    return listaElementow;
}
int priorytet(string operatorr) {
    if (operatorr == "~") {
        return 4;
    }
    if (operatorr == "^") {
        return 3;
    }
    if (operatorr == "*" || operatorr == "/") {
        return 2;
    }
    if (operatorr == "+" || operatorr == "-") {
        return 1;
    }
    return 0;

}
bool czyOperator(string element) {
    return element == "*" || element == "/" || element == "^" || element == "+" || element == "-" || element == "~";
}

string doONP(string odpowiedz) {
    vector<string> listaElementow = zOdpowiedziDoListy(odpowiedz);
    stack<string> stos;
    string wynik = "";
    for (int i = 0; i < listaElementow.size(); i++) {
        if (isdigit(listaElementow[i][0])) {
            wynik += listaElementow[i] + " ";
        }
        else {
            if (czyOperator(listaElementow[i])) {
                if (!stos.empty()) {
                    while (stos.empty() == 0 && priorytet(stos.top())>=priorytet(listaElementow[i])) {
                        wynik += stos.top() + " ";
                        stos.pop();
                    }
                }
                stos.push(listaElementow[i]);
            } else if(listaElementow[i] == "(") {
                stos.push(listaElementow[i]);
            } else if(listaElementow[i] == ")") {

                while (stos.top() != "(") {
                    wynik += stos.top() + " ";
                    stos.pop();
                }
                if (!stos.empty()) {
                    stos.pop();
                }
            }

        }


    }
    while (stos.empty() == 0) {
        wynik += stos.top() + " ";
        stos.pop();
    }
    return wynik;
}

int obliczONP(string odpowiedz) {
    vector<string> listaElementow = zOdpowiedziDoListy(odpowiedz);
    stack<int> stos;
    for (int i = 0; i < listaElementow.size(); i++) {
        if (isdigit(listaElementow[i][0])) {
            stos.push(stoi(listaElementow[i]));
        }
        else {
            if (listaElementow[i] == "~") {
                int a = stos.top();
                stos.pop();
                stos.push(-a);
            } else {
                int a = stos.top();
                stos.pop();
                int b = stos.top();
                stos.pop();
                if (listaElementow[i] == "+")
                    stos.push(b + a);
                else if (listaElementow[i] == "-")
                    stos.push(b - a);
                else if (listaElementow[i] == "*")
                    stos.push(b * a);
                else if (listaElementow[i] == "/")
                    stos.push(b / a);
                else if (listaElementow[i] == "^")
                    stos.push(pow(b,a));
            }

        }

    }
    return stos.top();
}


int main() {
    string wybor;
    string odpowiedz;
    cout<<"================================"<<endl;
    cout<<"ODWROTNA NOTACJA POLSKA PROGRAM"<<endl;
    cout<<"================================"<<endl;
    while (true) {
        cout<<"MENU"<<endl;
        cout<<"1. Konwersja z wyrazenia z notacji tradycyjnej do ONP"<<endl;
        cout<<"2. Obliczanie wartosci wyrazenia podanego w notacji ONP"<<endl;
        cout<<"3. Wylacz program"<<endl;
        cout<<"================================"<<endl;
        cout<<"Wybierz co zrobic:"<<endl;
        getline(cin,wybor);
        if (wybor == "1") {
            cout<<"Podaj wyrazenie w notacji tradycyjnej(kazdy element oddzielony spacja):"<<endl;
            getline(cin, odpowiedz);
            cout<<"Oto wyrazenie w ONP:"<<endl;
            cout<<doONP(odpowiedz)<<endl;
        }
        else if (wybor == "2") {
            cout<<"Podaj wyrazenie w ONP(kazdy element oddzielony spacja):"<<endl;
            getline(cin, odpowiedz);
            cout<<"Oto wynik:"<<endl;
            cout<<obliczONP(odpowiedz)<<endl;
        }
        else if (wybor == "3") {
            break;
        }
        else {
            break;
        }

    }

    return 0;
}