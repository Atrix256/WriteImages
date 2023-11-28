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

// Logic here can write to any pixel
void RenderImage(std::vector<float>& pixels)
{
	float* pixel = &pixels[0];
	for (int y = 0; y < c_height; ++y)
	{
		for (int x = 0; x < c_width; ++x)
		{
			float u = (float(x) + 0.5f) / float(c_width);
			pixel[2] = std::sin(u * c_pi * 2.0f * 10.0f) * 0.5f + 0.5f;
			pixel += 4;
		}
	}

	// TODO: add to this function or replace it completely
}

// Logic here writes to an individual pixel. This is how a pixel or compute shader runs on the GPU.
void RenderPixel(int x, int y, float* RGBA)
{
	float u = (float(x) + 0.5f) / float(c_width);
	float v = (float(y) + 0.5f) / float(c_height);

	RGBA[0] = u;
	RGBA[1] = v;
	RGBA[2] = 0.0f;
	RGBA[3] = 1.0f;

	// TODO: add to this function or replace it completely
}

int main(int argc, char** argv)
{
	// Allocate our pixels as floats
	std::vector<float> pixels(c_width * c_height * 4, 1.0f);

	// Draw the image
	for (int i = 0; i < c_width * c_height; ++i)
	{
		int x = i % c_width;
		int y = i / c_width;
		RenderPixel(x, y, &pixels[i * 4]);
	}
	RenderImage(pixels);

	// Convert from float to 8 bits per channel
	std::vector<unsigned char> pixelsU8(c_width * c_height * 4);
	for (int i = 0; i < c_width * c_height * 4; ++i)
		pixelsU8[i] = (unsigned char)std::max(std::min(pixels[i] * 255.0f, 255.0f), 0.0f);

	// write the image out
	stbi_write_png(c_fileName, c_width, c_height, 4, pixelsU8.data(), 0);

	return 0;
}

