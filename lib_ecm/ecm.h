#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "maths.h"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>

class Component;

class Entity {
private:
	std::vector<std::shared_ptr<Component>> _components;
	sf::Vector2f _position;
	
	int _points;
	float _rotation;
	bool _alive;
	bool _visible;
	bool _forDeletion;

public:
	Entity();
	virtual ~Entity() = default;

	virtual void Update(const double dt);
	virtual void Render();

	sf::Vector2f &getPosition();
	void setPosition(const sf::Vector2f &pos);
	bool is_forDeletion() const;
	float getRotation()	const;
	void setRotation(float _rot);
	bool isAlive() const;
	void setAlive(bool _value);
	void setForDelete();
	bool isVisible() const;
	void setVisible(bool _value);

	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "must be a component!");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}	

	const std::vector<std::shared_ptr<Component>>& getComponents() {
		return _components;
	}

	template<typename ComponentType>
	ComponentType* GetComponent() {
		for (unsigned int i = 0; i < _components.size(); ++i) {
			if (ComponentType* cmp = dynamic_cast<ComponentType*>(_components[i].get())) {
				return cmp;
			}
		}

		return nullptr;
	}

};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void Update(double dt);
	void Render();
};

class Component {
protected:
	Entity *_parent;
	bool _forDeletion;
	explicit Component(Entity *p);

public:
	Component() = delete;
	bool is_forDeletion();
	void setForDeletion();
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual ~Component();
};