#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int TABLE_SIZE = 8;
constexpr int WIN_SIZE = 800;
constexpr int TEXTURE_SIZE = 100;
constexpr short STEP = WIN_SIZE / TABLE_SIZE;
constexpr bool White = true;
constexpr bool Black = false;

enum class Pieces {
	KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, NONE
};

struct Str {
	Str(Pieces type, bool color);
	Str();

	Pieces type;
	bool color;
};

class Field {
private:
	Str data[TABLE_SIZE][TABLE_SIZE];

public:
	Field();
	bool setFigure(Vector2i pos, bool color, Pieces pp);
	Str& operator()(Vector2i pos);
};

void Start(Field* ff) noexcept;
