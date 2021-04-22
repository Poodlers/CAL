#include <iostream>
#include "client.h"
#include "productprovider.h"
#include "Graph.h"
#include "deliveryCar.h"

#include <chrono>
#include <cstdlib>
#include <ctime>

#include <iomanip>

using namespace std;

DeliveryCar deliveryCar("1",10);


void check_if_perm_works( vector<int> a, vector<Provider> providers, vector<vector<int>>& viableRoute )
{
    unordered_map<string,int> availableStock;
    Provider* currProvider;
    vector<int> possibleRoute;
    for( int i = 0 ; i < a.size() ; ++i ){
        currProvider = &providers[a[i]];
        possibleRoute.push_back(a[i]);
        for(auto& product: currProvider->getStock()){
            if(availableStock.find(product.first) != availableStock.end()){
                availableStock[product.first] += product.second;
            }else{
                availableStock[product.first] = product.second;
            }
        }
    }

    if(deliveryCar.checkIfMeetsRequirement(availableStock)){
        viableRoute.push_back(possibleRoute);
    };

}

void printPowerSet(int set[], int set_size, vector<vector<int>>& providerId)
{
    /*set_size of power set of a set with set_size
    n is (2**n -1)*/
    unsigned int pow_set_size = pow(2, set_size);
    int counter, j;
    vector<int> temp;
    /*Run from counter 000..0 to 111..1*/
    for(counter = 0; counter < pow_set_size; counter++)
    {
        temp = {};
        for(j = 0; j < set_size; j++)
        {
            if(counter & (1 << j))
                temp.push_back(set[j]);
        }
        providerId.push_back(temp);

    }
}

void display(int a[], int n)
{
    for (int i = 0; i < n; i++) {
        cout << a[i] << "  ";
    }
    cout << endl;
}

void findPermutations(vector<int> a, vector<vector<int>>& allPerms)
{

    // Sort the given array
    sort(a.begin(),a.end());

    do {
        allPerms.push_back(a);
    } while (next_permutation(a.begin(), a.end()));
}

void display2Dvec(vector<vector<int>> a)
{
    for(int c = 0; c < a.size(); c++){
        for (int i = 0; i < a[c].size(); i++) {
            cout << a[c][i] << "  ";
        }
        cout << endl;
    }

}




