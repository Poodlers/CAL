/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(int id,Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;
    double getEdgeDistance(Vertex<T>* dest);
    Edge<T> getEdge(Vertex<T>* dest);

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(int id, Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(id, d, w));
}

template <class T>
double Vertex<T>::getEdgeDistance(Vertex<T>* dest) {
    for(Edge<T> edge: this->adj){
        if(edge.getDest() == dest){
            return edge.getWeight();
        }
    }
    return 0;
}

template <class T>
Edge<T> Vertex<T>::getEdge(Vertex<T>* dest) {
    for(Edge<T> edge: this->adj){
        if(edge.getDest() == dest){
            return edge;
        }
    }
    return Edge<T>(0, nullptr,0);
}


template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    int id;
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(int id,Vertex<T> *d, double w);

    Vertex<T> *getDest() const;

    double getWeight() const;

    int getId() const;

    void setId(int id);

    friend class Graph<T>;
    friend class Vertex<T>;

};

template <class T>
Edge<T>::Edge(int id,Vertex<T> *d, double w): id(id),dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    int originNode = 0;
public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(int id,const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;
    void setOriginNode(int originNode);
    T getOriginNode();

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}

template<class T>
int Edge<T>::getId() const {
    return id;
}

template<class T>
void Edge<T>::setId(int id) {
    Edge::id = id;
}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
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
bool Graph<T>::addEdge(int id,const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(id,v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for(Vertex<T>* vertex: vertexSet){
        vertex->visited = false;
    }

    std::queue<Vertex<T> *> vertex_queue;
    Vertex<T>* vertexSource = findVertex(orig);
    vertex_queue.push(vertexSource);
    vertexSource->visited = true;
    Vertex<T>* vertexCurrent;

    while(!vertex_queue.empty()){
        vertexCurrent = vertex_queue.front();
        vertex_queue.pop();

        for(Edge<T> edge: vertexCurrent->adj){
            if(!edge.dest->visited){
                vertex_queue.push(edge.dest);
                edge.dest->visited = true;
                edge.dest->dist = vertexCurrent->dist++;
                edge.dest->path = vertexCurrent;
            }
        }
    }

}

template <class T>
void Graph<T>::setOriginNode(int originNode) {
    this->originNode = originNode;
}

template <class T>
T Graph<T>::getOriginNode() {
    return this->vertexSet[originNode]->info;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for(Vertex<T>* vertex: getVertexSet()){
        vertex->dist = 9999;
        vertex->path = NULL;
    }
    Vertex<T>* vertexSource = findVertex(origin);
    vertexSource->dist = 0;
    vertexSource->path = NULL;

    MutablePriorityQueue<Vertex<T> > q;
    q.insert(vertexSource);
    Vertex<T>* vertexCurrent;
    while(!q.empty()){
        vertexCurrent = q.extractMin();
        for(Edge<T> edge: vertexCurrent->adj){
            if(edge.dest->dist > vertexCurrent->dist + edge.weight){
                edge.dest->dist = vertexCurrent->dist + edge.weight;
                edge.dest->path = vertexCurrent;
                q.insert(edge.dest);
            }
        }
    }

}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    // TODO implement this
    for(Vertex<T>* vertex: getVertexSet()){
        vertex->dist = 9999;
        vertex->path = NULL;
    }

    int temp_distance = 0;
    Vertex<T>* vertexSource = findVertex(orig);
    vertexSource->dist = 0;
    for(Vertex<T>* vertex: getVertexSet()){
        //iterate through every edge V times

        for(Vertex<T>* vertex1: getVertexSet()){
            for(Edge<T> edge: vertex1->adj){
                temp_distance = vertex1->dist + edge.weight;
                if(temp_distance < edge.dest->dist){
                    edge.dest->dist = temp_distance;
                    edge.dest->path = vertex1;
                }
            }
        }

    }

    //iterate through every edge again
    for(Vertex<T>* vertex1: getVertexSet()){
        for(Edge<T> edge: vertex1->adj){
            if(vertex1->dist + edge.weight < edge.dest->dist){
                std::cout << "Negative cycle exists!" << std::endl;
            }
        }
    }

}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    T currInfo = dest;
    while(currInfo != origin){
        res.push_back(currInfo);
        currInfo = findVertex(currInfo)->path->info;
    }
    res.push_back(origin);
    std::reverse(res.begin(),res.end());
    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // TODO implement this

}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;
    // TODO implement this
    return res;
}


#endif /* GRAPH_H_ */
