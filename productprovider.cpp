#include "productprovider.h"

std::string Provider::getTypeOfNode() {
    return "Provider";
}

Provider::Provider(std::string id):Node(id) {};

bool Provider::addProduct(std::string productName, int stock) {
    if(this->stock.find(productName) != this->stock.end()){
        this->stock[productName] = this->stock[productName] + stock;
    }else{
        this->stock[productName] = stock;
    }
}

const std::unordered_map<std::string, int> &Provider::getStock() const {
    return stock;
}

bool Provider::operator==(const Node &node) const {
    return this->getId() == node.getId();
}

bool Provider::operator!=(const Node &node) const {
    return this->getId() != node.getId();
}