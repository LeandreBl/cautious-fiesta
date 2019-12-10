#include "GameManager.hpp"
#include "UdpConnection.hpp"
#include "Life.hpp"
#include "UiStats.hpp"

namespace cf {
int UdpConnect::stateHandler(sfs::Scene &scene, GameManager &manager, Serializer &s)
{
	int32_t Type;
	uint64_t id;
	float info;

	s >> Type;
	s >> id;
	s >> info;
	auto v = scene.getGameObjects<Life>();
	auto v2 = scene.getGameObjects<UiStats>();

	switch (static_cast<UdpPrctl::stateType>(Type)) {
	case UdpPrctl::stateType::SETLIFE:
		if (v.empty() == false)
			v[0]->changeLife(info, id);
		break;
	case UdpPrctl::stateType::KILL_NUMBER:
		manager._kills = info;
		if (v2.empty() == false) {
			v2[0]->changeKills(info, id);
		}
		break;
	case UdpPrctl::stateType::STAT_UP:
		if (v2.empty() == false) {
			v2[0]->changeStats(scene, info, id);
		}
	}
	return 0;
}
} // namespace cf