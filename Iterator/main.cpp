#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Iterator {
	public:
		virtual ~Iterator() {};
		Iterator(){;}
		virtual bool isDone() const = 0;
		virtual const T& operator*() = 0;
		virtual void operator++() = 0;

};



template <typename T>
class Visitor
{
public:
    virtual void Visit (T & element) =0;
    virtual bool IsDone () const
	{ return false; }
};



template <typename T>
class Container
{protected:

    Container (){};
 public:
    virtual int Count () const = 0;
    virtual bool IsEmpty () const {return Count()==0;};
    virtual bool IsFull () const = 0;
   	virtual void MakeNull() = 0;
 	virtual void Accept (Visitor<T> & v)=0;
 };



template <typename T>
class Set : public virtual Container<T>
{
protected:
  int count;
  int universeSize;
public:
	Set (int n) : universeSize (n) {
		universeSize = n;
		count = 0;
	}
	int UniverseSize() const {return universeSize;}
	int Count() const {return count;};
	virtual void Insert (T element)=0;
	virtual bool IsMember (T element) const=0;
	virtual void Withdraw (T element)=0;
 };


class SetAsArray : public Set<int>
{
	class Iter: public Iterator<int> {
		std::vector<bool> data;
		int universeSize;
		int index;
		public:
			Iter(std::vector<bool> array, int us): data(array), universeSize(us), index(0) {
				while (index < universeSize && !data[index]) {
					index++;
				}
			}
			~Iter(){}
			const int & operator*() override {
				return index;
			}
			void operator ++ () override {
				for (index++;index < universeSize;index++) {
					if (data[index]) {
						break;
					}
				}

			}
			bool isDone () const override {
				return index >= universeSize;
			}
	};
    vector<bool> array;
public:
    SetAsArray (unsigned int n): Set(n), array(n) {
    	for (int i = 0; i < n; i++) {
    		array[i] = false;
    	}
    }
	void MakeNull() {
	    for (int i = 0; i<universeSize;i++) {
		    array[i] = false;
	    }
    	count == 0;
    }//metody z containera
    void Insert (int element) {
    	if (array[element] == false) {
    		array[element] = true;
    		count++;
    	}
    	else {
    		return;
    	}

    }
	bool IsMember (int element) const {
	    return array[element];
    }
	void Withdraw (int element) {
	    if (array[element] == true) {
		    array[element] = false;
	    	count--;
	    }
    }
	bool IsFull () const {
		return (Count()==UniverseSize());
	};
	void Accept (Visitor<int> & v) {

	}
	//friend- funkcja uzyska prawo dostepu do prywatnych element�w danej klasy.

	friend SetAsArray operator + (
	SetAsArray const& s, SetAsArray const& t) {
		SetAsArray l(s.universeSize);
		for (int i = 0; i < s.universeSize; i++) {
			if (s.array[i] == true || t.array[i] == true) {
				l.array[i] = true;
				l.count++;
			}
		}
		return l;
	}
	friend SetAsArray operator - (
	SetAsArray const& s, SetAsArray const& t) {
		SetAsArray l(s.UniverseSize());
		for (int i = 0; i < s.universeSize; i++) {
			if (s.array[i]==true  && t.array[i] == false) {
				l.array[i] = true;
				l.count++;
			}
		}
		return l;
	}
    friend SetAsArray operator * (
	SetAsArray const& s, SetAsArray const& t) {
		SetAsArray l(s.universeSize);
		for (int i = 0; i < s.universeSize; i++) {
			if (s.array[i] == true && t.array[i] == true) {
				l.array[i] = true;
				l.count++;
			}
		}
		return l;
	}
    friend bool operator == (
	SetAsArray const& s, SetAsArray const& t) {
    	if (s.universeSize == t.universeSize) {
    		for (int i = 0; i < s.universeSize; i++) {
    			if (s.array[i] != t.array[i]) {
    				return false;
    			}
    		}
    		return true;
    	}
    	return false;
    }
    friend bool operator <= (
	SetAsArray const& s, SetAsArray const& t) {
    	if (s.universeSize != t.universeSize) {
    		return false;
    	}
    	if (s.universeSize == 0) {
    		return true;
    	}
	    if (s.universeSize == t.universeSize) {
		    for (int i = 0; i < s.universeSize; i++) {
			    if (s.array[i] == true) {
				    if (t.array[i] != true) {
				    	return false;
				    }
			    }
		    }
	    	return true;
	    }
    }

    void Wypisz() const {
		for (int i = 0; i < universeSize; i++) {
			if (array[i] == true) {
				cout << i << " ";
			}
		}
		cout << endl;
	}
	Iter & NewIterator() {
		return * new Iter(array,universeSize);
	}
};

class Odd_Visitor:public Visitor<int>
{
protected:
bool IsDone_;
public:
Odd_Visitor():IsDone_(false){};
void Visit(int & element) {if (element%2==1) IsDone_=true;
};
bool IsDone(){return IsDone_;}
};

int main() {
    SetAsArray A(10);
	SetAsArray B(10);
	for (int i = 0; i < 10; i++) {  // wstawiamt elementy parzyste do A
		if (i%2 == 0) {
			A.Insert(i);
		}
		if (i%2 != 0) {   // wstawiamy elementy nieparzyste do B
			B.Insert(i);
		}
	}
	Iterator<int>& itA = A.NewIterator();
	Iterator<int>& itB = B.NewIterator();
	while (!itA.isDone()) {
		cout << *itA << " ";
		++itA;
	}
	cout << endl;
	while (!itB.isDone()) {
		cout << *itB << " ";
		++itB;
	}
}