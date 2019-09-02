#pragma once

#include <Windows.h>

class Picture
{
	struct Pixel
	{
		Pixel(int r, int g, int b);
		Pixel();

		int R;
		int G;
		int B;

		int GetGray()
		{
			return (0.299*R) + (0.587*G) + (0.114*B);
		}
	};

public:
	Picture();
	~Picture();

	void OpenPic();

private:
	Pixel m_pixels[28][28];

	BITMAP m_hBit;
};

