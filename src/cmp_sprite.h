#pragma once
#include "ecm.h"

class ShapeComponent : public Component {
protected:
	std::shared_ptr<sf::Shape> _shape;

public:
	ShapeComponent() = delete;
	explicit ShapeComponent(Entity *p);

	void Update(double dt) override;
	void Render() override;

	sf::Shape &getShape() const;

	template<typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};