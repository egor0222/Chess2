#include "logic.hpp"

bool BishopMove(Vector2i pos, Vector2i move, Field& field, bool color) {
	if (field(Vector2i(pos.x, pos.y)).type == Pieces::NONE) return false;
	if (field(Vector2i(pos.x, pos.y)).color != color) return false;
	if (move.x < 0 || move.y < 0 || move.x >= TABLE_SIZE || move.y >= TABLE_SIZE) return false;
	if (field(move).type != Pieces::NONE && field(move).color == color) return false;

	int dx = move.x - pos.x;
	int dy = move.y - pos.y;
	if (dx == 0 || std::abs(dx) != std::abs(dy)) return false;

	int xstep = (dx > 0) ? 1 : -1;
	int ystep = (dy > 0) ? 1 : -1;
	int xpos = pos.x + xstep;
	int ypos = pos.y + ystep;
	for (; xpos != move.x || ypos != move.y; xpos += xstep, ypos += ystep) {
		if (field(Vector2i(xpos, ypos)).type != Pieces::NONE) return false;
	}
	return true;
}

bool RookMove(Vector2i pos, Vector2i move, Field& field, bool color) {
	if (field(Vector2i(pos.x, pos.y)).type == Pieces::NONE) return false;
	if (field(Vector2i(pos.x, pos.y)).color != color) return false;
	if (move.x < 0 || move.y < 0 || move.x >= TABLE_SIZE || move.y >= TABLE_SIZE) return false;
	if (field(move).type != Pieces::NONE && field(move).color == color) return false;

	int dx = move.x - pos.x;
	int dy = move.y - pos.y;
	if ((dx == 0) == (dy == 0)) return false;

	int xstep = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
	int ystep = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);
	int xpos = pos.x + xstep;
	int ypos = pos.y + ystep;
	for (; xpos != move.x || ypos != move.y; xpos += xstep, ypos += ystep) {
		if (field(Vector2i(xpos, ypos)).type != Pieces::NONE) return false;
	}
	return true;
}

bool QueenMove(Vector2i pos, Vector2i move, Field& field, bool color) {
	if (field(Vector2i(pos.x, pos.y)).type == Pieces::NONE) return false;
	if (field(Vector2i(pos.x, pos.y)).color != color) return false;
	if (move.x < 0 || move.y < 0 || move.x >= TABLE_SIZE || move.y >= TABLE_SIZE) return false;
	if (field(move).type != Pieces::NONE && field(move).color == color) return false;

	int dx = move.x - pos.x;
	int dy = move.y - pos.y;
	bool straight = (dx == 0) != (dy == 0);
	bool diagonal = dx != 0 && std::abs(dx) == std::abs(dy);
	if (!straight && !diagonal) return false;

	int xstep = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
	int ystep = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);
	int xpos = pos.x + xstep;
	int ypos = pos.y + ystep;
	for (; xpos != move.x || ypos != move.y; xpos += xstep, ypos += ystep) {
		if (field(Vector2i(xpos, ypos)).type != Pieces::NONE) return false;
	}
	return true;
}

bool KingMove(Vector2i pos, Vector2i move, Field& field, bool color) {
	if (field(Vector2i(pos.x, pos.y)).type == Pieces::NONE) return false;
	if (field(Vector2i(pos.x, pos.y)).color != color) return false;
	if (move.x < 0 || move.y < 0 || move.x >= TABLE_SIZE || move.y >= TABLE_SIZE) return false;
	if (field(move).type != Pieces::NONE && field(move).color == color) return false;

	int dx = move.x - pos.x;
	int dy = move.y - pos.y;
	if (std::abs(dx) > 1 || std::abs(dy) > 1 || (dx == 0 && dy == 0)) return false;

	Str kingCell = field(Vector2i(pos.x, pos.y));
	Str targetCell = field(move);
	field(Vector2i(pos.x, pos.y)) = Str(Pieces::NONE, Black);
	field(move) = Str(Pieces::NONE, Black);

	bool attacked = false;
	for (int i = 0; i < TABLE_SIZE && !attacked; i++) {
		for (int j = 0; j < TABLE_SIZE && !attacked; j++) {
			Vector2i enemy(i, j);
			Str piece = field(enemy);
			if (piece.type == Pieces::NONE || piece.color == color) continue;

			int ex = move.x - i;
			int ey = move.y - j;
			if (piece.type == Pieces::KING) {
				if (std::abs(ex) <= 1 && std::abs(ey) <= 1) attacked = true;
			}
			else if (piece.type == Pieces::PAWN) {
				// Пешка бьёт по диагонали вперёд, даже на пустую клетку.
				int dir = (piece.color == White) ? -1 : 1;
				if (std::abs(ex) == 1 && ey == dir) attacked = true;
			}
			else if (check_move(enemy, move, &field, !color)) {
				attacked = true;
			}
		}
	}

	field(Vector2i(pos.x, pos.y)) = kingCell;
	field(move) = targetCell;
	return !attacked;
}

bool KnightMove(Vector2i pos, Vector2i move, Field& field, bool color) {
	if (field(Vector2i(pos.x, pos.y)).type == Pieces::NONE) return false;
	if (field(Vector2i(pos.x, pos.y)).color != color) return false;
	if (move.x < 0 || move.y < 0 || move.x >= TABLE_SIZE || move.y >= TABLE_SIZE) return false;
	if (field(move).type != Pieces::NONE && field(move).color == color) return false;

	int x = move.x - pos.x;
	int y = move.y - pos.y;
	if ((std::abs(x) == 1 && std::abs(y) == 2) || (std::abs(x) == 2 && std::abs(y) == 1)) {
		return true;
	}
	return false;
}

bool PawnMove(Vector2i pos, Vector2i move, Field& field, bool color) {
	if (field(Vector2i(pos.x, pos.y)).type == Pieces::NONE) return false;
	if (field(Vector2i(pos.x, pos.y)).color != color) return false;
	if (move.x < 0 || move.y < 0 || move.x >= TABLE_SIZE || move.y >= TABLE_SIZE) return false;
	if (field(move).type != Pieces::NONE && field(move).color == color) return false;

	int x = move.x - pos.x;
	int y = move.y - pos.y;
	int dir = (field(pos).color == White) ? -1 : 1;
	bool targetEmpty = field(move).type == Pieces::NONE;

	if (x == 0 && y == dir && targetEmpty) return true;
	if (std::abs(x) == 1 && y == dir && !targetEmpty) return true;
	return false;
}

bool check_move(Vector2i pos, Vector2i move, Field* field, bool color) {
	if (pos == move) return false;
	if (pos.x < 0 || pos.y < 0 || pos.x >= TABLE_SIZE || pos.y >= TABLE_SIZE) return false;
	if (move.x < 0 || move.y < 0 || move.x >= TABLE_SIZE || move.y >= TABLE_SIZE) return false;

	switch ((*field)(pos).type) {
	case Pieces::NONE:
		return false;
	case Pieces::KING:
		return KingMove(pos, move, *field, color);
	case Pieces::KNIGHT:
		return KnightMove(pos, move, *field, color);
	case Pieces::PAWN:
		return PawnMove(pos, move, *field, color);
	case Pieces::BISHOP:
		return BishopMove(pos, move, *field, color);
	case Pieces::QUEEN:
		return QueenMove(pos, move, *field, color);
	case Pieces::ROOK:
		return RookMove(pos, move, *field, color);
	default:
		return false;
	}
}
