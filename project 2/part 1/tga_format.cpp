#include <iostream>
#include <string>
#include <vector>
#include "tga_format.h"
using namespace std;



pixel::pixel(unsigned char r, unsigned char g, unsigned char b) {
	red = r;
	green = g;
	blue = b;
}

const unsigned char pixel::All(int x) const {
	if (x == 0)
		return red;
	if (x == 1)
		return green;
	if (x == 2)
		return blue;
	return 0;
}

tga::tga(Header x) {
	head = x;
	width = x.width;
	height = x.height;
}

tga::tga() {
	head.idLength = 0;
	width = 0;
	height = 0;
}

void tga::printHeader() {
	cout << head.idLength << " ";
	cout << head.colorMapType << " ";
	cout << head.dataTypeCode << " ";
	cout << head.colorMapOrigin << " ";
	cout << head.colorMapLength << " ";
	cout << head.colorMapDepth << " ";
	cout << head.xOrigin << " ";
	cout << head.yOrigin << " ";
	cout << head.width << " ";
	cout << head.height << " ";
	cout << head.bitsPerPixel << " ";
	cout << head.imageDescriptor << " //// ";
	cout << "     Pixels: " << getPVC() << endl;
}

const tga::Header tga::getHeader() const {
	return head;
}

tga::Header tga::getHeader() {
	return head;
}

void tga::addPixel(pixel& p) {
	pixels.push_back(p);
}

const int tga::getPVC() const {
	return pixels.size();
}

int tga::getPVC() {
	return pixels.size();
}

const pixel tga::getPixel(int x) const {
	return pixels.at(x);
}

pixel tga::getPixel(int x) {
	return pixels.at(x);
}

const short tga::getHeight() const {
	return height;
}

const short tga::getWidth() const {
	return width;
}
