// author: Ethosa
#include "Color.h"


int Color::parse_color(int r, int g, int b, int a)
{
    return (a<<24) | (r<<16) | (g<<8) | b;
}

int Color::parse_color(int r, int g, int b)
{
    return parse_color(r, g, b, 255);
}

int Color::parse_color(std::string s)
{
    return std::stoul(s, nullptr, 16);
}

int Color::parse_color(int* rgba)
{
    if ((sizeof(rgba)/sizeof(*rgba)) == 4)
    {
        return parse_color(rgba[0], rgba[1], rgba[2], rgba[3]);
    } else if ((sizeof(rgba)/sizeof(*rgba)) == 3)
    {
        return parse_color(rgba[0], rgba[1], rgba[2], 255);
    }
}
