#pragma once

#include <pina/component/icomponentprovider.h>

namespace puma
{
    class ComponentProvider : public IComponentProvider
    {
    public:
        ComponentProvider() {}

        void uninit() override {}
    };
}