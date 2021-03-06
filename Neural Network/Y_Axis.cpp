#include "Y_Axis.h"

Y_Axis::Y_Axis()
{
	this->axis->setSize(sf::Vector2f(this->width, this->height));
	this->axis->setFillColor(sf::Color(166, 1, 180));
	this->axis->setPosition(sf::Vector2f(20.0f, 20.0f));
	this->maxY = 0;
}

void Y_Axis::setPosition(sf::Vector2f pos) {
	this->axis->setPosition(pos);

	for (size_t i = 0; i < this->axisNumbers.size(); i++)
	{
		this->axisNumbers.at(i)->setPosition(
			sf::Vector2f(this->axis->getPosition().x - 50,
				this->axis->getPosition().y + this->height - (this->height * i) / this->axisNumbers.size() * 1.0 - 1.3 * this->axisNumbers.at(i)->getHeight())
		);
	}
}

void Y_Axis::setRange(double value) {
	this->maxY = (value > this->maxY) ? value : this->maxY;

	for (size_t i = 0; i < this->axisNumbers.size(); i++)
	{
		this->axisNumbers.at(i)->setData((double)value * i / 5.0);
	}
}
