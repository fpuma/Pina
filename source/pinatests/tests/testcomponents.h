#include <pina/component.h>
#include <utils/numerictypes.h>

using namespace puma;
using namespace puma::pina;


class ComponentA : public Component
{
public:

    u32 getNumber() const { return m_number; }
    void setNumber( u32 _num ) { m_number = _num; }

private:

    u32 m_number = 0;
};

class ComponentB : public Component
{
public:

    float getNumber() const { return m_number; }
    void setNumber( float _num ) { m_number = _num; }

private:

    float m_number = 0;
};