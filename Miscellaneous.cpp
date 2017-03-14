#include "Miscellaneous.h"

//FLOAT -> STRING
std::string misc::floatToString(float num) {
	std::ostringstream string;
	string << num;
	return string.str();
}

//INT -> STRING
std::string misc::intToString(int num) {
	std::ostringstream string;
	string << num;
	return string.str();
}

//DOUBLE -> STRING
std::string misc::doubleToString(double num) {
	std::ostringstream string;
	string << num;
	return string.str();
}

//IS LETTER
bool misc::isLetter(const char c) {
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return true;
	else
		return false;
}

//EXTRACT BETWEEN
//returns string between two specific chars called tokens
std::string misc::extractBetween(std::string string, char token) {
	int start, end;
	bool found = 0;

	for (int i = 0; i < string.size(); i++) {
		if (string[i] == token) {
			if (found) {
				end = i;
				return string.substr(start + 1, end - start - 1);
			}
			else {
				start = i;
				found = 1;
			}
		}
	}

	if (found)
		return string.substr(start + 1, string.size() - start - 1);

	return "";
}

//EXTRACT BETWEEN REPLACE
//returns string between two specific chars called tokens, tokens are replaced with replace char
std::string misc::extractBetween(std::string& string, char token, char replace) {
	int start, end;
	bool found = 0;

	for (int i = 0; i < string.size(); i++)
		if (string[i] == token) {
			if (found) {
				end = i;
				return string.substr(start + 1, end - start - 1);
			}
			else {
				start = i;
				found = 1;
				string[i] = replace;
			}
		}

	if (found)
		return string.substr(start + 1, string.size() - start - 1);

	return "";
}

//DISTANCE
//Returns the distance between points a and b
float misc::distance(const sf::Vector2f a, const sf::Vector2f b) {
	return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
}

//MIDPOINT
//Returns the midpoint of line a->b
sf::Vector2f misc::midpoint(const sf::Vector2f a, const sf::Vector2f b) {
	return sf::Vector2f(((a.x + b.x) / 2), ((a.y + b.y) / 2));
}

//INTERSECTS
//determine if line a->b intersects line c->d
bool misc::intersects(const sf::Vector2f a, const sf::Vector2f b, const sf::Vector2f c, const sf::Vector2f d) {
	float den = ((d.y - c.y)*(b.x - a.x) - (d.x - c.x)*(b.y - a.y));
	float num1 = ((d.x - c.x)*(a.y - c.y) - (d.y - c.y)*(a.x - c.x));
	float num2 = ((b.x - a.x)*(a.y - c.y) - (b.y - a.y)*(a.x - c.x));
	float u1 = num1 / den;
	float u2 = num2 / den;

	if (u1 < 0 || u1 > 1 || u2 < 0 || u2 > 1)
		return 0;
	return 1;
}

//RANDOM
//generates a random int between min and max
int misc::random(int min, int max) {
	return rand() % max + min;
}

sf::Color misc::randomColor()
{
	return sf::Color(random(0, 255), random(0, 255), random(0, 255), 255);
}

//GET LINE ANGLE
//returns the angle of line
float misc::lineAngle(const sf::Vector2f centerpoint, const sf::Vector2f endpoint) {
	return ((atan2f((-centerpoint.y + endpoint.y), (centerpoint.x - endpoint.x)))) + PI;
}

//POINT LOCATION
//returns a new point location given starting point, angle, and distance
sf::Vector2f misc::pointLocation(const sf::Vector2f point, const float angle, const float distance) {
	return sf::Vector2f(point.x + distance * cos(angle), point.y + -distance * sin(angle));
}

//GET AREA POINTS
//returns a vector of points along a rectangle, resolution = spacing of points
std::vector<sf::Vector2f> misc::getAreaPoints(const sf::RectangleShape shape, const float resolution, const bool sides) {
	std::vector<sf::Vector2f> points;
	sf::Vector2f p;

	//get number of point
	int xPoints = shape.getSize().x / resolution;
	int yPoints = shape.getSize().y / resolution;
	int xpos = shape.getPosition().x;
	int ypos = shape.getPosition().y;
	int wOffset = shape.getSize().x / 2;
	int hOffset = shape.getSize().y / 2;

	//corners
	/*sf::Vector2f p1(xpos - wOffset, ypos - hOffset);
	sf::Vector2f p2(xpos + wOffset, ypos - hOffset);
	sf::Vector2f p3(xpos + wOffset, ypos + hOffset);
	sf::Vector2f p4(xpos - wOffset, ypos + hOffset);*/

	sf::Vector2f p1(shape.getTransform().transformPoint(shape.getPoint(0)));
	sf::Vector2f p2(shape.getTransform().transformPoint(shape.getPoint(1)));
	sf::Vector2f p3(shape.getTransform().transformPoint(shape.getPoint(2)));
	sf::Vector2f p4(shape.getTransform().transformPoint(shape.getPoint(3)));

	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);


	//side 1
	float a1 = lineAngle(p1, p2);
	float a2 = lineAngle(p1, p4);
	float d1 = distance(p1, p2);
	float d2 = distance(p1, p4);
	int n1 = (d1 / resolution) + 1;
	int n2 = (d2 / resolution) + 1;

	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++)
			points.push_back(sf::Vector2f(pointLocation(pointLocation(p1, a2, resolution * j + 1), a1, resolution * i + 1)));

	return points;
}