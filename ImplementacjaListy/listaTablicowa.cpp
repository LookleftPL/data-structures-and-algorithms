typedef int elementtype, position ; //  typedef sprawia ze mozemy pisac np elementtype zamiast int i to bedzie to samo
const int maxlength=10;          // dlugosc listy
struct List						// struktura lista zawieajacy tablice intow o dlguosci 10
{
	elementtype elements[maxlength];
	int last;           //indeks ostatniego elementu listy
};

position END(List l)    // zwraca indeks konca listy
{ 
	return l.last + 1;
}

position First(List l) // zwraca indeks poczatku listy (czyli zawsze 0)
{
	return 0;
}

position Next(position p,List l) // zwraca indeks kolejny po p
{
	if (p>l.last || p < First(l)) {
		return -1;
	}
	return p + 1;
}


position Previous(position p,List l) 
{
	if (p<=First(l) || p > END(l)) {
		return -1;
	}
	return p - 1;
}



position Locate(elementtype x, List l) 
{ //zwraca pozycje x w l, gdy nie ma x w l zwraca end(l)
	for (int i = First(l);i<=l.last;i++) {
		if (x == l.elements[i]) {
			return i;
		}
	}
	return END(l);
}

elementtype Retrieve(position p, List l) 
{
	if (p>l.last || p < First(l)) {
		return -10000000;
	}
	return l.elements[p];
}

bool Insert(int x, position p, List &l)
{
	if (p>END(l) || p < First(l)) {
		return false;
	}
	if (l.last == maxlength-1) {
		return false;
	}
	if (p == END(l)) {
		l.elements[p] = x;
		l.last++;
		return true;
	}
	for (int i = l.last;i>=p;i--) {
		l.elements[i+1] = l.elements[i] ;
	}
	l.elements[p] = x;
	l.last++;
	return true;
}

bool Delete(position p, List &l)
{
	if (p>l.last || p < First(l)) {
		return false;
	}
	for (int i = p;i<l.last;i++) {
		l.elements[i] = l.elements[i+1];
	}
	l.last--;
	return true;
}
