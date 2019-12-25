#include <iostream>
#include <ctime>
#include "lowgraphics/graphics/Image.h"
#include "lowgraphics/graphics/Color.h"

int main(int argc, char const *argv[])
{
    int now = clock();
    Image img = Image(256, 256, 0xFFFFFFFF);
    img.fill(0xFF212121);
    for (int i=0; i<256; ++i) img.set_at(i, 10, 0xFF77dd77);

    img.line(0, 0, 256, 256, 0x99dd7777);
    img.rect(7, 7, 55, 55, 0x757777dd);
    img.circle(128, 128, 32, 0xFFFFFFFF);

    int clr[4] = {200, 200, 200, 128};
    img.line(128, 64, 64, 128, Color::parse_color(clr));

    img.save("file.bmp", 0);
    std::cout << clock() - now << " times." << std::endl;
    return 0;
}
