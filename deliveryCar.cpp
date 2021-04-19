#include "deliveryCar.h"
#include <iostream>

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