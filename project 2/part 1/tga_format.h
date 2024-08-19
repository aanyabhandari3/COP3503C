#pragma once
#include <vector>
using namespace std;

class pixel {
public:
	pixel(unsigned char r, unsigned char g, unsigned char b);
	const unsigned char All(int x) const;
private:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

class tga {
public:
	struct Header {
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
	};
	
	tga();
	tga(Header x);

	void printHeader();
	const Header getHeader() const;

	Header getHeader();
	const pixel getPixel(int x) const;

	pixel getPixel(int x);
	const int getPVC() const;

	int getPVC();
	const short getHeight() const;
	const short getWidth() const;

	void addPixel(pixel& p);
	
private:
	Header head;
	short width;
	short height;
	vector<pixel> pixels;
};