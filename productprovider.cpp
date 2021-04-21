#include "productprovider.h"



Provider::Provider(std::string id):Node(id) {
    type = "Provider";
};

bool Provider::addProduct(std::string productName, int stock) {
    if(this->n1.find(productName) != this->n1.end()){
        this->n1[productName] = this->n1[productName] + stock;
    }else{
        this->n1[productName] = stock;
    }
    return true;
}


bool Provider::operator==(const Node &node) const {
    return this->getId() == node.getId();
}

bool Provider::operator!=(const Node &node) const {
    return this->getId() != node.getId();
}