vector<Node> whereCarWithNoWeightLimit(Graph<Node> graph, vector<Provider> providers, vector<Client> clients, Node node1){
    //next deliveryCar must check what combinations of providers it can go to get the necessary products;
    int a[] = { 0,1,2} ;
    vector<vector<int>> combinations;
    printPowerSet(a, 3, combinations);
    vector<vector<int>> viableRoutes;
    for(auto& combination: combinations){
        check_if_perm_works(combination,providers,viableRoutes);
    }

    //display2Dvec(viableRoutes);

    vector<vector<int>> allProviderPerms;
    for(auto& route: viableRoutes){
        findPermutations(route,allProviderPerms);
    }
    //display2Dvec(allProviderPerms);

    //now we have all of the possible providers our car could visit (in every possible order)

    //now we can get all the possible permutations on how to visit our clients!
    vector<vector<Node>> allPathsToSearch;
    vector<vector<int>> allClientPerms;
    vector<int> clientIds = {0,1};
    findPermutations(clientIds,allClientPerms);
    //display2Dvec(allClientPerms);

    vector<Node> Path;
    vector<Node> provPath;
    for(auto& provPerm: allProviderPerms){
        provPath = {node1}; //source node of the company
        for(auto& prov: provPerm) {
            provPath.push_back(providers[prov]);
        }
        for(auto& clientPerm: allClientPerms){
            Path = provPath;
            for(auto& client: clientPerm){
                Path.push_back(clients[client]);
            }
            allPathsToSearch.push_back(Path);
        }

    }

    /*
    graph.dijkstraShortestPath(node1);
    vector<Node> shortestPath = graph.getPath(node1,provider2);
    */
    vector<Node> intermediatePaths;
    vector<Node> best;
    int best_num_of_clients = 0;
    double best_dist = 100000;
    int num_clients = 0;
    int best_num_fabrics = 100000;
    int num_fabrics = 0;

    double costToTravel;
    for(auto& path1: allPathsToSearch){
        costToTravel = 0;
        num_clients = 0;
        num_fabrics = 0;
        for(int i = 0; i < path1.size(); i++){
            //cout << path1[i].getId() << " -> ";
            if(i < path1.size() - 1){
                //get the shortest path between these two vertices
                graph.dijkstraShortestPath(path1[i]);
                intermediatePaths = graph.getPath(path1[i], path1[i + 1]);
                //add the cost to travel in between these two nodes
                for(int c = 0; c < intermediatePaths.size(); c++){
                    if(c < intermediatePaths.size() - 1){
                        Vertex<Node>* nextVertex = graph.findVertex(intermediatePaths[c + 1]);
                        Vertex<Node>* currVertex = graph.findVertex(intermediatePaths[c]);
                        costToTravel += currVertex->getEdgeDistance(nextVertex);
                    }

                }
            }
        }
        for (int i = 0; i<path1.size(); i++){
            if (path1[i].getTypeOfNode() == "Client"){
                num_clients ++;
            }
            if (path1[i].getTypeOfNode() == "Provider"){
                num_fabrics ++;
            }
        }
        if (num_clients > best_num_of_clients){
            best = path1;
            best_num_of_clients = num_clients;
            best_dist = costToTravel;
            best_num_fabrics = num_fabrics;
        }
        else if (num_clients ==  best_num_of_clients && best_dist > costToTravel){
            best = path1;
            best_num_of_clients = num_clients;
            best_dist = costToTravel;
            best_num_fabrics = num_fabrics;
        }
        else if(num_clients ==  best_num_of_clients && best_dist == costToTravel && best_num_fabrics > num_fabrics){
            best = path1;
            best_num_of_clients = num_clients;
            best_dist = costToTravel;
            best_num_fabrics = num_fabrics;
        }
    }
    return best;
    //check which path costs less and its done!
}

