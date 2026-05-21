#ifndef FLOAT3_H
#define FLOAT3_H

class Float3 {
  public:
    float x;
    float y;
    float z;

    Float3();
    Float3(float x, float y, float z);

    Float3 operator+(const Float3 &a) const;
    Float3 operator-(const Float3 &a) const;
    Float3 operator*(const Float3 &a) const;
    static float dot(const Float3 &a, const Float3 &b);
    static Float3 cross(const Float3 &a, const Float3 &b);

    static Float3 scale(const Float3 &a, float r);

    float get_length() const;

    void print();
};

#endif
