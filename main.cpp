#include <iostream>
#include "productprovider.h"
#include "Graph.h"
#include "deliveryCar.h"
#include <iomanip>

using namespace std;

void display(int a[], int n)
{
    for (int i = 0; i < n; i++) {
        cout << a[i] << "  ";
    }
    cout << endl;
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

void makeGraph2(Graph<Node>& graph, vector<Client> clients, vector<Provider> providers){
    Node node1("1");
    Node node2("2");
    Node node3("3");
    Node node4("4");
    Node node5("5");

    graph.addVertex(node1);

    graph.addVertex(clients[1]);
    graph.addVertex(providers[0]);
    graph.addVertex(providers[1]);
    graph.addVertex(providers[2]);
    graph.addVertex(clients[0]);


    graph.addEdge(node1,clients[0],1);
    graph.addEdge(clients[0],node1,1);

    graph.addEdge(node1,clients[1],2);
    graph.addEdge(clients[1],node1,2);

    graph.addEdge(node1,providers[0],2);
    graph.addEdge(providers[0],node1,2);

    graph.addEdge(node1,providers[1],2);
    graph.addEdge(providers[1],node1,2);

    graph.addEdge(node1,providers[2],1);
    graph.addEdge(providers[2],node1,1);

    graph.addEdge(clients[1],clients[0],1);
    graph.addEdge(clients[0],clients[1],1);

    graph.addEdge(providers[0],clients[0],1);
    graph.addEdge(clients[0],providers[0],1);

    graph.addEdge(providers[1],clients[0],1);
    graph.addEdge(clients[0],providers[1],1);

    graph.addEdge(providers[2],clients[0],1);
    graph.addEdge(clients[0],providers[2],1);

    graph.addEdge(providers[0],clients[1],1);
    graph.addEdge(clients[1],providers[0],1);

    graph.addEdge(providers[1],clients[1],1);
    graph.addEdge(clients[1],providers[1],1);

    graph.addEdge(providers[2],clients[1],1);
    graph.addEdge(clients[1],providers[2],1);

    graph.addEdge(providers[0],providers[1],2);
    graph.addEdge(providers[1],providers[0],2);

    graph.addEdge(providers[0],providers[2],1);
    graph.addEdge(providers[2],providers[0],1);

    graph.addEdge(providers[2],providers[1],1);
    graph.addEdge(providers[1],providers[2],1);

}

void fill_client_and_provider(vector<Client>& clients, vector<Provider>& providers){
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
    clients = {client1, client2};
    providers = {provider1, provider2,provider3};
}

void makeGraph(Graph<Node>& graph, vector<Client> clients, vector<Provider> providers){
    Node node1("1");
    Node node2("2");
    Node node3("3");
    Node node4("4");
    Node node5("5");
    graph.addVertex(node1);
    graph.addVertex(node2);
    graph.addVertex(node3);
    graph.addVertex(node4);
    graph.addVertex(node5);
    for(Client client: clients){
        graph.addVertex(client);
    }
    for(Provider provider: providers){
        graph.addVertex(provider);
    }
    graph.setOriginNode(0);
    graph.addEdge(node1,node2,1);
    graph.addEdge(node2,node1,1);

    graph.addEdge(node1,node3,1);
    graph.addEdge(node3,node1,1);

    graph.addEdge(node1,node5,1);
    graph.addEdge(node5,node1,1);

    graph.addEdge(node1,node4,1);
    graph.addEdge(node4,node1,1);

    graph.addEdge(node1,providers[2],1);
    graph.addEdge(providers[2],node1,1);

    graph.addEdge(node1,clients[0],1);
    graph.addEdge(clients[0],node1,1);

    graph.addEdge(node4,providers[1],1);
    graph.addEdge(providers[1],node4,1);

    graph.addEdge(node2,providers[0],1);
    graph.addEdge(providers[0],node2,1);

    graph.addEdge(providers[2],clients[1],1);
    graph.addEdge(clients[1],providers[2],1);

}

void printPowerSet2(int set[], int set_size, vector<vector<int>>& clientId)
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
        clientId.push_back(temp);

    }
}

int main() {
    Graph<Node> graph;
    //distribute clients to cars

    vector<Client> clients;
    vector<Provider> providers;
    fill_client_and_provider(clients,providers);
    DeliveryCar deliveryCar("1",3);
    DeliveryCar deliveryCar1("2", 2);

    vector<DeliveryCar> deliveryCars = {deliveryCar,deliveryCar1};
    sort(deliveryCars.begin(), deliveryCars.end(), [](const DeliveryCar d1, const DeliveryCar d2){
        return d1.getCapacity() < d2.getCapacity();
    });
    sort(clients.begin(), clients.end(), [](const Client c1, const Client c2){
        return c1.getNumOfProducts() < c2.getNumOfProducts();
    });

    vector<vector<int>> allClientsCombos = {};
    int clientLen = 0;
    int a[1000];
    for(int i = 0; i < clients.size();i++){
        a[i] = i;
        clientLen++;
    }
    printPowerSet2(a,clientLen,allClientsCombos);

    double clientWeight = 0;
    double biggestWeightYet = -1;
    vector<int> clientsToDeliver;
    for(DeliveryCar deliveryCar2: deliveryCars) {
        clientsToDeliver = {};
        for (auto &set: allClientsCombos) {
            clientWeight = 0;
            for (int client : set) {
                clientWeight += clients[client].getNumOfProducts();
            }
            if (clientWeight <= deliveryCar2.getCapacity() && clientWeight > biggestWeightYet) {
                biggestWeightYet = clientWeight;
                clientsToDeliver = set;
                deliveryCar2.setClientsToDeliverTo(set);
            }
        }

        //"eliminate" the client Combinations that the car is already going to visit
        auto i = std::begin(allClientsCombos);
        bool toEliminate = false;
        while (i != std::end(allClientsCombos)) {
            // Do some stuff
            toEliminate = false;
            for (auto &client: clientsToDeliver) {
                if (find((*i).begin(), (*i).end(), client) != (*i).end()){
                    toEliminate = true;
                    break;
                }
            }
            if(toEliminate){
                i = allClientsCombos.erase(i);
            }
            else
                ++i;
        }
    }


    int biggestLen = 0;
    vector<vector<int>> clientIds;
    for(auto& combination: allClientsCombos){
        if(combination.size() > biggestLen){
            biggestLen = combination.size();
            clientIds = {};
            clientIds.push_back(combination);
        }
        else if(combination.size() == biggestLen){
            clientIds.push_back(combination);
        }
    }

    //makeGraph(graph,clients,providers);
    makeGraph2(graph,clients,providers);
    deliveryCar.printShoppingList();

    //next deliveryCar must check what combinations of providers it can go to get the necessary products;
    vector<Node> bestPath = deliveryCar.getBestPossiblePath(clientIds,providers,clients,graph);
    //check which path costs less and its done!
    for(Node node: bestPath) {
        cout << node.getId() <<  "-> ";
    }
    return 0;
}
