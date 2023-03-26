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

class IComponentC : public puma::pina::Component
{
public:
    virtual ~IComponentC() {}
    virtual std::string getNumber() const = 0;
    virtual void setNumber( std::string _str ) = 0;
};

class ComponentC : public IComponentC
{
public:

    std::string getNumber() const override { return m_str; }
    void setNumber( std::string _str ) override { m_str = _str; }

private:

    std::string m_str = "";
};