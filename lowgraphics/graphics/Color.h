// author: Ethosa
#include <iostream>

class Color
{
public:
    static int parse_color(int r, int g, int b, int a);
    static int parse_color(int r, int g, int b);
    static int parse_color(std::string s);
    static int parse_color(int* rgba);
};
