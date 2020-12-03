#ifndef VEC3_HPP_
# define VEC3_HPP_

template<typename T>
class		Vec3
{
public:
	T				x;
	T				y;
	T				z;

	Vec3(T x1 = 0, T y1 = 0, T z1 = 0) : x(x1), y(y1), z(z1) {}
	Vec3(const Vec3 &v) : x(v.x), y(v.y), z(v.z) {}

	Vec3				&operator=(const Vec3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	bool				operator==(const Vec3 &v)
	{
		return (x == v.x && y == v.y && z == v.z);
	}

	bool				operator!=(const Vec3 &v)
	{
		return !(*this == v);
	}

	T				operator[](const int i)
	{
		return (i == 0 ? x : (i == 1 ? y : z));
	}

	Vec3				operator+(const Vec3 &v)
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	Vec3				&operator+=(const Vec3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vec3				operator-(const Vec3 &v)
	{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	Vec3				&operator-=(const Vec3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec3				operator*(const Vec3 &v)
	{
		return Vec3(x * v.x, y * v.y, z * v.z);
	}

	Vec3				&operator*=(const Vec3 &v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vec3				operator/(const Vec3 &v)
	{
		return Vec3(x / v.x, y / v.y, z / v.z);
	}

	Vec3				&operator/=(const Vec3 &v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vec3				operator+(const T s)
	{
		return Vec3(x + s, y + s, z + s);
	}

	Vec3				&operator+=(const T s)
	{
		x += s;
		y += s;
		z += s;
		return *this;
	}

	Vec3				operator-(const T s)
	{
		return Vec3(x - s, y - s, z - s);
	}

	Vec3				&operator-=(const T s)
	{
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}

	Vec3				operator*(const T s)
	{
		return Vec3(x * s, y * s, z * s);
	}

	Vec3				&operator*=(const T s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vec3				operator/(const T s)
	{
		return Vec3(x / s, y / s, z / s);
	}

	Vec3				&operator/=(const T s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
};

template<typename T>
std::ostream				&operator<<(std::ostream &oss, const Vec3<T> &v)
{
	oss << "(" << v.x << ";" << v.y << ";" << v.z << ")";
	return oss;
}

typedef Vec3<float>		Vec3f;
typedef Vec3<int>		Vec3i;
typedef Vec3<unsigned int>	Vec3u;

#endif /*VEC3_HPP_*/
