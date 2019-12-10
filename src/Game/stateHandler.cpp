#include "GameManager.hpp"
#include "UdpConnection.hpp"
#include "Life.hpp"

namespace cf
{
int UdpConnect::stateHandler(sfs::Scene &scene, GameManager &manager, Serializer &s)
{
	int32_t Type;
	uint64_t id;
	float life;

	s >> Type;
	s >> id;
	s >> life;
	switch (static_cast<UdpPrctl::stateType>(Type))
	{
	case UdpPrctl::stateType::SETLIFE:
		auto v = scene.getGameObjects<Life>();
		if (v.empty() == false)
			v[0]->changeLife(life, id); //TODO faire avec l'id car sinon la vie des joueurs va etre update
		break;
	}
	return 0;
}
} // namespace cf