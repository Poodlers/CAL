#include "deliveryCar.h"
#include <iostream>
#include <Windows.h>
#include "graphviewer.h"

using namespace std;

using ViewerNode = GraphViewer::Node;
using ViewerEdge = GraphViewer::Edge;

DeliveryCar::DeliveryCar(std::string id, int capacity) {
    this->id = id;
    this->capacity = capacity;
}


bool DeliveryCar::addNodeTravelled(Node node) {
    this->nodesTravelled.push_back(node);
    return true;
}

bool DeliveryCar::addDistance(int distance) {
    this->distanceTravelled += distance;
    return true;
}

void DeliveryCar::removeFromClients(int clientToRemove) {
    this->clientsToDeliverTo.erase(std::remove_if(clientsToDeliverTo.begin(),clientsToDeliverTo.end(),
                                                  [&clientToRemove](const int& x){
            return x == clientToRemove;
    }));
}

bool DeliveryCar::addToShoppingList(std::string ProductName, int amount) {
    if(this->shoppingList.find(ProductName) != this->shoppingList.end()){
        this->shoppingList[ProductName] = this->shoppingList[ProductName] + amount;
    }else{
        this->shoppingList[ProductName] = amount;
    }
    return true;
}

void DeliveryCar::printShoppingList() {
    std::cout << "List of products for deliveryCar number " << this->id << " is: " << std::endl;
    for(auto& order: shoppingList){
        std::cout << order.first << " - " << order.second << std::endl;
    }
}

bool DeliveryCar::checkIfMeetsRequirement(std::unordered_map<std::string, int> &shoppingList) {
    for(auto& prod: this->shoppingList){
        if(shoppingList.find(prod.first) == shoppingList.end()){
            return false;
        }
        if(prod.second > shoppingList[prod.first]){
            return false;
        }

    }
    return true;
}

void DeliveryCar::fillShoppingList(std::vector<int> clientIds, std::vector<Client*> clients) {
    this->shoppingList.clear();
    std::unordered_map<std::string,int> clientOrder;
    for(int clientId: clientIds){
        clientOrder = clients[clientId]->getOrder();
        for(auto& order: clientOrder){
            addToShoppingList(order.first,order.second);
        }
    }
}

void DeliveryCar::findBest(vector<int> &visitedNodes, vector<int> ids, vector<int> &bestPath, int &bestDistance,
                           int curDistance, vector<Provider *> &providers, vector<Client *> &clients, std::unordered_map<std::string, int>& carStock){

    for (int i = 0; i < ids.size(); i++){
        auto itId = find(visitedNodes.begin(),visitedNodes.end(),ids[i]);
        if (itId == visitedNodes.end()) continue;
        auto itProv = find(providers.begin(),providers.end(), new Provider(to_string(ids[i])));
        if (itProv != providers.end()){
            visitedNodes.push_back(ids[i]);
            if (visitedNodes.size() > 1){
                //check distance between this node and the last
                
            }

            //add products to map
            this->loadCar(carStock,(*itProv)->getStock());
            findBest(visitedNodes,ids,bestPath,bestDistance,curDistance,providers,clients);
            visitedNodes.pop_back();
        }
        else{
            auto it = find(clients.begin(),clients.end(), new Client(to_string(ids[i])));
            if (visitedNodes.empty()) continue;
            else{
                //check distance between this node and the last
                //remove products from map
                //if you can they exist to remove proceed to next:
                visitedNodes.push_back(ids[i]);
                findBest(visitedNodes,ids,bestPath,bestDistance,curDistance,providers,clients);
                visitedNodes.pop_back();
                //else
                continue;
            }
        }
    }
    // if the thing leaves the loop it's because there is either nothing more to use or it hit a dead end
    // verify distance between this path and last best and return so that it can do more permutations
    if (visitedNodes.size() != ids.size()) return; //due to pre-selection it always chooses the min number of nodes it can visit
    if (bestPath.empty()){
        bestPath = visitedNodes;
        curDistance = bestDistance;
    }
    else if (curDistance < bestDistance){
        bestPath = visitedNodes;
        curDistance = bestDistance;
    }

}


