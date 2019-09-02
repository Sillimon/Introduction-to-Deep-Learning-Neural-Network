#include "Helpers.h"

// DigitsArray //
std::array<int, 10> DigitsArray::Parse(int z)
{
	switch (z)
	{
	case 0:
		return { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	case 1:
		return { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };

	case 2:
		return { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };

	case 3:
		return { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };

	case 4:
		return { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };

	case 5:
		return { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };

	case 6:
		return { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };

	case 7:
		return { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };

	case 8:
		return { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };

	case 9:
		return { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

	}
}


// ImageProcessing //
void ImageProcessing::PrintGrayScale()
{
	POINT _cursor;
	GetCursorPos(&_cursor);

	COLORREF _color = GetPixel(GetDC(NULL), _cursor.x, _cursor.y);

	int R = GetRValue(_color);
	int G = GetGValue(_color);
	int B = GetBValue(_color);

	printf("Red: 0x%02x\n", R);
	printf("Green: 0x%02x\n", G);
	printf("Blue: 0x%02x\n", B);

	int gray = (0.299*R) + (0.587*G) + (0.114*B);

	std::cout << "grayscale is " << gray << std::endl;
}
