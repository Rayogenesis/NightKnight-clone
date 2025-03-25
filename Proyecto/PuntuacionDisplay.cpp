#include "PuntuacionDisplay.h"
#include <iostream>

void PuntuacionDisplay::init(int size)
{
	this->numbers.resize(size);

	for (int i = 0; i < size; ++i) {
		numbers[i] = NumberGenerator::instance().createNum();
	}
}

void PuntuacionDisplay::displayNum(int num) {
	int n = numbers.size();
	int div = 1;
	for (int i = 0; i < n; ++i) {
		int digit = (num / div) % 10;
		numbers[n-i-1]->changeAnimation(digit);
		div *= 10;
	}
}

void PuntuacionDisplay::render()
{
	int n = numbers.size();
	for (int i = 0; i < n; ++i) numbers[i]->render();
}

void PuntuacionDisplay::setPosition(glm::vec2 pos)
{
	int n = numbers.size();
	int x_offset = 0;
	for (int i = 0; i < n; ++i) {
		numbers[i]->setPosition(pos + glm::vec2(x_offset, 0));
		x_offset += 21;
	}
}
