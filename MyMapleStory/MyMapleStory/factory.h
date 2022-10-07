#pragma once


namespace Factory {
	template<class tEntity>
	tEntity* CreateEntity(std::string name) {
		tEntity* ent = new tEntity(name);

	}
}