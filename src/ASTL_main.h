#ifndef ASTL_MAIN_H
#define ASTL_MAIN_H

#include <glm/glm.hpp>
#include <stdexcept>
#include <SDL3/SDL.h>
#include <vulkan/vulkan.h>
#include <SDL3/SDL_vulkan.h>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "stb_image.h"
#include <array>


struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};

        return bindingDescription;
    }
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};


struct QueueFamilyIndices
    {
        uint32_t graphicsFamily;
        uint32_t presentFamily;
    };
namespace ASTL {
    void Astl_InitializeVulkan(SDL_Window *window);
    class Vulkan
    {
    public:
        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkQueue queue;
        VkCommandPool commandPool;
        VkSurfaceKHR surface;
        SDL_Window *window;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        VkPipelineLayout pipelineLayout;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkCommandBuffer commandBuffer;
        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;
        VkSampler sampler;
        VkDescriptorPool descriptorPool;
        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorSet descriptorSet;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;

        void initVulkan(SDL_Window *window);
        void createVKdevice();
        void CreateSwapChain();
        void createImageViews();
        void createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView &imageView);
        void createRenderPass();
        void createGraphicsPipeline();
        void createFramebuffers();
        void createCommandBuffer(VkCommandBuffer &commandBuffer);
        void createSyncObjects();
        void drawFrame();
        void CreateSampler();
        void CreateDescriptorSetLayout();
        void CreateDescriptorPool();
        void createVertex();
        void createVertexBuffer();
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        VkShaderModule createShaderModule(const std::vector<char> &code);
        Uint32 getQueueFamilyIndex();
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
        void createTexture(VkExtent2D extent, VkImage &image, VkImageView &imageView, VkDeviceMemory &imageMemory, void* data, uint32_t width, uint32_t height, VkFormat format, Uint32 totalSize);
        void transitionLayout(VkCommandBuffer cmd, VkImage handle, VkImageLayout layout, VkImageLayout newLayout);
        void cleanUp();
    };




};

class SDLException : public std::exception
{
public:
    SDLException(const std::string &message) : message(message) {}

    const char *what() const noexcept override
    {
        return message.c_str();
    }

private:
    std::string message;
};

#endif