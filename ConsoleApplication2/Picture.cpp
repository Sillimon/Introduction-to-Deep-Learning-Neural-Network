#include "Picture.h"

//TEMP//
#include <iostream>
//----//

Picture::Picture()
{
	OpenPic();
}


Picture::~Picture()
{
}

Picture::Pixel::Pixel() {}

Picture::Pixel::Pixel(int r, int g, int b)
{
	R = r; G = g; B = b;
}

void Picture::OpenPic()
{

	/*
	// From File:
	HBITMAP hBit = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Simon\\Pictures\\1.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	GetObject(hBit, sizeof(m_hBit), &m_hBit);

	m_hBit.

	for (size_t i = 1; i <= 28; ++i)
	{
		for (size_t j = 1; j <= 28; ++j)
		{
			COLORREF _color = m_hBit.GetPixel(i, j, &pixelColor);
			m_pixels[i][j] = Pixel(pixelColor.GetR(), pixelColor.GetG(), pixelColor.GetB());
		}
	}
	*/
	
}