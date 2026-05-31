#ifndef FLOAT2_H
#define FLOAT2_H

struct Float2 {
    float x;
    float y;

    Float2();
    Float2(float x, float y);

    Float2 operator+(const Float2 &a) const;
    Float2 operator-(const Float2 &a) const;
    Float2 operator*(const Float2 &a) const;
    static float dot(const Float2 &a, const Float2 &b);
    static float cross(const Float2 &a, const Float2 &b);

    static Float2 scale(const Float2 &a, float r);

    float get_length() const;

    Float2 normalize() const;

    void print() const;
};

#endif