bool DeliveryCar::check_if_perm_works(std::vector<int> a, std::vector<Provider *> providers,
                                      std::vector<std::vector<int>> &viableRoute){
    unordered_map<string,int> availableStock;
    Provider* currProvider;
    vector<int> possibleRoute;
    if(a.size() == 0){
        return false;
    }
    for( int i = 0 ; i < a.size() ; ++i ){
        currProvider = providers[a[i]];
        possibleRoute.push_back(a[i]);
        for(auto& product: currProvider->getStock()){
            if(availableStock.find(product.first) != availableStock.end()){
                availableStock[product.first] += product.second;
            }else{
                availableStock[product.first] = product.second;
            }
        }
    }

    if(checkIfMeetsRequirement(availableStock)){
        viableRoute.push_back(possibleRoute);
        return true;
    };

    return false;

}

void findPermutations(vector<int> a, vector<vector<int>>& allPerms)
{
    sort(a.begin(),a.end());

    do {
        allPerms.push_back(a);
    } while (next_permutation(a.begin(), a.end()));
}

void DeliveryCar::setClientsToDeliverTo(std::vector<int> clients) {
    this->clientsToDeliverTo = clients;
}

void DeliveryCar::checkProviderCombinations(int set_size, std::vector<std::vector<int>> &providerId,
                                            std::vector<Provider *> &providers){
    vector<int> combination;
    for(int i = 0; i < set_size;i++){
        combination = {};
        combination.push_back(i);
        if(check_if_perm_works(combination,providers,providerId)){
            continue;
        }
        if(i == set_size - 1){
            return;
        }
        for(int j = i + 1; j < set_size; j++){
            combination.push_back(j);
            if(check_if_perm_works(combination,providers,providerId)){
                break;
            }
        }
    }
}

Provider* checkIfProvider(std::vector<Provider *> &providers, int id){
    for(int i = 0; i < providers.size(); i++){
        if(providers[i]->getId() == to_string(id)){
            return providers[i];
        }
    }
    return nullptr;
}
Client* checkIfClient(std::vector<Client*> &clients, int id){
    for(int i = 0; i < clients.size(); i++){
        if(clients[i]->getId() == to_string(id)){
            return clients[i];
        }
    }
    return nullptr;
}




void DeliveryCar::loadCar(std::unordered_map<std::string, int> &carStock,
                          std::unordered_map<std::string, int> &stockToLoad) {
    for(auto& prod: stockToLoad){
        if(this->shoppingList.find(prod.first) == this->shoppingList.end()){
            continue; //this product is not in the shoppingList for this car and can be ignored
        }else{
            if(stockToLoad[prod.first] >= shoppingList[prod.first]){ //provider has more than what the car needs
                carStock[prod.first] = carStock[prod.first] + shoppingList[prod.first]; //load the required for what the car needs
                shoppingList.erase(prod.first);
            }else{
                carStock[prod.first] = carStock[prod.first] + stockToLoad[prod.first]; // load all this provider can afford to give
                shoppingList[prod.first] = shoppingList[prod.first] - stockToLoad[prod.first];
            }
        }
    }
}

void unloadMerch(std::unordered_map<std::string, int> &carStock,Client* client){
    unordered_map<string,int> shoppingListClient = client->getOrder();
    for(auto& prod: shoppingListClient){
        if(carStock.find(prod.first) != carStock.end()){ //this product does not even exist in the car stock
            if(carStock[prod.first] > prod.second){
                carStock[prod.first] = carStock[prod.first] - prod.second;
            }else{
                carStock.erase(prod.first);
            }

        }

    }

}


