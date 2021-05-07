#include "deliveryCar.h"
#include <iostream>

using namespace std;
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
                carStock[prod.first] = shoppingList[prod.first]; //load the required for what the car needs
            }else{
                carStock[prod.first] = stockToLoad[prod.first]; // load all this provider can afford to give
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

pair<vector<Node>, double> DeliveryCar::getBestPossiblePath(std::vector<Provider *> &providers,
                                              std::vector<Client*> &clients, Graph<Node> &graph)  {

    fillShoppingList(clientsToDeliverTo, clients);
    vector<vector<int>> viableRoutes;
    checkProviderCombinations(providers.size(), viableRoutes,providers);

    //esta parte do código usa powerset like a boss mas dá para faze-lo com uma sliding window technique porvavelmente

    //display2Dvec(viableRoutes);

    /*
    vector<vector<int>> allProviderPerms;
    for(auto& route: viableRoutes){
        findPermutations(route,allProviderPerms);
    }
     */
    //display2Dvec(allProviderPerms);

    //now we have all of the possible providers our car could visit (in every possible order)

    //now we can get all the possible permutations on how to visit our clients!

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
            finalPermsToSearch.push_back(Path);
        }
    }

    vector<Node> intermediatePaths;
    vector<Node> best;
    vector<Node> currPath;
    double bestCost = 99999;
    double costToTravel;
    for(auto& path1: finalPermsToSearch){
        currPath = {};
        costToTravel = 0;
        for(int i = 0; i < path1.size(); i++){
            currPath.push_back(path1[i]);
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

        if(costToTravel < bestCost){
            bestCost = costToTravel;
            best = currPath;

        }
    }

    return make_pair(best,bestCost);

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
