//Font.cpp

#include "Font.h"

namespace Advanced2D
{
	Font::Font() : Sprite()
	{
		memset(&widths,0,sizeof(widths));
	}

	void Font::Print(int x,int y,const std::string& text,int colour)
	{
		float fX = x;
		float fY = y;

		SetColour(colour);

		for(unsigned int n = 0; n < text.length(); n++)
		{
			int frame = (int)text[n];
			SetCurrentFrame(frame);
			SetX(fX);
			SetY(fY);
			Draw();
			if(widths[frame] == 0) widths[frame] = width;
			fX += widths[frame] * scaling;
		}
	}

	bool Font::LoadWidthData(const std::string& filename)
	{
		unsigned char buffer[512];
		std::ifstream inFile;
		inFile.open(filename.c_str(),std::ios::binary);
		if(!inFile)return false;

		inFile.read((char*)(&buffer),512);
		if(inFile.bad()) return false;
		inFile.close();

		for(int n = 0; n < 256; n++)
		{
			widths[n] = (int)buffer[n*2];
		}
		return true;
	}
};