bool unloadCar(std::unordered_map<std::string, int> &carStock,Client* client){
    unordered_map<string,int> shoppingListClient = client->getOrder();
    for(auto& prod: shoppingListClient){
        if(carStock.find(prod.first) == carStock.end()){ //this product does not even exist in the car stock
            return false;
        }
        if(prod.second > carStock[prod.first]){ //the client needs more of this product than the car has in stock
            return false;
        }

    }
    return true;
}

pair<vector<Node>, double> DeliveryCar::getBestPossiblePathBruteForce(std::vector<Provider *> &providers,
                                              std::vector<Client*> &clients, Graph<Node> &graph, GraphViewer& gv, PATH_FINDING_ALGO algo)  {

    fillShoppingList(clientsToDeliverTo, clients);
    vector<vector<int>> viableRoutes;
    checkProviderCombinations(providers.size(), viableRoutes,providers);
    vector<Node> bestRoute;

    vector<int> clientIds = clientsToDeliverTo;
    vector<vector<Node>> allPathsToSearch;

    vector<Node> Path;
    vector<Node> provPath;
    for(auto& provPerm: viableRoutes){
        Path = {}; //source node of the company
        for(auto& prov: provPerm) {
            Path.push_back(*providers[prov]);
        }
        for(auto& client: clientIds) {
            Path.push_back(*clients[client]);
        }
        allPathsToSearch.push_back(Path);
    }

    //GENERATE ALL PERMUTATIONS
    vector<vector<Node>> finalPermsToSearch;
    vector<int> pathInt;
    vector<vector<int>> allPossiblePerms;
    for(auto& pathToSearch: allPathsToSearch){
        pathInt = {};
        allPossiblePerms = {};
        for(int i = 0; i < pathToSearch.size(); i++){
            pathInt.push_back(stoi(pathToSearch[i].getId()));
        }
        findPermutations(pathInt, allPossiblePerms);

        //now, trim all stupid Permutations
        unordered_map<string,int> stockSoFar; //will represent the stock the car is currently holding
        bool skipped = false;
        for(auto iter = allPossiblePerms.begin(); iter != allPossiblePerms.end();){
            stockSoFar.clear();
            skipped = false;
            for(auto& nodeId: *iter){
                Provider* provider = checkIfProvider(providers,nodeId);
                Client* client = checkIfClient(clients,nodeId);
                if(provider != nullptr){ //load the car
                    loadCar(stockSoFar,provider->getStock());
                }else if(client != nullptr){ //unload the car
                    if(!unloadCar(stockSoFar,client)){
                        iter = allPossiblePerms.erase(iter);
                        skipped = true;
                        break;
                    }
                }
            }
            if(!skipped) iter++;
        }

        for(auto& possiblePerm: allPossiblePerms){
            Path = {graph.getOriginNode()};
            for(auto& nodeId: possiblePerm){
                Provider* provider = checkIfProvider(providers,nodeId);
                Client* client = checkIfClient(clients,nodeId);
                if(provider != nullptr){
                    Path.push_back(*provider);
                }else{
                    Path.push_back(*client);
                }
            }
            Path.push_back(graph.getOriginNode());
            finalPermsToSearch.push_back(Path);
        }
    }

    std::pair<vector<Node>, double> intermediatePaths;
    vector<Node> best;
    vector<Node> currPath;
    double bestCost = 99999;
    double costToTravel;


    ViewerNode& node1 = gv.getNode(stoi(graph.getOriginNode().getId()));
    string deliveryCarId = "DELIVERY CAR ID: " + this->id;
    node1.setLabel(deliveryCarId);

    for(auto& path1: finalPermsToSearch){
        currPath = {};
        costToTravel = 0;
        gv.lock();

        //reset the graph for the new trip
        for(auto& node: gv.getNodes()){
            Client* client = checkIfClient(clients, node->getId());
            if(client != nullptr){
                string compras = "COMPRAS: \n";
                for(auto& prod: client->getOrder()){
                    compras = compras + prod.first + " " + to_string(prod.second) + "\n";
                }
                node->setLabel(compras);
                continue;
            }

            Provider* provider = checkIfProvider(providers, node->getId());
            if(provider != nullptr){
                string stock = "STOCK: \n";
                for(auto& prod: provider->getStock()){
                    stock = stock + prod.first + " " + to_string(prod.second) + "\n";
                }
                node->setLabel(stock);
                continue;
            }
            if(node->getId() != stoi(graph.getOriginNode().getId())) node->setColor(GraphViewer::BLUE);

        }

        for(auto& edge: gv.getEdges()){
            edge->setColor(GraphViewer::BLACK);
        }

        gv.unlock();
        for(int i = 0; i < path1.size(); i++){
            currPath.push_back(path1[i]);
            if(i < path1.size() - 1){
                //get the shortest path between these two vertices
                if(algo == DIJSKTRA){
                    intermediatePaths = graph.getDijsktraPath(path1[i], path1[i + 1]);
                    costToTravel = intermediatePaths.second;
                }
                else if(algo == FLOYD_WARSHALL){
                    intermediatePaths = graph.getfloydWarshallPath(path1[i], path1[i+ 1]);
                    costToTravel = intermediatePaths.second;
                }
                //add the cost to travel in between these two nodes
                for(int c = 0; c < intermediatePaths.first.size(); c++){
                    if(c < intermediatePaths.first.size() - 1){
                        Vertex<Node>* nextVertex = graph.findVertex(intermediatePaths.first[c + 1]);
                        Vertex<Node>* currVertex = graph.findVertex(intermediatePaths.first[c]);
                        costToTravel += currVertex->getEdgeDistance(nextVertex);

                        gv.lock();
                        ViewerNode& node0 = gv.getNode(stoi(currVertex->getInfo().getId()));
                        node0.setColor(GraphViewer::YELLOW);

                        fix_client_and_provider_color(clients,node0,providers,currVertex->getInfo().getId());


                        ViewerNode& node1 = gv.getNode(stoi(nextVertex->getInfo().getId()));
                        node1.setColor(GraphViewer::PINK);

                        fix_client_and_provider_color(clients,node1,providers,currVertex->getInfo().getId());

                        ViewerEdge& edge = gv.getEdge(currVertex->getEdge(nextVertex).getId());
                        ViewerEdge& edge2 = gv.getEdge(nextVertex->getEdge(currVertex).getId());
                        if(edge.getColor() == GraphViewer::GREEN){
                            edge.setColor(GraphViewer::RED);
                            edge2.setColor(GraphViewer::RED);
                        }else{
                            edge.setColor(GraphViewer::GREEN);
                            edge2.setColor(GraphViewer::GREEN);
                        }

                        gv.unlock();
                        //Sleep(100);

                    }

                }
            }

        }

        if(costToTravel < bestCost){
            bestCost = costToTravel;
            best = currPath;

        }
    }
    return make_pair(best,bestCost);

}

