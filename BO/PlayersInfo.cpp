#include "PlayersInfo.h"
#include <algorithm>
#include "Constants.h"
#include "Exceptions.h"

PlayersInfo::PlayersInfo(std::string params) {
	auto ss = std::stringstream(params);
	serialize(ss);
}

std::string PlayersInfo::deserialize() const {
	std::string s;
	std::string sep = "";
	std::for_each(begin(m_playersInfo), end(m_playersInfo), [&s, &sep](const std::pair<std::string, PlayerInfo>& p) {
		s += sep + p.second.deserialize();
		sep = SEPARATOR;
	});
	return s;
}

void PlayersInfo::serialize(std::stringstream& params) {
	while (params.good()) {
		std::string substr;
		getline(params, substr, SEPARATOR);
		if (substr != "") {
			auto pp = PlayerInfo(substr);
			m_playersInfo.insert(std::make_pair(pp.m_id, pp));
		}
	}
}

PlayerInfo& PlayersInfo::getPlayerInfo(std::string id) {
	auto it = m_playersInfo.find(id);
	if (it == end(m_playersInfo))
		throw NotFoundException();
	return it->second;
}

void PlayersInfo::addPlayerInfo(PlayerInfo pp) {
	m_playersInfo.insert(std::make_pair(pp.m_id, pp));
}