int main() {
    Graph<Node> graph;
    Node node1("1");
    Node node2("2");
    Node node3("3");
    Node node4("4");
    Node node5("5");
    Client client1("6");
    client1.addOrder("Shampoo", 1);
    client1.addOrder("Tomato", 1);
    Client client2("10");
    client2.addOrder("Burger", 1);
    client2.addOrder("Tomato", 1);
    Provider provider1("7");
    provider1.addProduct("Shampoo", 10);
    provider1.addProduct("Tomato", 10);
    Provider provider2("8");
    provider2.addProduct("Burger", 10);
    Provider provider3("9");
    provider3.addProduct("Tomato", 10);
    graph.addVertex(node1);
    /*
    graph.addVertex(node2);
    graph.addVertex(node3);
    graph.addVertex(node4);
    graph.addVertex(node5);*/
    graph.addVertex(client2);
    graph.addVertex(provider1);
    graph.addVertex(provider2);
    graph.addVertex(provider3);
    graph.addVertex(client1);

    vector<Client> clients = {client1, client2};
    unordered_map<string,int> clientOrder;
    for(Client client: clients){
        clientOrder = client.getOrder();
        for(auto& order: clientOrder){
            deliveryCar.addToShoppingList(order.first,order.second);
        }
    }
    //deliveryCar.printShoppingList();


    graph.addEdge(node1,client1,1);
    graph.addEdge(client1,node1,1);

    graph.addEdge(node1,client2,2);
    graph.addEdge(client2,node1,2);

    graph.addEdge(node1,provider1,2);
    graph.addEdge(provider1,node1,2);

    graph.addEdge(node1,provider2,2);
    graph.addEdge(provider2,node1,2);

    graph.addEdge(node1,provider3,1);
    graph.addEdge(provider3,node1,1);

    graph.addEdge(client2,client1,1);
    graph.addEdge(client1,client2,1);

    graph.addEdge(provider1,client1,1);
    graph.addEdge(client1,provider1,1);

    graph.addEdge(provider2,client1,1);
    graph.addEdge(client1,provider2,1);

    graph.addEdge(provider3,client1,1);
    graph.addEdge(client1,provider3,1);

    graph.addEdge(provider1,client2,1);
    graph.addEdge(client2,provider1,1);

    graph.addEdge(provider2,client2,1);
    graph.addEdge(client2,provider2,1);

    graph.addEdge(provider3,client2,1);
    graph.addEdge(client2,provider3,1);

    graph.addEdge(provider1,provider2,2);
    graph.addEdge(provider2,provider1,2);

    graph.addEdge(provider1,provider3,1);
    graph.addEdge(provider3,provider1,1);

    graph.addEdge(provider3,provider2,1);
    graph.addEdge(provider2,provider3,1);


    /*graph.addEdge(node1,node2,1);
    graph.addEdge(node2,node1,1);

    graph.addEdge(node1,node3,1);
    graph.addEdge(node3,node1,1);

    graph.addEdge(node1,node5,1);
    graph.addEdge(node5,node1,1);

    graph.addEdge(node1,node4,1);
    graph.addEdge(node4,node1,1);

    graph.addEdge(node1,provider3,1);
    graph.addEdge(provider3,node1,1);

    graph.addEdge(node1,client1,1);
    graph.addEdge(client1,node1,1);

    graph.addEdge(node4,provider2,1);
    graph.addEdge(provider2,node4,1);

    graph.addEdge(node2,provider1,1);
    graph.addEdge(provider1,node2,1);

    graph.addEdge(provider3,client2,1);
    graph.addEdge(client2,provider3,1);*/



    vector<Provider> providers = {provider1, provider2,provider3};

    /****/
    auto start = chrono::steady_clock::now();

    //vector<Node> best = whereCarWithNoWeightLimit(graph,providers,clients, node1);

    auto end = chrono::steady_clock::now();
    /****/

   /*for (int i = 0; i < best.size(); i++){
        cout << " " << best[i].getId();
    }

    cout << "\nran for: "<< chrono::duration_cast<chrono::microseconds>(end - start).count() << " micro seconds \n";
    */

    vector<Node> result, providers1, curr_path;
    vector<Node*> providers2;
    vector<int> cars;
    cars.push_back(3);
    cars.push_back(2);
    int max_nodes= 0, min_dist = 10000, min_fab = 10000, best_weight = 0;
    vector<Client> clients1 = {client1,client2};
    /****/
    auto start1 = chrono::steady_clock::now();

    //graph.whereCarWithNoWeightLimitBacktracking(0, max_nodes, node1, node1, providers1, curr_path, result, min_dist, min_fab, 0, 0);

    //graph.whereCarWithWeightLimitBacktracking(0, max_nodes, node1, node1, providers1, curr_path, result, min_dist, min_fab, 0, 0,4,0,best_weight);

    //graph.whereCarsWithWeightLimitBacktracking(0, max_nodes, node1, node1, providers2, curr_path, result, min_dist, min_fab, 0, 0,cars,0,0,0,best_weight);

    graph.whereCarWithWeightLimitBacktrackingA(0, max_nodes, node1, node1, providers1, curr_path, result, min_dist, min_fab, 0, 0,4,0,best_weight,clients);
    auto end1 = chrono::steady_clock::now();
    /****/

    for (int i = 0; i < result.size(); i++){
        cout << " " << result[i].getId();
    }
    cout << "\nDistance: " << min_dist << "\n";

    cout << "ran for: " << chrono::duration_cast<chrono::microseconds>(end1 - start1).count() << " micro seconds \n";



    return 0;
}
