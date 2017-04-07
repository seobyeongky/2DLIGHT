#pragma once
/*
global.h*/
#include <SFML\Graphics.hpp>
#include "loadImage.h"
#include "applyBody.h"

extern sf::Font font;
extern sf::RenderWindow window;
extern b2World* world;
extern applyBody bodyApplier;
extern loadImage load_Image;
