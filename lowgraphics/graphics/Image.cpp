// author: Ethosa
#include "Image.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <array>



Image::Image(int width, int height, int color)
/**
 * creates an image object for further work with it
 *
 * params:
 *     width {int} -- image width
 *     height {int} -- image height
 *     color {int} -- fill color
 */
{
    w = width;
    h = height;
    // fill image
    for (int x = 0; x < width; ++x)
    {
        std::vector<int> timed;
        self.push_back(timed);
        for (int y = 0; y < height; ++y)
        {
            self[x].push_back(color);
        }
    }
}


Image::Image(int width, int height)
/**
 * creates an image object for further work with it
 *
 * params:
 *     width {int} -- image width
 *     height {int} -- image height
 */
{
    Image(width, height, 0xFFFFFFFF);
}


Image::Image()
{
    Image(256, 256, 0xFFFFFFFF);
}


int calc_pt(int a , int b , float perc)
{
    int d = b - a;
    return std::ceil(a + (d * perc));
}


void Image::bezier(int x1, int y1, int x2, int y2,
                   int x3, int y3, int color)
{
    for(float i = 1.00; i > 0.00; i -= 0.001)
    {
        int xx = calc_pt(x1, x2, i);
        int yy = calc_pt(y1, y2, i);
        int xx1 = calc_pt(x2, x3, i);
        int yy1 = calc_pt(y2, y3, i);

        int x = calc_pt(xx, xx1, i);
        int y = calc_pt(yy, yy1, i);

        /* lines drawing */
        // impose(xx, yy, color);
        // impose(xx1, yy1, color);

        // curve drawing
        impose(x, y, color);
    }
}


void Image::circle(int x, int y, int radius, int color)
/**
 * Draws a circle according to the specified parameters
 *
 * params:
 *     x {int} -- circle center
 *     y {int} -- circle center
 *     radius {int} -- circle radius
 *     color {int} -- fill color
 */
{
    double step = 0.01;
    std::vector<std::array<int, 2>> positions;
    double t = 0.0;
    double pi = 3.14;
    double res = 2*pi;
    double r = (double)radius;
    double x1 = (double)x;
    double y1 = (double)y;
    positions.reserve(res / step + 2);

    while (t < res)
    {
        std::array<int, 2> timed = {(int)(r * std::cos(t) + x1), (int)(r * std::sin(t) + y1)};
        positions.push_back(timed);
        t += step;
    }

    for (int i = 0; i < positions.size(); ++i)
    {
        int x_end = positions[i][0] > 0 ? positions[i][0] : positions[i][0]*-2;
        int y_end = positions[i][1] > 0 ? positions[i][1] : positions[i][1]*-2;
        impose(x_end, y_end, color);
    }
}


void Image::fill_circle(int x, int y, int radius, int color, int fill_color)
/**
 * Draws a circle according to the specified parameters
 *
 * params:
 *     x {int} -- circle center
 *     y {int} -- circle center
 *     radius {int} -- circle radius
 *     color {int} -- fill borders color
 *     fill_color {int} -- fill color
 */
{
    circle(x, y, --radius, color);
    while (--radius)
        circle(x, y, radius, fill_color);
}


void Image::fill_circle(int x, int y, int radius, int color)
/**
 * Draws a circle according to the specified parameters
 *
 * params:
 *     x {int} -- circle center
 *     y {int} -- circle center
 *     radius {int} -- circle radius
 *     color {int} -- fill color
 */
{
    fill_circle(x, y, radius, color, color);
}


int Image::get_at(int x, int y)
/**
 * Returns color from the specified position
 *
 * params:
 *     x {int}
 *     y {int}
 */
{
    return self[x][y];
}


void Image::fill(int color)
/**
 * Fills the entire image with one color
 *
 * params:
 *     color {int} -- fill color
 */
{
    for (int x = 0; x < w; ++x)
    {
        for (int y = 0; y < h; ++y)
        {
            set_at(x, y, color);
        }
    }
}


void Image::fill()
{
    fill(0xFFFFFFFF);
}


void Image::impose(int x, int y, int color) {
    self[x][y] = calc_alpha(self[x][y], color);
}


void Image::line(int x1, int y1, int x2, int y2, int color)
/**
 * Draws a line from the first position to the second
 *
 * params:
 *     x1 {int} -- first position x
 *     y1 {int} -- first position y
 *     x2 {int} -- second position x
 *     y2 {int} -- second position y
 *     color {int} -- fill color
 */
{
    int nb_points = x1+x2 > y1+y2? x1+x2 : y1+y2;
    double x_spacing = (double)(x2 - x1) / (double)(nb_points + 1);
    double y_spacing = (double)(y2 - y1) / (double)(nb_points + 1);
    for (int i = 1; i < nb_points+1; ++i)
    {
        int x = x1 + (int)(i * x_spacing);
        int y = y1 + (int)(i * y_spacing);
        impose(x, y, color);
    }
}


