#ifndef VEC2_H
#define VEC2_H

template<typename T>
class		Vec2
{
public:
	T				x;
	T				y;

	Vec2(T x1 = 0, T y1 = 0) : x(x1), y(y1) {}
	Vec2(const Vec2 &v) : x(v.x), y(v.y) {}

	Vec2				&operator=(const Vec2 &v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	bool				operator==(const Vec2 &v)
	{
		return (x == v.x && y == v.y);
	}

	bool				operator!=(const Vec2 &v)
	{
		return !(*this == v);
	}

	T				operator[](const int i)
	{
		return (i == 0 ? x : y);
	}

	Vec2				operator+(const Vec2 &v)
	{
		return Vec2(x + v.x, y + v.y);
	}

	Vec2				&operator+=(const Vec2 &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2				operator-(const Vec2 &v)
	{
		return Vec2(x - v.x, y - v.y);
	}

	Vec2				&operator-=(const Vec2 &v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2				operator*(const Vec2 &v)
	{
		return Vec2(x * v.x, y * v.y);
	}

	Vec2				&operator*=(const Vec2 &v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vec2				operator/(const Vec2 &v)
	{
		return Vec2(x / v.x, y / v.y);
	}

	Vec2				&operator/=(const Vec2 &v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	Vec2				operator+(const T s)
	{
		return Vec2(x + s, y + s);
	}

	Vec2				&operator+=(const T s)
	{
		x += s;
		y += s;
		return *this;
	}

	Vec2				operator-(const T s)
	{
		return Vec2(x - s, y - s);
	}

	Vec2				&operator-=(const T s)
	{
		x -= s;
		y -= s;
		return *this;
	}

	Vec2				operator*(const T s)
	{
		return Vec2(x * s, y * s);
	}

	Vec2				&operator*=(const T s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vec2				operator/(const T s)
	{
		return Vec2(x / s, y / s);
	}

	Vec2				&operator/=(const T s)
	{
		x /= s;
		y /= s;
		return *this;
	}
};

template<typename T>
std::ostream				&operator<<(std::ostream &oss, const Vec2<T> &v)
{
	oss << "(" << v.x << ";" << v.y << ")";
	return oss;
}

typedef Vec2<float>		Vec2f;
typedef Vec2<int>		Vec2i;
typedef Vec2<unsigned int>	Vec2u;

#endif /*VEC2_HPP_*/
