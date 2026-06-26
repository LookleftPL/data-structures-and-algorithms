#include <iostream>
#include <vector>
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

 };


using namespace std;

int main() {
    cout << boolalpha;

    //
    // CZĘŚĆ 1: GRAF SKIEROWANY
    //
    cout << "--- GRAF SKIEROWANY ---" << endl;

    GraphAsMatrix gDir(10, true);
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


    return 0;
}