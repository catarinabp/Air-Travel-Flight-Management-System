#ifndef PROJETO2AED_GRAPH_H
#define PROJETO2AED_GRAPH_H

#include <cstddef>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <list>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

/****************** Provided structures  ********************/

/**
 * @brief Represents a vertex in the graph.
 */
template <class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field

    void addEdge(Vertex<T> *dest, std::string w);
    bool removeEdgeTo(Vertex<T> *d);
    bool removeEdgeToByWeight(Vertex<T> *d, const string &weight);
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

/**
 * @brief Represents an edge in the graph.
 */
template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    std::string weight;         // edge weight
public:
    Edge(Vertex<T> *d, std::string w);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    std::string getWeight() const;
    void setWeight(std::string weight);
    friend class Graph<T>;
    friend class Vertex<T>;
};

/**
 * @brief Represents a graph.
 */
template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;      // vertex set
    int _index_;                        // auxiliary field
    stack<Vertex<T>> _stack_;           // auxiliary field
    list<list<T>> _list_sccs_;        // auxiliary field

    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, string w);
    bool removeEdge(const T &sourc, const T &dest);
    bool removeEdgeByWeight(const T &sourc, const T &dest, const string &weight);
    vector<Vertex<T> * > getVertexSet() const;
    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
};

/****************** Provided constructors and functions ********************/

/**
 * @brief Constructor for the Vertex class.
 * @param in Content of the vertex.
 */
template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/**
 * @brief Constructor for the Edge class.
 * @param d Destination vertex.
 * @param w Edge weight.
 */
template <class T>
Edge<T>::Edge(Vertex<T> *d, std::string w): dest(d), weight(std::move(w)) {}

/**
 * @brief Gets the number of vertices in the graph.
 * @return The number of vertices.
 */
template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

/**
 * @brief Gets the vertex set of the graph.
 * @return Vector of vertices.
 */
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

/**
 * @brief Gets the content of the vertex.
 * @return The content of the vertex.
 */
template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

/**
 * @brief Sets the content of the vertex.
 * @param in The new content.
 */
template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

/**
 * @brief Checks if the vertex is being processed.
 * @return True if the vertex is being processed, false otherwise.
 */
template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

/**
 * @brief Sets the processing status of the vertex.
 * @param p The processing status.
 */
template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

/**
 * @brief Gets the destination vertex of the edge.
 * @return The destination vertex.
 */
template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

/**
 * @brief Sets the destination vertex of the edge.
 * @param d The destination vertex.
 */
template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

/**
 * @brief Gets the weight of the edge.
 * @return The weight of the edge.
 */
template<class T>
std::string Edge<T>::getWeight() const {
    return weight;
}

/**
 * @brief Sets the weight of the edge.
 * @param weight The new weight.
 */
template<class T>
void Edge<T>::setWeight(std::string weight) {
    Edge::weight = weight;
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

/**
 * @brief Checks if the vertex has been visited.
 * @return True if the vertex has been visited, false otherwise.
 */
template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

/**
 * @brief Sets the visited status of the vertex.
 * @param v The visited status.
 */
template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

/**
 * @brief Gets the adjacency list of the vertex.
 * @return The adjacency list of the vertex.
 */
template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

/**
 * @brief Sets the adjacency list of the vertex.
 * @param adj The new adjacency list.
 */
template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, string w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, string w) {
    adj.push_back(Edge<T>(d, w));
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    auto newEnd = remove_if(adj.begin(), adj.end(),
                            [d](const Edge<T>& edge) { return edge.dest == d; });

    bool removed = (newEnd != adj.end());

    // Erase the elements marked for removal
    adj.erase(newEnd, adj.end());

    return removed;
}

/**
 * @brief Removes an edge from a graph by its weight.
 * The edge is identified by the source (sourc) and destination (dest) contents,
 * and the weight of the edge.
 * @param sourc Source vertex content.
 * @param dest Destination vertex content.
 * @param weight Weight of the edge.
 * @return True if successful, false otherwise.
 */
template <class T>
bool Graph<T>::removeEdgeByWeight(const T &sourc, const T &dest, const string &weight) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    return v1->removeEdgeToByWeight(v2, weight);
}

/**
 * @brief Removes an edge from a vertex by its weight.
 * The edge is identified by the destination (d) vertex and the weight of the edge.
 * @param d Destination vertex.
 * @param weight Weight of the edge.
 * @return True if successful, false otherwise.
 */
template <class T>
bool Vertex<T>::removeEdgeToByWeight(Vertex<T> *d, const string &weight) {
    auto newEnd = remove_if(adj.begin(), adj.end(),
                            [d, weight](const Edge<T>& edge) {
                                return edge.dest == d && edge.weight == weight;
                            });

    bool removed = (newEnd != adj.end());

    // Erase the elements marked for removal
    adj.erase(newEnd);

    return removed;
}

/**
 * @brief Removes a vertex with a given content from the graph.
 *
 * Removes the vertex with the specified content (in) from the graph, including
 * all outgoing and incoming edges. Returns true if the removal is successful,
 * and false if a vertex with the given content does not exist.
 *
 * @param in The content of the vertex to be removed.
 * @return true if successful, false otherwise.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    auto v = findVertex(in);
    if (v == NULL)
        return false;

    for (auto u : vertexSet)
        u->removeEdgeTo(v);

    auto it = vertexSet.begin();
    while (it != vertexSet.end()) {
        if (*it == v) {
            it = vertexSet.erase(it);
            delete v;
        } else {
            ++it;
        }
    }

    return true;
}

/****************** DFS ********************/

/**
 * @brief Performs a depth-first search (DFS) traversal in the graph.
 *
 * Returns a vector containing the contents of the vertices in DFS order.
 * Follows the DFS algorithm as described in theoretical classes.
 *
 * @return Vector with the contents of the vertices by DFS order.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (!v->visited)
            dfsVisit(v, res);
    return res;
}

/**
 * @brief Auxiliary function for DFS that visits a vertex and its adjacent vertices recursively.
 *
 * Updates a parameter with the list of visited node contents during DFS traversal.
 *
 * @param v Pointer to the current vertex.
 * @param res Vector to store the contents of visited vertices in DFS order.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> &res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto &e : v->adj) {
        auto w = e.dest;
        if (!w->visited)
            dfsVisit(w, res);
    }
}

/****************** DFS ********************/

/**
 * @brief Performs a depth-first search (DFS) in the graph starting from the source node.
 *
 * Returns a vector containing the contents of the vertices in DFS order starting from
 * the specified source node. If the source node is not found, an empty vector is returned.
 *
 * @param source The content of the source node for DFS.
 * @return Vector with the contents of the vertices by DFS order from the source node.
 */
template <class T>
vector<T> Graph<T>::dfs(const T &source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}

/****************** BFS ********************/

/**
 * @brief Performs a breadth-first search (BFS) in the graph starting from the source node.
 *
 * Returns a vector containing the contents of the vertices in BFS order starting from
 * the specified source node. If the source node is not found, an empty vector is returned.
 *
 * @param source The content of the source node for BFS.
 * @return Vector with the contents of the vertices by BFS order from the source node.
 */
template <class T>
vector<T> Graph<T>::bfs(const T &source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto &e : v->adj) {
            auto w = e.dest;
            if (!w->visited) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}
#endif //PROJETO2AED_GRAPH_H
