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

    img.line(128, 64, 64, 128, Color::parse_color("OlIvE"));
    img.circle(64, 64, 32, Color::parse_color("aquamarine"));

    img.save("file.png", 0);
    std::cout << clock() - now << " times." << std::endl;
    auto rgba = Color::to_rgba(0xFF77dd77);
    std::cout << rgba.r << std::endl;
    std::cout << rgba.g << std::endl;
    std::cout << rgba.b << std::endl;
    std::cout << rgba.a << std::endl;
    std::cout << Color::parse_color(rgba) << std::endl;
    return 0;
}
