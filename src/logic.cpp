#include "logic.hpp"

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