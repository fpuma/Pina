#pragma once

#include <base/providers/icomponentprovider.h>

namespace puma
{
    class ComponentProvider : public IComponentProvider
    {
    public:
        ComponentProvider() {}

        void uninit() override {}
    };
}