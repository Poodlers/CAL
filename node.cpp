#include "node.h"

std::string Node::getTypeOfNode() {
    return "Basic";
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