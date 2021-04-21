#ifndef CAL_MP1_ALGO_CAR_H
#define CAL_MP1_ALGO_CAR_H

#include "client.h"
#include "Graph.h"
#include "productprovider.h"
#include <string>
#include <vector>
#include <unordered_map>


class DeliveryCar{
private:
    std::string id;
    int capacity;
    int distanceTravelled;
    std::unordered_map<std::string, int> shoppingList;
    std::vector<Node> nodesTravelled;
    std::vector<int> clientsToDeliverTo;
public:
    DeliveryCar(std::string id, int capacity);
    bool addDistance(int distance);
    bool addNodeTravelled(Node node);
    bool addToShoppingList(std::string ProductName, int amount);
    void printShoppingList();
    bool checkIfMeetsRequirement(std::unordered_map<std::string, int>& shoppingList);
    void fillShoppingList(std::vector<int> clientIds, std::vector<Client> clients);
    std::vector<Node> getBestPossiblePath(std::vector<Provider>& providers, std::vector<Client>& clients, Graph<Node>& graph);
    void check_if_perm_works( std::vector<int> a, std::vector<Provider> providers, std::vector<std::vector<int>>& viableRoute );
    void setClientsToDeliverTo(std::vector<int> clients);

    int getCapacity() const;
};

#endif //CAL_MP1_ALGO_CAR_H