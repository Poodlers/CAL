#include <iostream>
#include <algorithm>
#include <chrono>
#include "productprovider.h"
#include "Graph.h"
#include "deliveryCar.h"

using namespace std;

void display2Dvec(vector<vector<int>> a)
{
    for(int c = 0; c < a.size(); c++){
        for (int i = 0; i < a[c].size(); i++) {
            cout << a[c][i] << "  ";
        }
        cout << endl;
    }
}

void makeGraph3(Graph<Node>& graph, vector<Client> clients, vector<Provider> providers){
    Node node1("1");
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

bool check_if_available(unordered_map<string,int> availableStock,vector<int> clientId, vector<Client>& clients){
    for(int i = 0; i < clientId.size();i++){
        for(auto& product: clients[clientId[i]].getOrder()){
            if(availableStock.find(product.first) != availableStock.end()){
                if(availableStock[product.first] - product.second >= 0){
                    availableStock[product.first] -= product.second;
                }else{
                    return false;
                }
            }else{ //the requested product doesnt even exist in the providers
                return false;
            }
        }
    }
    return true;
}

void removeFromStock(unordered_map<string,int>& availableStock, vector<int> clientId, vector<Client>& clients){
    for(int i = 0; i < clientId.size();i++){
        for(auto& product: clients[clientId[i]].getOrder()){
            availableStock[product.first] -= product.second;
        }
    }
}


void planRouteForCars(vector<DeliveryCar*>& deliveryCars, vector<Client>& clients, vector<Provider>& providers){
    vector<int> bestClientCombo = {};
    vector<int> clientIds;
    for(int i = 0; i < clients.size();i++){
        clientIds.push_back(i);
    }
    //get the total stock of products the providers have
    unordered_map<string,int> availableStock;
    for(auto& provider: providers){
        for(auto& product: provider.getStock()){
            if(availableStock.find(product.first) != availableStock.end()){
                availableStock[product.first] += product.second;
            }else{
                availableStock[product.first] = product.second;
            }
        }
    }

    vector<int> clientCombo;

    double bestWeight = -1;
    double currWeight = 0;

    for(DeliveryCar* deliveryCar: deliveryCars){
        bestClientCombo = {};
        bestWeight = -1;
        for(int i = 0; i < clientIds.size();i++) {
            clientCombo = {};
            currWeight = 0;
            clientCombo.push_back(clientIds[i]);
            currWeight += clients[clientIds[i]].getNumOfProducts();
            if(currWeight > deliveryCar->getCapacity()){
                break;
            }
            if(check_if_available(availableStock,clientCombo,clients) && clientCombo.size() >= bestClientCombo.size() && currWeight > bestWeight){

                bestClientCombo = clientCombo;
                bestWeight = currWeight;

            }
            for(int j = i + 1; j < clientIds.size();j++) {
                clientCombo.push_back(clientIds[j]);
                currWeight += clients[clientIds[j]].getNumOfProducts();
                if(currWeight > deliveryCar->getCapacity()){
                    break;
                }
                if(check_if_available(availableStock,clientCombo,clients) && clientCombo.size() >= bestClientCombo.size() && currWeight > bestWeight){
                    bestClientCombo = clientCombo;
                    bestWeight = currWeight;
                }


            }

        }
        //after the best combination is found for one delivery car we need to remove the clients already being serviced
        for(auto iter = clientIds.begin(); iter != clientIds.end();){
            auto toRemove = find(bestClientCombo.begin(),bestClientCombo.end(),*iter);
            if(toRemove != bestClientCombo.end()){
                iter = clientIds.erase(iter);
            }else{
                iter++;
            }
        }

        if(bestClientCombo.size() == 0){
            cout << "No possible delieveries for delivery car number " << deliveryCar->getId() << "\n";
        }else{
            removeFromStock(availableStock, bestClientCombo,clients);
            deliveryCar->setClientsToDeliverTo(bestClientCombo);
        }

    }

    
}

int main() {
    Graph<Node> graph;
    //distribute clients to cars

    vector<Client> clients;
    vector<Provider> providers;
    //create provider and client information
    fill_client_and_provider(clients,providers);

    //create delivery cars
    DeliveryCar deliveryCar("1",4);
    //DeliveryCar deliveryCar1("2", 2);

    vector<DeliveryCar *> deliveryCars = {&deliveryCar};
    auto start1 = chrono::steady_clock::now();
    //we do a little sorting
    sort(deliveryCars.begin(), deliveryCars.end(), [](const DeliveryCar* d1, const DeliveryCar* d2){
        return d1->getCapacity() < d2->getCapacity();
    });
    sort(clients.begin(), clients.end(), [](const Client c1, const Client c2){
        return c1.getNumOfProducts() < c2.getNumOfProducts();
    });

    planRouteForCars(deliveryCars,clients,providers);

    //makeGraph(graph,clients,providers);

    //makeGraph2(graph,clients,providers);

    makeGraph3(graph,clients,providers);

    //next deliveryCar must check what combinations of providers it can go to get the necessary products;

    vector<Node> bestPath = deliveryCar.getBestPossiblePath(providers,clients,graph);
    //vector<Node> bestPath2 = deliveryCar1.getBestPossiblePath(providers,clients,graph);
    //check which path costs less and its done!
    auto end1 = chrono::steady_clock::now();
    for(Node node: bestPath) {
        cout << node.getId() <<  "-> ";
    }
    cout << "\n";
    /*
    for(Node node: bestPath2) {
        cout << node.getId() <<  "-> ";
    }
    cout << "\n";
    */
    cout << "ran for: " << chrono::duration_cast<chrono::microseconds>(end1 - start1).count() << " micro seconds \n";
    return 0;
}
