// Needed to make compiler happy with STB
#define _CRT_SECURE_NO_WARNINGS

// A library for writing out images, which is in a single header file.
// Very convinient and easy to use!
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <stdio.h>
#include <vector>
#include <cmath>

static const float c_pi = 3.14159265359f;

// Settings
static const int c_width = 256;
static const int c_height = 256;
static const char* c_fileName = "out.png";

struct RGBA
{
	float R = 0.0f;  // Red
	float G = 0.0f;  // Green
	float B = 0.0f;  // Blue
	float A = 1.0f;  // Alpha (opacity)
};

// Logic here can write to any pixel
void RenderImage(std::vector<RGBA>& pixels)
{
	for (int y = 0; y < c_height; ++y)
	{
		for (int x = 0; x < c_width; ++x)
		{
			float u = (float(x) + 0.5f) / float(c_width);
			pixels[y * c_width + x].B = std::sin(u * c_pi * 2.0f * 10.0f) * 0.5f + 0.5f;
		}
	}

	// TODO: add to this function or replace it completely
}

// Logic here writes to an individual pixel. This is how a pixel or compute shader runs on the GPU.
void RenderPixel(int x, int y, RGBA& pixel)
{
	float u = (float(x) + 0.5f) / float(c_width);
	float v = (float(y) + 0.5f) / float(c_height);

	pixel.R = u;
	pixel.G = v;
	pixel.B = 0.0f;
	pixel.A = 1.0f;

	// TODO: add to this function or replace it completely
}

int main(int argc, char** argv)
{
	// Allocate our pixels as floats
	std::vector<RGBA> pixels(c_width * c_height);

	// Draw the image
	for (int i = 0; i < c_width * c_height; ++i)
	{
		int x = i % c_width;
		int y = i / c_width;
		RenderPixel(x, y, pixels[i]);
	}
	RenderImage(pixels);

	// Convert from float to 8 bits per channel
	std::vector<unsigned char> pixelsU8(c_width * c_height * 4);
	for (int i = 0; i < c_width * c_height; ++i)
	{
		pixelsU8[i * 4 + 0] = (unsigned char)std::max(std::min(pixels[i].R * 255.0f, 255.0f), 0.0f);
		pixelsU8[i * 4 + 1] = (unsigned char)std::max(std::min(pixels[i].G * 255.0f, 255.0f), 0.0f);
		pixelsU8[i * 4 + 2] = (unsigned char)std::max(std::min(pixels[i].B * 255.0f, 255.0f), 0.0f);
		pixelsU8[i * 4 + 3] = (unsigned char)std::max(std::min(pixels[i].A * 255.0f, 255.0f), 0.0f);
	}

	// write the image out
	stbi_write_png(c_fileName, c_width, c_height, 4, pixelsU8.data(), 0);

	return 0;
}

