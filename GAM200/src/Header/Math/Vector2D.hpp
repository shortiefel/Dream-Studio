#ifndef VECTOR2D_H
#define VECTOR2D_H

typedef union Vector2D
{
	struct
	{
		float x, y;
	};

	float m[2];

	// Constructors
	Vector2D() : x{ 0.f }, y{ 0.f } {};
	Vector2D(float _x, float _y);

	// Assignment operators
	Vector2D& operator += (const Vector2D& rhs);
	Vector2D& operator -= (const Vector2D& rhs);
	Vector2D& operator *= (float rhs);
	Vector2D& operator /= (float rhs);

	// Unary operators
	Vector2D operator-() const;

} Vector2D, Vec2, Point2D, Pt2;;


// Binary operators
Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator * (const Vector2D& lhs, float rhs);
Vector2D operator * (float lhs, const Vector2D& rhs);
Vector2D operator / (const Vector2D& lhs, float rhs);

/**************************************************************************/
/*!
	In this function, pResult will be the unit vector of pVec0
 */
 /**************************************************************************/
void	Vec2Normalize(Vector2D& pResult, const Vector2D& pVec0);

/**************************************************************************/
/*!
	This function returns the length of the vector pVec0
 */
 /**************************************************************************/
float	Vec2Length(const Vector2D& pVec0);

/**************************************************************************/
/*!
	This function returns the square of pVec0's length. Avoid the square root
 */
 /**************************************************************************/
float	Vec2SquareLength(const Vector2D& pVec0);

/**************************************************************************/
/*!
	In this function, pVec0 and pVec1 are considered as 2D points.
	The distance between these 2 2D points is returned
 */
 /**************************************************************************/
float	Vec2Distance(const Vector2D& pVec0, const Vector2D& pVec1);

/**************************************************************************/
/*!
	In this function, pVec0 and pVec1 are considered as 2D points.
	The squared distance between these 2 2D points is returned.
	Avoid the square root
 */
 /**************************************************************************/
float	Vec2SquareDistance(const Vector2D& pVec0, const Vector2D& pVec1);

/**************************************************************************/
/*!
	This function returns the dot product between pVec0 and pVec1
 */
 /**************************************************************************/
float	Vec2DotProduct(const Vector2D& pVec0, const Vector2D& pVec1);

/**************************************************************************/
/*!
	This function returns the cross product magnitude
	between pVec0 and pVec1
 */
 /**************************************************************************/
float	Vec2CrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1);

#endif