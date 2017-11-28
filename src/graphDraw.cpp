#include "graphDraw.hpp"

#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Platform/Sdl2Application.h>

GraphDraw::GraphDraw(const BaseGraph& graph) : _graph(graph){}

std::pair<float, float> GraphDraw::coordinates(const Node& node) {
  auto diff = (2.*3.14)/_graph.nodes.size();

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

  std::vector<Vertex> vNodes; vNodes.reserve(_graph.nodes.size());
  std::vector<Vertex> vEdges; vEdges.reserve(_graph.edges.size()*2);
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
