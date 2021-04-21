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

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;
    double getEdgeDistance(Vertex<T>* dest);

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
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
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
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);

    Vertex<T> *getDest() const;

    double getWeight() const;

    friend class Graph<T>;
    friend class Vertex<T>;

};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    void whereCarWithNoWeightLimitBacktracking(int visited_nodes, int &max_nodes, Node node1, Node last_node, std::vector<T> providers , std::vector<Node> cur_path, std::vector<Node>& best_path, int &min_dist, int &min_fab, int cur_distance, int cur_fab);
    void whereCarWithWeightLimitBacktracking(int visited_nodes, int &max_nodes, Node node1, Node last_node, std::vector<T> providers , std::vector<Node> cur_path, std::vector<Node>& best_path, int &min_dist, int &min_fab, int cur_distance, int cur_fab, int car_cap, int weight_used, int &best_weight);
    void whereCarsWithWeightLimitBacktracking(int visited_nodes, int &max_nodes, Node node1, Node last_node, std::vector<T*> providers , std::vector<Node> cur_path, std::vector<Node>& best_path, int &min_dist, int &min_fab, int cur_distance, int cur_fab, std::vector<int> car_cap,int current_car, int weight_used, int total_weight_used, int &best_weight);


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
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/
template<class T>
void Graph<T>::whereCarWithNoWeightLimitBacktracking(int visited_nodes, int &max_nodes, Node node1, Node last_node, std::vector<T> providers , std::vector<Node> cur_path, std::vector<Node>& best_path, int &min_dist, int &min_fab, int cur_distance, int cur_fab){
    Vertex<Node>* v1 = this->findVertex(last_node);
    cur_path.push_back(last_node);
    if (last_node == node1){
        for (int i = 0; i < v1->adj.size(); i++){
            std::string a = v1->adj[i].dest->info.getTypeOfNode();
            if (v1->adj[i].dest->info.getTypeOfNode() == "Provider"){
                providers.push_back(v1->adj[i].dest->info);
                cur_fab ++;
                cur_distance += v1->adj[i].getWeight();
                v1->adj[i].dest->visited = true;
                whereCarWithNoWeightLimitBacktracking(visited_nodes, max_nodes,node1,v1->adj[i].dest->info,providers,cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab);
                cur_fab --;
                v1->adj[i].dest->visited = false;
                cur_distance -= v1->adj[i].getWeight();
                providers.pop_back();
            }
        }
    }
    else{
        for (int i = 0; i < v1->adj.size(); i++){
            if (v1->adj[i].dest->info.getTypeOfNode() == "Provider" && !v1->adj[i].dest->visited){
                providers.push_back(v1->adj[i].dest->info);
                cur_fab ++;
                cur_distance += v1->adj[i].getWeight();
                v1->adj[i].dest->visited = true;
                whereCarWithNoWeightLimitBacktracking(visited_nodes, max_nodes,node1,v1->adj[i].dest->info,providers, cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab);
                cur_fab --;
                v1->adj[i].dest->visited = false;
                cur_distance -= v1->adj[i].getWeight();
                providers.pop_back();
            }
            else if(v1->adj[i].dest->info.getTypeOfNode() == "Client" && !v1->adj[i].dest->visited){
                std::vector<T> provCop = providers;
                Node clientCop = v1->adj[i].dest->info;
                for (int e = 0; e < providers.size(); e++){
                    std::unordered_map<std::string,int> m1 = providers[e].getStock();
                    std::unordered_map<std::string,int> c1 = v1->adj[i].dest->info.getOrder();
                    for(auto& product: m1){
                        for (auto& prod: c1){
                            if (prod.second != 0){
                                if (product.first == prod.first){
                                    if (product.second >= prod.second){
                                        m1[product.first] = product.second - prod.second;
                                        c1[prod.first] = 0;
                                    }
                                    else if(product.second < prod.second){
                                        c1[prod.first] = prod.second - product.second;
                                        m1[product.first] = 0;
                                    }
                                }
                            }
                        }
                    }
                    v1->adj[i].dest->info.changeMap(c1);
                    providers[e].changeMap(m1);
                }
                bool n = true;
                for (auto& prod: v1->adj[i].dest->info.getOrder()){
                    if (prod.second != 0) {
                        n = false;
                        providers = provCop;
                        v1->adj[i].dest->info.changeMap(clientCop.getStock());
                        break;
                    }
                }
                if (n){
                    visited_nodes ++;
                    cur_distance += v1->adj[i].getWeight();
                    v1->adj[i].dest->visited = true;
                    whereCarWithNoWeightLimitBacktracking(visited_nodes, max_nodes,node1,v1->adj[i].dest->info,providers, cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab);
                    visited_nodes --;
                    cur_distance -= v1->adj[i].getWeight();
                    v1->adj[i].dest->visited = false;
                    providers = provCop;
                    v1->adj[i].dest->info.changeMap(clientCop.getStock());
                }
            }
        }
    }

    if (visited_nodes > max_nodes){
        best_path = cur_path;
        max_nodes = visited_nodes;
        min_dist = cur_distance;
        min_fab = cur_fab;

    }
    else if(visited_nodes == max_nodes && min_dist > cur_distance){
        best_path = cur_path;
        min_dist = cur_distance;
        min_fab = cur_fab;
    }
    else if(visited_nodes == max_nodes && min_dist == cur_distance && min_fab > cur_fab){
        best_path = cur_path;
        min_fab = cur_fab;
    }
    return;

}


