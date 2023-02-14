#pragma once
#include <SFML/Graphics.hpp>

class Value
{
	sf::Sprite f;
	sf::Sprite s;
	sf::Text t;
public:
	//int val;

	Value(std::string first, std::string second);
	void draw();
	void updateValue(std::string value);
	void updatePosition(int x, int y);
	int getWidth();
	int getHeight();
	int getX();
	int getY();
};

//class Values
//{
//	Value v1;
//	Value v2;
//	Value v3;
//	Value v4;
//public:
//	int margin;
//
//	Values();
//	void draw();
//	void updateValue(int val);
//	void updatePosition(int x, int y);
//	int getWidth();
//	int getHeight();
//};