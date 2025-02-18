#include "ASTL_main.h"

namespace ASTL {
    void Astl_InitializeVulkan(SDL_Window *window){
        ASTL::Vulkan vlk;
        vlk.initVulkan(window);
    };

}





using namespace ASTL;

int main(int argc, char *argv[])
{
    ASTL::Vulkan vlk = {};

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    if (result != 1)
    {
        throw SDLException{"SDL konnte nicht initialisiert werden!"};
        return 1;
    } // Beispiel für einen alternativen Pfad

    SDL_Window *window = SDL_CreateWindow(
        "Vulkan Window",
        800,
        600,
        SDL_WINDOW_VULKAN
    );

    if (!window)
    {
        printf("SDL Error: %s\n", SDL_GetError());
        throw SDLException{"Fenster konnte nicht erstellt werden!"};
        SDL_Quit();
        return 1;
    }

    vlk.initVulkan(window);

    VkImage image = {};
    VkDeviceMemory imageMemory = {};
    VkImageView imageView = {};

    int width, height, channels;

    stbi_uc *data = stbi_load("Content/pic/SpaceShip.png", &width, &height, &channels, 4);

    if (!data) {
        throw std::runtime_error("Failed to load texture image!");
    }

    vlk.createTexture(
        VkExtent2D{static_cast<uint32_t>(width), static_cast<uint32_t>(height)},
        image, imageView, imageMemory, data, width, height, VK_FORMAT_R8G8B8A8_SRGB, width * height * 4
    );

    // Speicher freigeben, um Memory-Leaks zu vermeiden
    stbi_image_free(data);


    SDL_GPUDevice *device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_DXIL, true, nullptr);

    if (!device)
    {
        throw SDLException{"SDL_CreateGPUDevice fehlgeschlagen!"};
    }
    SDL_ShowWindow(window);

    SDL_Event event;
    bool isRunning{true};

    while (isRunning)
    {
        vlk.drawFrame();
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                isRunning = false;
                break;
            default:
                break;
            }
        }
    }
}