template<class T>
void Graph<T>::whereCarWithWeightLimitBacktracking(int visited_nodes, int &max_nodes, Node node1, Node last_node, std::vector<T> providers , std::vector<Node> cur_path, std::vector<Node>& best_path, int &min_dist, int &min_fab, int cur_distance, int cur_fab, int car_cap, int weight_used, int &best_weight){
    Vertex<Node>* v1 = this->findVertex(last_node);
    cur_path.push_back(last_node);
    if (last_node == node1){
        for (int i = 0; i < v1->adj.size(); i++){
            std::string a = v1->adj[i].dest->info.getTypeOfNode();
            if (v1->adj[i].dest->info.getTypeOfNode() == "Provider"){
                providers.push_back(v1->adj[i].dest->info);
                cur_fab ++;
                cur_distance += v1->adj[i].getWeight();
                v1->adj[i].dest->visited = true;
                whereCarWithWeightLimitBacktracking(visited_nodes, max_nodes,node1,v1->adj[i].dest->info,providers,cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab, car_cap, weight_used, best_weight);
                cur_fab --;
                v1->adj[i].dest->visited = false;
                cur_distance -= v1->adj[i].getWeight();
                providers.pop_back();
            }
        }
    }
    else{
        for (int i = 0; i < v1->adj.size(); i++){
            if (v1->adj[i].dest->info.getTypeOfNode() == "Provider" && !v1->adj[i].dest->visited){
                providers.push_back(v1->adj[i].dest->info);
                cur_fab ++;
                cur_distance += v1->adj[i].getWeight();
                v1->adj[i].dest->visited = true;
                whereCarWithWeightLimitBacktracking(visited_nodes, max_nodes,node1,v1->adj[i].dest->info,providers, cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab, car_cap, weight_used, best_weight);
                cur_fab --;
                v1->adj[i].dest->visited = false;
                cur_distance -= v1->adj[i].getWeight();
                providers.pop_back();
            }
            else if(v1->adj[i].dest->info.getTypeOfNode() == "Client" && !v1->adj[i].dest->visited){
                std::vector<T> provCop = providers;
                Node clientCop = v1->adj[i].dest->info;
                int weight_needed = 0;
                for (auto& prod: v1->adj[i].dest->info.getOrder()){
                    weight_needed += prod.second;
                }
                if (weight_needed + weight_used > car_cap){
                    break;
                }
                for (int e = 0; e < providers.size(); e++){
                    std::unordered_map<std::string,int> m1 = providers[e].getStock();
                    std::unordered_map<std::string,int> c1 = v1->adj[i].dest->info.getOrder();
                    for(auto& product: m1){
                        for (auto& prod: c1){
                            if (prod.second != 0){
                                if (product.first == prod.first){
                                    if (product.second >= prod.second){
                                        m1[product.first] = product.second - prod.second;
                                        c1[prod.first] = 0;
                                    }
                                    else if(product.second < prod.second){
                                        c1[prod.first] = prod.second - product.second;
                                        m1[product.first] = 0;
                                    }
                                }
                            }
                        }
                    }
                    v1->adj[i].dest->info.changeMap(c1);
                    providers[e].changeMap(m1);
                }
                bool n = true;
                for (auto& prod: v1->adj[i].dest->info.getOrder()){
                    if (prod.second != 0) {
                        n = false;
                        providers = provCop;
                        v1->adj[i].dest->info.changeMap(clientCop.getStock());
                        break;
                    }
                }
                if (n){
                    visited_nodes ++;
                    cur_distance += v1->adj[i].getWeight();
                    v1->adj[i].dest->visited = true;
                    weight_used += weight_needed;
                    whereCarWithWeightLimitBacktracking(visited_nodes, max_nodes,node1,v1->adj[i].dest->info,providers, cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab, car_cap, weight_used, best_weight);
                    visited_nodes --;
                    cur_distance -= v1->adj[i].getWeight();
                    v1->adj[i].dest->visited = false;
                    weight_used -= weight_needed;
                    providers = provCop;
                    v1->adj[i].dest->info.changeMap(clientCop.getStock());
                }
            }
        }
    }
    if (visited_nodes > max_nodes){
        best_path = cur_path;
        max_nodes = visited_nodes;
        min_dist = cur_distance;
        min_fab = cur_fab;
        best_weight = weight_used;

    }
    else if (visited_nodes == max_nodes && best_weight < weight_used){
        best_path = cur_path;
        max_nodes = visited_nodes;
        min_dist = cur_distance;
        min_fab = cur_fab;
        best_weight = weight_used;
    }
    else if(visited_nodes == max_nodes && best_weight == weight_used && min_dist > cur_distance){
        best_path = cur_path;
        max_nodes = visited_nodes;
        min_dist = cur_distance;
        min_fab = cur_fab;
        best_weight = weight_used;
    }
    else if(visited_nodes == max_nodes && best_weight == weight_used && min_dist == cur_distance && min_fab > cur_fab){
        best_path = cur_path;
        max_nodes = visited_nodes;
        min_dist = cur_distance;
        min_fab = cur_fab;
        best_weight = weight_used;
    }
    return;

}

