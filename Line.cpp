//Line.cpp
#include "Line.h"
#include "Advanced2D.h"

namespace Advanced2D
{
	Line::Line() : Entity(RENDER2D),color(0xFFFFFFFF),width(1),line(NULL)
	{
		points[0] = points[1] = D3DXVECTOR2(0,0);
	}

	Line::~Line()
	{
		if(line)
			line->Release();
	}

	bool Line::Init()
	{
		D3DXCreateLine(g_engine->GetDevice(),&line);
	
		if(!line)
			return false;

		line->SetWidth(width);
		line->SetAntialias(true);

		return true;
	}

	void Line::Draw()
	{
		line->Begin();
		line->Draw(points,2,color);
		line->End();
	}

	void Line::Animate()
	{
	}

	void Line::Move()
	{
	}
}