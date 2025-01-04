#pragma once

#include <cstddef>
#include <type_traits>

namespace pongone {

template <typename Type, size_t componentsCount>
struct Vector {
    static_assert(std::is_standard_layout_v<Type>);
    static_assert(componentsCount >= 2u && componentsCount <= 4u);

    constexpr Vector() = default;

    constexpr Vector(Type x, Type y)
        : values{x, y} {
        static_assert(componentsCount == 2u);
    }

    constexpr Vector(Type x, Type y, Type z)
        : values{x, y, z} {
        static_assert(componentsCount == 3u);
    }

    constexpr Vector(Type x, Type y, Type z, Type w)
        : values{x, y, z, w} {
        static_assert(componentsCount == 4u);
    }

    template <typename U>
    constexpr explicit Vector(const Vector<U, 2> &other)
        : values{{static_cast<Type>(other.x()),
                  static_cast<Type>(other.y())}} {}

    template <typename U>
    constexpr explicit Vector(const Vector<U, 3> &other)
        : values{{static_cast<Type>(other.x()),
                  static_cast<Type>(other.y()),
                  static_cast<Type>(other.z())}} {}

    template <typename U>
    constexpr explicit Vector(const Vector<U, 4> &other)
        : values{{static_cast<Type>(other.x()),
                  static_cast<Type>(other.y()),
                  static_cast<Type>(other.z()),
                  static_cast<Type>(other.w())}} {}

    constexpr Type x() const { return values[0]; }
    constexpr Type y() const { return values[1]; }
    constexpr Type z() const {
        static_assert(componentsCount >= 3u && componentsCount <= 4u);
        return values[2];
    }
    constexpr Type w() const {
        static_assert(componentsCount == 4u);
        return values[3];
    }

    constexpr Type r() const { return x(); }
    constexpr Type g() const { return y(); }
    constexpr Type b() const { return z(); }
    constexpr Type a() const { return w(); }

    Type values[componentsCount]{};
};

template <typename Type>
using Vector2D = Vector<Type, 2>;

template <typename Type>
using Vector3D = Vector<Type, 3>;

} // namespace pongone