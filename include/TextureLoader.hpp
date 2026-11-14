#pragma once

#include "global.hpp"
#include <string>

struct TextureContainerBucket {
	std::string name;
	Texture* texture = nullptr;
};

using Tcb = TextureContainerBucket;

class TextureLoader {
public:
	void init();
	~TextureLoader();
	Texture* operator()(std::string name);

private:
	Tcb* data = nullptr;
	size_t size = 0;
	bool inited = false;

	void getData();
};