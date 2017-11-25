#include "triangle.hpp"

Traingle::Traingle() {
  using namespace Magnum;
  using namespace Math::Literals;

  struct TriangleVertex {
      Vector2 position;
      Color3 color;
  };
  
  static const TriangleVertex data[]{
      {{-0.5f, -0.5f}, 0xff0000_srgbf},   /* Left vertex, red color */
      {{ 0.5f, -0.5f}, 0x00ff00_srgbf},   /* Right vertex, green color */
      {{ 0.0f,  0.5f}, 0x0000ff_srgbf}    /* Top vertex, blue color */
  };

  _buffer.setData(data, BufferUsage::StaticDraw);
  _mesh.setPrimitive(MeshPrimitive::Triangles)
      .setCount(3)
      .addVertexBuffer(_buffer, 0,
          Shaders::VertexColor2D::Position{},
          Shaders::VertexColor2D::Color{Shaders::VertexColor2D::Color::Components::Three});
}

void Traingle::draw() {
  _mesh.draw(_shader);
}
