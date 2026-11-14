#pragma once
#include "global.hpp"
#include "TextureLoader.hpp"

std::string PieceToStr(Pieces pp);

class Draw {
private:
	TextureLoader tl;
	bool selFirst;
	Vector2i firstSelected;
	Vector2i canSelected;
	bool StepColor;
	Field ff;
	RenderWindow* win;
	
public:
	Draw(RenderWindow* rw);
	void draw();
	void canSel(Vector2i pos);
	void select();

private:
	void RendereSelectedTexture(Vector2i pos);
	void FigureMove(Vector2i from, Vector2i to);
};