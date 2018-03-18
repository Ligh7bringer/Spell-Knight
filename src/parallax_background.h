#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <memory>

class ParallaxBackground {
protected:
    sf::Vector2f _target;
    sf::Vector2f _size;
    std::shared_ptr<sf::Texture> _currTexture;
    std::vector<std::shared_ptr<sf::Texture>> _textures;
    std::vector<std::pair<float, std::shared_ptr<sf::Sprite>>> _layers;
    int _widthMultiplier;

public:
    ParallaxBackground() = default;
    explicit ParallaxBackground(const sf::Vector2f& size);

    void update(double dt);
    void render();

    void addLayer(float coeff, const std::string& tex);
    void setTarget(const sf::Vector2f& target);
    void setWidthMultiplier(int mult);
};