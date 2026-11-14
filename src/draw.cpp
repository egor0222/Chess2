#include "draw.hpp"

#include <iostream>

std::string PieceToStr(Pieces pp) {
	switch (pp) {
	case Pieces::KING:
		return "king";
	case Pieces::KNIGHT:
		return "knight";
	case Pieces::PAWN:
		return "pawn";
	case Pieces::BISHOP:
		return "bishop";
	case Pieces::QUEEN:
		return "queen";
	case Pieces::ROOK:
		return "rook";
	default:
		return "";
	}
}

Draw::Draw(RenderWindow* rw) {
	win = rw;
	tl.init();
	selFirst = false;
	firstSelected = { 0, 0 };
	Start(&ff);
	StepColor = White;
}

void Draw::draw() {
	bool color = true;
	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < TABLE_SIZE; j++) {
			Texture* text = color ? tl("white") : tl("black");
			RectangleShape rect;
			rect.setTexture(text);
			rect.setPosition(j * STEP, i * STEP);
			rect.setSize(Vector2f(TEXTURE_SIZE, TEXTURE_SIZE));
			win->draw(rect);
			color = !color;
		}
		color = !color;
	}
	if (canSelected.x >= 0 && canSelected.y >= 0) {
		RendereSelectedTexture(canSelected);
	}
	if (selFirst) {
		RendereSelectedTexture(firstSelected);
	}
	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < TABLE_SIZE; j++) {
			if (ff(Vector2i(j, i)).type != Pieces::NONE) {
				std::string typeName = PieceToStr(ff(Vector2i(j, i)).type);
				std::string pieceColor = (ff(Vector2i(j, i)).color == White) ? "white" : "black";
				Texture* text = tl(typeName + pieceColor);
				RectangleShape rect;
				rect.setSize(Vector2f(TEXTURE_SIZE, TEXTURE_SIZE));
				rect.setTexture(text);
				rect.setPosition(j * STEP, i * STEP);
				win->draw(rect);
			}
		}
	}
}

void Draw::canSel(Vector2i pos) {
	int x = pos.x / STEP;
	int y = pos.y / STEP;
	std::cout << x << ' ' << y << std::endl;
	canSelected = Vector2i(x, y);
}

void Draw::select() {
	if (selFirst) {
		if (!rightMove(firstSelected, canSelected, &ff)) return;
		FigureMove(firstSelected, canSelected);
		selFirst = false;
		std::cout << "Moved: " << canSelected.x << ' ' << canSelected.y << std::endl;
	}
	else if (ff(canSelected).type != Pieces::NONE) {
		firstSelected = canSelected;
		selFirst = true;
		std::cout << "Do not move: " << canSelected.x << ' ' << canSelected.y << std::endl;
	}
}

void Draw::RendereSelectedTexture(Vector2i pos) {
	Texture* text = tl("selected");
	RectangleShape rect;
	rect.setSize(Vector2f(TEXTURE_SIZE, TEXTURE_SIZE));
	rect.setTexture(text);
	rect.setPosition(canSelected.x * STEP, canSelected.y * STEP);
	win->draw(rect);
}

void Draw::FigureMove(Vector2i from, Vector2i to) {
	ff(to) = ff(from);
	ff(from).type = Pieces::NONE;
}