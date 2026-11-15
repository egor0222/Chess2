#pragma once
#include "global.hpp"

bool check_move(Vector2i pos, Vector2i move, Field* field, bool color);

bool BishopMove(Vector2i pos, Vector2i move, Field& field, bool color);

bool RookMove(Vector2i pos, Vector2i move, Field& field, bool color);

bool QueenMove(Vector2i pos, Vector2i move, Field& field, bool color);

bool KingMove(Vector2i pos, Vector2i move, Field& field, bool color);

bool KnightMove(Vector2i pos, Vector2i move, Field& field, bool color);

bool PawnMove(Vector2i pos, Vector2i move, Field& field, bool color);