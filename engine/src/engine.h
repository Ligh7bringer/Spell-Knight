#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include <future>
#include <maths.h>
#include <mutex>
#include <string>
#include "../../src/misc/parallax_background.h"

class Scene {
public:
  struct less_than_y {
    inline bool operator() (const sf::Vector2f& left, const sf::Vector2f& right)
    {
        return (left.y < right.y);
    }
  };

  Scene() = default;
  virtual ~Scene();
  virtual void Load() = 0;
  virtual void LoadAsync();
  virtual void UnLoad();
  virtual void Update(const double& dt);
  virtual void Render();
  bool isLoaded() const;
  std::shared_ptr<Entity> makeEntity();
  sf::View& getView();
  void setView(const sf::View& view);

  EntityManager ents;

  std::string _sceneID = "";

protected:
  void setLoaded(bool);
  sf::View _view;
  ParallaxBackground _parBackground;
  
private:
  mutable bool _loaded;
  mutable std::future<void> _loaded_future;
  mutable std::mutex _loaded_mtx;
};

class Engine {
public:
  Engine() = delete;
  static void Start(unsigned int width, unsigned int height,
                    const std::string& gameName, Scene* scn);
  static void ChangeScene(Scene*);
  static sf::RenderWindow& GetWindow();
  static sf::Vector2u getWindowSize();
  static void setVsync(bool b);
  static sf::View& getCurrentView();
  static void setView(const sf::View& view);
  static bool _pause;
  static void Exit();
  static sf::Event getEvent();
  static std::vector<char>& getKeysText();
  static std::vector<sf::Keyboard::Key>& getKeys();
  static bool isPaused();
  static void toggleFullscreen();
  static bool isFullscreen();
  static void setResolution(const sf::Vector2u& res);

    static const sf::Vector2u &getResolution();

private:
  static Scene* _activeScene;
  static std::string _gameName;
  static void Update();
  static void Render(sf::RenderWindow& window);
  static sf::Event _event;
  static std::vector<char> _keysText;
  static bool _fullscreen;
  static sf::Vector2u _currentResolution;
  static std::vector<sf::Keyboard::Key> _keys;
};

namespace timing {
// Return time since Epoc
long long now();
// Return time since last() was last called.
long long last();
} // namespace timing