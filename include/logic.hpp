#pragma once
#include "global.hpp"

bool rightMove(Vector2i pos, Vector2i move, Field* field);

bool BishopMove(Vector2i pos, Vector2i move, Field& field);

bool RookMove(Vector2i pos, Vector2i move, Field& field);

bool QueenMove(Vector2i pos, Vector2i move, Field& field);

bool KingMove(Vector2i pos, Vector2i move, Field& field);

bool KnightMove(Vector2i pos, Vector2i move, Field& field);

bool PawnMove(Vector2i pos, Vector2i move, Field& field);