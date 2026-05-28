#include "Float2.h"
#ifndef FLOAT3_H
#define FLOAT3_H

struct Float3 {
    union {
        struct {
            float x, y, z;
        };
        struct {
            float r, g, b;
        };
    };

    Float3();
    Float3(float x, float y, float z);

    Float3 operator+(const Float3 &a) const;
    Float3 operator-(const Float3 &a) const;
    Float3 operator*(const Float3 &a) const;
    static float dot(const Float3 &a, const Float3 &b);
    static Float3 cross(const Float3 &a, const Float3 &b);

    static Float3 scale(const Float3 &a, float r);

    float get_length() const;

    Float3 normalize() const;

    Float2 xy() const;

    void print();
};

#endif
