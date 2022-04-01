#ifndef HELLOTRIANGLE_H
#define HELLOTRIANGLE_H

#include "common.hpp"
#include "IGlesHandle.hpp"

class HelloTriangle : public IGlesHandle
{
public:
    HelloTriangle();
    ~HelloTriangle();

protected:
    bool initialize(ESContext &esContext) override;
    void render() override;
    void release() override;
    void updateData() override;

private:
    ESContext m_esContext;
};

#endif // HELLOTRIANGLE_H
