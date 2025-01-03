#include "render_buffer.h"

#include <cstddef>
#include <cstdint>

namespace pongone {

struct FramebufferDescriptor {
    size_t framebufferSize{0u};
    size_t orderingTableSize{0u};
    uint32_t width{0u};
    uint32_t height{0u};
};

class Framebuffer {
  public:
    void initialize(const FramebufferDescriptor &descriptor);

    void setClearColor(int8_t r, int8_t g, int8_t b);

    void present();

  private:
    RenderBuffer &getDisplayBuffer();
    RenderBuffer &getDrawBuffer();

  private:
    static constexpr size_t renderBufferCount = 2u;

    RenderBuffer m_renderBuffers[renderBufferCount];
    uint8_t m_activeRenderBufferIndex{0u};
    uint8_t *m_bufferPointer{nullptr};
};

} // namespace pongone
