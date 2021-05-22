#include "utils.h"
#include <fstream>
#include <sstream>
#include <string>

void display2Dvec(vector<vector<int>> a)
{
    for(int c = 0; c < a.size(); c++){
        for (int i = 0; i < a[c].size(); i++) {
            cout << a[c][i] << "  ";
        }
        cout << endl;
    }
}

void makeGraph3(Graph<Node>& graph, vector<Client> clients, vector<Provider *> providers){
    Node node1("1");
    graph.addVertex(node1);

    graph.addVertex(clients[1]);
    graph.addVertex(*providers[0]);
    graph.addVertex(*providers[1]);
    graph.addVertex(*providers[2]);
    graph.addVertex(clients[0]);
    graph.addEdge(node1,clients[0],1);
    graph.addEdge(clients[0],node1,1);

    graph.addEdge(node1,clients[1],2);
    graph.addEdge(clients[1],node1,2);

    graph.addEdge(node1,*providers[0],2);
    graph.addEdge(*providers[0],node1,2);

    graph.addEdge(node1,*providers[1],2);
    graph.addEdge(*providers[1],node1,2);

    graph.addEdge(node1,*providers[2],1);
    graph.addEdge(*providers[2],node1,1);

    graph.addEdge(clients[1],clients[0],1);
    graph.addEdge(clients[0],clients[1],1);

    graph.addEdge(*providers[0],clients[0],1);
    graph.addEdge(clients[0],*providers[0],1);

    graph.addEdge(*providers[1],clients[0],1);
    graph.addEdge(clients[0],*providers[1],1);

    graph.addEdge(*providers[2],clients[0],1);
    graph.addEdge(clients[0],*providers[2],1);

    graph.addEdge(*providers[0],clients[1],1);
    graph.addEdge(clients[1],*providers[0],1);

    graph.addEdge(*providers[1],clients[1],1);
    graph.addEdge(clients[1],*providers[1],1);

    graph.addEdge(*providers[2],clients[1],1);
    graph.addEdge(clients[1],*providers[2],1);

    graph.addEdge(*providers[0],*providers[1],2);
    graph.addEdge(*providers[1],*providers[0],2);

    graph.addEdge(*providers[0],*providers[2],1);
    graph.addEdge(*providers[2],*providers[0],1);

    graph.addEdge(*providers[2],*providers[1],1);
    graph.addEdge(*providers[1],*providers[2],1);
}

void makeGraph2(Graph<Node>& graph, vector<Client> clients, vector<Provider> providers){
    Node node1("1");
    Node node2("2");
    Node node3("3");
    Node node4("4");
    Node node5("5");

    graph.addVertex(node1);

    graph.addVertex(clients[1]);
    graph.addVertex(providers[0]);
    graph.addVertex(providers[1]);
    graph.addVertex(providers[2]);
    graph.addVertex(clients[0]);


    graph.addEdge(node1,clients[0],1);
    graph.addEdge(clients[0],node1,1);

    graph.addEdge(node1,clients[1],2);
    graph.addEdge(clients[1],node1,2);

    graph.addEdge(node1,providers[0],2);
    graph.addEdge(providers[0],node1,2);

    graph.addEdge(node1,providers[1],2);
    graph.addEdge(providers[1],node1,2);

    graph.addEdge(node1,providers[2],1);
    graph.addEdge(providers[2],node1,1);

    graph.addEdge(clients[1],clients[0],1);
    graph.addEdge(clients[0],clients[1],1);

    graph.addEdge(providers[0],clients[0],1);
    graph.addEdge(clients[0],providers[0],1);

    graph.addEdge(providers[1],clients[0],1);
    graph.addEdge(clients[0],providers[1],1);

    graph.addEdge(providers[2],clients[0],1);
    graph.addEdge(clients[0],providers[2],1);

    graph.addEdge(providers[0],clients[1],1);
    graph.addEdge(clients[1],providers[0],1);

    graph.addEdge(providers[1],clients[1],1);
    graph.addEdge(clients[1],providers[1],1);

    graph.addEdge(providers[2],clients[1],1);
    graph.addEdge(clients[1],providers[2],1);

    graph.addEdge(providers[0],providers[1],2);
    graph.addEdge(providers[1],providers[0],2);

    graph.addEdge(providers[0],providers[2],1);
    graph.addEdge(providers[2],providers[0],1);

    graph.addEdge(providers[2],providers[1],1);
    graph.addEdge(providers[1],providers[2],1);

}

