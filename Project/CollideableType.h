#pragma once
#include "Collideable.h"

//A template class for all object that can be collide with (using this class for factory)
template <typename T>
class CollideableType :
	public Collideable {
	public:
		virtual ~CollideableType() = 0 {}
		std::type_index type() const override {
			return typeid(T);
		}
};

