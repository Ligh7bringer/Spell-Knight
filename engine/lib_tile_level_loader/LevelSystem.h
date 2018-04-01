#pragma once

#include <SFML/Graphics.hpp>
#include <maths.h>
#include <memory>
#include <string>
#include <vector>

#define ls LevelSystem

class LevelSystem {
public:
    static void loadLevelFile(const std::string&, float tileSize = 100.0f);
    static void unload();
    static void render(sf::RenderWindow& window);

    typedef unsigned char Tile;
    struct groundTiles {
        enum types {
            GROUND1 = '1',
            GROUND2 = '2',
            GROUND3 = '3',
            GROUND4 = '4',
            GROUND5 = '5',
            GROUND6 = '6',
            GROUND7 = '7',
            GROUND8 = '8',
            GROUND9 = '9',
            INVISIBLE = '0',
            COIN = 'C',
            ITEM = 'G'
        };
    };
    struct platformTiles {
        enum types {
            PLATFORM1 = 'I',
            PLATFORM2 = 'O',
            PLATFORM3 = 'P',
            PLATFORM_MOVING = 'M',
            PLATFORM_FALLING = 'F'
        };
    };
    struct baseTiles{
        enum types {
            EMPTY = 'x',
            START = 'S',
            END = 'E',
            ENEMY = 'N',
            DEADFALL = 'D',
            WAYPOINT = '+'
        };
    };
    struct enemyTiles {
        enum types {
            EYE = 'e',
            SLIME = 's',
            PLANT = 'p',
            BIRD = 'b'
        };
    };

    static Tile getTile(sf::Vector2ul);

    static Tile getGroundTile(sf::Vector2ul);

    static Tile getTileAt(sf::Vector2f);

    static Tile getGroundTileAt(sf::Vector2f);

    static std::vector<sf::Vector2ul> getGroundTiles();

    static bool isOnGrid(sf::Vector2f);

    static size_t getWidth();

    static size_t getHeight();

    static sf::Vector2f getTilePosition(sf::Vector2ul);

    static std::vector<sf::Vector2ul> findTiles(Tile);

    static std::vector<sf::Vector2f> getPosition(Tile t);

    //static sf::Color getColor(Tile t);
    static sf::IntRect getRect(Tile t);

    //static void setColor(Tile t, sf::Color c);

    static void setOffset(const sf::Vector2f& _offset);

    static const sf::Vector2f& getOffset();

    static float getTileSize();

protected:
    static std::unique_ptr<Tile[]> _tiles;
    static size_t _width;
    static size_t _height;
    static sf::Vector2f _offset;
    static std::unique_ptr<Tile[]> _groundTiles;

    static std::vector<std::unique_ptr<sf::Sprite>> _sprites;

    static void buildSprites(bool optimise = true);

    static float _tileSize; // for rendering
    //static std::map<Tile, sf::Color> _colours;
    static std::map<LevelSystem::Tile, sf::IntRect> _rects;

    static sf::Texture _spritesheet;
    static std::vector<sf::Sprite> _texs;

private:
    LevelSystem() = delete;

    ~LevelSystem() = delete;
};
