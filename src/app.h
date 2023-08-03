#ifndef _H_APP_
#define _H_APP_

#include <iostream>

#include <string>

#include <map>

#include <memory>

#include <SFML/Graphics.hpp>


enum class Option { 
      NONE = -1
    , IN_FILE = 0
    , OUT_FILE 
    , OUT_DIR
    , DISABLE_WINDOW
    , CON_LOG
    , RED, GREEN, BLUE
    , SKIP_SAVE
    , HELP
};

enum class Mode { 
      NONE = -1
    , ENCODE = 0
    , DECODE
};

class App {

public:

    App(const uint32_t w, const uint32_t h, const std::string& inPath1, const std::string& inPath2, const std::string& outPath);

    ~App();

    int32_t load();

    int32_t run();

private:

    void render_next();

    bool save_img(const std::string& filename);

private:

    Mode                            m_mode;

    bool                            m_resized;

    uint32_t                        m_windowWidth;

    uint32_t                        m_windowHeight;

    bool                            m_running;

    bool                            m_reDraw;

    const std::string               m_imgInPath1;

    const std::string               m_imgInPath2;

    const std::string               m_imgOutPath;
    
    sf::RenderWindow                m_window;

    sf::Event                       m_event;

    std::unique_ptr<sf::Texture>    m_texture1;

    std::unique_ptr<sf::Texture>    m_texture2;

    sf::Sprite                      m_textureSprite;

};

#endif  //  _H_APP_
