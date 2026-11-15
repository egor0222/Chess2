#include "global.hpp"

#include <algorithm>
#include <cstdlib>

Str::Str(Pieces type, bool color) : type(type), color(color) {}
Str::Str() = default;

Field::Field() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < TABLE_SIZE; j++) {
			data[i][j].type = Pieces::NONE;
			data[i][j].color = Black;
		}
	}
}

bool Field::setFigure(Vector2i pos, bool color, Pieces pp) {
	if (pp == Pieces::NONE) return false;
	if (data[pos.y][pos.x].type != Pieces::NONE) return false;
	data[pos.y][pos.x] = Str(pp, color);
	return true;
}

Str& Field::operator()(Vector2i pos) {
	return data[pos.y][pos.x];
}

void Start(Field* ff) noexcept {
	for (int i = 0; i < TABLE_SIZE; i++) {
		ff->setFigure(Vector2i(i, 1), Black, Pieces::PAWN);
		ff->setFigure(Vector2i(i, 6), White, Pieces::PAWN);
	}

	ff->setFigure(Vector2i(0, 0), Black, Pieces::ROOK);
	ff->setFigure(Vector2i(7, 0), Black, Pieces::ROOK);
	ff->setFigure(Vector2i(0, 7), White, Pieces::ROOK);
	ff->setFigure(Vector2i(7, 7), White, Pieces::ROOK);

	ff->setFigure(Vector2i(1, 0), Black, Pieces::KNIGHT);
	ff->setFigure(Vector2i(6, 0), Black, Pieces::KNIGHT);
	ff->setFigure(Vector2i(1, 7), White, Pieces::KNIGHT);
	ff->setFigure(Vector2i(6, 7), White, Pieces::KNIGHT);

	ff->setFigure(Vector2i(2, 0), Black, Pieces::BISHOP);
	ff->setFigure(Vector2i(5, 0), Black, Pieces::BISHOP);
	ff->setFigure(Vector2i(2, 7), White, Pieces::BISHOP);
	ff->setFigure(Vector2i(5, 7), White, Pieces::BISHOP);

	ff->setFigure(Vector2i(4, 0), Black, Pieces::KING);
	ff->setFigure(Vector2i(3, 0), Black, Pieces::QUEEN);
	ff->setFigure(Vector2i(4, 7), White, Pieces::KING);
	ff->setFigure(Vector2i(3, 7), White, Pieces::QUEEN);
}

