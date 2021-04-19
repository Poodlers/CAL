#ifndef CAL_MP1_ALGO_BASICNODE_H
#define CAL_MP1_ALGO_BASICNODE_H

#include <string>


class Node{
private:
    std::string id;
public:
    Node(std::string id);
    virtual std::string getTypeOfNode();
    std::string getId() const;
    bool operator==(const Node& node) const;
    bool operator!=(const Node& node) const;
};

#endif //CAL_MP1_ALGO_BASICNODE_H