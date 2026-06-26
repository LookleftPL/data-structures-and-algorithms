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

 };


using namespace std;

int main() {
    cout << boolalpha;

    //
    // CZĘŚĆ 1: GRAF SKIEROWANY
    //
    cout << "--- GRAF SKIEROWANY ---" << endl;

    GraphAsMatrix gDir(10, true);
    Iterator<Vertex> & initVitDir = gDir.VerticesIter();
    while (!initVitDir.IsDone()) {
      Vertex & v = *initVitDir;
      v.weight = v.Number() * v.Number(); // [cite: 110]
      ++initVitDir;
 }
 delete &initVitDir;
    cout << "Liczba wierzcholkow: " << gDir.NumberOfVertices() << endl;
    cout << "Liczba krawedzi: " << gDir.NumberOfEdges() << endl;

    Vertex* vDir = gDir.SelectVertex(2);
    cout << "Unikalny Numer v: " << vDir->Number() << endl;
    vDir->weight = vDir->Number() * vDir->Number();
    cout << "Waga v: " << vDir->weight << endl;

    gDir.AddEdge(1, 2);
    gDir.AddEdge(1, 2);
    gDir.AddEdge(2, 3);
    gDir.AddEdge(3, 4);
    gDir.AddEdge(9, 9);

    cout << "Wierzcholki po dodaniu: " << gDir.NumberOfVertices() << endl;
    cout << "Krawedzie po dodaniu: " << gDir.NumberOfEdges() << endl;
    cout << "Czy istnieje krawedz (1,1): " << gDir.IsEdge(1, 1) << endl;
    cout << "Czy istnieje krawedz (1,2): " << gDir.IsEdge(1, 2) << endl;
    cout << "Czy istnieje krawedz (2,1): " << gDir.IsEdge(2, 1) << endl;

    Edge* e;

    e = gDir.SelectEdge(1, 2);
    cout << "e(1,2) V0: " << e->V0()->Number() << " V1: " << e->V1()->Number() << endl;
    cout << "Sasiad (V0): " << e->Mate(e->V0())->Number() << " Sasiad (V1): " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() + e->V1()->Number();
    cout << "Waga krawedzi e: " << e->weight << endl;

    e = gDir.SelectEdge(2, 3);
    cout << "e(2,3) V0: " << e->V0()->Number() << " V1: " << e->V1()->Number() << endl;
    cout << "Sasiad (V0): " << e->Mate(e->V0())->Number() << " Sasiad (V1): " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() + e->V1()->Number();
    cout << "Waga krawedzi e: " << e->weight << endl;

    e = gDir.SelectEdge(3, 4);
    cout << "e(3,4) V0: " << e->V0()->Number() << " V1: " << e->V1()->Number() << endl;
    cout << "Sasiad (V0): " << e->Mate(e->V0())->Number() << " Sasiad (V1): " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() + e->V1()->Number();
    cout << "Waga krawedzi e: " << e->weight << endl;

    e = gDir.SelectEdge(9, 9);
    cout << "e(9,9) V0: " << e->V0()->Number() << " V1: " << e->V1()->Number() << endl;
    cout << "Sasiad (V0): " << e->Mate(e->V0())->Number() << " Sasiad (V1): " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() + e->V1()->Number();
    cout << "Waga krawedzi e: " << e->weight << endl;


    //
    // CZĘŚĆ 2: GRAF NIESKIEROWANY
    //
    cout << "\n--- GRAF NIESKIEROWANY ---" << endl;

    GraphAsMatrix gUndir(10, false);
    Iterator<Vertex> & initVitUndir = gUndir.VerticesIter();
    while (!initVitUndir.IsDone()) {
      Vertex & v = *initVitUndir;
      v.weight = v.Number() * v.Number(); // [cite: 110]
      ++initVitUndir;
 }
 delete &initVitUndir;
    cout << "Liczba wierzcholkow: " << gUndir.NumberOfVertices() << endl;
    cout << "Liczba krawedzi: " << gUndir.NumberOfEdges() << endl;

    Vertex* vUndir = gUndir.SelectVertex(2);
    cout << "Unikalny Numer v: " << vUndir->Number() << endl;
    vUndir->weight = vUndir->Number() * vUndir->Number();
    cout << "Waga v: " << vUndir->weight << endl;

    gUndir.AddEdge(1, 2);
    gUndir.AddEdge(1, 2);
    gUndir.AddEdge(2, 3);
    gUndir.AddEdge(3, 4);
    gUndir.AddEdge(9, 9);

    cout << "Wierzcholki po dodaniu: " << gUndir.NumberOfVertices() << endl;
    cout << "Krawedzie po dodaniu: " << gUndir.NumberOfEdges() << endl;
    cout << "Czy istnieje krawedz (1,1): " << gUndir.IsEdge(1, 1) << endl;
    cout << "Czy istnieje krawedz (1,2): " << gUndir.IsEdge(1, 2) << endl;
    cout << "Czy istnieje krawedz (2,1): " << gUndir.IsEdge(2, 1) << endl;

    e = gUndir.SelectEdge(1, 2);
    cout << "e(1,2) V0: " << e->V0()->Number() << " V1: " << e->V1()->Number() << endl;
    cout << "Sasiad (V0): " << e->Mate(e->V0())->Number() << " Sasiad (V1): " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() + e->V1()->Number();
    cout << "Waga krawedzi e: " << e->weight << endl;

    e = gUndir.SelectEdge(2, 3);
    cout << "e(2,3) V0: " << e->V0()->Number() << " V1: " << e->V1()->Number() << endl;
    cout << "Sasiad (V0): " << e->Mate(e->V0())->Number() << " Sasiad (V1): " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() + e->V1()->Number();
    cout << "Waga krawedzi e: " << e->weight << endl;

    e = gUndir.SelectEdge(3, 4);
    cout << "e(3,4) V0: " << e->V0()->Number() << " V1: " << e->V1()->Number() << endl;
    cout << "Sasiad (V0): " << e->Mate(e->V0())->Number() << " Sasiad (V1): " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() + e->V1()->Number();
    cout << "Waga krawedzi e: " << e->weight << endl;

    e = gUndir.SelectEdge(9, 9);
    cout << "e(9,9) V0: " << e->V0()->Number() << " V1: " << e->V1()->Number() << endl;
    cout << "Sasiad (V0): " << e->Mate(e->V0())->Number() << " Sasiad (V1): " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() + e->V1()->Number();
    cout << "Waga krawedzi e: " << e->weight << endl;


   // NOWE TESTY ---------ITERATORY
  // SKIEROWANY
 // 1. Wypisanie wierzchołków
 cout << "\n--- Iteracja po wierzcholkach (Directed) ---" << endl;
 Iterator<Vertex> & vitDir = gDir.VerticesIter();
 while (!vitDir.IsDone()) {
  Vertex & v = *vitDir;
  cout << "V: " << v.Number() << " Waga: " << v.weight << endl;
  ++vitDir;
 }
 delete &vitDir;

 // 2. Dodanie wymaganych krawędzi
 gDir.AddEdge(3, 5);
 gDir.AddEdge(8, 3);
 gDir.AddEdge(5, 2);

 // 3. Wszystkie krawędzie
 cout << "\n--- Wszystkie krawedzie (Directed) ---" << endl;
 Iterator<Edge> & eitDir = gDir.EdgesIter();
 while (!eitDir.IsDone()) {
  Edge & e = *eitDir;
  cout << "E: " << e.V0()->Number() << " -> " << e.V1()->Number() << endl;
  ++eitDir;
 }
 delete &eitDir;

 // 4. Krawędzie wychodzące z 3
 cout << "\n--- Emanating z 3 (Directed) ---" << endl;
 Iterator<Edge> & emanIt = gDir.EmanatingEdgesIter(3);
 while (!emanIt.IsDone()) {
  cout << "Eman: " << (*emanIt).V0()->Number() << " -> " << (*emanIt).V1()->Number() << endl;
  ++emanIt;
 }
 delete &emanIt;

 // 5. Krawędzie dochodzące do 2
 cout << "\n--- Incident do 2 (Directed) ---" << endl;
 Iterator<Edge> & inciIt = gDir.IncidentEdgesIter(2);
 while (!inciIt.IsDone()) {
  cout << "Inci: " << (*inciIt).V0()->Number() << " -> " << (*inciIt).V1()->Number() << endl;
  ++inciIt;
 }
 delete &inciIt;

 // NIESKIEROWANY---------------------------------
 // Po dodaniu krawędzi do gUndir:
 cout << "\n--- Iteracja po wierzcholkach (Undirected) ---" << endl;
 Iterator<Vertex> & vitUndir = gUndir.VerticesIter();
 while (!vitUndir.IsDone()) {
  cout << "V: " << (*vitUndir).Number() << " Waga: " << (*vitUndir).weight << endl;
  ++vitUndir;
 }
 delete &vitUndir;
 gUndir.AddEdge(3, 5);
 gUndir.AddEdge(8, 3);
 gUndir.AddEdge(5, 2);

 cout << "\n--- Wszystkie krawedzie (Undirected) ---" << endl;
 Iterator<Edge> & eitUndir = gUndir.EdgesIter();
 while (!eitUndir.IsDone()) {
  Edge & e = *eitUndir;
  // Wypisze każdą krawędź dwa razy: raz jako (u,v) i raz jako (v,u)
  cout << "E: " << e.V0()->Number() << " - " << e.V1()->Number() << endl;
  ++eitUndir;
 }
 delete &eitUndir;

 cout << "\n--- Emanating/Incident dla 3 (Undirected) ---" << endl;
 Iterator<Edge> & emanUndir = gUndir.EmanatingEdgesIter(3);
 while (!emanUndir.IsDone()) {
  cout << "Krawedz przy 3: " << (*emanUndir).V0()->Number() << " <-> " << (*emanUndir).V1()->Number() << endl;
  ++emanUndir;
 }
 delete &emanUndir;

 cout << "\n--- TEST: Krawedzie dochodzace do (2) [Nieskierowany] ---" << endl;
 Iterator<Edge> &inciUndir = gUndir.IncidentEdgesIter(2); //
 while (!inciUndir.IsDone()) {
  Edge &e = *inciUndir;
  // Wypisujemy v0 i v1
  cout << "Dochodzaca (Undir): " << e.V0()->Number() << " - " << e.V1()->Number() << endl;
  ++inciUndir;
 }
 delete &inciUndir; //

    return 0;
}
