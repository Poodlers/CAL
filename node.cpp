#include "node.h"

std::string Node::getTypeOfNode(){
    return type;
}


std::unordered_map<std::string, int> Node::getOrder(){
    return n1;
}
const std::unordered_map<std::string, int> &Node::getStock() const{
    return n1;
}

void Node::changeMap(std::unordered_map<std::string, int> m1){
    n1 = m1;
}

bool Node::checkIfMeetsRequirement(std::unordered_map<std::string, int> &shoppingList) {
    for(auto& prod: this->n1){
        if(shoppingList.find(prod.first) == shoppingList.end()){
            return false;
        }
        if(prod.second > shoppingList[prod.first]){
            return false;
        }

    }
    return true;
}

Node::Node(std::string id) {
    this->id = id;
}

std::string Node::getId() const {
    return this->id;
}

bool Node::operator==(const Node &node) const {
    return node.id == this->id;
}

bool Node::operator!=(const Node &node) const {
    return node.id != this->id;
}