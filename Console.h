//Console.h
#pragma once
#include "Includes.h"
#include "Font.h"
#include "Sprite.h"

namespace Advanced2D
{
	class Console
	{
		public:
			Console();
			virtual ~Console();

			bool Init();
			void Draw();
			void Clear();
			void Print(const std::string& text,int line = -1);
			bool IsShowing()const {return isShowing;}
			void Show(){ isShowing = true;}
			void Hide(){ isShowing = false;}
			void SetShowing(bool value){isShowing = value;}
		private:
			bool isShowing;
			Sprite* panel;
			Font* font;
			int currentLine;
			std::vector<std::string> textLines;
			std::vector<std::string>::iterator iter;
	};
};
