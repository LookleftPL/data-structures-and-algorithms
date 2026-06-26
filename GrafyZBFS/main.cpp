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
 void DFS(Vertex *v) {
   for (int i = 0; i < numberOfVertices; i++) {  // ustawiamy tablice visited na false
    visited[i] = false;
   }
   if (v != nullptr) {            // jezeli wskaznik nie jest null pointerem to wywolujemy DFS1
    DFS1(v,visited);
   }
   Iterator<Vertex> &vit = VerticesIter();        // tworzymy iterator po wierzcholkach
   while (!vit.IsDone()) {
    Vertex &x = *vit;
    if (!visited[x.Number()]) {                  // jezeli nieodwiedzony
     DFS1(&x,visited);                        // to DFS1
    }
    ++vit;                                      // przesuwamy o kolejny wierzcholek
   }
   delete &vit;

  }
 void DFS1(Vertex *v,std::vector<bool> & visited) {
   std::cout << v->Number() << " ";             // wypisujemy wierzcholek
   visited[v->Number()] = true;                 // oznaczamy jako odwiedzony

   Iterator<Edge> &eit = EmanatingEdgesIter(v->Number());  // tworzymy iterator po
   while (!eit.IsDone()) {
    Edge &e = *eit;
    Vertex *u = e.Mate(v);

    if (!visited[u->Number()]) {
     DFS1(u, visited);
    }
    ++eit;
   }
   delete &eit;
  }

 };


using namespace std;

int main() {
 //  DFS grafu nieskierowanego
 std::cout << "--- 1. DFS grafu nieskierowanego ---" << std::endl;
 // Tworzymy graf nieskierowany  o 10 wierzchołkach
 GraphAsMatrix* graph = new GraphAsMatrix(10, false);

 // Dodawanie krawędzi
 graph->AddEdge(0, 1);
 graph->AddEdge(1, 2);
 graph->AddEdge(2, 3);
 graph->AddEdge(3, 4);
 graph->AddEdge(3, 7);
 graph->AddEdge(4, 5);
 graph->AddEdge(5, 9);
 graph->AddEdge(9, 9);
 graph->AddEdge(6, 8);
 graph->AddEdge(8, 6);
 graph->AddEdge(0, 8);
 graph->AddEdge(5, 7);

 std::cout << "Kolejnosc odwiedzin DFS (start od wierzcholka 0): " << std::endl;
 graph->DFS(graph->SelectVertex(0));
 std::cout << "\n" << std::endl;


 //  DFS grafu skierowanego
 std::cout << "--- 2. DFS grafu skierowanego ---" << std::endl;
 // Tworzymy graf skierowany (true) o 10 wierzchołkach
 GraphAsMatrix* graphDir = new GraphAsMatrix(10, true);

 // Dodawanie krawędzi
 graphDir->AddEdge(0, 1);
 graphDir->AddEdge(1, 2);
 graphDir->AddEdge(2, 3);
 graphDir->AddEdge(3, 4);
 graphDir->AddEdge(3, 7);
 graphDir->AddEdge(4, 5);
 graphDir->AddEdge(5, 9);
 graphDir->AddEdge(9, 9);
 graphDir->AddEdge(6, 8);

 std::cout << "Kolejnosc odwiedzin DFS (start od wierzcholka 0): " << std::endl;
 graphDir->DFS(graphDir->SelectVertex(0));
 std::cout << "\n" << std::endl;

 // Czyszczenie pamięci
 delete graph;
 delete graphDir;

 return 0;

    return 0;
}

