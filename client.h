#ifndef CAL_MP1_ALGO_CLIENT_H
#define CAL_MP1_ALGO_CLIENT_H

#include "node.h"
#include <string>
#include <unordered_map>

class Client : public Node{
private:
public:
    Client(std::string id);
    bool addOrder(std::string productName, int stock);
    bool operator==(const Node& node) const;
    bool operator!=(const Node& node) const;
};

#endif //CAL_MP1_ALGO_PROD_H