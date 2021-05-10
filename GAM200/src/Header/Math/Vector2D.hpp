#ifndef VectorND_H
#define VectorND_H

template <typename T>
class VectorND
{
public:
	T x, y;

	// Constructors
	VectorND() : x{ T{} }, y{ T{} } {};
	VectorND(T _x, T _y) : x{ _x }, y{ _y } {}

	// Assignment operators
	VectorND<T>& operator += (const VectorND<T>& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	VectorND<T>& operator -= (const VectorND<T>& rhs) {
		return *this += -rhs;
	}

	VectorND<T>& operator *= (T rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	VectorND<T>& operator /= (T rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	// Unary operators
	VectorND<T> operator-() const {
		VectorND tem;
		tem.x = -x;
		tem.y = -y;
		return tem;
	}
};


// Binary operators
template <typename T>
VectorND<T> operator + (const VectorND<T>& lhs, const VectorND<T>& rhs) {
	VectorND tem(lhs.x, lhs.y);
	tem += rhs;
	return tem;
}

template <typename T>
VectorND<T> operator - (const VectorND<T>& lhs, const VectorND<T>& rhs) {
	return lhs + -rhs;
}

template <typename T>
VectorND<T> operator * (const VectorND<T>& lhs, T rhs) {
	VectorND tem(lhs.x, lhs.y);
	tem *= rhs;
	return tem;
}

template <typename T>
VectorND<T> operator * (T lhs, const VectorND<T>& rhs) {
	return rhs * lhs;
}

template <typename T>
VectorND<T> operator / (const VectorND<T>& lhs, T rhs) {
	VectorND tem(lhs.x, lhs.y);
	tem /= rhs;
	return tem;
}


/**************************************************************************/
/*!
	In this function, pResult will be the unit vector of pVec0
 */
 /**************************************************************************/
template <typename T>
void	Vec2Normalize(VectorND<T>& pResult, const VectorND<T>& pVec0) {
	pResult = pVec0 / Vec2Length(pVec0);
}

/**************************************************************************/
/*!
	This function returns the length of the vector pVec0
 */
 /**************************************************************************/
template <typename T>
T	Vec2Length(const VectorND<T>& pVec0) {
	return T(sqrt(pow(pVec0.x, 2) + pow(pVec0.y, 2)));
}

/**************************************************************************/
/*!
	This function returns the square of pVec0's length. Avoid the square root
 */
 /**************************************************************************/
template <typename T>
T	Vec2SquareLength(const VectorND<T>& pVec0) {
	return T(pow(pVec0.x, 2) + pow(pVec0.y, 2));
}

/**************************************************************************/
/*!
	In this function, pVec0 and pVec1 are considered as 2D points.
	The distance between these 2 2D points is returned
 */
 /**************************************************************************/
template <typename T>
T	Vec2Distance(const VectorND<T>& pVec0, const VectorND<T>& pVec1) {
	VectorND tem(pVec0);
	tem -= pVec1;
	return Vec2Length(tem);
}

/**************************************************************************/
/*!
	In this function, pVec0 and pVec1 are considered as 2D points.
	The squared distance between these 2 2D points is returned.
	Avoid the square root
 */
 /**************************************************************************/
template <typename T>
T	Vec2SquareDistance(const VectorND<T>& pVec0, const VectorND<T>& pVec1) {
	VectorND tem(pVec0);
	tem -= pVec1;
	return Vec2SquareLength(tem);
}

/**************************************************************************/
/*!
	This function returns the dot product between pVec0 and pVec1
 */
 /**************************************************************************/
template <typename T>
T	Vec2DotProduct(const VectorND<T>& pVec0, const VectorND<T>& pVec1) {
	return T((pVec0.x * pVec1.x) + (pVec0.y * pVec1.y));
}

/**************************************************************************/
/*!
	This function returns the cross product magnitude
	between pVec0 and pVec1
 */
 /**************************************************************************/
template <typename T>
T	Vec2CrossProductMag(const VectorND<T>& pVec0, const VectorND<T>& pVec1) {
	return T((pVec0.x * pVec1.y) - (pVec0.y * pVec1.x));
}



using Vec2 = VectorND<float>;
using iVec2 = VectorND<int>;
using uiVec2 = VectorND<unsigned int>;
#endif