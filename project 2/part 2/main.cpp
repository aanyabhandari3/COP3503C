// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include "methods.h"
// #include "data.h"
// using namespace std;
// using namespace method_Imp;

///////////////////////////// Milestone 1 printing main //////////////////////////////////
// int main()
// {
//     //part1
// 	tga top1 = read("input/layer1.tga");
// 	tga bot1 = read("input/pattern1.tga");
// 	tga Img1 = Multiply(top1, bot1);
// 	write("output/part1.tga", Img1);
	
//     //part 2
// 	tga top2 = read("input/layer2.tga");
// 	tga bot2 = read("input/car.tga");
// 	tga Img2 = Subtract(top2, bot2);
// 	write("output/part2.tga", Img2);
			
// 	// part 3
// 	tga top3 = read("input/layer1.tga");
// 	tga bot3 = read("input/pattern2.tga");
// 	tga screen = read("input/text.tga");
// 	tga Img3 = Screen(top3, bot3, screen);
// 	write("output/part3.tga", Img3);
			
// 	// part 4
// 	tga top4 = read("input/layer2.tga");
// 	tga bot4 = read("input/circles.tga");
// 	tga sub = read("input/pattern2.tga");
// 	tga Pro4 = Multiply(top4, bot4);
// 	tga Img4 = Subtract(sub, Pro4);
// 	write("output/part4.tga", Img4);
			
// 	// part 5
// 	tga top5 = read("input/layer1.tga");
// 	tga bot5 = read("input/pattern1.tga");
// 	tga Img5 = Overlay(top5, bot5);
// 	write("output/part5.tga", Img5);
			
// 	// part 6: add only green 200
// 	tga top6 = read("input/car.tga");
// 	tga Img6 = Addition(top6, 0, 200, 0);
// 	write("output/part6.tga", Img6);

// 	// part 7
// 	tga top7 = read("input/car.tga");
// 	tga Img7 = Scale(top7, true, 4.0, false, 0.0, true, 0.0);
// 	write("output/part7.tga", Img7);
			
// 	// part 8: red, green, blue
// 	tga top8 = read("input/car.tga");
// 	vector<tga> Img8 = Separate(top8);
// 	write("output/part8_r.tga", Img8.at(0));	
// 	write("output/part8_g.tga", Img8.at(1));			
// 	write("output/part8_b.tga", Img8.at(2));
			
// 	// part 9
// 	tga top9red = read("input/layer_red.tga");
// 	tga top9green = read("input/layer_green.tga");
// 	tga top9blue = read("input/layer_blue.tga");
// 	tga Img9 = Layer(top9red, top9green, top9blue);
// 	write("output/part9.tga", Img9);

// 	// part 10
// 	tga top10 = read("input/text2.tga");
// 	tga Img10 = Rotation(top10);
// 	write("output/part10.tga", Img10);
// 	cout << "Compiler finished Tasks 1-10." << endl;

// 	return 0;
// }


///////////////////////////// Milestone 2 printing main /////////////////////////////////
#include <vector>
#include <stdexcept>
#include "data.h"
#include <iostream>
#include <fstream>
using namespace std;

int invalid1(string argc, string& f){
    string n = string(argc);
    f = n;
    if (n.length() < 4 || n.find(".tga") != n.length() - 4) {
        cout << "Invalid argument, invalid file name." << endl;
        return 0;
    }
    
    ifstream o(n, ios::binary);
    if(!o){
        string check = "input/" + n;
        ifstream o2(check, ios::binary);
        if(!o2){
            cout << "Invalid argument, file does not exist." << endl;
            return 0;
        }
        else{
            f = check;
            return 1;
        }
    }
    return 1;
}

int invalid2(string argc, string& f){
    string n = string(argc);
    f = n;
    if(!(n.length() >= 4 && n.substr(n.length() - 4) == ".tga")){
        cout << "Invalid file name." << endl;
        return 0;
    }
    ifstream o(n, ios::binary);
    if(!o){
        string check = "input/" + n;
        ifstream o2(check, ios::binary);
        if(!o2){
            cout << "File does not exist." << endl;
            return 0;
        }
        else{
            f = check;
            return 1;
        }
    }
    return 1;
}


