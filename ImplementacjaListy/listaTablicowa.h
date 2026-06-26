#ifndef LISTATABLICOWA_H
#define LISTATABLICOWA_H

typedef int elementtype, position;
const int maxlength = 10;

struct List {
    elementtype elements[maxlength];
    int last;
};

position END(List l);
position First(List l);
position Next(position p, List l);
position Previous(position p, List l);
position Locate(elementtype x, List l);
elementtype Retrieve(position p, List l);
bool Insert(int x, position p, List &l);
bool Delete(position p, List &l);

#endif // LISTATABLICOWA_H