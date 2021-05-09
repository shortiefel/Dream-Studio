#include "Vector2D.hpp"
#include "math.h"

/*************************************************************************
Pass by passmeter
*************************************************************************/
Vector2D::Vector2D(float _x, float _y) : x{ _x }, y{ _y } {}

/*************************************************************************
Add assignment
*************************************************************************/
Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

/*************************************************************************
Minus assignment
*************************************************************************/
Vector2D& Vector2D::operator-=(const Vector2D& rhs) {
    return *this += -rhs;
}

/*************************************************************************
Multiply assignment
*************************************************************************/
Vector2D& Vector2D::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
}

/*************************************************************************
Divide assignment
*************************************************************************/
Vector2D& Vector2D::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
}

/*************************************************************************
Negate
*************************************************************************/
Vector2D Vector2D::operator-() const {
    Vector2D tem;
    tem.x = -x;
    tem.y = -y;
    return tem;
}

/*************************************************************************
Add
*************************************************************************/
Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs) {
    Vector2D tem(lhs.x, lhs.y);
    tem += rhs;
    return tem;
}

/*************************************************************************
Minus
*************************************************************************/
Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) {
    return lhs + -rhs;
}

/*************************************************************************
Multiply
*************************************************************************/
Vector2D operator*(const Vector2D& lhs, float rhs) {
    Vector2D tem(lhs.x, lhs.y);
    tem *= rhs;
    return tem;
}

/*************************************************************************
Multiply
*************************************************************************/
Vector2D operator*(float lhs, const Vector2D& rhs) {
    return rhs * lhs;
}

/*************************************************************************
Divide
*************************************************************************/
Vector2D operator/(const Vector2D& lhs, float rhs) {
    Vector2D tem(lhs.x, lhs.y);
    tem /= rhs;
    return tem;
}

/*************************************************************************
In this function, pResult will be the unit vector of pVec0
*************************************************************************/
void Vec2Normalize(Vector2D& pResult, const Vector2D& pVec0) {
    pResult = pVec0 / Vec2Length(pVec0);
}

/*************************************************************************
This function returns the length of the vector pVec0
*************************************************************************/
float Vec2Length(const Vector2D& pVec0) {
    return float(sqrt(pow(pVec0.x, 2) + pow(pVec0.y, 2)));

}

/*************************************************************************
This function returns the square of pVec0's length. Avoid the square root
*************************************************************************/
float Vec2SquareLength(const Vector2D& pVec0) {
    return float(pow(pVec0.x, 2) + pow(pVec0.y, 2));
}

/*************************************************************************
In this function, pVec0 and pVec1 are considered as 2D points.
The distance between these 2 2D points is returned
*************************************************************************/
float Vec2Distance(const Vector2D& pVec0, const Vector2D& pVec1) {
    Vector2D tem(pVec0);
    tem -= pVec1;
    return Vec2Length(tem);
}

/*************************************************************************
In this function, pVec0 and pVec1 are considered as 2D points.
The squared distance between these 2 2D points is returned.
Avoid the square root
*************************************************************************/
float	Vec2SquareDistance(const Vector2D& pVec0, const Vector2D& pVec1) {
    Vector2D tem(pVec0);
    tem -= pVec1;
    return Vec2SquareLength(tem);
}

/*************************************************************************
This function returns the dot product between pVec0 and pVec1
*************************************************************************/
float	Vec2DotProduct(const Vector2D& pVec0, const Vector2D& pVec1) {
    return float((pVec0.x * pVec1.x) + (pVec0.y * pVec1.y));
}

/*************************************************************************
This function returns the cross product magnitude
between pVec0 and pVec1
*************************************************************************/
float	Vec2CrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1) {

    return float((pVec0.x * pVec1.y) - (pVec0.y * pVec1.x));
}