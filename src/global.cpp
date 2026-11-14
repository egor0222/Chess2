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

bool BishopMove(Vector2i pos, Vector2i move, Field& field) {
	int x = pos.x - move.x;
	int y = pos.y - move.y;
	if (std::abs(x) != std::abs(y)) return false;

	int xstep = (x > 0) ? 1 : -1;
	int ystep = (y > 0) ? 1 : -1;
	int xpos = pos.x;
	int ypos = pos.y;
	for (; xpos != move.x || ypos != move.y; xpos += xstep, ypos += ystep) {
		if (field(Vector2i(xpos, ypos)).type != Pieces::NONE) return false;
	}
	return true;
}

bool RookMove(Vector2i pos, Vector2i move, Field& field) {
	int x = pos.x - move.x;
	int y = pos.y - move.y;
	if (x == 0) {
		for (int i = std::min(pos.y, move.y); i <= std::max(pos.y, move.y); i++) {
			if (field(Vector2i(x, i)).type != Pieces::NONE) return false;
		}
		return true;
	}
	if (y == 0) {
		for (int i = std::min(pos.x, move.x); i <= std::max(pos.x, move.x); i++) {
			if (field(Vector2i(y, i)).type != Pieces::NONE) return false;
		}
		return true;
	}
	return false;
}

bool QueenMove(Vector2i pos, Vector2i move, Field& field) {
	int x = pos.x - move.x;
	int y = pos.y - move.y;
	if ((x == 0 && y != 0) || (x != 0 && y == 0)) {
		return RookMove(pos, move, field);
	}
	if (std::abs(x) == std::abs(y)) return BishopMove(pos, move, field);
	return false;
}

bool KingMove(Vector2i pos, Vector2i move, Field& field) {
	int x = pos.x - move.x;
	int y = pos.y - move.y;
	if (std::abs(x) > 1 || std::abs(y) > 1) return false;

	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < TABLE_SIZE; j++) {
			if (field(Vector2i(i, j)).color != field(pos).color) {
				if (field(Vector2i(i, j)).type == Pieces::KING) continue;
				if (rightMove(Vector2i(i, j), move, &field)) return false;
			}
		}
	}
	return true;
}

bool KnightMove(Vector2i pos, Vector2i move, Field& field) {
	int x = pos.x - move.x;
	int y = pos.y - move.y;
	if ((std::abs(x) == 1 && std::abs(y) == 2) || (std::abs(x) == 2 && std::abs(y) == 1)) {
		return field(move).color != field(pos).color;
	}
	return false;
}

bool PawnMove(Vector2i pos, Vector2i move, Field& field) {
	int x = pos.x - move.x;
	int y = pos.y - move.y;
	if (field(pos).color == White) {
		if (x == 0 && y == 1 && field(move).type == Pieces::NONE) return true;
		if (std::abs(x) == 1 && y == -1 && field(move).type != Pieces::NONE
			&& field(move).color != field(pos).color) return true;
	}
	else {
		if (x == 0 && y == -1 && field(move).type == Pieces::NONE) return true;
		if (std::abs(x) == 1 && y == 1 && field(move).type != Pieces::NONE
			&& field(move).color != field(pos).color) return true;
	}
	return false;
}

bool rightMove(Vector2i pos, Vector2i move, Field* field) {
	switch ((*field)(pos).type) {
	case Pieces::KING:
		return KingMove(pos, move, *field);
	case Pieces::KNIGHT:
		return KnightMove(pos, move, *field);
	case Pieces::PAWN:
		return PawnMove(pos, move, *field);
	case Pieces::BISHOP:
		return BishopMove(pos, move, *field);
	case Pieces::QUEEN:
		return QueenMove(pos, move, *field);
	case Pieces::ROOK:
		return RookMove(pos, move, *field);
	default:
		return false;
	}
}