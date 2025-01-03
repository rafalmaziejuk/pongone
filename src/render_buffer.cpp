#include "render_buffer.h"

#include <psxgpu.h>

namespace pongone {

struct RenderBuffer::Impl {
    size_t bufferSize{0u};
    size_t orderingTableSize{0u};
    uint8_t *bufferData{nullptr};
    uint32_t *orderingTable{nullptr};

    DISPENV displayEnvironment;
    DRAWENV drawEnvironment;
};

RenderBuffer::RenderBuffer()
    : m_impl{new Impl{}} {}

RenderBuffer::~RenderBuffer() {
    delete m_impl->bufferData;
    m_impl->bufferData = nullptr;

    delete m_impl->orderingTable;
    m_impl->orderingTable = nullptr;
}

void RenderBuffer::initialize(const RenderBufferDescriptor &descriptor) {
    m_impl->bufferSize = descriptor.bufferSize;
    m_impl->bufferData = new uint8_t[m_impl->bufferSize];

    m_impl->orderingTableSize = descriptor.orderingTableSize;
    m_impl->orderingTable = new uint32_t[m_impl->orderingTableSize];

    SetDefDispEnv(&m_impl->displayEnvironment, descriptor.x, descriptor.y, descriptor.width, descriptor.height);
    SetDefDrawEnv(&m_impl->drawEnvironment, descriptor.x, descriptor.y, descriptor.width, descriptor.height);
}

void RenderBuffer::setClearColor(uint8_t r, uint8_t g, uint8_t b) {
    setRGB0(&m_impl->drawEnvironment, r, g, b);
    m_impl->drawEnvironment.isbg = 1u;
}

size_t RenderBuffer::getSize() const {
    return m_impl->bufferSize;
}

size_t RenderBuffer::getOrderingTableSize() const {
    return m_impl->orderingTableSize;
}

uint8_t *RenderBuffer::getPointer(size_t position) const {
    return (m_impl->bufferData + position);
}

uint32_t *RenderBuffer::getOrderingTableEntry(size_t index) const {
    return (m_impl->orderingTable + index);
}

void RenderBuffer::clear() {
    ClearOTagR(m_impl->orderingTable, m_impl->orderingTableSize);
}

void RenderBuffer::draw() {
    DrawOTagEnv(&m_impl->orderingTable[m_impl->orderingTableSize - 1u], &m_impl->drawEnvironment);
}

void RenderBuffer::display() {
    PutDispEnv(&m_impl->displayEnvironment);
}

} // namespace pongone
