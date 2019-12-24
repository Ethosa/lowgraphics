#include <iostream>
#include <vector>

class image
{
public:
    int w, h, clr;
    std::vector<std::vector<int>> self;

    image(int width, int height, int color);
    image(int width, int height);
    image();
    int get_at(int x, int y);
    void fill(int color);
    void fill();
    void line(int x1, int y1, int x2, int y2, int color);
    void rect(int x, int y, int width, int height, int color);
    void set_at(int x, int y, int color);
    void save(std::string file, int mode);
private:
    int calcAlpha(int dst, int src);
};