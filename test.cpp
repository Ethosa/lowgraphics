#include <iostream>
#include <ctime>
#include "lowgraphics/graphics/Image.h"
#include "lowgraphics/graphics/Color.h"

int main(int argc, char const *argv[])
{
    int now = clock();
    Image img = Image(512, 512, 0xFFFFFFFF);

    // img.bezier(25, 25, 128, 64, 64, 128, 0xFF212121);
    // img.bezier(64, 128, 25, 256, 256, 25, 0xFF212121);
    img.bezier(25, 25, 256, 25, 25, 256, 0xFF212121);
    img.fill_rect(128, 128, 64, 64, 0x507777dd);

    img.save("file.png", 0);
    std::cout << clock() - now << " times." << std::endl;
    return 0;
}
