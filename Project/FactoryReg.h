#pragma once
#include <string>
#include "Factory.h"
#include "NormalTile.h"
#include "CollideableTile.h"

class FactoryReg {
public:
	FactoryReg(const std::string& name) 
		: m_name(name), m_isReg(true) {}
	std::string m_name;
	bool m_isReg;
	static std::shared_ptr<FactoryReg> regNoramlTile(const std::string& symbol, std::string& id) {
		Factory<NormalTile>::getInstance().add(id, &NormalTile::create);
		return std::make_shared<FactoryReg>(id);
	}
	static std::shared_ptr<FactoryReg> regCollideableTile(const std::string& symbol, std::string& id) {
		Factory<CollideableTile>::getInstance().add(id, &CollideableTile::create);
		return std::make_shared<FactoryReg>(id);
	}
private:
	static bool regit;
	static bool regit2;
};
bool FactoryReg::regit = Factory<FactoryReg>::getInstance().add("NoramlTile", &FactoryReg::regNoramlTile);
bool FactoryReg::regit2 = Factory<FactoryReg>::getInstance().add("CollideableTile", &FactoryReg::regCollideableTile);

