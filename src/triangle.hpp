
#include <Magnum/Buffer.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Mesh.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColor.h>

class Traingle
{
public:
  Traingle();

  ~Traingle() = default;
  Traingle(const Traingle& other) = default;
  Traingle(Traingle&& other) = default;
  Traingle& operator=(const Traingle& other) = default;
  Traingle& operator=(Traingle&& other) = default;

  void draw();

private:
  Magnum::Buffer _buffer;
  Magnum::Mesh _mesh;
  Magnum::Shaders::VertexColor2D _shader;
};
