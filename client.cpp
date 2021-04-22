#include "client.h"



Client::Client(std::string id) : Node(id) {
    type = "Client";
};

bool Client::addOrder(std::string productName, int stock) {
    if(this->n1.find(productName) != this->n1.end()){
        this->n1[productName] = this->n1[productName] + stock;
    }else{
        this->n1[productName] = stock;
    }
}

bool Client::operator!=(const Node &node) const {
    return getId() != node.getId();
}

bool Client::operator==(const Node &node) const {
    return getId() == node.getId();
}

