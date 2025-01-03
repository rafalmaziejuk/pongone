#include "framebuffer.h"

#include <cstddef>
#include <cstdint>

namespace pongone {

enum class GraphicsResetMode : uint8_t {
    RESET_GPU = 0,
    RESET_COMMAND_BUFFER_AND_CANCEL_DMA = 1,
    RESET_COMMAND_BUFFER = 3,
};

class Renderer {
  public:
    explicit Renderer(GraphicsResetMode mode);

    void createFramebuffer(const FramebufferDescriptor &descriptor);

    void setClearColor(uint8_t r, uint8_t g, uint8_t b);

    void present();

  private:
    Framebuffer m_framebuffer;
};

} // namespace pongone
