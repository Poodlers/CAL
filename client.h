#ifndef CAL_MP1_ALGO_CLIENT_H
#define CAL_MP1_ALGO_CLIENT_H

#include "node.h"
#include <string>
#include <unordered_map>

class Client : public Node{
private:
    std::unordered_map<std::string, int> order;
public:
    Client(std::string id);
    Client(std::string id, double lat, double lng,std::unordered_map<std::string, int>& order );
    std::string getTypeOfNode() override;
    bool addOrder(std::string productName, int stock);
    std::unordered_map<std::string, int>& getOrder();
    bool operator==(const Node& node) const;
    bool operator!=(const Node& node) const;
    int getNumOfProducts() const;
};

#endif //CAL_MP1_ALGO_PROD_H