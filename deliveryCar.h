#ifndef CAL_MP1_ALGO_CAR_H
#define CAL_MP1_ALGO_CAR_H

#include "node.h"
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
public:
    DeliveryCar(std::string id, int capacity);
    bool addDistance(int distance);
    bool addNodeTravelled(Node node);
    bool addToShoppingList(std::string ProductName, int amount);
    void printShoppingList();
    bool checkIfMeetsRequirement(std::unordered_map<std::string, int>& shoppingList);
};

#endif //CAL_MP1_ALGO_CAR_H