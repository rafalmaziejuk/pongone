#include "framebuffer.h"

#include <psxgpu.h>

namespace pongone {

struct Framebuffer::Impl {
    inline RenderBuffer &getDisplayBuffer() {
        return renderBuffers[activeRenderBufferIndex ^ 1];
    }

    inline RenderBuffer &getDrawBuffer() {
        return renderBuffers[activeRenderBufferIndex];
    }

    template <typename T>
    inline T *allocatePrimitive(uint32_t depth) {
        auto primitive = reinterpret_cast<T *>(nextPrimitivePointer);
        addPrim(getDrawBuffer().getOrderingTableEntry(depth), primitive);

        nextPrimitivePointer += sizeof(T);

        return primitive;
    }

    static constexpr size_t renderBufferCount = 2u;

    RenderBuffer renderBuffers[renderBufferCount];
    uint8_t activeRenderBufferIndex{0u};
    uint8_t *nextPrimitivePointer{nullptr};
};

Framebuffer::Framebuffer()
    : m_impl{new Impl{}} {}

Framebuffer::~Framebuffer() {
    delete m_impl;
    m_impl = nullptr;
}

void Framebuffer::initialize(const FramebufferDescriptor &descriptor) {
    for (size_t i = 0u; i < Impl::renderBufferCount; i++) {
        RenderBufferDescriptor renderBufferDescriptor{
            .bufferSize = descriptor.framebufferSize,
            .orderingTableSize = descriptor.orderingTableSize,
            .size = {descriptor.size.x(), descriptor.size.y()},
            .position = {0u, i * descriptor.size.y()},
            .clearColor = descriptor.clearColor,
        };

        auto &renderBuffer = m_impl->renderBuffers[i];
        renderBuffer.initialize(renderBufferDescriptor);
    }

    auto &activeRenderBuffer = m_impl->getDrawBuffer();
    m_impl->nextPrimitivePointer = activeRenderBuffer.getPointer(0u);
    activeRenderBuffer.clear();

    SetDispMask(1);
}

void Framebuffer::pushPrimitive(const PrimitiveTileDescriptor &descriptor) {
    auto primitive = m_impl->allocatePrimitive<TILE>(descriptor.depth);
    setTile(primitive);
    setXY0(primitive, descriptor.position.x(), descriptor.position.y());
    setWH(primitive, descriptor.size.x(), descriptor.size.y());
    setRGB0(primitive, descriptor.color.r(), descriptor.color.g(), descriptor.color.b());
}

void Framebuffer::present() {
    DrawSync(0);
    VSync(0);

    m_impl->getDisplayBuffer().display();
    m_impl->getDrawBuffer().draw();

    m_impl->activeRenderBufferIndex ^= 1;
    m_impl->nextPrimitivePointer = m_impl->getDrawBuffer().getPointer(0u);
    m_impl->getDrawBuffer().clear();
}

} // namespace pongone
