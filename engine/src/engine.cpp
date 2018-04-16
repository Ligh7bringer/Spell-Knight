#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>
#include "../lib_texture_manager/texture_manager.h"
#include "../../src/Log.h"
#include "../lib_input_manager/input_manager.h"
#include "../lib_settings_parser/settings_parser.h"
#include "../lib_audio_manager/audio_manager.h"
#include "../../src/config.h"

using namespace sf;
using namespace std;

Scene* Engine::_activeScene = nullptr;
std::string Engine::_gameName;
sf::Event Engine::_event;
std::vector<char> Engine::_keysText;
std::vector<sf::Keyboard::Key> Engine::_keys;
static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;

bool Engine::_fullscreen = false;
sf::Vector2u Engine::_currentResolution;

structlog LOGCFG = {};

void Loading_update(float dt, const Scene* const scn) {
  //  cout << "Eng: Loading Screen\n";
  if (scn->isLoaded()) {
    LOG(INFO) << "Eng: Exiting Loading Screen";
    loading = false;
  } else {
    loadingspinner += 220.0f * dt;
    loadingTime += dt;
  }
}
void Loading_render() {
  // cout << "Eng: Loading Screen Render\n";
  static CircleShape octagon(80, 8);
  octagon.setOrigin(80, 80);
  octagon.setRotation(loadingspinner);
  octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
  octagon.setFillColor(Color(255,255,255,min(255.f,40.f*loadingTime)));
  static Text t("Loading", *Resources::get<sf::Font>("RobotoMono-Regular.ttf"));
  t.setFillColor(Color(255,255,255,min(255.f,40.f*loadingTime)));
  t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.4f,0.3f));
  Renderer::queue(&t);
  Renderer::queue(&octagon);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  {
    frametimes[++ftc] = dt;
    static string avg = _gameName + " FPS:";
    if (ftc % 60 == 0) {
      double davg = 0;
      for (const auto t : frametimes) {
        davg += t;
      }
      davg = 1.0 / (davg / 255.0);
      _window->setTitle(avg + toStrDecPt(2, davg));
    }
  }

  if (loading) {
    Loading_update(dt, _activeScene);
  } else if (_activeScene != nullptr) {
	  if (!_pause) {
		  Physics::update(dt);
		  _activeScene->Update(dt);
	  }
  }
}

void Engine::Render(RenderWindow& window) {
  if (loading) {
    Loading_render();
  } else if (_activeScene != nullptr) {
    _activeScene->Render();
  }

  Renderer::render();
}

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

sf::View& Engine::getCurrentView() {
  return _activeScene->getView();
}

void Engine::setView(const sf::View& view) {
  _activeScene->setView(view);
}
Event event;
bool Engine::_pause = false;
void Engine::Start(unsigned int width, unsigned int height,
                   const std::string& gameName, Scene* scn) {
  Config::setCurrentLanguage(Config::getSetting("language"));
  _currentResolution.x = width;
  _currentResolution.y = height;

  //set up logging:
  //display logging level
  LOGCFG.headers = true; 
  //min logging level 
  LOGCFG.level = DEBUG;

  //initialise input manager
  InputManager::initialise();
  
  //initialise texture manager
  TextureManager::initialise();

  AudioManager::initialise();

  RenderWindow window(VideoMode(width, height), gameName, sf::Style::Close | sf::Style::Resize);

  _gameName = gameName;
  _window = &window;

  auto fullscr_str = Config::getSetting("fullscreen");
  auto fullscr = stoi(fullscr_str);
  _currentResolution = Vector2u(width, height);

  if(fullscr != 0) {
    toggleFullscreen();
  }

  Renderer::initialise(window);
  Physics::initialise();
  ChangeScene(scn);
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      _keysText.clear();
      _keys.clear();
      if (event.type == Event::Closed) {
        window.close();
      }
    
      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P))
      {
        _pause = !_pause;
		_activeScene->Render();
      }
      //pause if the window loses focus
      if(event.type == sf::Event::LostFocus) {
        _pause = true;
      }
      //unpause if it regains focus
      if(event.type == sf::Event::GainedFocus) {
        _pause = false;
      }
      if(event.type == Event::Resized) {
          LOG(DEBUG) << "RESIZED";
        //resize view when window is resized so textures are not stretched
        auto old = _window->getView();
        auto oldPos = Vector2f(old.getViewport().left, old.getViewport().top);
        View v = View(FloatRect(oldPos.x, oldPos.y, event.size.width, event.size.height));
        Renderer::setView(v);
        _activeScene->setView(v);
      }
      //capture the pressed keys in order to figure out what key has been pressed for the key bindings menu
      //only happens in the options scene
      if((event.type == Event::TextEntered || event.type == Event::KeyPressed) && _activeScene->_sceneID.compare("options") == 0) {
          _keys.push_back(event.key.code);
          //LOG(DEBUG) << "IN OPTIONS SCENE";
      }
    }

	window.clear();
	Update();
	Render(window);
	window.display();

  }
  if (_activeScene != nullptr) {
    _activeScene->UnLoad();
    _activeScene = nullptr;
  }
  window.close();
  Physics::shutdown();
  // Render::shutdown();
}

