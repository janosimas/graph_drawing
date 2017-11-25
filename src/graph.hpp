#include <string>
#include <graph/graph.h>

#include <Magnum/Buffer.h>
#include <Magnum/Mesh.h>
#include <Magnum/Shaders/VertexColor.h>

class Node
{
public:
  explicit Node(int id) : _id(id) {}

  ~Node() = default;
  Node(const Node& other) = default;
  Node(Node&& other) = default;
  Node& operator=(const Node& other) = default;
  Node& operator=(Node&& other) = default;

  int id() const {return _id; }
  bool operator==(const Node& other) const { return id() == other.id(); }
  bool operator<(const Node& other) const { return id() < other.id(); }

private:
  int _id;
};

class Edge
{
public:
  explicit Edge() = default;

  ~Edge() = default;
  Edge(const Edge& other) = default;
  Edge(Edge&& other) = default;
  Edge& operator=(const Edge& other) = default;
  Edge& operator=(Edge&& other) = default;

};

class GraphDraw
{
public:
  explicit GraphDraw(const std::string& graphFile);

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

  int _nodesNumber;
  int _edgesNumber;
  Graph<Node, Edge> _graph;
  std::map<Node, std::pair<float, float>> _nodeXY;
};
