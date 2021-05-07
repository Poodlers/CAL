#ifndef CAL_MP1_ALGO_BASICNODE_H
#define CAL_MP1_ALGO_BASICNODE_H

#include <string>


class Node{
private:
    std::string id;
    double lat;
    double lng;
public:
    Node(std::string id);

    Node(const std::string &id, double lat, double lng);

    virtual std::string getTypeOfNode();
    std::string getId() const;
    bool operator==(const Node& node) const;
    bool operator!=(const Node& node) const;

    double getLat() const;

    void setLat(double lat);

    double getLng() const;

    void setLng(double lng);
};

#endif //CAL_MP1_ALGO_BASICNODE_H