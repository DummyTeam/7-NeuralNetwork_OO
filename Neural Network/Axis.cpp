#include"Axis.h"

Axis::Axis()
{

}

void Axis::draw(sf::RenderWindow* window)
{
	window->draw(*(this->axis));
}

float Axis::getWidth()
{
	return this->width;
}

float Axis::getHeight()
{
	return this->height;
}

const sf::Vector2f &Axis::getPosition() const
{
	return axis->getPosition();
}