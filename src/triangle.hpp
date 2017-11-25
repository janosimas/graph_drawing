
#include <Magnum/Buffer.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Mesh.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColor.h>

class Triangle
{
public:
  Triangle();

  ~Triangle() = default;
  Triangle(const Triangle& other) = default;
  Triangle(Triangle&& other) = default;
  Triangle& operator=(const Triangle& other) = default;
  Triangle& operator=(Triangle&& other) = default;

  void draw();

private:
  Magnum::Buffer _buffer;
  Magnum::Mesh _mesh;
  Magnum::Shaders::VertexColor2D _shader;

  struct TriangleVertex {
      Magnum::Vector2 position;
      Magnum::Color3 color;
  };

  TriangleVertex data[3];
};
