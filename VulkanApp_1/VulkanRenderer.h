﻿#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <array>
#include <set>
#include <algorithm>

#include "Utilities.h"

class VulkanRenderer
{
public:
	VulkanRenderer() = default;

	int init(GLFWwindow* newWindow);
	void draw();
	void cleanup();
	
	~VulkanRenderer() = default;

private:
	GLFWwindow* window;

	int currentFrame = 0;

	// Vulkan Components
	// - Main
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	struct {
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;
	} mainDevice;
	VkQueue graphicsQueue;
	VkQueue presentationQueue;
	VkSurfaceKHR surface;
	VkSwapchainKHR swapchain;
	
	std::vector<SwapchainImage> swapChainImages;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	std::vector<VkCommandBuffer> commandBuffers;

	// - Pipeline
	VkPipeline graphicsPipeline;
	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;

	// - Pools
	VkCommandPool graphicsCommandPool;

	// - Utility
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	// - Synchronisaition
	std::vector<VkSemaphore> imageAvailable;
	std::vector<VkSemaphore> renderFinished;
	std::vector<VkFence> drawFences;

	// Vulkan Functions
	// - Create Functions
	void createInstance();
	void createLogicalDevice();
	void createSurface();
	void createSwapChain();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createSynchronisation();

	// - Record Function
	void recordCommands();

	// - Get Functions
	void getPhysicalDevice();

	// - Support Functions
	// -- Checker Functions
	bool checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	bool checkDeviceSuitable(VkPhysicalDevice device);
	bool checkValidationLayerSupport();

	// -- Getter Functions
	QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);
	SwapChainDetails getSwapChainDetails(VkPhysicalDevice device);

	// -- Choose Functions
	VkSurfaceFormatKHR chooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
	VkPresentModeKHR chooseBestPresentationMode(const std::vector<VkPresentModeKHR> presentationModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& surfaceCapabilities);

	// -- Create Functions
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	std::vector<const char*> getRequiredExtensions();
	
	// Validation
	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif
	
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

	// Validation Message Callbacks
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
															VkDebugUtilsMessageTypeFlagsEXT messageType,
															const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
															void* pUserData);
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
};

