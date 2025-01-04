#include "renderer.h"

#include <cstdio>

namespace {

constexpr uint32_t screenWidth = 320u;
constexpr uint32_t screenHeight = 240u;

} // namespace

int main(int argc, const char **argv) {
    pongone::Renderer renderer{pongone::GraphicsResetMode::RESET_GPU};

    pongone::FramebufferDescriptor framebufferDescriptor{
        .framebufferSize = 8192u,
        .orderingTableSize = 2u,
        .size = {screenWidth, screenHeight},
        .clearColor = {63u, 0u, 127u},
    };
    auto &framebuffer = renderer.createFramebuffer(framebufferDescriptor);

    std::printf("logged something\n");

    uint16_t x = 0, y = 0;
    uint16_t dx = 1, dy = 1;
    for (;;) {
        // Update the position and velocity of the bouncing square.
        if (x < 0 || x > (screenWidth - 64))
            dx = -dx;
        if (y < 0 || y > (screenHeight - 64))
            dy = -dy;

        x += dx;
        y += dy;

        // Draw the square by allocating a TILE (i.e. untextured solid color
        // rectangle) primitive at Z = 1.
        pongone::PrimitiveTileDescriptor tileDescriptor{};
        tileDescriptor.position = {static_cast<int16_t>(x), static_cast<int16_t>(y)};
        tileDescriptor.size = {64u, 64u};
        tileDescriptor.color = {255u, 255u, 0u};
        tileDescriptor.depth = 1u;
        framebuffer.pushPrimitive(tileDescriptor);

        framebuffer.present();
    }

    return 0;
}
