#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        Node *parent = nullptr;
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        std::vector<Node *> neighbors;    
      
        void FindNeighbors();
      	float distance(Node other) const {
          // Note the current node's x and y is inherited from the Model::Node class
          return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
        };      
      
		Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}

        
      
      private:
        // Add private Node variables and methods here.
        int index;
        RouteModel * parent_model = nullptr;
        RouteModel::Node * FindNeighbor(std::vector<int> node_indices);
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml);  
    // This variable will eventually store the path that is found by the A* search.
    std::vector<Node> path; 
    // Add a public "getter" method `SNodes`. This method should return a reference to the vector of `Nodes` stored as `m_Nodes`.
    auto &SNodes() { return m_Nodes;}
    auto &GetNodeToRoadMap() { return node_to_road; }
    Node &FindClosestNode(float x, float y);

  private:
    // Add private RouteModel variables and methods here.
    //1. Add a private vector of `Node` objects named `m_Nodes`. This will store all of the nodes from the Open Street Map data.
    std::vector<Node> m_Nodes;
  	std::unordered_map<int, std::vector<const Model::Road*>> node_to_road;
  	void CreateNodeToRoadHashmap();
  

};

#endif