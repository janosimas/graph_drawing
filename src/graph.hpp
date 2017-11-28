
#ifndef GRAPH
#define GRAPH

#include <graph/graph.h>

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

using BaseGraph = Graph<Node, Edge>;

#endif // GRAPH
