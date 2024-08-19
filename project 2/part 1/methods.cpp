#include "methods.h"
using namespace method_Imp;

const unsigned char global_max = 255;
const unsigned char global_min = 0;

tga method_Imp::read(string path) {
	ifstream file(path, ios_base::binary);
	if (file.is_open()) {

		tga::Header t;
		file.read(&t.idLength, sizeof(t.idLength));
		file.read(&t.colorMapType, sizeof(t.colorMapType));
		file.read(&t.dataTypeCode, sizeof(t.dataTypeCode));
		file.read((char*)&t.colorMapOrigin, sizeof(t.colorMapOrigin));
		file.read((char*)&t.colorMapLength, sizeof(t.colorMapLength));
		file.read((char*)&t.colorMapDepth, sizeof(t.colorMapDepth));
		file.read((char*)&t.xOrigin, sizeof(t.xOrigin));
		file.read((char*)&t.yOrigin, sizeof(t.yOrigin));
		file.read((char*)&t.width, sizeof(t.width));
		file.read((char*)&t.height, sizeof(t.height));
		file.read(&t.bitsPerPixel, sizeof(t.bitsPerPixel));
		file.read(&t.imageDescriptor, sizeof(t.imageDescriptor));

		tga temp_pic = tga(t);

		for (int i = 0; i < (t.height * t.width); ++i) {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			file.read((char*)&b, sizeof(b));
			file.read((char*)&g, sizeof(g));
			file.read((char*)&r, sizeof(r));
			pixel p = pixel(r, g, b);
			temp_pic.addPixel(p);
		}

		file.close();
		return temp_pic;
	}

	cout << "404 Error. Could not load: '" << path << "'." << endl; /////////////////////
	return tga();
}

bool method_Imp::write(string path, tga& temp_pic) {
	ofstream file(path, ios_base::binary);
	if (file.is_open()) {

		tga::Header t = temp_pic.getHeader();
		file.write(&t.idLength, sizeof(t.idLength));
		file.write(&t.colorMapType, sizeof(t.colorMapType));
		file.write(&t.dataTypeCode, sizeof(t.dataTypeCode));
		file.write((char*)&t.colorMapOrigin, sizeof(t.colorMapOrigin));
		file.write((char*)&t.colorMapLength, sizeof(t.colorMapLength));
		file.write((char*)&t.colorMapDepth, sizeof(t.colorMapDepth));
		file.write((char*)&t.xOrigin, sizeof(t.xOrigin));
		file.write((char*)&t.yOrigin, sizeof(t.yOrigin));
		file.write((char*)&t.width, sizeof(t.width));
		file.write((char*)&t.height, sizeof(t.height));
		file.write(&t.bitsPerPixel, sizeof(t.bitsPerPixel));
		file.write(&t.imageDescriptor, sizeof(t.imageDescriptor));

		for (int i = 0; i < temp_pic.getPVC(); ++i) {
			unsigned char All[3];
			pixel p = temp_pic.getPixel(i);
			for (int j = 0; j < 3; ++j)
				All[j] = p.All(j);

			file.write((char*)&All[2], sizeof(All[2]));
			file.write((char*)&All[1], sizeof(All[1]));
			file.write((char*)&All[0], sizeof(All[0]));
		}
		file.close();
		return true;
	}
	return false;
}


void method_Imp::PrintInfo(tga& temp_pic) {
	temp_pic.printHeader();
}

float method_Imp::Transpose(unsigned char c, unsigned char top, unsigned char bot) {
	float pro = ((float)c / (float)(top - bot));
	return pro;
}

