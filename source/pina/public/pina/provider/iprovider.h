#pragma once

#include <utils/noncopyable.h>

namespace puma
{
    class IProvider : public NonCopyable
    {
    public:
        virtual ~IProvider() {}
        virtual void uninit() = 0;
    };
}