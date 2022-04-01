#ifndef IGLESHANDLE_HPP
#define IGLESHANDLE_HPP

#include "esUtil.h"

class IGlesHandle
{
public:
    virtual ~IGlesHandle(){}
    virtual bool initialize(ESContext &esContext) = 0;
    virtual void render() = 0;
    virtual void release() = 0;
    virtual void updateData() = 0;
};

#endif // IGLESHANDLE_HPP
