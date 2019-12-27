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
        self[x_end][y_end] = calc_alpha(self[x_end][y_end], color);
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
            self[x][y] = color;
        }
    }
}

void Image::fill()
{
    fill(0xFFFFFFFF);
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
        self[x][y] = calc_alpha(self[x][y], color);
    }
}

void Image::rect(int x, int y, int width, int height, int color)
{
    for (int i = x; i < width+x; ++i)
    {
        self[i][y] = calc_alpha(self[i][y], color);
        self[i][y+height] = calc_alpha(self[i][y+height], color);
    }
    for (int i = y; i < height+y; ++i)
    {
        self[x][i] = calc_alpha(self[x][i], color);
        self[x+width][i] = calc_alpha(self[x+width][i], color);
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
            self[x+i][y+j] = calc_alpha(self[x+i][y+j], fill_color);
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
    double a = (double)src_a * (1.0/255.0);
    int r, g, b;

    r = (double)dst_r*(1.0-a) + (double)src_r*a;
    g = (double)dst_g*(1.0-a) + (double)src_g*a;
    b = (double)dst_b*(1.0-a) + (double)src_b*a;

    return ((int)(a*255)<<24) | (r<<16) | (g<<8) | b;
}
