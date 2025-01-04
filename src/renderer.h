#pragma once

#include "framebuffer.h"

#include <cstdint>

namespace pongone {

enum class GraphicsResetMode : uint8_t {
    RESET_GPU = 0u,
    RESET_COMMAND_BUFFER_AND_CANCEL_DMA = 1u,
    RESET_COMMAND_BUFFER = 3u,
};

enum class PrimitiveType : uint8_t {
    TILE = 0u,
};

template <PrimitiveType type>
struct Primitive {
    Primitive(uint32_t *orderingTableEntry, uint8_t *nextPrimitivePointer) {
    }
};

class Renderer {
  public:
    explicit Renderer(GraphicsResetMode mode);

    [[nodiscard]] Framebuffer &createFramebuffer(const FramebufferDescriptor &descriptor);

  private:
    Framebuffer m_framebuffer;
};

} // namespace pongone
