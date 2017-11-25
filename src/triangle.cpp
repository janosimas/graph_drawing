#include "triangle.hpp"

using namespace Magnum;
using namespace Math::Literals;

Triangle::Triangle() {
  data[0] = {{-0.5f, -0.5f}, 0xff0000_srgbf};
  data[1] = {{ 0.5f, -0.5f}, 0x00ff00_srgbf};
  data[2] = {{ 0.0f,  0.5f}, 0x0000ff_srgbf};
}

void Triangle::draw() {
  data[0].position.x() = data[0].position.x()+0.1;

  _buffer.setData(data, BufferUsage::StaticDraw);
  _mesh.setPrimitive(MeshPrimitive::Triangles)
      .setCount(3)
      .addVertexBuffer(_buffer, 0,
          Shaders::VertexColor2D::Position{},
          Shaders::VertexColor2D::Color{Shaders::VertexColor2D::Color::Components::Three});

  _mesh.draw(_shader);
}
