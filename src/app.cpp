#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Context.h>
#include <Magnum/Renderer.h>
#include <Magnum/Version.h>
#include <Magnum/Math/Color.h>

#include "graph.hpp"

#include <memory>
#include <iostream>

class MyApplication: public Magnum::Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);
        void mousePressEvent(MouseEvent& event) override;

    private:
        void drawEvent() override;
        std::unique_ptr<GraphDraw> graph;
};

MyApplication::MyApplication(const Arguments& arguments):
  Magnum::Platform::Application{arguments}
{
  using namespace Magnum::Math::Literals;

  if(arguments.argc != 2) {
    std::cout << "Expected graph file as parameter...\n";
    throw std::invalid_argument("One argument expected.");
  }

  graph = std::make_unique<GraphDraw>(arguments.argv[1]);

  Magnum::Renderer::setClearColor(0xffffff_srgbf);
  Magnum::Debug() << "Hello! This application is running on" << Magnum::Context::current().version()
                  << "using" << Magnum::Context::current().rendererString();
}

void MyApplication::mousePressEvent(MouseEvent& ) {
  drawEvent();
};

void MyApplication::drawEvent() {
    Magnum::defaultFramebuffer.clear(Magnum::FramebufferClear::Color);

    Magnum::Debug() << "Draw!\n";
    graph->draw();

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
