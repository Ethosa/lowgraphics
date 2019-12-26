// author: Ethosa
#include "RGBA.h"
#include <iostream>
#include <locale>
#include <map>

class Color
{
public:
    typedef std::map<std::string, int> _colors_map;
    static _colors_map colors_map;
    static int parse(int r, int g, int b, int a);
    static int parse(int r, int g, int b);
    static int parse(std::string s);
    static int parse(int* rgba);
    static int parse(RGBA rgba);
    static RGBA to_rgba(int color);
};
