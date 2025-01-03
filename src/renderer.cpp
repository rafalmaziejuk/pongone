#include "renderer.h"

#include <psxgpu.h>

namespace pongone {

Renderer::Renderer(GraphicsResetMode mode) {
    ResetGraph(static_cast<int32_t>(mode));
}

void Renderer::createFramebuffer(const FramebufferDescriptor &descriptor) {
    m_framebuffer.initialize(descriptor);
}

void Renderer::setClearColor(uint8_t r, uint8_t g, uint8_t b) {
    m_framebuffer.setClearColor(r, g, b);
}

void Renderer::present() {
    m_framebuffer.present();
}

} // namespace pongone
