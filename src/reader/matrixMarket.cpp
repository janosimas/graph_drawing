#include "matrixMarket.hpp"

#include "../graph.hpp"

#include <graph/graph.h>

std::unique_ptr<GraphDraw> reader::MatrixMarket(const std::string& graphFile) {
  std::fstream file(graphFile, std::ios_base::in);
  if(!file.is_open())
    throw std::invalid_argument("Invalid argument. File not found.\n");

  std::string header;
  // header
  std::getline(file, header);

  // matrix info
  std::string info;
  std::getline(file, info);
  std::stringstream infos(info);

  MyGraph graph;
  std::set<int> nodes;
  for (std::string line; std::getline(file, line); ) {
    std::stringstream ss(line);
    int n1, n2;
    ss >> n1;
    ss >> n2;

    // Magnum::Debug() << n1 << n2;
    if(n1 == n2) continue;

    decltype(graph.nodes.begin()) node1, node2;
    if(nodes.find(n1) == nodes.cend()) {
      node1 = graph.add_node(Node(n1));
      nodes.insert(n1);
    } else {
      for(auto it = graph.nodes.begin(); it != graph.nodes.end(); ++it) {
        if(it->id() == n1)
          node1 = it;
      }
    }

    if(nodes.find(n2) == nodes.cend()) {
      node2 = graph.add_node(Node(n2));
      nodes.insert(n2);
    } else {
      for(auto it = graph.nodes.begin(); it != graph.nodes.end(); ++it) {
        if(it->id() == n2)
          node2 = it;
      }
    }

    graph.add_edge(Edge(), node1, node2);
  }

  return std::make_unique<GraphDraw>(graph);
}
