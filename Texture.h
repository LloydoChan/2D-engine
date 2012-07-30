//Texture.h
#pragma once
#include "Includes.h"

namespace Advanced2D
{
	class Texture
	{
		public:
			Texture();
			~Texture();
			bool Load(std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0));
			void Release();
			LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
			int GetWidth();
			int GetHeight();
		private:
			LPDIRECT3DTEXTURE9 texture;
			D3DXIMAGE_INFO info;
	};
};