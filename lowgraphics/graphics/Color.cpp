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
    if (s == "white") s = "0xFFFFFFFF";
    else if (s == "black") s = "0xFF000000";
    else if (s == "red") s = "0xFFFF0000";
    else if (s == "green") s = "0xFF00FF00";
    else if (s == "blue") s = "0xFF0000FF";
    else if (s == "yellow") s = "0xFFFFFF00";
    else if (s == "cyan") s = "0xFF00FFFF";
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