void Image::rect(int x, int y, int width, int height, int color)
/**
 * Draws a rectangle without filling it with color
 *
 * params:
 *     x {int} -- start position
 *     y {int} -- start position
 *     width {int} -- rectangle width
 *     height {int} -- rectangle height
 *     color {int} -- fill color
 */
{
    int maxw = width+x, maxh = height+y;
    for (int i = x; i < maxw; ++i)
    {
        impose(i+1, y, color);
        impose(i, y+height, color);
    }
    for (int i = y; i < maxh; ++i)
    {
        impose(x, i, color);
        impose(x+width, i+1, color);
    }
}


void Image::fill_rect(int x, int y, int width, int height, int color, int fill_color)
/**
 * Draws a rectangle in the specified area.
 *
 * params:
 *     x {int} -- start position
 *     y {int} -- start position
 *     width {int} -- rectangle width
 *     height {int} -- rectangle height
 *     color {int} -- fill color
 *     fill_color {int} -- fill color
 */
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            impose(x+i, y+j, color);
        }
    }
    if (color != fill_color)
        rect(x, y, width, height, color);
}


void Image::fill_rect(int x, int y, int width, int height, int color)
{
    fill_rect(x, y, width, height, color, color);
}


void Image::set_at(int x, int y, int color)
/**
 * Sets the pixel to a specific position
 *
 * params:
 *     x {int}
 *     y {int}
 *     color {int} -- fill color
 */
{
    self[x][y] = color;
}


void Image::save(std::string file, int mode)
/**
 * saves image
 *
 * params:
 *     file {std::string} -- file name
 *     mode {int} -- file mode (0 - bmp)
 */
{
    if (mode == 0)  // create BMP image
    {
        std::ofstream fout;
        fout.open(file, std::ios_base::binary);

        // write header
        char bmp[18] = {'B', 'M', '\x9a', '\x00', '\x00', '\x00',
            '\x00', '\x00', '\x00', '\x00', 'z', '\x00', '\x00', '\x00',
            'l', '\x00', '\x00', '\x00'};
        fout.write((char*) &bmp, sizeof(bmp));

        fout.write((char*)&w, sizeof(w));
        fout.write((char*)&h, sizeof(h));

        char bmp1[96] = {'\x01', '\x00', ' ', '\x00', '\x03', '\x00',
            '\x00', '\x00', ' ', '\x00', '\x00', '\x00', '\x13', '\x0b',
            '\x00', '\x00', '\x13', '\x0b', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
            '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xFF', '\x00', '\x00', '\xFF',
            '\x00', '\x00', '\xFF', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xFF',
            ' ', 'n', 'i', 'W', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
            '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
            '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
            '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
            '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
            '\x00', '\x00', '\x00', '\x00', '\x00'};
        fout.write((char*) &bmp1, sizeof(bmp1));

        // transpose
        for (int x = 0; x < w; ++x)
        {
            std::reverse(self[x].begin(), self[x].end());
        }

        // write pixels in file
        for (int x = 0; x < w; ++x)
        {
            for (int y = 0; y < h; ++y)
            {
                fout.write((char*)&self[y][x], sizeof(self[y][x]));
            }
        }

        fout.close();

        // again transpose
        for (int x = 0; x < w; ++x)
        {
            std::reverse(self[x].begin(), self[x].end());
        }
    }
}


void Image::paste(Image other, int x, int y)
{
    for (int i = 0; i < other.w-1; ++i)
    {
        for (int j = 0; j < other.h-1; ++j)
        {
            impose(x+i, y+j, other.self[i][j]);
        }
    }
}


int Image::calc_alpha(int dst, int src)
/**
 * calcAlpha method is used to overlay one pixel on another
 *
 * params:
 *     dst {int} -- pixel to overlay
 *     src {int} -- pixel overlay
 */
{
    int dst_r, dst_g, dst_b;
    int src_r, src_g, src_b, src_a;
    dst_b = dst & 255;
    dst_g = (dst >> 8) & 255;
    dst_r = (dst >> 16) & 255;

    src_b = src & 255;
    src_g = (src >> 8) & 255;
    src_r = (src >> 16) & 255;
    src_a = (src >> 24) & 255;
    float a = (float)src_a * (1.0/255.0);
    int r, g, b;

    r = (float)dst_r*(1.0-a) + (float)src_r*a;
    g = (float)dst_g*(1.0-a) + (float)src_g*a;
    b = (float)dst_b*(1.0-a) + (float)src_b*a;

    return (255<<24) | (r<<16) | (g<<8) | b;
}
