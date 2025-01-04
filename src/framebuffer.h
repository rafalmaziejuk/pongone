#pragma once

#include "render_buffer.h"
#include "vector.h"

#include <cstddef>
#include <cstdint>

namespace pongone {

struct FramebufferDescriptor {
    size_t framebufferSize{0u};
    size_t orderingTableSize{0u};
    Vector2D<uint32_t> size{0u, 0u};
    Vector3D<uint8_t> clearColor{0u, 0u, 0u};
};

struct PrimitiveDescriptor {
    uint32_t depth{0u};
};

struct PrimitiveTileDescriptor : public PrimitiveDescriptor {
    Vector2D<int16_t> position{0, 0};
    Vector2D<int16_t> size{0, 0};
    Vector3D<uint8_t> color{0u, 0u, 0u};
};

class Framebuffer {
  public:
    Framebuffer();
    ~Framebuffer();

    void initialize(const FramebufferDescriptor &descriptor);

    void pushPrimitive(const PrimitiveTileDescriptor &descriptor);

    void present();

  public:
    Framebuffer(const Framebuffer &) = delete;
    Framebuffer &operator=(const Framebuffer &) = delete;
    Framebuffer(Framebuffer &&) = delete;
    Framebuffer &operator=(Framebuffer &&) = delete;

  private:
    struct Impl;
    Impl *m_impl{nullptr};
};

} // namespace pongone
