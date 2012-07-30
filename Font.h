//Font.h
#pragma once
#include "Includes.h"
#include "Sprite.h"

namespace Advanced2D
{
	class Font : public Sprite
	{
	public:
		Font();
		virtual ~Font(){};

		int GetCharWidth()const {return width;}
		int GetCharHeight()const {return height;}
		void SetCharWidth(int wdth) {width = wdth;}
		void SetCharSize(int size,int size2) {width = size; height = size2;}

		void Print(int x,int y,const std::string& text,int colour = 0xFFFFFFFF);
		bool LoadWidthData(const std::string& fileName);
	private:
		int widths[256];
	};
};