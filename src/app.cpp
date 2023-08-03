#include "app.h"

#include "oddsteg.h"

App::App(const uint32_t w, const uint32_t h, const std::string& inPath1, const std::string& inPath2, const std::string& outPath)
    : m_window(sf::VideoMode(w, h), "OddSTEG")
    , m_texture1(std::make_unique<sf::Texture>())
    , m_texture2(std::make_unique<sf::Texture>())
    , m_imgInPath1(inPath1)
    , m_imgInPath2(inPath2)
    , m_imgOutPath(outPath) {

    m_mode = Mode::NONE;
    m_windowWidth = w;
    m_windowHeight = h;
    m_resized = false;
    m_running = false;
    m_reDraw = false;
    m_event = {};
    m_textureSprite = {};   
}

App::~App() {

}

int32_t App::load() {
    int32_t err = 0;
    if (!m_texture1->loadFromFile(m_imgInPath1)) {
        err = 5;
        return err;
    }

    if (!m_texture2->loadFromFile(m_imgInPath2)) {
        err = 6;
        return err;
    }

    const sf::Vector2u maxWindowSize = { 1000, 800 };
    sf::Vector2u newWindowSize = m_texture1->getSize();
    
    if (newWindowSize.x > maxWindowSize.x)
        newWindowSize.x = maxWindowSize.x;

    if (newWindowSize.y > maxWindowSize.y)
        newWindowSize.y = maxWindowSize.y;

    m_window.setSize(newWindowSize);
    m_resized = true;

    m_textureSprite.setTexture(*m_texture1);
    m_textureSprite.setPosition(1.f, 1.f);

    return err;
}

int32_t App::run() {
    m_running = true;
    m_reDraw = true;
    int32_t err = 0;
    while (m_running) {
        while(m_window.pollEvent(m_event)) {
            if (m_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                m_reDraw = false;
                m_running = false;
                break;
            }
            
            else if (m_event.type == sf::Event::Resized || m_resized) {
                m_window.setView(sf::View(sf::FloatRect(0, 0, m_event.size.width, m_event.size.height)));
                m_resized = false;
                m_reDraw = true;
                break;
            }

            switch (m_event.key.code) {
            case sf::Keyboard::E:
                m_mode = Mode::ENCODE;
                break;
            
            case sf::Keyboard::D:
                m_mode = Mode::DECODE;
                break;

            default:
                break;
            }

        }

        switch (m_mode) {
        case Mode::ENCODE:
            odd_steg_encode(&m_texture1, &m_texture2, Channel::RED, true);  //  in-Original, in-ToEmbed, channel to embed within, odd = !even
            if (!save_img("/encoded-output.png"))
                return 10;

            m_reDraw = true;
            m_mode = Mode::NONE;
            break;

        case Mode::DECODE:
            odd_steg_decode(&m_texture1, Channel::RED, true);
            if (!save_img("/decoded-output.png"))
                return 11;

            m_reDraw = true;
            m_mode = Mode::NONE;
            break;

        case Mode::NONE:
            break;
                
        default:
            break;
        }

        if (m_reDraw) {
            render_next();
            m_reDraw = false;
        }
    }

    return err;
}

void App::render_next() {
    m_window.clear(sf::Color::Black);
    m_window.draw(m_textureSprite);
    m_window.display();
}

bool App::save_img(const std::string& filename) {
    const sf::Image& out = m_texture1->copyToImage();
    if (!out.saveToFile(m_imgOutPath + filename))
        return false;
    
    return true;
}
