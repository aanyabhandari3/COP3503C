#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "tga_format.h"
using namespace std;

namespace method_Imp {
	tga read(string path);
	bool write(string path, tga& pic);
	void PrintInfo(tga& pic);
	float Transpose(unsigned char c, unsigned char top, unsigned char bot);
	tga Multiply(const tga& top, const tga& bot);
	tga Screen(const tga& top, const tga& bot, const tga& screen);
	tga Subtract(const tga& top, const tga& bot);
	tga Addition(const tga& top, unsigned char red, unsigned char green, unsigned char blue);
	tga Overlay(const tga& top, const tga& bot);
	tga Scale(const tga& top, bool red, float a, bool green, float b, bool blue, float c);
	vector<tga> Separate(const tga& top);
	tga Layer(const tga& red, const tga& green, const tga& blue);
	tga Rotation(const tga& top);
}