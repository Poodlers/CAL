#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include "productprovider.h"
#include "Graph.h"
#include "deliveryCar.h"
#include "graphviewer.h"
#include "utils.h"

using namespace std;



void planRouteForCars(vector<DeliveryCar*>& deliveryCars, vector<Client* >& clients, vector<Provider *>& providers, Graph<Node>& graph, GraphViewer& gv){
    vector<vector<int>> bestClientCombo = {};
    vector<int> clientIds;
    for(int i = 0; i < clients.size();i++){
        clientIds.push_back(i);
    }
    //get the total stock of products the providers have
    unordered_map<string,int> availableStock;
    for(auto& provider: providers){
        for(auto& product: provider->getStock()){
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
            currWeight += clients[clientIds[i]]->getNumOfProducts();
            if(currWeight > deliveryCar->getCapacity()){
                break;
            }
            handleNewClientCombo(bestClientCombo,clientCombo,bestWeight,currWeight,availableStock,clients);
            for(int j = i + 1; j < clientIds.size();j++) {
                clientCombo.push_back(clientIds[j]);
                currWeight += clients[clientIds[j]]->getNumOfProducts();
                if(currWeight > deliveryCar->getCapacity()){
                    break;
                }
                handleNewClientCombo(bestClientCombo,clientCombo,bestWeight,currWeight,availableStock,clients);

            }

        }
        double bestDistance = 999999;
        vector<int> trueBestClientCombo;
        pair<vector<Node>, double> bestPath;
        //now we have the best combinations possible for this car, lets test them and see which one ends up with our car travelling the least!
        if(bestClientCombo.size() == 0){
            cout << "No possible delieveries for delivery car number " << deliveryCar->getId() << "\n";
        }else{
            for(auto& combo: bestClientCombo){
                deliveryCar->setClientsToDeliverTo(combo);
                bestPath = deliveryCar->getBestPossiblePath(providers,clients,graph,gv);
                if(bestPath.second < bestDistance){
                    trueBestClientCombo = combo;
                    bestDistance = bestPath.second;
                }
            }

        }

        //after the best combination is found for one delivery car we need to remove the clients already being serviced
        for(auto iter = clientIds.begin(); iter != clientIds.end();){
            auto toRemove = find(trueBestClientCombo.begin(),trueBestClientCombo.end(),*iter);
            if(toRemove != trueBestClientCombo.end()){
                iter = clientIds.erase(iter);
            }else{
                iter++;
            }
        }

        //before going to the next deliveryCar, remove the stock from this delivery as if it was already done!
        removeFromStock(availableStock,trueBestClientCombo,clients);
        removeFromProviders(providers,bestPath.first,deliveryCar->getShoppingList());
        deliveryCar->setNodesTravelled(bestPath.first);

    }

    
}

int main() {
    Graph<Node> graph;
    //distribute clients to cars

    vector<Client *> clients;
    vector<Provider *> providers;

    //create provider and client information
    vector<string> products = {"A", "B", "C", "D", "E"};

    fill_client_and_provider_rand(getNodeIds("penafiel_strong_nodes_latlng.txt"),clients,providers,10,3,products);

    
    //create delivery cars
    DeliveryCar deliveryCar("1",4);
    //DeliveryCar deliveryCar1("2", 2);

    vector<DeliveryCar *> deliveryCars = {&deliveryCar};
    auto start1 = chrono::steady_clock::now();
    //we do a little sorting
    sort(deliveryCars.begin(), deliveryCars.end(), [](const DeliveryCar* d1, const DeliveryCar* d2){
        return d1->getCapacity() < d2->getCapacity();
    });
    sort(clients.begin(), clients.end(), [](const Client* c1, const Client* c2){
        return c1->getNumOfProducts() < c2->getNumOfProducts();
    });

    GraphViewer gv;
    buildGraphFromTxt(gv,graph,"penafiel_strong_edges.txt", "penafiel_strong_nodes_latlng.txt", "penafiel_strong_nodes_xy.txt",clients,providers);
    planRouteForCars(deliveryCars,clients,providers,graph,gv);



    //next deliveryCar must check what combinations of providers it can go to get the necessary products;

    auto end1 = chrono::steady_clock::now();
    
    for(DeliveryCar* deliveryCar1: deliveryCars){
        cout << "best path for car " << deliveryCar1->getId() << " is: " << "\n";
        for(Node node: deliveryCar1->getNodesTravelled()){
            cout << node.getId() << "->";
        }
        cout << "\n";
    }

    cout << "ran for: " << chrono::duration_cast<chrono::milliseconds >(end1 - start1).count() << " milli seconds \n";


    return 0;

}
