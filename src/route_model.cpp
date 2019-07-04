  #include "route_model.h"
  #include <iostream>

  RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml)
  {
      // We extend the Model class to get access to Nodes() by using this keyword
      int counter = 0;
      for (Model::Node node : this->Nodes())
      {
          m_Nodes.push_back(Node(counter, this, node));
          counter++;
      }
      CreateNodeToRoadHashmap();
  }

  void RouteModel::CreateNodeToRoadHashmap() 
  {
    for (const Model::Road &road : Roads()) {
      if (road.type != Model::Road::Type::Footway) {
        for (int node_index : Ways()[road.way].nodes) {
          // If the node index is not in the node_to_road hashmap yet, 
          // set the value for the node_idx key to be an empty vector of const Model::Road* objects.
          if (node_to_road.find(node_index) == node_to_road.end()) {
            node_to_road[node_index] = std::vector<const Model::Road*> ();
          }
          // Push a pointer-to-the-current-road-in-the-loop to the back of the vector given by the node_idx key in node_to_road.
          node_to_road[node_index].push_back(&road);
        }
      }
    }
  }

  RouteModel::Node * RouteModel::Node::FindNeighbor(std::vector<int> node_indices)
  {
    Node *closest_node = nullptr;
    RouteModel::Node node;

    for (int node_index : node_indices) {
      node = parent_model->SNodes()[node_index];
      if ( this->distance(node) != 0.0 && !node.visited){
        // If the closest_node equals nullptr, or the distance from this to node is less than the distance from this to *closest_node
        if (closest_node == nullptr || this->distance(node) < this->distance(*closest_node)) {
          closest_node = &parent_model->SNodes()[node_index];
        }
      }
    }
    return closest_node;
  }

  void RouteModel::Node::FindNeighbors()
  {
    for (auto & road : parent_model->node_to_road[this->index]) {
      RouteModel::Node* new_neighbor = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
      if (new_neighbor) {
        this->neighbors.emplace_back(new_neighbor);
      }
    }
  }

  RouteModel::Node& RouteModel::FindClosestNode(float x, float y){
    Node input;
    input.x = x;
    input.y = y;

    float min_dist = std::numeric_limits<float>::max();
    float dist;
    int closest_idx;

    for (const Model::Road &road : Roads()) {
      if (road.type != Model::Road::Type::Footway) {
        for (int node_idx : Ways()[road.way].nodes) {
          dist = input.distance(SNodes()[node_idx]);
          if (dist < min_dist) {
            closest_idx = node_idx;
            min_dist = dist;
          }
        }
      }
    }
    return SNodes()[closest_idx];
  }
