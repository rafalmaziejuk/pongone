#include "framebuffer.h"

#include <psxgpu.h>

namespace pongone {

void Framebuffer::initialize(const FramebufferDescriptor &descriptor) {
    for (size_t i = 0u; i < renderBufferCount; i++) {
        RenderBufferDescriptor renderBufferDescriptor{
            .bufferSize = descriptor.framebufferSize,
            .orderingTableSize = descriptor.orderingTableSize,
            .width = descriptor.width,
            .height = descriptor.height,
            .x = 0u,
            .y = i * descriptor.height,
        };

        auto &renderBuffer = m_renderBuffers[i];
        renderBuffer.initialize(renderBufferDescriptor);
    }

    auto &activeRenderBuffer = getDrawBuffer();
    m_bufferPointer = activeRenderBuffer.getPointer(0u);
    activeRenderBuffer.clear();

    SetDispMask(1);
}

void Framebuffer::setClearColor(int8_t r, int8_t g, int8_t b) {
    for (size_t i = 0u; i < renderBufferCount; i++) {
        auto &renderBuffer = m_renderBuffers[i];
        renderBuffer.setClearColor(r, g, b);
    }
}

void Framebuffer::present() {
    DrawSync(0);
    VSync(0);

    getDisplayBuffer().display();
    getDrawBuffer().draw();

    m_activeRenderBufferIndex ^= 1;
    m_bufferPointer = getDrawBuffer().getPointer(0u);
    getDrawBuffer().clear();
}

RenderBuffer &Framebuffer::getDisplayBuffer() {
    return m_renderBuffers[m_activeRenderBufferIndex ^ 1];
}

RenderBuffer &Framebuffer::getDrawBuffer() {
    return m_renderBuffers[m_activeRenderBufferIndex];
}

} // namespace pongone
