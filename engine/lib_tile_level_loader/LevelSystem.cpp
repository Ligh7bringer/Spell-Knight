#include "LevelSystem.h"
#include <fstream>
#include "../../src/Log.h"

using namespace std;
using namespace sf;


std::map<LevelSystem::Tile, sf::IntRect> LevelSystem::_rects{
	{ groundTiles::GROUND1, IntRect(0, 0, 32, 32) },
	{ groundTiles::GROUND2, IntRect(32, 64, 32, 32) },
	{ groundTiles::GROUND3, IntRect(64, 64, 32, 32) },
	{ groundTiles::GROUND4, IntRect(96, 64, 32, 32) },
	{ groundTiles::GROUND5, IntRect(0, 96, 32, 32) },
	{ groundTiles::GROUND6, IntRect(32, 96, 32, 32) },
	{ groundTiles::GROUND7, IntRect(64, 96, 32, 32) },
	{ groundTiles::GROUND8, IntRect(96, 96, 32, 32) },
	{ groundTiles::GROUND9, IntRect(128, 0, 32, 32) },
	{ platformTiles::PLATFORM1, IntRect(64, 0, 32, 32) },
	{ platformTiles::PLATFORM2, IntRect(96, 0, 32, 32) },
	{ platformTiles::PLATFORM3, IntRect(0, 32, 32, 32) },
	{ baseTiles::END, IntRect(0,32, 32, 32) },
	{groundTiles::INVISIBLE, IntRect(0, 64, 32,32)},
	{groundTiles::COIN, IntRect(0, 0, 0, 0)},
	{groundTiles::ITEM, IntRect(0, 0, 0, 0)},
	{baseTiles::DEADFALL, IntRect(64,32,32,32)}
};

std::vector<sf::Sprite> LevelSystem::_texs;
sf::Texture LevelSystem::_spritesheet;


sf::IntRect LevelSystem::getRect(LevelSystem::Tile t) {
  auto it = _rects.find(t);
  return _rects[t];
}


std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;
std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_groundTiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;

float LevelSystem::_tileSize(32.f);
Vector2f LevelSystem::_offset(0.0f, 30.0f);
// Vector2f LevelSystem::_offset(0,0);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
  _tileSize = tileSize;
  size_t w = 0, h = 0;
  string buffer;

  // Load in file to buffer
  ifstream f(path);
  if (f.good()) {
    f.seekg(0, std::ios::end);
    buffer.resize(f.tellg());
    f.seekg(0);
    f.read(&buffer[0], buffer.size());
    f.close();
  } else {
    LOG(ERROR) << "Couldn't open level file: " << path;
  }

  std::vector<Tile> temp_tiles;
  std::vector<Tile> tempGroundTiles;
  int widthCheck = 0;
  for (int i = 0; i < buffer.size(); ++i) {
    const char c = buffer[i];
	if (c == '\0'){
		break;
	}
	if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c=='I'||c=='O'||c=='P' || c=='0') {
		tempGroundTiles.push_back((Tile)c);
	}
    if (c == '\n') { // newline
      if (w == 0) {  // if we haven't written width yet
        w = i;       // set width
      } else if (w != (widthCheck - 1)) {

        LOG(ERROR) << "non uniform width:" << to_string(h) << " " << path;
      }
      widthCheck = 0;
      h++; // increment height
    } else {
      temp_tiles.push_back((Tile)c);
    }
    ++widthCheck;
  }

  if (temp_tiles.size() != (w * h)) {
    LOG(ERROR) << "Can't parse level file" << path;
  }
  _tiles = std::make_unique<Tile[]>(w * h);
  _groundTiles = std::make_unique<Tile[]>(w*h);

  _width = w; // set static class vars
  _height = h;
  std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
  std::copy(tempGroundTiles.begin(), tempGroundTiles.end(), &_groundTiles[0]);
  cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
  buildSprites(true);
}

