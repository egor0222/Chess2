#include "TextureLoader.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>

void TextureLoader::init() {
	inited = true;
	getData();
}

TextureLoader::~TextureLoader() {
	for (size_t i = 0; i < size; i++) {
		delete data[i].texture;
	}
	delete[] data;
}

Texture* TextureLoader::operator()(std::string name) {
	if (!inited) return nullptr;
	name.append(".png");
	for (size_t i = 0; i < size; i++) {
		if (data[i].name == name) return data[i].texture;
	}
	std::cout << "File not found: " << name << std::endl;
	return nullptr;
}

void TextureLoader::getData() {
	std::filesystem::path imageDirectory = std::filesystem::current_path() / "images";
	if (!std::filesystem::exists(imageDirectory) || !std::filesystem::is_directory(imageDirectory)) {
		std::cout << "Not derictory" << std::endl;
		std::abort();
	}
	for (const auto& entry : std::filesystem::directory_iterator(imageDirectory)) {
		this->size++;
	}

	data = new Tcb[this->size];
	size_t iter = 0;
	for (const auto& entry : std::filesystem::directory_iterator(imageDirectory)) {
		if (entry.is_regular_file()) {
			data[iter].name = entry.path().filename().generic_string();
			data[iter].texture = new Texture();
			data[iter].texture->loadFromFile(entry.path().generic_string());
			iter++;
		}
	}
}