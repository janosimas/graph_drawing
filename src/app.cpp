#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Context.h>
#include <Magnum/Renderer.h>
#include <Magnum/Version.h>
#include <Magnum/Math/Color.h>

#include "graph.hpp"

using namespace Magnum;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);
        void mousePressEvent(MouseEvent& event) override;

    private:
        void drawEvent() override;
        GraphDraw graph;
};

MyApplication::MyApplication(const Arguments& arguments):
  Platform::Application{arguments},
  graph("/home/janosimas/off-devel/magnum-bootstrap/src/ash85.mtx")
{
  using namespace Magnum::Math::Literals;

  // Renderer::setClearColor(Color3::fromHsv(216.0_degf, 0.85f, 1.0f));
  Debug() << "Hello! This application is running on" << Context::current().version()
          << "using" << Context::current().rendererString();
}

void MyApplication::mousePressEvent(MouseEvent& ) {
  drawEvent();
};

void MyApplication::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color);

    Debug() << "Draw!\n";
    graph.draw();

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