//this is to be used only in the menu scene!
void Engine::Exit() {
  _activeScene->UnLoad();
  _window->close();
}

std::shared_ptr<Entity> Scene::makeEntity() {
  auto e = make_shared<Entity>(this);
  ents.list.push_back(e);
  return std::move(e);
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(Scene* s) {
  LOG(INFO) << "Eng: changing scene: " << s;
  auto old = _activeScene;
  _activeScene = s;

  if (old != nullptr) {
    old->UnLoad(); // todo: Unload Async
  }

  if (!s->isLoaded()) {
    LOG(INFO) << "Eng: Entering Loading Screen";
    loadingTime = 0;
    _activeScene->Load();
    loading = true;
  }
}

sf::Event Engine::getEvent() {
  return _event;
}

std::vector<char> &Engine::getKeysText() {
  return _keysText;
}


void Engine::toggleFullscreen() {
  _fullscreen = !_fullscreen;
  if(_fullscreen) {
    _window->create(VideoMode(_currentResolution.x, _currentResolution.y), _gameName, sf::Style::Fullscreen);
  } else {
    _window->create(VideoMode(_currentResolution.x, _currentResolution.y), _gameName, sf::Style::Close | sf::Style::Resize);
  }
}

bool Engine::isFullscreen() {
  return _fullscreen;
}

void Engine::setResolution(const sf::Vector2u &res) {
  _currentResolution = res;

  Config::setSetting("width", to_string(res.x));
  Config::setSetting("height", to_string(res.y));

  _window->create(VideoMode(res.x, res.y), _gameName, _fullscreen ? sf::Style::Fullscreen : sf::Style::Close | sf::Style::Resize);
}

std::vector<sf::Keyboard::Key> &Engine::getKeys() {
  return _keys;
}

bool Engine::isPaused() {
      return _pause;
}

void Scene::Update(const double& dt) { 
  ents.update(dt); 
}

void Scene::Render() { 
  ents.render();
}

bool Scene::isLoaded() const {
  {
    std::lock_guard<std::mutex> lck(_loaded_mtx);
    // Are we already loading asynchronously?
    if (_loaded_future.valid() // yes
        &&                     // Has it finished?
        _loaded_future.wait_for(chrono::seconds(0)) ==
            future_status::ready) {
      // Yes
      _loaded_future.get();
      _loaded = true;
    }
    return _loaded;
  }
}
void Scene::setLoaded(bool b) {
  {
    std::lock_guard<std::mutex> lck(_loaded_mtx);
    _loaded = b;
  }
}

void Scene::UnLoad() {
  ents.list.clear();
  setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

namespace timing {
// Return time since Epoc
long long now() {
  return std::chrono::high_resolution_clock::now()
      .time_since_epoch()
      .count();
}
// Return time since last() was last called.
long long last() {
  auto n = now();
  static auto then = now();
  auto dt = n - then;
  then = n;
  return dt;
}
} // namespace timing

sf::View& Scene::getView() {
  return _view;
}

void Scene::setView(const sf::View& view) {
  _view = view;
}

Scene::~Scene() { UnLoad(); }
