#include "graph.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Platform/Sdl2Application.h>

GraphDraw::GraphDraw(const std::string& graphFile) {
  Magnum::Debug() << graphFile;

  std::fstream file(graphFile, std::ios_base::in);

  std::string header;
  // header
  std::getline(file, header);

  // matrix info
  std::string info;
  std::getline(file, info);
  std::stringstream infos(info);
  infos >> _nodesNumber; infos >> _nodesNumber;
  infos >> _edgesNumber; _edgesNumber-=_nodesNumber;

  std::set<int> nodes;
  for (std::string line; std::getline(file, line); ) {
    std::stringstream ss(line);
    int n1, n2;
    ss >> n1;
    ss >> n2;

    // Magnum::Debug() << n1 << n2;
    if(n1 == n2) continue;

    decltype(_graph.nodes.begin()) node1, node2;
    if(nodes.find(n1) == nodes.cend()) {
      node1 = _graph.add_node(Node(n1));
      nodes.insert(n1);
    } else {
      for(auto it = _graph.nodes.begin(); it != _graph.nodes.end(); ++it) {
        if(it->id() == n1)
          node1 = it;
      }
    }

    if(nodes.find(n2) == nodes.cend()) {
      node2 = _graph.add_node(Node(n2));
      nodes.insert(n2);
    } else {
      for(auto it = _graph.nodes.begin(); it != _graph.nodes.end(); ++it) {
        if(it->id() == n2)
          node2 = it;
      }
    }

    _graph.add_edge(Edge(), node1, node2);
  }
}

std::pair<float, float> GraphDraw::coordinates(const Node& node) {
  auto diff = (2.*3.14)/_nodesNumber;

  auto it = _nodeXY.find(node);
  if(it == _nodeXY.end()) {
    auto angle = (node.id()-1)*diff;
    //nova coordenada
    float newX = static_cast<float>(std::cos(angle)*0.9);
    float newY = static_cast<float>(std::sin(angle)*0.9);

    auto p = std::make_pair(newX,newY);
    _nodeXY[node] = p;
    return p;
  } else {
    return it->second;
  }
}

void GraphDraw::draw() {
  using namespace Magnum;
  using namespace Math::Literals;

  Magnum::Debug() << "Number of nodes: " << _graph.nodes.size() << _nodesNumber;
  Magnum::Debug() << "Number of edges: " << _graph.edges.size() << _edgesNumber;

  std::vector<Vertex> vNodes; vNodes.reserve(_nodesNumber);
  std::vector<Vertex> vEdges; vEdges.reserve(_edgesNumber*2);
  for(auto node = _graph.nodes.begin(); node != _graph.nodes.end(); ++node) {
    auto xy = coordinates(*node);
    vNodes.emplace_back(Vertex{{xy.first, xy.second}, 0xff0000_srgbf});

    vEdges.emplace_back(Vertex{{xy.first, xy.second}, 0x000000_srgbf});
    vEdges.emplace_back(Vertex{{0,0}, 0x000000_srgbf});
    for(auto edge = node.begin(); edge != node.end(); ++edge) {
      auto n1 = edge.left();
      auto n2 = edge.right();

      auto v1 = coordinates(*n1);
      auto v2 = coordinates(*n2);
      vEdges.emplace_back(Vertex{{v1.first, v1.second}, 0x000000_srgbf});
      vEdges.emplace_back(Vertex{{v2.first, v2.second}, 0x000000_srgbf});
    }
  }

  _buffer2.setData(vEdges, BufferUsage::StaticDraw);
  _mesh2.setPrimitive(MeshPrimitive::Lines)
        .setCount(static_cast<int>(vEdges.size()*2))
        .addVertexBuffer(_buffer2, 0,
          Shaders::VertexColor2D::Position{},
          Shaders::VertexColor2D::Color{Shaders::VertexColor2D::Color::Components::Three});
  _mesh2.draw(_shader2);

  _buffer.setData(vNodes, BufferUsage::StaticDraw);
  _mesh.setPrimitive(MeshPrimitive::Points)
      .setCount(static_cast<int>(vNodes.size()))
      .addVertexBuffer(_buffer, 0,
          Shaders::VertexColor2D::Position{},
          Shaders::VertexColor2D::Color{Shaders::VertexColor2D::Color::Components::Three});
  _mesh.draw(_shader);
}
