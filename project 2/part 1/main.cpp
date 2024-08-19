#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "methods.h"
using namespace std;
using namespace method_Imp;

int main()
{
    //part1
	tga top1 = read("input/layer1.tga");
	tga bot1 = read("input/pattern1.tga");
	tga Img1 = Multiply(top1, bot1);
	write("output/part1.tga", Img1);
	
    //part 2
	tga top2 = read("input/layer2.tga");
	tga bot2 = read("input/car.tga");
	tga Img2 = Subtract(top2, bot2);
	write("output/part2.tga", Img2);
			
	// part 3
	tga top3 = read("input/layer1.tga");
	tga bot3 = read("input/pattern2.tga");
	tga screen = read("input/text.tga");
	tga Img3 = Screen(top3, bot3, screen);
	write("output/part3.tga", Img3);
			
	// part 4
	tga top4 = read("input/layer2.tga");
	tga bot4 = read("input/circles.tga");
	tga sub = read("input/pattern2.tga");
	tga Pro4 = Multiply(top4, bot4);
	tga Img4 = Subtract(sub, Pro4);
	write("output/part4.tga", Img4);
			
	// part 5
	tga top5 = read("input/layer1.tga");
	tga bot5 = read("input/pattern1.tga");
	tga Img5 = Overlay(top5, bot5);
	write("output/part5.tga", Img5);
			
	// part 6: add only green 200
	tga top6 = read("input/car.tga");
	tga Img6 = Addition(top6, 0, 200, 0);
	write("output/part6.tga", Img6);

	// part 7
	tga top7 = read("input/car.tga");
	tga Img7 = Scale(top7, true, 4.0, false, 0.0, true, 0.0);
	write("output/part7.tga", Img7);
			
	// part 8: red, green, blue
	tga top8 = read("input/car.tga");
	vector<tga> Img8 = Separate(top8);

	write("output/part8_r.tga", Img8.at(0));	
	write("output/part8_g.tga", Img8.at(1));			
	write("output/part8_b.tga", Img8.at(2));
			
	// part 9
	tga top9red = read("input/layer_red.tga");
	tga top9green = read("input/layer_green.tga");
	tga top9blue = read("input/layer_blue.tga");
	tga Img9 = Layer(top9red, top9green, top9blue);
	write("output/part9.tga", Img9);

	// part 10
	tga top10 = read("input/text2.tga");
	tga Img10 = Rotation(top10);
	write("output/part10.tga", Img10);
	
	cout << "Compiler finished Tasks 1-10." << endl;

	return 0;
}