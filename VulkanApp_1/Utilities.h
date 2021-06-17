﻿#pragma once

// Indices (locations) of Queue Families (if they exist at all)
const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct QueueFamilyIndices
{
	int graphicsFamily = -1;			// Location of Graphics Family
	int presentationFamily = -1;		// Location of Presentation Family

	// Check if queue familes are valid
	bool isValid()
	{
		return graphicsFamily >= 0 && presentationFamily >= 0;
	}
};