//
// Created by radio on 07/05/2021.
//

#ifndef CAL_MP1_ALGO_UTILS_H
#define CAL_MP1_ALGO_UTILS_H

#include <vector>
#include "productprovider.h"
#include "Graph.h"
#include "client.h"

using namespace std;

void display2Dvec(std::vector<vector<int>> a);
void makeGraph3(Graph<Node>& graph, std::vector<Client> clients, std::vector<Provider *> providers);
void makeGraph2(Graph<Node>& graph, std::vector<Client> clients, std::vector<Provider> providers);
void fill_client_and_provider(std::vector<Client*>& clients, std::vector<Provider *>& providers);
void makeGraph(Graph<Node>& graph, std::vector<Client> clients, std::vector<Provider> providers);
bool check_if_available(unordered_map<string,int> availableStock, std::vector<int> clientId, std::vector<Client*>& clients);
void removeFromStock(unordered_map<string,int>& availableStock, std::vector<int> clientId, std::vector<Client*>& clients);
void handleNewClientCombo(std::vector<std::vector<int>>& bestClientCombo, std::vector<int>& clientCombo, double & bestWeight, double currWeight, unordered_map<string,int>& availableStock, std::vector<Client* >& clients);
void removeFromProviders(std::vector<Provider*>& providers, std::vector<Node>& path, unordered_map<std::string,int> shoppingList);
void buildGraphFromTxt(Graph<Node>& graph, string edgesTxt, string nodesTxt, std::vector<Client* >& clients, std::vector<Provider*>& providers);
double calculate_distance_between_two_nodes(Node node1, Node node2);
std::vector<int> getNodeIds(string nodesTxt);
void fill_client_and_provider_rand(std::vector<int> nodeIds, std::vector<Client* >& clients, std::vector<Provider *>& providers, int number_clients, int number_providers, std::vector<string> products){



#endif //CAL_MP1_ALGO_UTILS_H