int main(int argc, const char** argv){
    if(argc == 1){
        cout << "Project 2: Image Processing, Summer 2024\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    }
    if(argc == 2 && string(argv[1]) == "--help"){
        cout << "Project 2: Image Processing, Summer 2024\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    }
    string n2 = string(string(argv[1]));
    try{
        if(!(n2.length() >= 4 && n2.substr(n2.length() - 4) == ".tga")){
            throw invalid_argument("Invalid file name.");
        }
    }
    catch(invalid_argument& l){
        cout << l.what() << endl;
        return 0;
    }
    
    Image finding;
    Header pulls1;
    string test;
    if (invalid2(string(argv[2]), test) == 0) {
        return 0;
    }
    ifstream input_f(test, ios::binary);
    finding.read(input_f, pulls1);

    vector<Pixel> finding1;
    finding.readP(input_f, finding1, pulls1.width, pulls1.height);
    int ind = 3;
    while(ind < argc){
        try{
            if(string(argv[ind]) == "subtract"){
                if(ind == argc - 1){
                    throw invalid_argument("Missing argument.");
                }
                ind++;

                Header pulls2;
                if (invalid1(string(argv[ind]), test) == 1) {
                    ifstream input_f2(test, ios::binary);
                    finding.read(input_f2, pulls2);
                    vector<Pixel> input_px2;
                    finding.readP(input_f2, input_px2, pulls2.width, pulls2.height);
                    for(int i = 0; i < input_px2.size(); i++){
                        finding1[i] = finding.subtract(finding1[i], input_px2[i]);
                    }
                } else {
                    return 0;
                }
                ind++;
            } else if(string(argv[ind]) == "multiply"){
                if(ind == argc - 1) {
                    throw invalid_argument("Missing argument.");
                }
                ind++;

                Header pulls2;
                if (invalid1(string(argv[ind]), test) == 1) {
                    ifstream input_f2(test, ios::binary);
                    finding.read(input_f2, pulls2);
                    vector<Pixel> input_px2;
                    finding.readP(input_f2, input_px2, pulls2.width, pulls2.height);
                    for(int i = 0; i < input_px2.size(); i++){
                        finding1[i] = finding.multiply(finding1[i], input_px2[i]);
                    }
                } else {
                    return 0;
                }
                ind++;
            } else if(string(argv[ind]) == "overlay"){
                if(ind == argc - 1){
                    throw invalid_argument("Missing argument.");
                }
                ind++;
                Header pulls2;
                if (invalid1(string(argv[ind]), test) == 1) {
                    ifstream input_f2(test, ios::binary);
                    finding.read(input_f2, pulls2);
                    vector<Pixel> input_px2;
                    finding.readP(input_f2, input_px2, pulls2.width, pulls2.height);
                    for(int i = 0; i < input_px2.size(); i++){
                        finding1[i] = finding.overlay(finding1[i], input_px2[i]);
                    }
                } else {
                    return 0;
                }
                ind++;

            } else if(string(argv[ind]) == "screen"){
                if(ind == argc - 1){
                    throw invalid_argument("Missing argument.");
                }
                ind++;
                Header pulls2;
                if (invalid1(string(argv[ind]), test) == 1) {
                    ifstream input_f2(test, ios::binary);
                    finding.read(input_f2, pulls2);
                    vector<Pixel> input_px2;
                    finding.readP(input_f2, input_px2, pulls2.width, pulls2.height);
                    for(int i = 0; i < input_px2.size(); i++){
                        finding1[i] = finding.screen(input_px2[i], finding1[i]);
                    }
                } else {
                    return 0;
                }
                ind++;
            } else if(string(argv[ind]) == "combine") {
                if (ind == argc - 1) {
                    throw invalid_argument("Missing argument.");
                }
                if (ind == argc - 2) {
                    throw invalid_argument("Missing argument.");
                }
                ind++;
                if (invalid1(string(argv[ind]), test) == 1) {
                    Header pulls2;
                    ifstream input_f2(test, ios::binary);
                    finding.read(input_f2, pulls2);

                    vector<Pixel> green;
                    finding.readP(input_f2, green, pulls2.width, pulls2.height);
                    ind++;
                    if (invalid1(string(argv[ind]), test) == 1) {
                        Header pulls3;
                        ifstream input_f3(test, ios::binary);
                        finding.read(input_f3, pulls3);
                        vector<Pixel> blue;
                        finding.readP(input_f3, blue, pulls3.width, pulls3.height);
                        for (int i = 0; i < blue.size(); i++) {
                            Pixel pixel;
                            pixel.red = finding1[i].red;
                            pixel.green = green[i].green;
                            pixel.blue = blue[i].blue;
                            finding1[i] = pixel;
                        }
                    } else {
                        return 0;
                    }
                    ind++;
                } else {
                    return 0;
                }
            } else if(string(argv[ind]) == "flip"){
                vector<Pixel> copy = finding1;
                int count = 0;
                for(int i = finding1.size() - 1; i >= 0; i--) {
                    finding1[count] = copy[i];
                    count++;
                }
                ind++;
            } else if(string(argv[ind]) == "onlyred"){
                vector<unsigned char> redC, greenC, blueC;
                for(int i = 0; i < finding1.size(); i++){
                    redC.push_back(finding1[i].red);
                }
                for(int i = 0; i < redC.size(); i++){
                    Pixel u;
                    u.red = redC[i];
                    u.green = redC[i];
                    u.blue = redC[i];
                    finding1[i] = u;
                }
                ind++;
            } else if(string(argv[ind]) == "onlygreen"){
                vector<unsigned char> redC, greenC, blueC;
                for(int i = 0; i < finding1.size(); i++){
                    greenC.push_back(finding1[i].green);
                }
                for(int i = 0; i < greenC.size(); i++){
                    Pixel u;
                    u.red = greenC[i];
                    u.green = greenC[i];
                    u.blue = greenC[i];
                    finding1[i] = u;
                }
                ind++;
            } else if(string(argv[ind]) == "onlyblue"){
                vector<unsigned char> redC, greenC, blueC;
                for(int i = 0; i < finding1.size(); i++){
                    blueC.push_back(finding1[i].green);
                }
                for(int i = 0; i < blueC.size(); i++){
                    Pixel u;
                    u.red = blueC[i];
                    u.green = blueC[i];
                    u.blue = blueC[i];
                    finding1[i] = u;
                }
                ind++;
            } else if(string(argv[ind]) == "addred"){
                if(ind == argc - 1){
                    throw invalid_argument("Missing argument.");
                }
                ind++;
                try {
                    stoi(argv[ind]);
                } catch (...) {
                    cout << "Invalid argument, expected number.";
                    return 0;
                }

                for(int i = 0; i < finding1.size(); i++){
                    int shade = int(finding1[i].red) + stoi(argv[ind]);
                    if (shade < 0) {
                        shade = 0;
                    } else if (shade > 255) {
                        shade = 255;
                    }
                    finding1[i].red = shade;
                }
                ind++;
            } else if(string(argv[ind]) == "addgreen"){
                if(ind == argc - 1){
                    throw invalid_argument("Missing argument.");
                }
                ind++;
                try {
                    stoi(argv[ind]);
                } catch (...) {
                    cout << "Invalid argument, expected number.";
                    return 0;
                }

                for(int i = 0; i < finding1.size(); i++){
                    int new_green = int(finding1[i].green) + stoi(argv[ind]);
                    if (new_green < 0) {
                        new_green = 0;
                    } else if (new_green > 255) {
                        new_green = 255;
                    }
                    finding1[i].green = new_green;
                }
                ind++;
            } else if(string(argv[ind]) == "addblue"){
                if(ind == argc - 1){
                    throw invalid_argument("Missing argument.");
                }
                ind++;
                try {
                    stoi(argv[ind]);
                } catch (...) {
                    cout << "Invalid argument, expected number.";
                    return 0;
                }

                for(int i = 0; i < finding1.size(); i++){
                    int shade = int(finding1[i].blue) + stoi(argv[ind]);
                    if (shade < 0) {
                        shade = 0;
                    } else if (shade > 255) {
                        shade = 255;
                    }
                    finding1[i].blue = shade;
                }
                ind++;
            } else if(string(argv[ind]) == "scalered"){
                if(ind == argc - 1){
                    throw invalid_argument("Missing argument.");
                }
                ind++;
                try {
                    stoi(argv[ind]);
                } catch (...) {
                    cout << "Invalid argument, expected number.";
                    return 0;
                }
                for(int i = 0; i < finding1.size(); i++){
                    finding1[i].red = min(finding1[i].red * stoi(argv[ind]), 255);
                }
                ind++;
            } else if(string(argv[ind]) == "scalegreen"){
                if(ind == argc - 1){
                    throw invalid_argument("Missing argument.");
                }
                ind++;
                try {
                    stoi(argv[ind]);
                } catch (...) {
                    cout << "Invalid argument, expected number.";
                    return 0;
                }
                for(int i = 0; i < finding1.size(); i++){
                    finding1[i].green = min(finding1[i].green * stoi(argv[ind]), 255);
                }
                ind++;
            } else if(string(argv[ind]) == "scaleblue"){
                if(ind == argc - 1){
                    throw invalid_argument("Missing argument.");
                }
                ind++;
                try {
                    stoi(argv[ind]);
                } catch (...) {
                    cout << "Invalid argument, expected number.";
                    return 0;
                }
                for(int i = 0; i < finding1.size(); i++){
                    finding1[i].blue = min(finding1[i].blue * stoi(argv[ind]), 255);
                }
                ind++;

            }else{
                cout << "Invalid method name." << endl;
                return 0;
            }
        } catch(invalid_argument& e){
            cout << e.what() << endl;
            return 0;
        }
    }
    ofstream goodbye(n2, ios::binary);
    finding.write(goodbye, finding1, pulls1);
    return 0;
}