tga method_Imp::Multiply(const tga& top, const tga& bot) {
	tga temp_pic = tga(top.getHeader());

	for (int i = 0; i < top.getPVC(); ++i) {
		pixel pTop = top.getPixel(i);
		pixel pBot = bot.getPixel(i);
		float All[6];
		unsigned char proAll[3];

		for (int j = 0; j < 6; ++j) {
			if (j < 3)
				All[j] = Transpose(pTop.All(j), global_max, global_min);
			else
				All[j] = Transpose(pBot.All(j - 3), global_max, global_min);
		}

		for (int j = 0; j < 3; ++j) {
			if (All[j] * All[j + 3] > 1)
				proAll[j] = global_max;
			else
				proAll[j] = (unsigned char)((All[j] * All[j + 3]) * 255 + 0.5f);
		}

		pixel p = pixel(proAll[0], proAll[1], proAll[2]);
		temp_pic.addPixel(p);
	}

	return temp_pic;
}

tga method_Imp::Screen(const tga& top, const tga& bot, const tga& screen) {
	tga pro = Multiply(top, bot);
	tga temp_pic = tga(pro.getHeader());

	for (int i = 0; i < screen.getPVC(); ++i) {
		pixel pTop = screen.getPixel(i);
		pixel pBot = pro.getPixel(i);
		float All[6];
		unsigned char proAll[3];

		for (int j = 0; j < 6; ++j) {
			if (j < 3)
				All[j] = Transpose(pTop.All(j), global_max, global_min);
			else
				All[j] = Transpose(pBot.All(j - 3), global_max, global_min);
		}

		for (int j = 0; j < 3; ++j) {
			float a = 1 - (1 - All[j]) * (1 - All[j + 3]);
			if (a > 1)
				a = 1;
			else if (a < 0)
				a = 0;
			proAll[j] = (unsigned char)(a * 255 + 0.5f);
		}

		pixel p = pixel(proAll[0], proAll[1], proAll[2]);
		temp_pic.addPixel(p);
	}

	return temp_pic;
}


tga method_Imp::Subtract(const tga& top, const tga& bot) {
	tga temp_pic = tga(top.getHeader());

	for (int i = 0; i < top.getPVC(); ++i) {
		pixel pTop = top.getPixel(i);
		pixel pBot = bot.getPixel(i);
		unsigned char All[6];
		unsigned char proAll[3];

		for (int j = 0; j < 6; ++j) {
			if (j < 3)
				All[j] = pTop.All(j);
			else
				All[j] = pBot.All(j - 3);
		}

		for (int j = 0; j < 3; ++j) {
			if (All[j+3] - All[j] < 0)
				proAll[j] = global_min;
			else
				proAll[j] = (All[j+3] - All[j]);
		}

		pixel p = pixel(proAll[0], proAll[1], proAll[2]);
		temp_pic.addPixel(p);
	}

	return temp_pic;
}

tga method_Imp::Addition(const tga& top, unsigned char red, unsigned char green, unsigned char blue) {
	tga temp_pic = tga(top.getHeader());

	for (int i = 0; i < top.getPVC(); ++i) {
		pixel pTop = top.getPixel(i);
		float All[3];
		unsigned char proAll[3];

		for (int j = 0; j < 3; ++j)
			All[j] = Transpose(pTop.All(j), global_max, global_min);
		
			float a = All[0] + Transpose(red, global_max, global_min);
			if (a > 1)
				a = 1;
			proAll[0] = (unsigned char)(a * 255 + 0.5f);
			a = All[1] + Transpose(green, global_max, global_min);
			if (a > 1)
				a = 1;
			proAll[1] = (unsigned char)(a * 255 + 0.5f);
			a = All[2] + Transpose(blue, global_max, global_min);
			if (a > 1)
				a = 1;
			proAll[2] = (unsigned char)(a * 255 + 0.5f);

		pixel p = pixel(proAll[0], proAll[1], proAll[2]);
		temp_pic.addPixel(p);
	}

	return temp_pic;
}

