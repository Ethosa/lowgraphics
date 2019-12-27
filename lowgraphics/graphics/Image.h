// author: Ethosa
#include <iostream>
#include <vector>

class Image
{
public:
    int w, h;
    std::vector<std::vector<int>> self;

    Image(int width, int height, int color);
    Image(int width, int height);
    Image();
    void circle(int x, int y, int radius, int color);
    void fill_circle(int x, int y, int radius, int color, int fill_color);
    void fill_circle(int x, int y, int radius, int color);
    int get_at(int x, int y);
    void fill(int color);
    void fill();
    void line(int x1, int y1, int x2, int y2, int color);
    void rect(int x, int y, int width, int height, int color);
    void fill_rect(int x, int y, int width, int height, int color, int fill_color);
    void fill_rect(int x, int y, int width, int height, int color);
    void set_at(int x, int y, int color);
    void save(std::string file, int mode);
private:
    static int calc_alpha(int dst, int src);
};
