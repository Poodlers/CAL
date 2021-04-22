#ifndef CAL_MP1_ALGO_BASICNODE_H
#define CAL_MP1_ALGO_BASICNODE_H

#include <string>
#include <unordered_map>

class Node{
private:
    std::string id;
protected:
    std::unordered_map<std::string, int> n1;
    std::string type = "Basic";
public:
    Node(std::string id);
    std::string getTypeOfNode();
    std::string getId() const;
    std::unordered_map<std::string, int> getOrder();
    const std::unordered_map<std::string, int> &getStock() const;
    void changeMap(std::unordered_map<std::string, int> m1);
    bool checkIfMeetsRequirement(std::unordered_map<std::string, int> &shoppingList);
    bool operator==(const Node& node) const;
    bool operator!=(const Node& node) const;
};

#endif //CAL_MP1_ALGO_BASICNODE_H