void LevelSystem::buildSprites(bool optimise) {
  _sprites.clear();

  if(!_spritesheet.loadFromFile("res/img/tiles5.png")) {
    LOG(ERROR) << "Couldn't load level system spritesheet!";
  }

  struct tp {
    sf::Vector2f p;
    sf::Vector2f s;
    sf::Sprite sprite;
    sf::Texture tex;
  };
  vector<tp> tps;
  const auto tls = Vector2f(_tileSize, _tileSize);
    //loop through all the tiles and find the tiles which aren't empty tiles
  for (size_t y = 0; y < _height; ++y) {
    for (size_t x = 0; x < _width; ++x) {
      Tile t = getTile({x, y});
      if (t == baseTiles::EMPTY) {
        continue;
      }

      tp temp;
      temp.p = getTilePosition({x, y});
      temp.s = tls;
      temp.sprite.setTexture(_spritesheet);
      temp.sprite.setTextureRect(getRect(t));
      tps.push_back(temp);

    }
  }

  const auto nonempty = tps.size();

  // If tile of the same type are next to each other,
  // We can use one large sprite instead of two.
  if (optimise && nonempty) {

    vector<tp> tpo;
    tp last = tps[0];
    size_t samecount = 0;

    for (size_t i = 1; i < nonempty; ++i) {
      // Is this tile compressible with the last?
      bool same = ((tps[i].p.y == last.p.y) &&
                   (tps[i].p.x == last.p.x + (tls.x * (1 + samecount))) &&
        tps[i].sprite.getTexture() == last.sprite.getTexture() &&
        tps[i].sprite.getTextureRect() == last.sprite.getTextureRect());
      if (same) {
        ++samecount; // Yes, keep going
      } else {
        if (samecount) {
          last.s.x = (1 + samecount) * tls.x; // Expand tile
        }
        // write tile to list
        tpo.push_back(last);
        samecount = 0;
        last = tps[i];
      }
    }
    // catch the last tile
    if (samecount) {
      last.s.x = (1 + samecount) * tls.x;
      tpo.push_back(last);
    }

    // No scan down Y, using different algo now that compressible blocks may
    // not be contiguous
    const auto xsave = tpo.size();
    samecount = 0;
    vector<tp> tpox;
    for (size_t i = 0; i < tpo.size(); ++i) {
      last = tpo[i];
      for (size_t j = i + 1; j < tpo.size(); ++j) {
        bool same = ((tpo[j].p.x == last.p.x) && (tpo[j].s == last.s) &&
                     (tpo[j].p.y == last.p.y + (tls.y * (1 + samecount))) &&
                     tpo[j].sprite.getTexture() == last.sprite.getTexture() &&
                     tpo[j].sprite.getTextureRect() == last.sprite.getTextureRect());
        if (same) {
          ++samecount;
          tpo.erase(tpo.begin() + j);
          --j;
        }
      }
      if (samecount) {
        last.s.y = (1 + samecount) * tls.y; // Expand tile
      }
      // write tile to list
      tpox.push_back(last);
      samecount = 0;
    }

    tps.swap(tpox);
  }

  for (auto& t : tps) {
    auto s = make_unique<sf::RectangleShape>();
    //auto s = t.sprite;
    s->setPosition(t.p);
    s->setSize(t.s);
    s->setTexture(t.sprite.getTexture());
      s->setTextureRect((t.sprite.getTextureRect()));
    _sprites.push_back(move(s));
  }

  cout << "Level with " << (_width * _height) << " Tiles, With " << nonempty
       << " Not Empty, using: " << _texs.size() << " Sprites\n";
}

void LevelSystem::render(RenderWindow& window) {
    for (auto& t : _sprites) {
        window.draw(*t);
    }
}

LevelSystem::Tile LevelSystem::getTile(sf::Vector2ul p) {
  if (p.x > _width || p.y > _height) {
    LOG(ERROR) << "Tile out of range: " << to_string(p.x) << "," << to_string(p.y) << ")";
  }
  return _tiles[(p.y * _width) + p.x];
}

LevelSystem::Tile LevelSystem::getGroundTile(sf::Vector2ul p) {
	if (p.x > _width || p.y > _height) {
		LOG(ERROR) << "Tile out of range: " << to_string(p.x) << "," <<	to_string(p.y) << ")";
	}
	auto v = vector<sf::Vector2ul>();
	for (size_t i = 0; i < _width * _height; ++i) {
		if (_tiles[i] == '1' || _tiles[i] == '2' || _tiles[i] == '3' || _tiles[i] == '4' || _tiles[i] == '5' || _tiles[i] == '6'
			|| _tiles[i] == '7' || _tiles[i] == '8' || _tiles[i] == '9' || _tiles[i] == '0' || _tiles[i] == 'I' || _tiles[i] == 'O' || _tiles[i] == 'P') {
			return _tiles[(p.y * _width) + p.x];
		}
	}
}

size_t LevelSystem::getWidth() { return _width; }

size_t LevelSystem::getHeight() { return _height; }

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p) {
  return (Vector2f(p.x, p.y) * _tileSize) + _offset;
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(LevelSystem::Tile type) {
  auto v = vector<sf::Vector2ul>();
  for (size_t i = 0; i < _width * _height; ++i) {
    if (_tiles[i] == type) {
      v.push_back({i % _width, i / _width});
    }
  }

  return v;
}
std::vector<sf::Vector2ul> LevelSystem::getGroundTiles()
{
	auto v = vector<sf::Vector2ul>();
	for (size_t i = 0; i < _width * _height; ++i) {
		if (_tiles[i] == '1' || _tiles[i] == '2' || _tiles[i] == '3' || _tiles[i] == '4' || _tiles[i] == '5' || _tiles[i] == '6'
			|| _tiles[i] == '7' || _tiles[i] == '8' || _tiles[i] == '9'|| _tiles[i] =='0' || _tiles[i]== 'I' || _tiles[i] == 'O'|| _tiles[i] == 'P') {
			v.push_back({ i % _width, i / _width });
		}
	}
	//cout << v.size() << endl;
	return v;
}

LevelSystem::Tile LevelSystem::getTileAt(Vector2f v) {
  auto a = v - _offset;
  if (a.x < 0 || a.y < 0) {

    LOG(ERROR) << "Tile out of range ";
  }
  return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

LevelSystem::Tile LevelSystem::getGroundTileAt(Vector2f v)
{
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		LOG(ERROR) << "Tile out of range ";
	}
	return getGroundTile(Vector2ul((v - _offset) / (_tileSize)));
}



bool LevelSystem::isOnGrid(sf::Vector2f v) {
  auto a = v - _offset;
  if (a.x < 0 || a.y < 0) {
    return false;
  }
  auto p = Vector2ul((v - _offset) / (_tileSize));
  if (p.x > _width || p.y > _height) {
    return false;
  }
  return true;
}

void LevelSystem::setOffset(const Vector2f& _offset) {
  LevelSystem::_offset = _offset;
  buildSprites();
}

void LevelSystem::unload() {
  cout << "LevelSystem unloading\n";
  _sprites.clear();
  _texs.clear();
  _tiles.reset();
  _width = 0;
  _height = 0;
  _offset = {0, 0};
}

const Vector2f& LevelSystem::getOffset() { return _offset; }

float LevelSystem::getTileSize() { return _tileSize; }