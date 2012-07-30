#include "Console.h"
#include "Advanced2D.h"

namespace Advanced2D
{
	Console::Console()
	{
		isShowing = false;
		currentLine = 0;
		Clear();
	}

	Console::~Console()
	{
		delete font;
		delete panel;
	}

	bool Console::Init()
	{
		panel = new Sprite;
		if(!panel->LoadImg("panel.tga")) return false;
		float scale = g_engine->GetScreenWidth()/640.0f;
		panel->SetScale(scale);
		panel->SetColour(0x99FFFFFF);

		font = new Font;
		
		if(!font->LoadImg("system12.tga"))return false;

		font->SetColumns(16);
		font->SetCharSize(14,16);
		if(!font->LoadWidthData("system12.dat"))return false;
		return true;
	}

	void Console::Draw()
	{
		int x = 5;
		int y = 0;
		if(!isShowing)return;
		panel->Draw();

		for(unsigned int line = 0; line < textLines.size(); line++)
		{
			font->Print(x,y*14,textLines[line],0xFF000000);
			y += 1;
			if(y > 26)
			{
				if(x > 10)break;
				x = g_engine->GetScreenWidth()/2 + 5;
				y = 0;
			}
		}
	}

	void Console::Print(const std::string& text,int line)
	{
		if(line > -1) currentLine = line;
		textLines[currentLine] = text;
		if(currentLine++ > 52) currentLine = 0;
	}

	void Console::Clear()
	{
		for(int line = 0; line < 55; line++)
			textLines.push_back("");
	}
};