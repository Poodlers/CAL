#include "productprovider.h"

std::string Provider::getTypeOfNode()  {
    return "Provider";
}

Provider::Provider(std::string id):Node(id) {};

Provider::Provider(std::string id, double lat, double lng, std::unordered_map<std::string, int> &stock) : Node(id, lat, lng) {
    this->stock = stock;
}

bool Provider::addProduct(std::string productName, int stock) {
    if(this->stock.find(productName) != this->stock.end()){
        this->stock[productName] = this->stock[productName] + stock;
    }else{
        this->stock[productName] = stock;
    }
    return true;
}

bool Provider::removeProduct(std::string productName, int stock) {
    this->stock[productName] -= stock;
    return true;
}

std::unordered_map<std::string, int> &Provider::getStock()  {
    return stock;
}

bool Provider::operator==(const Node &node) const {
    return this->getId() == node.getId();
}

bool Provider::operator!=(const Node &node) const {
    return this->getId() != node.getId();
}