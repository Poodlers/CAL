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