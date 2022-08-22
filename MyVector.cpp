#include<cmath>
#include "Vector3.h"


float Vector3::length() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector3& Vector3::normalize()
{
    float len = length();
    if (len != 0)
    {
        return *this /= len;
    }
    return *this;
}


float Vector3::dot(const Vector3& v)const
{
    //return v.dot(v);
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);

}

Vector3 Vector3::cross(const Vector3& v)const
{
    //return v.cross(v);
    Vector3 temp;
    temp.x = this->y * v.z - this->z * v.y;
    temp.y = this->z * v.x - this->x * v.z;
    temp.z = this->x - v.y - this->y * v.x;
    return temp;
}

//Vector2 ƒNƒ‰ƒX‚É‘®‚³‚È‚¢ŠÖ”ŒQ
//“ñ€‰‰Zq

const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
    Vector3 temp(v1);
    return temp += v2;
}


const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
    Vector3 temp(v1);
    return temp -= v2;
}


const Vector3 operator*(const Vector3& v, float s)
{
    Vector3 temp(v);
    return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v)
{
    return v * s;
}

const Vector3 operator/(const Vector3& v, float s)
{
    Vector3 temp(v);
    return  temp /= s;
}