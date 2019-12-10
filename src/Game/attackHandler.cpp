#include "GameManager.hpp"
#include "GoPlayer.hpp"
#include "UdpConnection.hpp"

namespace cf
{
int UdpConnect::attackHandler(sfs::Scene &scene, GameManager &manager, Serializer &s)
{
	int32_t attackType;
	float angle;

	s >> attackType;
	s >> angle;
	switch (static_cast<UdpPrctl::attackType>(attackType))
	{
	case UdpPrctl::attackType::DEFAULT:
		manager._self->getAttackSound().stop();
		manager._self->getAttackSound().play();
		break;
	case UdpPrctl::attackType::SPECIAL:
		break;
	}
	return 0;
}
} // namespace cf