#ifndef FLOAT2_H
#define FLOAT2_H

class Float2 {
  public:
    float x;
    float y;

    Float2();
    Float2(float x, float y);

    static Float2 add(const Float2 &a, const Float2 &b);
    static float dot(const Float2 &a, const Float2 &b);
    static float cross(const Float2 &a, const Float2 &b);

    void print();
};

#endif
