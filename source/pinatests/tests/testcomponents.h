#include <pina.h>

#include <utils/numerictypes.h>
#include <string>

class ComponentA : public puma::pina::Component
{
public:

    puma::s32 getNumber() const { return m_number; }
    void setNumber( puma::s32 _num ) { m_number = _num; }

private:

    puma::s32 m_number = 0;
};

class ComponentB : public puma::pina::Component
{
public:

    float getNumber() const { return m_number; }
    void setNumber( float _num ) { m_number = _num; }

private:

    float m_number = 0.0f;
};

class ComponentC : public puma::pina::Component
{
public:

    std::string getNumber() const { return m_str; }
    void setNumber( std::string _str ) { m_str = _str; }

private:

    std::string m_str = "";
};