bool checkIfClientIsDeliverable(Client* client, std::unordered_map<std::string, int> currCarryingCar ){
    for(auto& product: client->getOrder()){
        if(currCarryingCar.find(product.first) != currCarryingCar.end()){
            if(currCarryingCar[product.first] - product.second >= 0){
                currCarryingCar[product.first] -= product.second;
            }else{
                return false;
            }
        }else{ //the requested product doesnt even exist in the providers
            return false;
        }
    }
    return true;
}

bool checkIfProviderIsRelevant(Provider* provider, std::unordered_map<std::string, int> shoppingList ){
    if(provider->isVisited()) return false;
    for(auto& product: provider->getStock()){
        if(shoppingList.find(product.first) != shoppingList.end()){
            return true;
        }
    }
    return false;
}

std::pair<std::vector<Node>, double> DeliveryCar::getBestPossiblePathNearestNeighbournoGV(
        std::vector<Provider *> &providers, std::vector<Client *> &clients, Graph<Node> &graph,
        PATH_FINDING_ALGO algo) {
    //get all the deliverable clients
    for(Provider* provider: providers){
        provider->setVisited(false);
    }
    fillShoppingList(clientsToDeliverTo,clients);
    bool isClientDeliverableNext = false;
    int deliverableClientID = 0;
    Provider* nearestProvider;

    int currNode = 0;
    double totalCost = 0;
    double closestDistance;

    std::vector<Node> finalPath;
    int amountOfDeliverableClients = 0;

    finalPath.push_back(graph.getOriginNode());
    std::unordered_map<std::string, int> currCarryingCar;
    std::pair<std::vector<Node>, double> intermediatePaths;
    double costToTravel = 0;

    while(!clientsToDeliverTo.empty()) {
        amountOfDeliverableClients = 0;
        closestDistance = 99999999;
        for (int clientID: clientsToDeliverTo) {
            costToTravel = 0;
            if (checkIfClientIsDeliverable(clients[clientID], currCarryingCar)) {
                amountOfDeliverableClients++;
                //check the distance between currentNode and client
                if (algo == DIJSKTRA) {
                    intermediatePaths = graph.getDijsktraPath(finalPath[currNode], *clients[clientID]);

                } else if (algo == FLOYD_WARSHALL) {
                    intermediatePaths = graph.getfloydWarshallPath(finalPath[currNode], *clients[clientID]);
                }
                costToTravel = intermediatePaths.second;
                //add the cost to travel in between these two nodes
                if (costToTravel < closestDistance) {
                    closestDistance = costToTravel;
                    isClientDeliverableNext = true;
                    deliverableClientID = clientID;
                }

            }
        }

        //if all clients are already deliverable theres no point in visiting another provider
        if (amountOfDeliverableClients != clientsToDeliverTo.size()) {
            //get the closest provider that has products relevant to the cause
            for (Provider *provider: providers) {
                costToTravel = 0;
                if (checkIfProviderIsRelevant(provider, shoppingList)) {
                    //check the distance between currentNode and client
                    if (algo == DIJSKTRA) {
                        intermediatePaths = graph.getDijsktraPath(finalPath[currNode], *provider);

                    } else if (algo == FLOYD_WARSHALL) {
                        intermediatePaths = graph.getfloydWarshallPath(finalPath[currNode], *provider);
                    }
                    costToTravel = intermediatePaths.second;
                    //add the cost to travel in between these two nodes
                    if (costToTravel < closestDistance) {
                        closestDistance = costToTravel;
                        isClientDeliverableNext = false;
                        nearestProvider = provider;
                    }

                }
            }
        }

        if (!isClientDeliverableNext) {
            loadCar(currCarryingCar, nearestProvider->getStock());
            finalPath.push_back(*nearestProvider);
            nearestProvider->setVisited(true);

        } else {
            removeFromClients(deliverableClientID);
            finalPath.push_back(*clients[deliverableClientID]);
            unloadMerch(currCarryingCar,clients[deliverableClientID]);
        }
        currNode++;
        totalCost += closestDistance;
    }
    finalPath.push_back(graph.getOriginNode());
    if (algo == DIJSKTRA) {
        intermediatePaths = graph.getDijsktraPath(finalPath[currNode], graph.getOriginNode());
    } else if (algo == FLOYD_WARSHALL) {
        intermediatePaths = graph.getfloydWarshallPath(finalPath[currNode], graph.getOriginNode());
    }
    totalCost += intermediatePaths.second;

    return make_pair(finalPath,totalCost);


}


