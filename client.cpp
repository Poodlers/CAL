#include "client.h"

std::string Client::getTypeOfNode() {
    return "Client";
}

Client::Client(std::string id) : Node(id) {};

Client::Client(std::string id, double lat, double lng, std::unordered_map<std::string, int>& order) : Node(id, lat,lng) {
    this->order = order;
}

bool Client::addOrder(std::string productName, int stock) {
    if(this->order.find(productName) != this->order.end()){
        this->order[productName] = this->order[productName] + stock;
    }else{
        this->order[productName] = stock;
    }
}

std::unordered_map<std::string, int>& Client::getOrder() {
    return this->order;
}
bool Client::operator!=(const Node &node) const {
    return getId() != node.getId();
}

bool Client::operator==(const Node &node) const {
    return getId() == node.getId();
}

int Client::getNumOfProducts() const{
    int totalCapacity = 0;
    for(auto& prod: this->order){
        totalCapacity += prod.second;
    }
    return totalCapacity;
}