void fill_client_and_provider(vector<Client* >& clients, vector<Provider *>& providers){
    Client* client1 = new Client("7100");
    client1->addOrder("Shampoo", 1);
    client1->addOrder("Tomato", 1);
    Client* client2 = new Client("3216");
    client2->addOrder("Burger", 1);
    client2->addOrder("Tomato", 1);
    Provider* provider1 = new Provider("8369");
    provider1->addProduct("Shampoo", 10);
    provider1->addProduct("Tomato", 10);
    Provider* provider2 = new Provider("5811");
    provider2->addProduct("Burger", 10);
    Provider* provider3 = new Provider("8371");
    provider3->addProduct("Tomato", 10);
    clients = {client1, client2};
    providers = {provider1, provider2,provider3};
}

void fill_client_and_provider_rand(vector<int> nodeIds, vector<Client* >& clients, vector<Provider *>& providers, int number_clients, int number_providers,vector<string> products){
    vector<int> usedNodes;

    for (int i = 0; i<number_clients; i++){
        int node;
        if (usedNodes.size() == nodeIds.size()){
            break;
        }
        while (true){
            node = rand() % nodeIds.size();
            std::vector<int>::iterator it = find(usedNodes.begin(),usedNodes.end(),nodeIds[node]);
            if (it == usedNodes.end()) break;
        }
        usedNodes.push_back(nodeIds[node]);
        Client* client = new Client(to_string(nodeIds[node]));
        int num_prod = rand() % products.size();
        for (int e = 0; e < num_prod; e++){
            int prod = rand() % products.size();
            int ammount = rand() % 9 +1;
            client->addOrder(products[prod],ammount);
        }
        clients.push_back(client);
    }

    for (int i = 0; i<number_providers; i++){
        int node;
        if (usedNodes.size() == nodeIds.size()){
            break;
        }
        while (true){
            node = rand() % nodeIds.size();
            std::vector<int>::iterator it = find(usedNodes.begin(),usedNodes.end(),nodeIds[node]);
            if (it == usedNodes.end()) break;
        }
        usedNodes.push_back(nodeIds[node]);
        Provider* provider = new Provider(to_string(nodeIds[node]));
        int num_prod = rand() % products.size();
        for (int e = 0; e < num_prod; e++){
            int prod = rand() % products.size();
            int ammount = rand() % 9 +1;
            provider->addProduct(products[prod],ammount);
        }
        providers.push_back(provider);
    }
}

vector<int> getNodeIds(string nodesTxt){
    vector<int> nodeIds;
    ifstream nodes_file(nodesTxt);
    string line;
    std::getline(nodes_file, line); //get rid of first line with the number of nodes 
    while (std::getline(nodes_file, line))
    {
        std::istringstream iss(line);
        int id;
        char delim;
        if (!(iss >> delim >> id >> delim)) { break; } // error
        nodeIds.push_back(id);
    }
    return nodeIds;
}

void makeGraph(Graph<Node>& graph, vector<Client> clients, vector<Provider> providers){
    Node node1("1");
    Node node2("2");
    Node node3("3");
    Node node4("4");
    Node node5("5");
    graph.addVertex(node1);
    graph.addVertex(node2);
    graph.addVertex(node3);
    graph.addVertex(node4);
    graph.addVertex(node5);
    for(Client client: clients){
        graph.addVertex(client);
    }
    for(Provider provider: providers){
        graph.addVertex(provider);
    }
    graph.setOriginNode(0);
    graph.addEdge(node1,node2,1);
    graph.addEdge(node2,node1,1);

    graph.addEdge(node1,node3,1);
    graph.addEdge(node3,node1,1);

    graph.addEdge(node1,node5,1);
    graph.addEdge(node5,node1,1);

    graph.addEdge(node1,node4,1);
    graph.addEdge(node4,node1,1);

    graph.addEdge(node1,providers[2],1);
    graph.addEdge(providers[2],node1,1);

    graph.addEdge(node1,clients[0],1);
    graph.addEdge(clients[0],node1,1);

    graph.addEdge(node4,providers[1],1);
    graph.addEdge(providers[1],node4,1);

    graph.addEdge(node2,providers[0],1);
    graph.addEdge(providers[0],node2,1);

    graph.addEdge(providers[2],clients[1],1);
    graph.addEdge(clients[1],providers[2],1);

}

bool check_if_available(unordered_map<string,int> availableStock,vector<int> clientId, vector<Client*>& clients){
    for(int i = 0; i < clientId.size();i++){
        for(auto& product: clients[clientId[i]]->getOrder()){
            if(availableStock.find(product.first) != availableStock.end()){
                if(availableStock[product.first] - product.second >= 0){
                    availableStock[product.first] -= product.second;
                }else{
                    return false;
                }
            }else{ //the requested product doesnt even exist in the providers
                return false;
            }
        }
    }
    return true;
}

void removeFromStock(unordered_map<string,int>& availableStock, vector<int> clientId, vector<Client*>& clients){
    for(int i = 0; i < clientId.size();i++){
        for(auto& product: clients[clientId[i]]->getOrder()){
            availableStock[product.first] -= product.second;
        }
    }
}

