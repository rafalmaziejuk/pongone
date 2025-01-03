#include <cstddef>
#include <cstdint>

namespace pongone {

struct RenderBufferDescriptor {
    size_t bufferSize{0u};
    size_t orderingTableSize{0u};
    uint32_t width{0u};
    uint32_t height{0u};
    uint32_t x{0u};
    uint32_t y{0u};
};

class RenderBuffer {
  public:
    RenderBuffer();
    ~RenderBuffer();

    void initialize(const RenderBufferDescriptor &descriptor);

    void setClearColor(uint8_t r, uint8_t g, uint8_t b);

    size_t getSize() const;
    size_t getOrderingTableSize() const;
    uint8_t *getPointer(size_t position) const;
    uint32_t *getOrderingTableEntry(size_t index) const;

    void clear();
    void draw();
    void display();

  private:
    struct Impl;
    Impl *m_impl{nullptr};
};

} // namespace pongone
