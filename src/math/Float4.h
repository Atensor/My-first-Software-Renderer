#include "Float3.h"
#ifndef FLOAT4_H
#define FLOAT4_H

struct Float4 {
    union {
        struct {
            float x, y, z, w;
        };
        struct {
            float r, g, b, a;
        };
    };

    Float4();
    Float4(float x, float y, float z, float w);
    Float4(const Float3 &a, float w);

    Float4 operator+(const Float4 &a) const;
    Float4 operator-(const Float4 &a) const;
    Float4 operator*(const Float4 &a) const;
    static float dot(const Float4 &a, const Float4 &b);

    static Float4 scale(const Float4 &a, float r);

    float get_length() const;

    Float4 normalize() const;

    Float2 xy() const;
    Float3 xyz() const;

    Float4 alpha_composite(const Float4 &a);
    void print();
};

#endif