template<class T>
void Graph<T>::whereCarsWithWeightLimitBacktracking(int visited_nodes, int &max_nodes, Node node1, Node last_node, std::vector<T*> providers , std::vector<Node> cur_path, std::vector<Node>& best_path, int &min_dist, int &min_fab, int cur_distance, int cur_fab, std::vector<int> car_cap,int current_car, int weight_used, int total_weight_used, int &best_weight){
    Vertex<Node>* v1 = this->findVertex(last_node);
    cur_path.push_back(last_node);
    if (last_node == node1){
        for (int i = 0; i < v1->adj.size(); i++){
            std::string a = v1->adj[i].dest->info.getTypeOfNode();
            if (v1->adj[i].dest->info.getTypeOfNode() == "Provider"){
                providers.push_back(&v1->adj[i].dest->info);
                cur_fab ++;
                cur_distance += v1->adj[i].getWeight();
                v1->adj[i].dest->visited = true;
                whereCarsWithWeightLimitBacktracking(visited_nodes, max_nodes,node1,v1->adj[i].dest->info,providers, cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab, car_cap,current_car, weight_used, total_weight_used, best_weight);
                cur_fab --;
                v1->adj[i].dest->visited = false;
                cur_distance -= v1->adj[i].getWeight();
                providers.pop_back();
            }
        }
    }
    else{
        for (int i = 0; i < v1->adj.size(); i++){
            if (v1->adj[i].dest->info.getTypeOfNode() == "Provider" && !v1->adj[i].dest->visited){
                providers.push_back(&v1->adj[i].dest->info);
                cur_fab ++;
                cur_distance += v1->adj[i].getWeight();
                v1->adj[i].dest->visited = true;
                whereCarsWithWeightLimitBacktracking(visited_nodes, max_nodes,node1,v1->adj[i].dest->info,providers, cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab, car_cap,current_car, weight_used, total_weight_used, best_weight);
                cur_fab --;
                v1->adj[i].dest->visited = false;
                cur_distance -= v1->adj[i].getWeight();
                providers.pop_back();
            }
            else if(v1->adj[i].dest->info.getTypeOfNode() == "Client" && !v1->adj[i].dest->visited){
                std::vector<T> provCop;
                Node clientCop = v1->adj[i].dest->info;
                int weight_needed = 0;
                for (auto& prod: v1->adj[i].dest->info.getOrder()){
                    weight_needed += prod.second;
                }
                if (weight_needed + weight_used > car_cap[current_car]){
                    break;
                }
                for (int e = 0; e < providers.size(); e++){
                    provCop.push_back(*providers[e]);
                    std::unordered_map<std::string,int> m1 = providers[e]->getStock();
                    std::unordered_map<std::string,int> c1 = v1->adj[i].dest->info.getOrder();
                    for(auto& product: m1){
                        for (auto& prod: c1){
                            if (prod.second != 0){
                                if (product.first == prod.first){
                                    if (product.second >= prod.second){
                                        m1[product.first] = product.second - prod.second;
                                        c1[prod.first] = 0;
                                    }
                                    else if(product.second < prod.second){
                                        c1[prod.first] = prod.second - product.second;
                                        m1[product.first] = 0;
                                    }
                                }
                            }
                        }
                    }
                    v1->adj[i].dest->info.changeMap(c1);
                    providers[e]->changeMap(m1);

                }
                bool n = true;
                for (auto& prod: v1->adj[i].dest->info.getOrder()){
                    if (prod.second != 0) {
                        n = false;
                        for (int s = 0; s<providers.size(); s++){
                            providers[s]->changeMap(provCop[s].getStock());
                        }
                        v1->adj[i].dest->info.changeMap(clientCop.getStock());
                        break;
                    }
                }
                if (n){
                    visited_nodes ++;
                    cur_distance += v1->adj[i].getWeight();
                    v1->adj[i].dest->visited = true;
                    weight_used += weight_needed;
                    Vertex<T> *v3;
                    whereCarsWithWeightLimitBacktracking(visited_nodes, max_nodes,node1,v1->adj[i].dest->info,providers, cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab, car_cap,current_car, weight_used, total_weight_used, best_weight);
                    visited_nodes --;
                    cur_distance -= v1->adj[i].getWeight();
                    v1->adj[i].dest->visited = false;
                    weight_used -= weight_needed;
                    for (int s = 0; s<providers.size(); s++){
                        providers[s]->changeMap(provCop[s].getStock());
                    }
                    v1->adj[i].dest->info.changeMap(clientCop.getStock());
                }
            }
            if(current_car == 0 && i == v1->adj.size() -1){
                return;
            }
        }
    }

    if (current_car == car_cap.size() -1){
        if (visited_nodes > max_nodes){
            best_path = cur_path;
            max_nodes = visited_nodes;
            min_dist = cur_distance;
            min_fab = cur_fab;
            best_weight = total_weight_used;

        }
        else if (visited_nodes == max_nodes && best_weight < total_weight_used){
            best_path = cur_path;
            max_nodes = visited_nodes;
            min_dist = cur_distance;
            min_fab = cur_fab;
            best_weight = total_weight_used;
        }
        else if(visited_nodes == max_nodes && best_weight == total_weight_used && min_dist > cur_distance){
            best_path = cur_path;
            max_nodes = visited_nodes;
            min_dist = cur_distance;
            min_fab = cur_fab;
            best_weight = total_weight_used;
        }
        else if(visited_nodes == max_nodes && best_weight == total_weight_used && min_dist == cur_distance && min_fab > cur_fab){
            best_path = cur_path;
            max_nodes = visited_nodes;
            min_dist = cur_distance;
            min_fab = cur_fab;
            best_weight = total_weight_used;
        }
        return;
    }
    else{
        total_weight_used += weight_used;
        std::vector<T> copyPath= cur_path;
        for (int i = 0; i<cur_path.size();i++){
            Vertex<T> *v2;
            if (cur_path[i].getTypeOfNode() == "Provider"){
                v2 = findVertex(cur_path[i]);
                v2->visited = false;
            }
        }
        std::vector<T*> providers1 = {};
        whereCarsWithWeightLimitBacktracking(visited_nodes, max_nodes,node1,node1,providers1, cur_path, best_path, min_dist, min_fab, cur_distance, cur_fab, car_cap, current_car+1, 0,total_weight_used, best_weight);
        cur_path = copyPath;
        total_weight_used -= weight_used;
    }

}




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
