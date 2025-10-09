#pragma once
#include <iostream>
#include <SFML/System/Vector2.hpp>

// Component-wise plussing a value
template<typename T>
sf::Vector2<T>& operator+=(sf::Vector2<T>& vector, const T value)
{
	vector.x += value;
	vector.y += value;
	return vector;
}

// Component-wise minusing a value
template<typename T>
sf::Vector2<T>& operator-=(sf::Vector2<T>& vector, const T value)
{
	vector.x -= value;
	vector.y -= value;
	return vector;
}

// Component-wise timesing by a vector
template<typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
	return {
		left.x * right.x,
		left.y * right.y
	};
}

// Component-wise dividing by a vector
template<typename T>
sf::Vector2<T> operator/(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
	return {
		left.x / right.x,
		left.y / right.y
	};
}

// Component-wise timesing assignment
template<typename T>
sf::Vector2<T>& operator*=(sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
	left.x *= right.x;
	left.y *= right.y;
	return left;
}

// Component-wise division assignment
template<typename T>
sf::Vector2<T>& operator/=(sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
	left.x /= right.x;
	left.y /= right.y;
	return left;
}

// ++ing both components of a vector
//? the int is a temp thingy
template<typename T>
sf::Vector2<T>& operator++(sf::Vector2<T>& vector, int)
{
	vector.x++;
	vector.y++;
	return vector;
}

// --ing both components of a vector
//? the int is a temp thingy
template<typename T>
sf::Vector2<T>& operator--(sf::Vector2<T>& vector, int)
{
	vector.x--;
	vector.y--;
	return vector;
}

// Printing a vector
template<typename T>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& vector)
{
	stream << "<" << vector.x << ", " << vector.y << ">";
	return stream;
}