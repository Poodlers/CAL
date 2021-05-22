#ifndef CAL_MP1_ALGO_PROD_H
#define CAL_MP1_ALGO_PROD_H

#include "node.h"
#include <string>
#include <unordered_map>

class Provider : public Node{
private:
    std::unordered_map<std::string, int> stock;
public:
    Provider(std::string id);
    Provider(std::string id, double lat, double lng, double x, double y, std::unordered_map<std::string, int>& stock);
    std::string getTypeOfNode() override;
    bool addProduct(std::string productName, int stock);
    bool operator==(const Node& node) const;
    bool operator!=(const Node& node) const;
    std::unordered_map<std::string, int> &getStock();
    bool removeProduct(std::string productName, int stock);

};

#endif //CAL_MP1_ALGO_PROD_H