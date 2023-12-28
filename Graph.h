#ifndef PROJETO2AED_GRAPH_H
#define PROJETO2AED_GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field

    void addEdge(Vertex<T> *dest, double w, std::string);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    friend class Graph<T>;
};

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    std::string attribute; // edge attribute
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w, std::string attr = "");
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    double getWeight() const;
    void setWeight(double weight);
    string getAttribute() const;
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w, std::string attr);
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    int inDegree(const T &v) const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, std::string attr): dest(d), weight(w), attribute(attr) {}


template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}

template<class T>
void Edge<T>::setWeight(double weight) {
    Edge::weight = weight;
}
template<class T>
string Edge<T>::getAttribute() const {
    return attribute;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


//=============================================================================
// Exercise 1: Graph implementation
//=============================================================================
// Subexercise 1.1: addVertex
//=============================================================================
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
//TODO
template <class T>
bool Graph<T>::addVertex(const T &in) {
    // Check if a vertex with the same content already exists
    if (findVertex(in) != nullptr) {
        // Vertex with the same content already exists
        return false;
    }

    // Create a new vertex with the provided content
    Vertex<T> *newVertex = new Vertex<T>(in);

    // Add the new vertex to the graph
    vertexSet.push_back(newVertex);

    return true;
}

//=============================================================================
// Subexercise 1.2: addEdge
//=============================================================================
/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
//TODO
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, std::string attr) {
    // Find the source and destination vertices
    Vertex<T> *sourceVertex = findVertex(sourc);
    Vertex<T> *destVertex = findVertex(dest);

    // Check if both source and destination vertices exist
    if (sourceVertex == nullptr || destVertex == nullptr) {
        // One or both of the vertices do not exist
        return false;
    }

    // Create a new edge from the source to the destination with the given weight
    Edge<T> newEdge(destVertex, w, attr);

    // Add the new edge to the source vertex's adjacency list
    sourceVertex->addEdge(destVertex, w, attr);

    // Update the adjacency list of the source vertex using setAdj
    sourceVertex->setAdj(sourceVertex->getAdj());

    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
//TODO
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w, std::string attr) {
    Edge<T> newEdge(d, w, attr);
    adj.push_back(newEdge);
}

//=============================================================================
// Subexercise 1.3: removeEdge
//=============================================================================
/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
//TODO
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    // HINT: Use "findVertex" to obtain the actual vertices.
    // HINT: Use "removeEgeTo" to actually remove the edge.
    // Find the source and destination vertices
    Vertex<T> *sourceVertex = findVertex(sourc);
    Vertex<T> *destVertex = findVertex(dest);

    // Check if both source and destination vertices exist
    if (sourceVertex == nullptr || destVertex == nullptr) {
        // One or both of the vertices do not exist
        return false;
    }

    // Use the removeEdgeTo method to remove the edge
    return sourceVertex->removeEdgeTo(destVertex);
    return false;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
//TODO
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    // HINT: use an iterator to scan the "adj" vector and then erase the edge.
    // Use an iterator to scan the "adj" vector and erase the edge
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        if (it->getDest() == d) {
            adj.erase(it);
            return true;  // Edge found and removed
        }
    }
    // Edge not found
    return false;
}

//=============================================================================
// Subexercise 1.4: removeVertex
//=============================================================================
/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
//TODO
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    // HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
    // HINT: take advantage of "removeEdgeTo" to remove incoming edges.
    // Find the vertex with the specified content
    auto it = find_if(vertexSet.begin(), vertexSet.end(), [&in](Vertex<T> *v) {
        return v->getInfo() == in;
    });

    // Check if the vertex with the specified content was found
    if (it == vertexSet.end()) {
        // Vertex not found
        return false;
    }

    // Remove incoming edges to the vertex
    for (Vertex<T> *v : vertexSet) {
        v->removeEdgeTo(*it);
    }

    // Erase the vertex from the vertexSet
    delete *it;  // Delete the vertex to free memory
    vertexSet.erase(it);

    return true;
};
#endif //PROJETO2AED_GRAPH_H
