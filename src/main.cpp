#include "renderer.h"

namespace {

constexpr uint32_t screenWidth = 320u;
constexpr uint32_t screenHeight = 240u;

} // namespace

int main(int argc, const char **argv) {
    pongone::Renderer renderer{pongone::GraphicsResetMode::RESET_GPU};

    pongone::FramebufferDescriptor framebufferDescriptor{
        .framebufferSize = 8192u,
        .orderingTableSize = 2u,
        .width = screenWidth,
        .height = screenHeight,
    };
    renderer.createFramebuffer(framebufferDescriptor);
    renderer.setClearColor(255u, 255u, 255u);

    for (;;) {
        renderer.present();
    }

    return 0;
}
