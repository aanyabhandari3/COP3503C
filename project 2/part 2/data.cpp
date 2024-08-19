#include <iostream>
#include "data.h"
#include <algorithm>
#include <fstream>
using namespace std;

void Image::read(ifstream& file, Header& header) {
    file.read(&header.id_length, 1);
    file.read(&header.colormap_type, 1);
    file.read(&header.image_type, 1);
    file.read(reinterpret_cast<char*>(&header.colormap_index), 2);
    file.read(reinterpret_cast<char*>(&header.colormap_length), 2);
    file.read(&header.colormap_size, 1);
    file.read(reinterpret_cast<char*>(&header.x_origin), 2);
    file.read(reinterpret_cast<char*>(&header.y_origin), 2);
    file.read(reinterpret_cast<char*>(&header.width), 2);
    file.read(reinterpret_cast<char*>(&header.height), 2);
    file.read(&header.P_depth, 1);
    file.read(&header.image_descriptor, 1);
}

void Image::readP(ifstream& file, vector<Pixel>& p, int width, int height) {
    for(int i = 0; i < width * height; i++){
        Pixel pixel;
        p.push_back(pixel);
        file.read(reinterpret_cast<char*>(&p[i].blue), 1);
        file.read(reinterpret_cast<char*>(&p[i].green), 1);
        file.read(reinterpret_cast<char*>(&p[i].red), 1);
    }
}

void Image::write(ofstream& file, const vector<Pixel>& p, const Header& header){
    file.write(reinterpret_cast<const char*>(&header.id_length), 1);
    file.write(reinterpret_cast<const char*>(&header.colormap_type), 1);
    file.write(reinterpret_cast<const char*>(&header.image_type), 1);
    file.write(reinterpret_cast<const char*>(&header.colormap_index), 2);
    file.write(reinterpret_cast<const char*>(&header.colormap_length), 2);
    file.write(reinterpret_cast<const char*>(&header.colormap_size), 1);
    file.write(reinterpret_cast<const char*>(&header.x_origin), 2);
    file.write(reinterpret_cast<const char*>(&header.y_origin), 2);
    file.write(reinterpret_cast<const char*>(&header.width), 2);
    file.write(reinterpret_cast<const char*>(&header.height), 2);
    file.write(reinterpret_cast<const char*>(&header.P_depth), 1);
    file.write(reinterpret_cast<const char*>(&header.image_descriptor), 1);
    for(auto lh : p){
        file.write(reinterpret_cast<const char*>(&lh.blue), 1);
        file.write(reinterpret_cast<const char*>(&lh.green), 1);
        file.write(reinterpret_cast<const char*>(&lh.red), 1);
    }
}

Pixel Image::screen(const Pixel& x1, const Pixel& x2) {
    Pixel h;
    h.red = static_cast<unsigned char>((1 - ((1 - static_cast<float>(x1.red)/255) * (1 - static_cast<float>(x2.red)/255)))*255 + 0.5f);
    h.green = static_cast<unsigned char>((1 - ((1 - static_cast<float>(x1.green)/255) * (1 - static_cast<float>(x2.green)/255)))*255 + 0.5f);
    h.blue = static_cast<unsigned char>((1 - ((1 - static_cast<float>(x1.blue)/255) * (1 - static_cast<float>(x2.blue)/255)))*255 + 0.5f);
    return h;
}

Pixel Image::addition(const Pixel& x1, const Pixel& x2) {
    Pixel h;
    h.red = min(static_cast<int>(x1.red) + x2.red, 255);
    h.green = min(static_cast<int>(x1.green) + x2.green, 255);
    h.blue = min(static_cast<int>(x1.blue) + x2.blue, 255);
    return h;
}

Pixel Image::subtract(const Pixel& x1, const Pixel& x2) {
    Pixel h;
    if (x1.red >= x2.red)
        h.red = x1.red - x2.red;
    else
        h.red = 0;
    if (x1.green >= x2.green)
        h.green = x1.green - x2.green;
    else
        h.green = 0;
    if (x1.blue >= x2.blue)
        h.blue = x1.blue - x2.blue;
    else
        h.blue = 0;
    return h;
}

Pixel Image::overlay(const Pixel& x1, const Pixel& x2) {
    float nx1 = static_cast<float>(x1.red) / 255.0f;
    float nx2 = static_cast<float>(x2.red) / 255.0f;
    float orr, ogg, obb;
    if (nx2 <= 0.5f)
        orr = 2 * nx1 * nx2;
    else
        orr = 1 - 2 * (1 - nx1) * (1 - nx2);
        nx1 = static_cast<float>(x1.green) / 255.0f;
        nx2 = static_cast<float>(x2.green) / 255.0f;
        if (nx2 <= 0.5f)
            ogg = 2 * nx1 * nx2;
    else
        ogg = 1 - 2 * (1 - nx1) * (1 - nx2);
        nx1 = static_cast<float>(x1.blue) / 255.0f;
        nx2 = static_cast<float>(x2.blue) / 255.0f;
        if (nx2 <= 0.5f)
            obb = 2 * nx1 * nx2;
    else
        obb = 1 - 2 * (1 - nx1) * (1 - nx2);
        Pixel h;
        h.green = static_cast<unsigned char>(ogg * 255 + 0.5f);
        h.blue = static_cast<unsigned char>(obb * 255 + 0.5f);
        h.red = static_cast<unsigned char>(orr * 255 + 0.5f);
    return h;
}

Pixel Image::multiply(const Pixel& x1, const Pixel& x2) {
    Pixel h;
    h.red = static_cast<unsigned char>((static_cast<float>(x1.red) * static_cast<float>(x2.red)) / 255 + 0.5f);
    h.green = static_cast<unsigned char>((static_cast<float>(x1.green) * static_cast<float>(x2.green)) / 255 + 0.5f);
    h.blue = static_cast<unsigned char>((static_cast<float>(x1.blue) * static_cast<float>(x2.blue)) / 255 + 0.5f);
    return h;
}
