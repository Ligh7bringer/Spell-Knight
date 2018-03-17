#include "parallax_background.h"
#include "../engine/src/system_renderer.h"
#include "Log.h"
#include "../engine/lib_texture_manager/TextureManager.h"
#include <engine.h>

using namespace sf;
using namespace std;

Texture bg, trees, ground;

/*
* Allows the creation of parallax backgrounds. They consist of layers and every layer moves at different speed 
* to create an effect of depth.
*/

ParallaxBackground::ParallaxBackground(const sf::Vector2f& size) : _target(Vector2f(0.f, 0.f)) {
    //this variable allows the sprites to be repeated. Each sprite's width is multiplied by this factor which creates a
    //scrolling background. A big multiplie may reduce performance and fps.
    _widthMultiplier = 5;
    //size will be used to set origins and positions
    _size = size;
}

//updates each layer
void ParallaxBackground::update(double dt) {
    //iterate over the layers
    for (auto iter = _layers.begin(); iter != _layers.end(); iter++) {
        //get the parallax coefficient 
        float coefficient = iter->first;
        //get the actual image
        auto layer = iter->second;
        //to create the effect a view is needed for every layer
        View v;
        //set the view position and size
        v.reset(FloatRect(0, 0, _size.x, _size.y));
        //set the center, change the x position by multiplying it by the parallax coefficient
        v.setCenter(Vector2f(coefficient * _target.x, 0));
        //set the view
        Renderer::setView(v);
        //unfortunately the rendering has to happen in the update
        Engine::GetWindow().draw(*layer);
    }
}

void ParallaxBackground::render() {}

//adds another "layer" to the background
void ParallaxBackground::addLayer(float coeff, const string& tex) {
    //load texture and store it in a shared pointer! not using pointers results in white squares 
    _currTexture = make_shared<Texture>(TextureManager::getTexture(tex));
    //set repeated to true in order to have a scrolling background
    _currTexture->setRepeated(true);
    //add texture to the vector of textures which might not be needed at all

    _textures.push_back(_currTexture);
    //initilise sprite
    shared_ptr<Sprite> sprite = make_shared<Sprite>();    
    //set its texture
    sprite->setTexture(*_textures.back());
    //multiply width by the mutiplier to create a repeated background
    sprite->setTextureRect(IntRect(0, 0, (int)_size.x * _widthMultiplier, (int)_size.y));
    //set origin to the centre of the image
    sprite->setOrigin(_size / 2.f);

    //and finally add the layer to the vector of layers 
    _layers.push_back(std::pair<float, shared_ptr<Sprite>>(coeff, sprite));
    LOG(INFO) << "Adding a new layer to Parallax Background with coefficient of " << coeff;
}

//this is used to pass the main view's centre to this class
void ParallaxBackground::setTarget(const Vector2f& target) {
    _target = target;
}