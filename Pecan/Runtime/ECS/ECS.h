#ifndef PECANENGINE_ECS_H
#define PECANENGINE_ECS_H

#include "pcpch.h" // 包含预编译头文件

#include "Runtime/Core/Timestep.h"

namespace Pecan
{

    class Component; // 前向声明 Component 类
    class Entity;    // 前向声明 Entity 类

    using ComponentID = std::size_t; // 定义 ComponentID 类型为 std::size_t

    // 获取组件类型 ID 的函数
    inline ComponentID GetComponentTypeID()
    {
        static ComponentID lastID = 0; // 静态变量，用于生成唯一 ID
        return lastID++;               // 返回并递增 ID
    }

    // 模板函数，获取特定类型组件的类型 ID
    template<typename T>
    inline ComponentID GetComponentTypeID() noexcept
    {
        static ComponentID typeID = GetComponentTypeID(); // 静态变量，存储特定类型的 ID
        return typeID;                                    // 返回特定类型的 ID
    }

    constexpr std::size_t g_MaxComponent = 32;                                     // 最大组件数常量
    using ComponentBitSet                = std::bitset<g_MaxComponent>;            // 定义组件位集合类型
    using ComponentArray                 = std::array<Component*, g_MaxComponent>; // 定义组件数组类型

    class Component
    {
    public:
        Entity* m_Entity; // 指向所属实体的指针

        virtual void OnAttach() {}     // 虚拟初始化函数
        virtual void OnUpdate(Timestep ts) {} // 虚拟更新函数
        virtual void Draw() {}     // 虚拟绘制函数

        virtual ~Component() {} // 虚拟析构函数
    };

    class Entity
    {
    private:
        bool                                    m_Active = true; // 实体是否活跃标志
        std::vector<std::unique_ptr<Component>> m_Components;    // 组件的容器

        ComponentArray  m_ComponentArray;  // 组件数组
        ComponentBitSet m_ComponentBitSet; // 组件位集合

    public:
        // 更新实体的所有组件
        void OnUpdate(Timestep ts)
        {
            for (auto& c : m_Components)
            {
                c->OnUpdate(ts); // 调用每个组件的更新函数
            }
        }

        // 绘制函数
        void Draw()
        {
            for (auto& c : m_Components)
            {
                c->Draw(); // 调用每个组件的绘制函数
            }
        }

        bool IsActive() const { return m_Active; } // 检查实体是否活跃

        void Destroy() { m_Active = false; } // 将实体设置为非活跃

        // 检查实体是否包含特定类型的组件
        template<typename T>
        bool HasComponent() const
        {
            return m_ComponentBitSet[GetComponentTypeID<T>]; // 根据组件类型 ID 检查位集合
        }

        // 添加组件并初始化
        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... mArgs)
        {
            T* c(new T(std::forward<TArgs>(mArgs)...)); // 创建新组件
            c->m_Entity = this;                         // 设置组件所属的实体
            std::unique_ptr<Component> uPtr {c};        // 创建组件的智能指针
            m_Components.emplace_back(std::move(uPtr)); // 将组件添加到容器

            m_ComponentArray[GetComponentTypeID<T>()]  = c;    // 将组件添加到数组
            m_ComponentBitSet[GetComponentTypeID<T>()] = true; // 设置位集合中的对应位

            c->OnAttach(); // 初始化组件
            return *c; // 返回组件引用
        }

        // 获取特定类型的组件
        template<typename T>
        T& GetComponent() const
        {
            auto ptr(m_ComponentArray[GetComponentTypeID<T>()]); // 从数组中获取组件指针
            return *static_cast<T*>(ptr);                        // 转换为特定类型并返回引用
        }
    };

    class Manager
    {
    private:
        std::vector<std::unique_ptr<Entity>> m_Entities; // 实体的容器

    public:
        // 更新所有实体
        void OnUpdate(Timestep ts)
        {
            for (auto& e : m_Entities)
            {
                e->OnUpdate(ts); // 调用每个实体的更新函数
            }
        }

        // 绘制所有实体
        void Draw()
        {
            for (auto& e : m_Entities)
            {
                e->Draw(); // 调用每个实体的绘制函数
            }
        }

        // 刷新实体容器，移除非活跃实体
        void Refresh()
        {
            m_Entities.erase(std::remove_if(std::begin(m_Entities),
                                            std::end(m_Entities),
                                            [](const std::unique_ptr<Entity>& mEntity) {
                                                return !mEntity->IsActive();
                                            }),     // 检查实体是否活跃
                             std::end(m_Entities)); // 移除非活跃实体
        }

        // 添加新实体并返回引用
        Entity& AddEntity()
        {
            Entity*                 e = new Entity(); // 创建新实体
            std::unique_ptr<Entity> uPtr {e};         // 创建实体的智能指针
            m_Entities.emplace_back(std::move(uPtr)); // 将实体添加到容器
            return *e;                                // 返回实体引用
        }
    };

} // namespace Pecan

#endif // PECANENGINE_ECS_H
