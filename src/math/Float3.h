#ifndef FLOAT3_H
#define FLOAT3_H

class Float3 {
  public:
    float x;
    float y;
    float z;

    Float3();
    Float3(float x, float y, float z);

    static Float3 add(const Float3 &a, const Float3 &b);
    static float dot(const Float3 &a, const Float3, Float3 b);
    static Float3 cross(const Float3 &a, const Float3, Float3 b);

    void print();
};

#endif