int DeliveryCar::getCapacity() const {
    return capacity;
}

const string &DeliveryCar::getId() const {
    return id;
}

unordered_map<std::string, int> DeliveryCar::getShoppingList() const {
    return shoppingList;
}

void DeliveryCar::setNodesTravelled(const vector<Node> &nodesTravelled) {
    DeliveryCar::nodesTravelled = nodesTravelled;
}

const vector<Node> &DeliveryCar::getNodesTravelled() const {
    return nodesTravelled;
}

pair<vector<Node>, double> DeliveryCar::getBestPossiblePathNoGVBruteForce(std::vector<Provider *> &providers,
                                                                std::vector<Client*> &clients, Graph<Node> &graph, PATH_FINDING_ALGO algo)  {

    fillShoppingList(clientsToDeliverTo, clients);
    vector<vector<int>> viableRoutes;
    checkProviderCombinations(providers.size(), viableRoutes,providers);
    vector<Node> bestRoute;

    vector<int> clientIds = clientsToDeliverTo;
    vector<vector<Node>> allPathsToSearch;

    vector<Node> Path;
    vector<Node> provPath;
    for(auto& provPerm: viableRoutes){
        Path = {}; //source node of the company
        for(auto& prov: provPerm) {
            Path.push_back(*providers[prov]);
        }
        for(auto& client: clientIds) {

            Path.push_back(*clients[client]);
        }
        allPathsToSearch.push_back(Path);
    }

    //GENERATE ALL PERMUTATIONS
    vector<vector<Node>> finalPermsToSearch;
    vector<int> pathInt;
    vector<vector<int>> allPossiblePerms;
    for(auto& pathToSearch: allPathsToSearch){
        pathInt = {};
        allPossiblePerms = {};
        for(int i = 0; i < pathToSearch.size(); i++){
            pathInt.push_back(stoi(pathToSearch[i].getId()));
        }
        findPermutations(pathInt, allPossiblePerms);

        //now, trim all stupid Permutations
        unordered_map<string,int> stockSoFar; //will represent the stock the car is currently holding
        bool skipped = false;
        for(auto iter = allPossiblePerms.begin(); iter != allPossiblePerms.end();){
            stockSoFar.clear();
            skipped = false;
            for(auto& nodeId: *iter){
                Provider* provider = checkIfProvider(providers,nodeId);
                Client* client = checkIfClient(clients,nodeId);
                if(provider != nullptr){ //load the car
                    loadCar(stockSoFar,provider->getStock());
                }else if(client != nullptr){ //unload the car
                    if(!unloadCar(stockSoFar,client)){
                        iter = allPossiblePerms.erase(iter);
                        skipped = true;
                        break;
                    }
                }
            }
            if(!skipped) iter++;
        }

        for(auto& possiblePerm: allPossiblePerms){
            Path = {graph.getOriginNode()};
            for(auto& nodeId: possiblePerm){
                Provider* provider = checkIfProvider(providers,nodeId);
                Client* client = checkIfClient(clients,nodeId);
                if(provider != nullptr){
                    Path.push_back(*provider);
                }else{
                    Path.push_back(*client);
                }
            }
            Path.push_back(graph.getOriginNode());
            finalPermsToSearch.push_back(Path);
        }
    }

    std::pair<vector<Node>, double> intermediatePaths;
    vector<Node> best;
    vector<Node> currPath;
    double bestCost = 9999999;
    double costToTravel;


    for(auto& path1: finalPermsToSearch){
        currPath = {};
        costToTravel = 0;
        for(int i = 0; i < path1.size(); i++){
            currPath.push_back(path1[i]);
            if(i < path1.size() - 1){
                //get the shortest path between these two vertices
                if(algo == DIJSKTRA){
                    intermediatePaths = graph.getDijsktraPath(path1[i], path1[i + 1]);
                }
                else if(algo == FLOYD_WARSHALL){
                    intermediatePaths = graph.getfloydWarshallPath(path1[i], path1[i+ 1]);
                }
                costToTravel = intermediatePaths.second;

            }

        }
        if(costToTravel < bestCost){
            bestCost = costToTravel;
            best = currPath;

        }
    }
    return make_pair(best,bestCost);

}