#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "src/core/Application.h"

static const int WIDTH = 1280;
static const int HEIGHT = 800;

int main()
{   
    Application app(WIDTH, HEIGHT);
    app.run();
    return 0;
}