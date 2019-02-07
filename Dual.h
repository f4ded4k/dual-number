#pragma once
#include <ostream>
#include <cmath>

namespace constants
{
	using ld = long double;

	const ld pi = 3.14159265358979323846l;
	const ld e = 2.71828182845904523536l;
}

template <typename T = double>
class Dual
{
private:
	T x, dx;
public:
	Dual(T x, T dx = T(0)) : x(x), dx(dx) {}

	T getX() const
	{
		return x;
	}

	T getDx() const
	{
		return dx;
	}

	friend Dual<T> operator+(const Dual<T>& a, const Dual<T>& b)
	{
		return Dual<T>{a.x + b.x, a.dx + b.dx};
	}

	friend Dual<T> operator-(const Dual<T>& a, const Dual<T>& b)
	{
		return Dual<T>{a.x - b.x, a.dx - b.dx};
	}

	friend Dual<T> operator*(const Dual<T>& a, const Dual<T>& b)
	{
		return Dual<T>{a.x * b.x, a.x * b.dx + b.x * a.dx};
	}

	friend Dual<T> operator/(const Dual<T>& a, const Dual<T>& b)
	{
		return Dual<T>{a.x / b.x, a.dx / b.x - a.x * b.dx / (b.x * b.x)};
	}

	friend Dual<T> sin(const Dual<T>& a)
	{
		return Dual<T>{sin(a.x), a.dx * cos(a.x)};
	}
	
	friend Dual<T> cos(const Dual<T>& a)
	{
		return Dual<T>{cos(a.x), -a.dx * sin(a.x)};
	}
	
	friend Dual<T> tan(const Dual<T>& a)
	{
		return sin(a) / cos(a);
	}

	friend Dual<T> pow(const Dual<T>& base, const Dual<T>& expo)
	{
		T temp = pow(base.x, expo.x - 1);
		return Dual<T>{temp * base.x, expo.x * temp * base.dx + temp * base.x * log(base.x) * expo.dx};
	}
	
	friend Dual<T> log(const Dual<T>& x, T base = T(constants::e))
	{
		return Dual<T>{log2(x.x) / log2(base), x.dx / (x.x * log(base))};
	}
	
	friend Dual<T> log2(const Dual<T>& x)
	{
		return log(x, 2.0l);
	}

	friend Dual<T> log10(const Dual<T>& x)
	{
		return log(x, 10.0l);
	}

	friend Dual<T> ln(const Dual<T>& x)
	{
		return Dual<T>{log(x.x), x.dx*log(x.x)};
	}
	
	friend Dual<T> sqr(const Dual<T>& x)
	{
		return pow(x, T(2.0));
	}

	friend Dual<T> cube(const Dual<T>& x)
	{
		return pow(x, T(3.0));
	}

	friend Dual<T> sqrt(const Dual<T>& x)
	{
		return pow(x, T(0.5));
	}

	friend std::ostream& operator<<(std::ostream& os, const Dual<T>& x)
	{
		os << "<" << x.x << ", " << x.dx << ">";
		return os;
	}
};