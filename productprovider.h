#ifndef CAL_MP1_ALGO_PROD_H
#define CAL_MP1_ALGO_PROD_H

#include "node.h"
#include <string>
#include <unordered_map>

class Provider : public Node{
public:
    Provider(std::string id);
    bool addProduct(std::string productName, int stock);
    bool operator==(const Node& node) const;
    bool operator!=(const Node& node) const;


};

#endif //CAL_MP1_ALGO_PROD_H