tga method_Imp::Overlay(const tga& top, const tga& bot) {
	tga temp_pic = tga(top.getHeader());

	for (int i = 0; i < top.getPVC(); ++i) {
		pixel pTop = top.getPixel(i);
		pixel pBot = bot.getPixel(i);
		float All[6];
		unsigned char proAll[3];

		for (int j = 0; j < 6; ++j) {
			if (j < 3)
				All[j] = Transpose(pTop.All(j), global_max, global_min);
			else
				All[j] = Transpose(pBot.All(j - 3), global_max, global_min);
		}

		for (int j = 0; j < 3; ++j) {
			if (All[j + 3] <= 0.5) {
				float a = 2 * All[j] * All[j + 3];
				if (a > 1)
					a = 1;
				proAll[j] = (unsigned char)(a * 255 + 0.5f);
			}
			else {
				float a = 1 - 2 * (1 - All[j]) * (1 - All[j + 3]);
				if (a > 1)
					a = 1;
				else if (a < 0)
					a = 0;
				proAll[j] = (unsigned char)(a * 255 + 0.5f);
			}
		}

		pixel p = pixel(proAll[0], proAll[1], proAll[2]);
		temp_pic.addPixel(p);
	}

	return temp_pic;
}

tga method_Imp::Scale(const tga& top, bool red, float a, bool green, float b, bool blue, float c) {
	tga pro = tga(top.getHeader());

	for (int i = 0; i < top.getPVC(); ++i) {
		pixel pTop = top.getPixel(i);
		unsigned char All[3];
		unsigned char proAll[3];

		for (int j = 0; j < 3; ++j)
			All[j] = pTop.All(j);

		if (red == 1) {
			if (All[0] * a > global_max)
				proAll[0] = global_max;
			else
				proAll[0] = (unsigned char)(All[0] * a);
		}
		else
			proAll[0] = All[0];
		if (green == 1) {
			if (All[1] * b > global_max)
				proAll[1] = global_max;
			else
				proAll[1] = (unsigned char)(All[1] * b);
		}
		else
			proAll[1] = All[1];
		if (blue == 1) {
			if (All[2] * c > global_max)
				proAll[2] = global_max;
			else
				proAll[2] = (unsigned char)(All[2] * c);
		}
		else
			proAll[2] = All[2];

		pixel p = pixel(proAll[0], proAll[1], proAll[2]);
		pro.addPixel(p);
	}

	return pro;
}

vector<tga> method_Imp::Separate(const tga& top) {
	vector<tga> prov;
	prov.push_back(tga(top.getHeader())); 
	prov.push_back(tga(top.getHeader())); 
	prov.push_back(tga(top.getHeader())); 
	
	for (int i = 0; i < top.getPVC(); ++i) {
		pixel pTop = top.getPixel(i);
		unsigned char red = pTop.All(0);
		unsigned char green = pTop.All(1);
		unsigned char blue = pTop.All(2);
		pixel redP = pixel(red, red, red);
		pixel greenP = pixel(green, green, green);
		pixel blueP = pixel(blue, blue, blue);

		// PUSH LAYERS
		prov.at(0).addPixel(redP);
		prov.at(1).addPixel(greenP);
		prov.at(2).addPixel(blueP);
	}

	return prov;
}

tga method_Imp::Layer(const tga& red, const tga& green, const tga& blue) {
	tga pro = tga(red.getHeader());

	for (int i = 0; i < red.getPVC(); ++i) {
		unsigned char All[3];
		All[0] = red.getPixel(i).All(0);
		All[1] = green.getPixel(i).All(0);
		All[2] = blue.getPixel(i).All(0);
		pixel p = pixel(All[0], All[1], All[2]);
		pro.addPixel(p);
	}

	return pro;
}

tga method_Imp::Rotation(const tga& top) {
	tga pro = tga(top.getHeader());
	int i = (top.getHeight() * top.getWidth()) - 1;
	for (i; i > -1; --i) {
		pixel p = top.getPixel(i);
		pro.addPixel(p);
	}

	return pro;
}
