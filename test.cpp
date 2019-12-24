#include <iostream>
#include <ctime>
#include "lowgraphics/graphics/image.h"

int main(int argc, char const *argv[])
{
    int now = clock();
    image img = image(256, 256, 0xFFFFFFFF);
    img.fill(0xFF212121);
    for (int i=0; i<256; ++i) img.set_at(i, 10, 0xFF77dd77);

    img.line(0, 0, 256, 256, 0x99dd7777);
    img.rect(7, 7, 55, 55, 0x757777dd);
    img.circle(128, 128, 32, 0xFFFFFFFF);

    img.line(128, 64, 64, 128, image::parse_color(32, 64, 128));

    img.save("file.bmp", 0);
    std::cout << clock() - now << " times." << std::endl;
    return 0;
}
