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
        if(prod.second > shoppingList[prod.first]){
            return false;
        }
    }
    return true;
}

void DeliveryCar::fillShoppingList(std::vector<int> clientIds, std::vector<Client> clients) {
    this->shoppingList.clear();
    std::unordered_map<std::string,int> clientOrder;
    for(int clientId: clientIds){
        clientOrder = clients[clientId].getOrder();
        for(auto& order: clientOrder){
            addToShoppingList(order.first,order.second);
        }
    }
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

bool DeliveryCar::check_if_perm_works(std::vector<int> a, std::vector<Provider> providers,
                                      std::vector<std::vector<int>> &viableRoute){
    unordered_map<string,int> availableStock;
    Provider* currProvider;
    vector<int> possibleRoute;
    if(a.size() == 0){
        return false;
    }
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
                                            std::vector<Provider> &providers){
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

vector<Node> DeliveryCar::getBestPossiblePath(std::vector<Provider> &providers,
                                              std::vector<Client> &clients, Graph<Node> &graph)  {

    //fillShoppingList(clientsToDeliverTo, clients);
    vector<vector<int>> viableRoutes;
    checkProviderCombinations(providers.size(), viableRoutes,providers);

    //esta parte do código usa powerset like a boss mas dá para faze-lo com uma sliding window technique porvavelmente

    //display2Dvec(viableRoutes);

    vector<vector<int>> allProviderPerms;
    for(auto& route: viableRoutes){
        findPermutations(route,allProviderPerms);
    }
    //display2Dvec(allProviderPerms);

    //now we have all of the possible providers our car could visit (in every possible order)

    //now we can get all the possible permutations on how to visit our clients!
    double bestClientCost = 99999;
    vector<Node> bestRoute;
    /*
    for(auto& clientCombos: clientIds){
     */
    vector<int> clientIds = clientsToDeliverTo;
    vector<vector<Node>> allPathsToSearch;
    vector<vector<int>> allClientPerms;
    findPermutations(clientIds,allClientPerms);
    //display2Dvec(allClientPerms);

    vector<Node> Path;
    vector<Node> provPath;
    for(auto& provPerm: allProviderPerms){
        provPath = {graph.getOriginNode()}; //source node of the company
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

    vector<Node> intermediatePaths;
    vector<Node> best;
    vector<Node> currPath;
    double bestCost = 99999;
    double costToTravel;
    for(auto& path1: allPathsToSearch){
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

    return best;

}

int DeliveryCar::getCapacity() const {
    return capacity;
}
