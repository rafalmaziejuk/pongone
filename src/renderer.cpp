#include "renderer.h"

#include <psxgpu.h>

namespace pongone {

Renderer::Renderer(GraphicsResetMode mode) {
    ResetGraph(static_cast<int32_t>(mode));
}

Framebuffer &Renderer::createFramebuffer(const FramebufferDescriptor &descriptor) {
    m_framebuffer.initialize(descriptor);
    return m_framebuffer;
}

} // namespace pongone
