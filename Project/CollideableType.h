#pragma once
#include "Collideable.h"

template <typename T>
class CollideableType :
	public Collideable {
	public:
		virtual ~CollideableType() = 0 {}
		std::type_index type() const override {
			return typeid(T);
		}
};

