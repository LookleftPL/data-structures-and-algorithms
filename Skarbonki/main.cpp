#include <iostream>
#include <vector>



template <typename T>

class Iterator
{
public:
 virtual ~Iterator (){;}
 Iterator(){;}
 virtual bool IsDone () = 0;
 virtual T & operator * () = 0;
 virtual void operator ++ () = 0;
};

class Vertex
{
 int number;
public:
 int weight;
 std::string label;
 Vertex(int n) {
  number = n;
 }
 int Number() const {
  return number;
 }
};


class Edge
{
protected:
 Vertex* v0;
 Vertex* v1;
public:
 int weight;
 std::string label;
 Edge (Vertex *V0, Vertex* V1) {
  v0 = V0;
  v1 = V1;
 }
 Vertex* V0 (){return v0;};
 Vertex* V1 (){return v1;};
 Vertex* Mate (Vertex *v) {
  if (v == v0) {
   return v1;
  }
  return v0;
 }
};

class GraphAsMatrix {
  std::vector<Vertex *> vertices;
  std::vector< std::vector<Edge *> > adjacencyMatrix;
  std::vector<bool> visited;
  bool isDirected;
  int numberOfVertices;
  int numberOfEdges=0;
  public:
 class AllVerticesIter: public Iterator<Vertex>
 {
  GraphAsMatrix & owner;
  int current;
 public:
  AllVerticesIter(GraphAsMatrix &owner):owner(owner), current(0) {}
  bool IsDone() override {
   return current >= owner.NumberOfVertices();
  }
  Vertex & operator*() override {
    return *(owner.vertices[current]);
  };
  void operator++() override {
   current++;
  };
 };
 class AllEdgesIter: public Iterator<Edge>
 {
  GraphAsMatrix & owner;
  int row;
  int col;
  public:
   void next() {
    col++;
     for (; row<owner.numberOfVertices; row++) {
      for (; col<owner.numberOfVertices; col++) {
         if (owner.adjacencyMatrix[row][col]!=nullptr) {
          return;
         }
      }
      col = 0;
     }

   }
   AllEdgesIter(GraphAsMatrix &owner): owner(owner),row(0), col(-1) {
    next();
   }
   bool IsDone() override {
    return row >= owner.NumberOfVertices();
   }
   Edge & operator*() override {
     return *(owner.adjacencyMatrix[row][col]);
   };
   void operator++() override {
    next();
   }
 };
 class EmanEdgesIter: public Iterator<Edge>
 {
  GraphAsMatrix & owner;
  int row;
  int col;
 public:
  void next() {
   col++;
   for (; col < owner.NumberOfVertices(); col++) {
    if (owner.adjacencyMatrix[row][col] != nullptr) {
     return;
    }
   }
  }
  EmanEdgesIter(GraphAsMatrix &owner,int v):owner(owner), row(v),col(-1) {
   next();
  }
  bool IsDone() override {
   return col >= owner.NumberOfVertices();
  };
  Edge & operator*() override {
   return *(owner.adjacencyMatrix[row][col]);
  }
  void operator++()override {
   next();
  }
 };

 class InciEdgesIter: public Iterator<Edge>
 {
  GraphAsMatrix & owner;
  int row;
  int col;
 public:
  void next() {
   row++;
   for (; row < owner.NumberOfVertices(); row++) {
    if (owner.adjacencyMatrix[row][col] != nullptr) {
     return;
    }
   }
  }
  InciEdgesIter(GraphAsMatrix &owner,int v):owner(owner), row(-1), col(v) {
   next();
  }
  bool IsDone()override {
   return row >= owner.NumberOfVertices();
  }
  Edge & operator*() override {
   return *(owner.adjacencyMatrix[row][col]);
  }
  void operator++()override {
   next();
  }
 };

