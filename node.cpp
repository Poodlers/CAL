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

double Node::getLat() const {
    return lat;
}

void Node::setLat(double lat) {
    Node::lat = lat;
}

double Node::getLng() const {
    return lng;
}

void Node::setLng(double lng) {
    Node::lng = lng;
}

Node::Node(const std::string &id, double lat, double lng) : id(id), lat(lat), lng(lng) {}
