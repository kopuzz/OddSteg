#ifndef _H_ODD_STEG
#define _H_ODD_STEG

#include <iostream>

#include <string>

#include <memory>

#include <SFML/Graphics.hpp>

enum class Channel { NONE = -1, RED = 0, GREEN, BLUE };

void odd_steg_encode(std::unique_ptr<sf::Texture>* texture1, const std::unique_ptr<sf::Texture>* texture2, const Channel channel, const bool odd);

void odd_steg_decode(std::unique_ptr<sf::Texture>* texture1, const Channel channel, const bool odd);

#endif  //  _H_ODD_STEG