  GraphAsMatrix (int n, bool b) {
   isDirected = b;
   numberOfVertices = n;

   visited.resize(n,false);
   for (int i = 0; i < numberOfVertices; i++) {
    vertices.push_back(new Vertex(i));
   }
   adjacencyMatrix.resize(n, std::vector<Edge *>(n,nullptr));
  }
  int NumberOfVertices() {
   return numberOfVertices;
  }
  bool IsDirected() {
   return isDirected;
  }
  int NumberOfEdges() {
   return numberOfEdges;
  }
  bool IsEdge(int u, int v) {
   if (u < 0 || u >= numberOfVertices || v < 0 || v >= numberOfVertices) return false;
   return adjacencyMatrix[u][v] != nullptr;
  }
  void MakeNull() {
   for (int i = 0; i < numberOfVertices; i++) {
    for (int j = 0; j < numberOfVertices; j++) {
     if (adjacencyMatrix[i][j] != nullptr) {
      // W grafie nieskierowanym ten sam wskaźnik może być w dwóch miejscach
      // dlatego sprawdzamy czy nie usuwamy dwa razy tego samego
      if (!isDirected && i > j) {
       adjacencyMatrix[i][j] = nullptr;
      } else {
       delete adjacencyMatrix[i][j];
       adjacencyMatrix[i][j] = nullptr;
      }
     }
    }
   }
   numberOfEdges = 0;
  }
  void AddEdge (int u, int v) {
   if (u>= numberOfVertices || v>= numberOfVertices|| u<0 || v<0)
    return;

   Edge* edge = new Edge(vertices[u], vertices[v]);
   adjacencyMatrix[u][v] = edge;
   if (!IsDirected()) {
    adjacencyMatrix[v][u] = edge;
   }
   numberOfEdges++;
  }
  Edge * SelectEdge (int u, int v) {
   if (u < 0 || u >= numberOfVertices || v < 0 || v >= numberOfVertices) return nullptr;
   return adjacencyMatrix[u][v];
  }
  Vertex * SelectVertex(int v) {
   if (v>=0 && v<numberOfVertices) {
    return vertices[v];
   }
   return nullptr;
  }
 Iterator<Vertex> & VerticesIter() {
   return *new AllVerticesIter(*this);
  }
 Iterator<Edge> & EdgesIter() {
   return *new AllEdgesIter(*this);
  }
 Iterator<Edge> & EmanatingEdgesIter(int v) {
   return *new EmanEdgesIter(*this,v);
  }
 Iterator<Edge> & IncidentEdgesIter(int v) {
   return *new InciEdgesIter(*this,v);
  }

 int DFS_Skarbonki() { // przechodzimy przez caly graf i zliczamy skladowe
   int licznik_spojnych_skladowych=0;;
   for (int i=0; i < numberOfVertices; i++) {    // ustawiamy visited na false
     visited[i] = false;
   }
   Iterator<Vertex> &vit = VerticesIter();       // tworzymy iterator ktory pozwala na przegladanie wiecholkow
   while (!vit.IsDone()) {
    Vertex &x = *vit;            // pobieramy referencje do aktualnie rozpatrywanego wiercholka
    if (!visited[x.Number()]) {           // sprawdzamy czy wierzcholek zostal odwiedzony
     licznik_spojnych_skladowych++;
     DFS_1(&x, visited);                // wywolujemy DFS_1 startujac od aktualnie rozpatrywanego wierzcholka
    }
    ++vit;                        // przesuwamy na kolejny wierzcholek
   }
   delete &vit;
   return licznik_spojnych_skladowych;
  }
//--------------------------------------------------------------

 void DFS_1(Vertex *v, std::vector<bool> & visited) {
   visited[v->Number()] = true;

   Iterator<Edge> &eit = EmanatingEdgesIter(v->Number());  // tworzymy iterator po krawedziach wychodzacych z wierzcholka v
   while (!eit.IsDone()) {
    Edge &e = *eit;           // pobietamy referencje do aktualnie badanej  krawedzi
    Vertex *u = e.Mate(v);      // wierzocholek na drugim koncu

    if (!visited[u->Number()]) {       // sprawdzamy czy nieodwiedzony
     DFS_1(u, visited);         // jesli nieodwiedzony to rekurencyjnie schodzimy w glab
    }
    ++eit;                 // przesuwamy na kolejna krawedz
   }
   delete &eit;
  }
 };

using namespace std;

int main() {
    int n; // liczba skarbonek
    cout<<"Podaj liczbe skarbonek: "<<endl;
    cin >> n;

    GraphAsMatrix graf(n, false);// tworzymy graf nieskierowany
    cout<<"Podaj sekwencje skarbonek:"<<endl;
    for (int i = 0; i < n; i++) {
     int skarbonka_z_kluczem;
     cin >> skarbonka_z_kluczem;
     // w grafie indeksujemu od 0 a tutaj numery skarbonek sa od 1 wiec musimy odpowiednio dopasowac
     int lokalizacja_klucza = skarbonka_z_kluczem - 1;
     int skarbonka_do_klucza = i;

     graf.AddEdge(lokalizacja_klucza, skarbonka_do_klucza); // dodajemy krawedz łączaca skarbonki
    }
    int wynik = graf.DFS_Skarbonki();
    cout<<"Nalezy rozbic tyle skarbonek:"<<endl;
    cout<<wynik<<endl;
    return 0;
}

