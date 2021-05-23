#ifndef CAL_MP1_ALGO_CAR_H
#define CAL_MP1_ALGO_CAR_H

#include "client.h"
#include "utils.h"
#include "Graph.h"
#include "productprovider.h"
#include "graphviewer.h"
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
    void fillShoppingList(std::vector<int> clientIds, std::vector<Client*> clients);
    std::pair<std::vector<Node>, double> getBestPossiblePath(std::vector<Provider *>& providers, std::vector<Client*>& clients, Graph<Node>& graph,
                                                             GraphViewer& gv, PATH_FINDING_ALGO algo);
    bool check_if_perm_works( std::vector<int> a, std::vector<Provider *> providers, std::vector<std::vector<int>>& viableRoute );
    void setClientsToDeliverTo(std::vector<int> clients);
    void checkProviderCombinations(int set_size, std::vector<std::vector<int>>& providerId, std::vector<Provider *>& providers);
    int getCapacity() const;
    void loadCar(std::unordered_map<std::string, int>& carStock, std::unordered_map<std::string, int>& stockToLoad );

    const std::string &getId() const;

    std::unordered_map<std::string, int> getShoppingList() const;

    void setNodesTravelled(const std::vector<Node> &nodesTravelled);

    const std::vector<Node> &getNodesTravelled() const;


    pair<vector<Node>, double> getBestPossiblePathNoGV(std::vector<Provider *> &providers,
                                                                    std::vector<Client*> &clients, Graph<Node> &graph, PATH_FINDING_ALGO algo);
};

#endif //CAL_MP1_ALGO_CAR_H