#pragma once

#include <iostream>

namespace Pecan
{
    class Vector2D
    {
    public:
        Vector2D() : x(0.0f), y(0.0f) {};
        Vector2D(float x, float y) : x(x), y(y) {}

        Vector2D& Add(const Vector2D& vec)
        {
            x += vec.x;
            y += vec.y;

            return *this;
        }
        Vector2D& Subtract(const Vector2D& vec)
        {
            x -= vec.x;
            y -= vec.y;

            return *this;
        }
        Vector2D& Multiply(const Vector2D& vec)
        {
            x *= vec.x;
            y *= vec.y;

            return *this;
        }
        Vector2D& Divide(const Vector2D& vec)
        {
            x /= vec.x;
            y /= vec.y;

            return *this;
        }

        friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2) { return v1.Add(v2); }
        friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2) { return v1.Subtract(v2); }
        friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2) { return v1.Multiply(v2); }
        friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2) { return v1.Divide(v2); }

        Vector2D& operator+=(const Vector2D& vec) { return this->Add(vec); }
        Vector2D& operator-=(const Vector2D& vec) { return this->Subtract(vec); }
        Vector2D& operator*=(const Vector2D& vec) { return this->Multiply(vec); }
        Vector2D& operator/=(const Vector2D& vec) { return this->Divide(vec); }

        friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
        {
            stream << "(" << vec.x << ", " << vec.y << ")";
            return stream;
        }


        float x;
        float y;
    };
} // namespace Pecan
