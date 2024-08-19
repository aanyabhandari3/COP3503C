#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>


struct Header {
    char id_length;
    char colormap_type;
    char image_type;
    short colormap_index;
    short colormap_length;
    char colormap_size;
    short x_origin;
    short y_origin;
    short width;
    short height;
    char P_depth;
    char image_descriptor;
};

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

class Image {
public:
    void read(std::ifstream& file, Header& header);
    void readP(std::ifstream& file, std::vector<Pixel>& pixels, int width, int height);
    void write(std::ofstream& file, const std::vector<Pixel>& pixels, const Header& header);

    Pixel multiply(const Pixel& x1, const Pixel& x2);
    Pixel screen(const Pixel& x1, const Pixel& x2);
    Pixel subtract(const Pixel& x1, const Pixel& x2);
    Pixel addition(const Pixel& x1, const Pixel& x2);
    Pixel overlay(const Pixel& x1, const Pixel& x2);
};

#endif