void handleNewClientCombo(vector<vector<int>>& bestClientCombo, vector<int>& clientCombo, double & bestWeight, double currWeight, unordered_map<string,int>& availableStock, vector<Client*>& clients){
    if(check_if_available(availableStock,clientCombo,clients)){
        if(bestClientCombo.empty()){
            bestClientCombo.push_back(clientCombo);
            bestWeight = currWeight;
            return;
        }
        else if(clientCombo.size() > bestClientCombo[0].size()){
            bestClientCombo.clear();
            bestClientCombo.push_back(clientCombo);
            bestWeight = currWeight;
        }
        else if(clientCombo.size() == bestClientCombo[0].size()){
            if(currWeight > bestWeight){
                bestClientCombo.clear();
                bestClientCombo.push_back(clientCombo);
                bestWeight = currWeight;
            }else if(currWeight == bestWeight){
                bestClientCombo.push_back(clientCombo);
            }

        }
    }
}

Provider* getProvider(vector<Provider*>& providers, Node& node){
    for(Provider* provider: providers){
        if(provider->getId() == node.getId()){
            return provider;
        }
    }
    return nullptr;
}

void removeFromProviders(vector<Provider*>& providers, vector<Node>& path, unordered_map<std::string,int> shoppingList){

    for(Node node: path){
        Provider* provider = getProvider(providers,node);
        if(provider != nullptr){
            unordered_map<string,int> providerStock = provider->getStock();
            for(auto& prod: providerStock){ //iterate through the products in this provider!
                if(shoppingList.find(prod.first) == shoppingList.end() || shoppingList[prod.first] == 0){
                    continue; //this product is not in the shoppingList for this car and can be ignored
                }else{
                    if(prod.second >= shoppingList[prod.first]){ //provider has more than what the car needs
                        provider->removeProduct(prod.first,shoppingList[prod.first]); //load the required for what the car needs
                        shoppingList[prod.first] = 0;
                    }else{
                        provider->removeProduct(prod.first,prod.second);
                        shoppingList[prod.first] -= prod.second;
                    }
                }
            }
        }

    }

}

double calculate_distance_between_two_nodes(Node node1, Node node2){

    const int R = 6371 * 1000; // metres
    const double s1 = node1.getLat() * M_PI/180; // φ, λ in radians
    const double s2 = node2.getLat() * M_PI/180;
    const double p1 = (node2.getLat() - node1.getLat()) * M_PI/180;
    const double p2 = (node2.getLng() - node1.getLng()) * M_PI/180;

    const double a = sin(p1/2) * sin(p1/2) +
                     cos(s1) * cos(s2) *
                     sin(p2/2) * sin(p2/2);
    const double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return R * c; // in metres
}

void buildGraphFromTxt(Graph<Node>& graph, string edgesTxt, string nodesTxt, vector<Client* >& clients, vector<Provider*>& providers){
    ifstream edge_file(edgesTxt);
    ifstream nodes_file(nodesTxt);
    string line;
    std::getline(nodes_file, line);
    int num_of_nodes = stoi(line);
    graph.setOriginNode(5);
    while (std::getline(nodes_file, line))
    {
        std::istringstream iss(line);
        int id;
        double lat, lng;
        char delim;
        if (!(iss >> delim >> id >> delim >> lat >> delim >> lng  >>delim)) { break; } // error
        Node* node = new Node(to_string(id), lat, lng);
        for(Client* client1: clients){
            if(*node == *client1){
                client1->setLat(lat);
                client1->setLng(lng);
                node = new Client(to_string(id), lat, lng, client1->getOrder());
                break;
            }
        }
        for(Provider* provider: providers){
            if(*node == *provider){
                provider->setLng(lng);
                provider->setLat(lat);
                node = new Provider(to_string(id), lat,lng, provider->getStock());
                break;
            }
        }

        graph.addVertex(*node);
        //cout << "Lat: " << lat << "   Long: " << lng << endl;
        // process  (id, lat, lng)
    }

    std::getline(edge_file, line);
    int num_of_edges = stoi(line);
    while (std::getline(edge_file, line))
    {
        std::istringstream iss(line);
        int node1, node2;
        char delim;
        if (!(iss >> delim >> node1 >> delim >> node2 >> delim)) { break; } // error
        Node node3(to_string(node1));
        Node node4(to_string(node2));
        Vertex<Node>* v1 = graph.findVertex(node3);
        Vertex<Node>* v2 = graph.findVertex(node4);
        double distance = calculate_distance_between_two_nodes(v1->getInfo(), v2->getInfo());
        graph.addEdge(v1->getInfo(), v2->getInfo(), distance);
        graph.addEdge(v2->getInfo(), v1->getInfo(),distance);
        // process  (id, lat, lng)
    }


}
