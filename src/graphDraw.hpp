
#include "graph.hpp"

#include <string>

#include <Magnum/Buffer.h>
#include <Magnum/Mesh.h>
#include <Magnum/Shaders/VertexColor.h>

#ifndef GRAPH_DRAW
#define GRAPH_DRAW

class GraphDraw
{
public:
  explicit GraphDraw(const MyGraph& graph);

  ~GraphDraw() = default;
  GraphDraw(const GraphDraw& other) = default;
  GraphDraw(GraphDraw&& other) = default;
  GraphDraw& operator=(const GraphDraw& other) = default;
  GraphDraw& operator=(GraphDraw&& other) = default;

  void draw();
private:
  std::pair<float, float> coordinates(const Node& node);

  Magnum::Buffer _buffer;
  Magnum::Mesh _mesh;
  Magnum::Shaders::VertexColor2D _shader;

  Magnum::Buffer _buffer2;
  Magnum::Mesh _mesh2;
  Magnum::Shaders::VertexColor2D _shader2;
  struct Vertex {
      Magnum::Vector2 position;
      Magnum::Color3 color;
  };

  size_t _nodesNumber;
  size_t _edgesNumber;
  MyGraph _graph;
  std::map<Node, std::pair<float, float>> _nodeXY;
};

#endif //GRAPH_DRAW
