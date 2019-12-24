// author: Ethosa
#include "image.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>



image::image(int width, int height, int color)
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
    clr = color;
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

image::image(int width, int height)
/**
 * creates an image object for further work with it
 *
 * params:
 *     width {int} -- image width
 *     height {int} -- image height
 */
{
    image(width, height, 0xFFFFFFFF);
}

image::image()
{
    image(256, 256, 0xFFFFFFFF);
}

int image::get_at(int x, int y)
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

void image::fill(int color)
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

void image::fill()
{
    fill(0xFFFFFFFF);
}

void image::line(int x1, int y1, int x2, int y2, int color)
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

void image::rect(int x, int y, int width, int height, int color)
/**
 * Draws a rectangle in the specified area.
 *
 * params:
 *     x {int} -- start position
 *     y {int} -- start position
 *     width {int} -- rectangle width
 *     height {int} -- rectangle height
 *     color {int} -- fill color
 */
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            self[x+i][y+j] = calc_alpha(self[x+i][y+j], color);
        }
    }
}

void image::set_at(int x, int y, int color)
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

void image::save(std::string file, int mode)
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

int image::calc_alpha(int dst, int src)
/**
 * calcAlpha method is used to overlay one pixel on another
 *
 * params:
 *     dst {int} -- pixel to overlay
 *     src {int} -- pixel overlay
 */
{
    int dst_r, dst_g, dst_b, dst_a;
    int src_r, src_g, src_b, src_a;
    dst_b = dst & 255;
    dst_g = (dst >> 8) & 255;
    dst_r = (dst >> 16) & 255;
    dst_a = (dst >> 24) & 255;

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
