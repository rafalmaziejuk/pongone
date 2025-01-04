#pragma once

#include "vector.h"

#include <cstddef>
#include <cstdint>

namespace pongone {

struct RenderBufferDescriptor {
    size_t bufferSize{0u};
    size_t orderingTableSize{0u};
    Vector2D<uint32_t> size{0u, 0u};
    Vector2D<uint32_t> position{0u, 0u};
    Vector3D<uint8_t> clearColor{0u, 0u, 0u};
};

class RenderBuffer {
  public:
    RenderBuffer();
    ~RenderBuffer();

    void initialize(const RenderBufferDescriptor &descriptor);

    size_t getSize() const;
    size_t getOrderingTableSize() const;
    uint8_t *getPointer(size_t position) const;
    uint32_t *getOrderingTableEntry(size_t index) const;

    void clear();
    void draw();
    void display();

  public:
    RenderBuffer(const RenderBuffer &) = delete;
    RenderBuffer &operator=(const RenderBuffer &) = delete;
    RenderBuffer(RenderBuffer &&) = delete;
    RenderBuffer &operator=(RenderBuffer &&) = delete;

  private:
    struct Impl;
    Impl *m_impl{nullptr};
};

} // namespace pongone
