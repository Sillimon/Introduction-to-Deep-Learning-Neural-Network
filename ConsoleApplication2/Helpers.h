#pragma once

#include <Windows.h>
#include <array>
#include <iostream>
#include <vector>

// Digits as array //
static class DigitsArray
{
public:
	static std::array<int, 10> Parse(int z);
};

// Image processing functions
static class ImageProcessing
{
public:
	static void PrintGrayScale();
};

// Constants //
enum LayerType
{
	INPUT_LAYER,
	HIDDEN_LAYER,
	OUTPUT_LAYER,
};