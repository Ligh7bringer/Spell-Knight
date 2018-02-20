#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

namespace sf {
	//create definition for our type
	const double PI = 3.14159265358979323846; /* pi */
	typedef Vector2<size_t> Vector2ul;

	//returns the length of a sf::vector
	template<typename T> double length(const Vector2<T> &v) {
		//to do
		return sqrt( (v.x * v.x) + (v.y * v.y) );
	}

	//returns normalized sf::vector
	template<typename T> Vector2<T> normalize(const Vector2<T> &v) {
		Vector2<T> vector;
		double l = length(v);
		if (l != 0) {
			vector.x /= l;
			vector.y /= l;
		}
		//to do
		return vector;
	}

	//allow casting
	template <typename T, typename U> Vector2<T> Vcast(const Vector2<U> &v) {
		return Vector2<T>(static_cast<T>(v.x), static_cast<T>(v.y));
	}

	//deg to rad conversion
	static double deg2rad(double degrees) {
		//to do
		return degrees * PI / 180.0f;
	}

	//rotate a vector by an angle (degrees)
	template<typename T>
	Vector2<T> rotate(const Vector2<T> &v, const double degrees) {
		const double theta = deg2rad(degrees);
		const double cs = cos(theta);
		const double sn = sin(theta);
		return { (T)(v.x * cs - v.y * sn), (T)(v.x * sn + v.y * cs) };
	}

	//cout!
	template<typename T>	
	std::ostream &operator<<(std::ostream &os, const Vector2<T> &v) {
		os << '(' << v.x << ", " << v.y << ')';
		return os;
	}

}