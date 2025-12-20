#include "ObjectSelection.h"

class PickingFramebuffer
{
public:

    PickingFramebuffer();

    void Init(uint32_t width, uint32_t height);
    void Bind();
    void Unbind();

    EntityID ReadPixel(uint32_t x, uint32_t y) const;

private:
    uint32_t m_FBO = 0;
    uint32_t m_ColorAttachment = 0;
    uint32_t m_DepthAttachment = 0;
};
