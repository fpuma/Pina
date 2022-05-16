#pragma once
#include <algorithm>
#include <assert.h>

#include <pina/entity/entity.h>

#include <utils/noncopyable.h>
#include <utils/numerictypes.h>

#include <vector>
namespace pina
{
    class EntityProvider final : public puma::NonCopyable
    {
    public:
        EntityProvider() {}

        void EntityProvider::init(puma::u32 _entityCount)
        {
            m_entities.resize(_entityCount, EntityStatus::Unassigned);
        }

        void EntityProvider::uninit()
        {
            assert(std::all_of(m_entities.begin(), m_entities.end(), [](const EntityStatus& _status)
                {
                    return _status == EntityStatus::Unassigned;
                }));

            m_entities.clear();
        }

        Entity EntityProvider::requestEntity()
        {
            Entity result;

            auto itFoundEntity = std::find(m_entities.begin(), m_entities.end(), EntityStatus::Unassigned);

            if (m_entities.end() != itFoundEntity)
            {
                result = Entity(std::distance(m_entities.begin(), itFoundEntity));
                *itFoundEntity = EntityStatus::Enabled;
            }
            else
            {
                result = Entity(m_entities.size());
                m_entities.push_back(EntityStatus::Enabled);
            }

            return result;
        }

        void EntityProvider::disposeEntity(const Entity& _entity)
        {
            assert(m_entities[_entity.value()] != EntityStatus::Unassigned);
            m_entities[_entity.value()] = EntityStatus::Unassigned;
        }

        void EntityProvider::enableEntity(const Entity& _entity)
        {
            assert(m_entities[_entity.value()] != EntityStatus::Unassigned);
            m_entities[_entity.value()] = EntityStatus::Enabled;
        }

        void EntityProvider::disableEntity(const Entity& _entity)
        {
            assert(m_entities[_entity.value()] != EntityStatus::Unassigned);
            m_entities[_entity.value()] = EntityStatus::Disabled;
        }

        bool EntityProvider::isEntityEnabled(const Entity& _entity) const
        {
            assert(m_entities[_entity.value()] != EntityStatus::Unassigned);
            return m_entities[_entity.value()] == EntityStatus::Enabled;
        }

    private:

        enum class EntityStatus
        {
            Enabled,
            Disabled,
            Unassigned
        };

        std::vector<EntityStatus> m_entities;
    };


}