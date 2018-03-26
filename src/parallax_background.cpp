#include "parallax_background.h"
#include "../engine/src/system_renderer.h"
#include "Log.h"
#include "../engine/lib_texture_manager/TextureManager.h"
#include <engine.h>

using namespace sf;
using namespace std;

Texture bg, trees, ground;

/*
* Allows the creation of parallax backgrounds. They consist of layers and every layer 
* moves at different speed to create an effect of depth.
*/

Vector2f mainViewSize, mainViewCentre, mainViewPosition;
View mainView;

ParallaxBackground::ParallaxBackground(const sf::Vector2f& size) : _target(Vector2f(0.f, 0.f)) {
    //this variable allows the sprites to be repeated. Each sprite's width is multiplied by this factor which creates a
    //scrolling background. A big multiplie may reduce performance and fps.
    _widthMultiplier = 10;
    //set size
    _size = size;
}

//updates each layer
void ParallaxBackground::update(double dt) {
    //get the current view size and centre
    mainView = Engine::getCurrentView();
    mainViewSize = mainView.getSize();
    mainViewCentre = mainView.getCenter(); 
    mainViewPosition = Vector2f(mainView.getViewport().left, mainView.getViewport().top);
}

void ParallaxBackground::render() {
    
    //iterate over the layers
    for (auto iter = _layers.begin(); iter != _layers.end(); iter++) {
        //get the parallax coefficient 
        float coefficient = iter->first;
        //get the actual image
        auto layer = iter->second;
        //to create the effect a view is needed for every layer
        View v; 
        //set the view position and size
        //use the size of the current view so that when the window is resized sprites are not stretched
        v.reset(FloatRect(mainViewPosition.x, mainViewPosition.y, mainViewSize.x, mainViewSize.y));
        //set the center, change the x position by multiplying it by the parallax coefficient
        v.setCenter(Vector2f(coefficient * mainViewCentre.x, mainViewCentre.y));

        //set the view
        Renderer::setView(v);
        //render
        Engine::GetWindow().draw(*layer);
    }

    //don't forget to set the view back to the main view!!
    Renderer::setView(mainView);
}

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
    sprite->setOrigin(Vector2f(_size.x / 2.f, 0));
    //and finally add the layer to the vector of layers 
    _layers.push_back(std::pair<float, shared_ptr<Sprite>>(coeff, sprite));
    LOG(INFO) << "Adding a new layer to Parallax Background with coefficient of " << coeff;
}

//sets the number of times the background should be repeated
void ParallaxBackground::setWidthMultiplier(int mult) {
    _widthMultiplier = mult;
}