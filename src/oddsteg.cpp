#include "oddsteg.h"

void odd_steg_encode(std::unique_ptr<sf::Texture>* texture1, const std::unique_ptr<sf::Texture>* texture2, const Channel channel, const bool odd) {
    sf::Image originalImg = texture1->get()->copyToImage();
    const sf::Image imgToEmbed = texture2->get()->copyToImage();

    const sf::Vector2u originalImgSize = originalImg.getSize();
    const sf::Vector2u embedImgSize = imgToEmbed.getSize();

    if (embedImgSize.x > originalImgSize.x || embedImgSize.y > originalImgSize.y)  
        return;

    sf::Color originalColorBuffer = sf::Color::Red;
    sf::Color embedColorBuffer = sf::Color::Red;
    uint32_t x = 0, y = 0;
    for (x = 0; x < embedImgSize.x; ++x) {
        for (y = 0; y < embedImgSize.y; ++y) {
            embedColorBuffer = imgToEmbed.getPixel(x, y);
            if (odd && embedColorBuffer == sf::Color::White) {
                originalColorBuffer = originalImg.getPixel(x, y);
                switch (channel) {
                case Channel::RED:
                    if (originalColorBuffer.r % 2 != 1)
                        --originalColorBuffer.r;
                    break;
                
                case Channel::GREEN:
                    if (originalColorBuffer.g % 2 != 1)
                        --originalColorBuffer.g;
                    break;

                case Channel::BLUE:
                    if (originalColorBuffer.b % 2 != 1)
                        --originalColorBuffer.b;
                    break;

                case Channel::NONE:
                    return;
                
                default:
                    break;
                }

                originalImg.setPixel(x, y, originalColorBuffer);
            }
        }
    }

    texture1->get()->loadFromImage(originalImg);
}

void odd_steg_decode(std::unique_ptr<sf::Texture>* texture1, const Channel channel, const bool odd) {
    sf::Image originalImg = texture1->get()->copyToImage();
    const sf::Vector2u originalImgSize = originalImg.getSize();

    sf::Color originalColorBuffer = sf::Color::Red;
    uint32_t x = 0, y = 0;
    for (x = 0; x < originalImgSize.x; ++x) {
        for (y = 0; y < originalImgSize.y; ++y) {
            originalColorBuffer = originalImg.getPixel(x, y);
            switch (channel) {
            case Channel::RED:
                if (originalColorBuffer.r % 2 == 0)
                    originalColorBuffer = sf::Color::White;
                else
                    originalColorBuffer = sf::Color::Black;
                break;
            
            case Channel::GREEN:
                if (originalColorBuffer.g % 2 == 0)
                    originalColorBuffer = sf::Color::White;
                else
                    originalColorBuffer = sf::Color::Black;
                break;

            case Channel::BLUE:
                if (originalColorBuffer.b % 2 == 0)
                    originalColorBuffer = sf::Color::White;
                else
                    originalColorBuffer = sf::Color::Black;
                break;

            case Channel::NONE:
                return;
            
            default:
                break;
            }

            originalImg.setPixel(x, y, originalColorBuffer);
        }
    }

    texture1->get()->loadFromImage(originalImg);
}
