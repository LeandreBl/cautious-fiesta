#include "Udp.h"

namespace cf
{
UdpPrctl::UdpPrctl(enum type type, uint32_t size, uint16_t index) noexcept
{
	_header.type = type;
	_header.size = size;
	_header.magic = UDP_MAGIC;
	_header.index = index;
}

bool UdpPrctl::isCorrect() const noexcept
{
	return _header.magic == UDP_MAGIC && _header.type <= UNKNOWN;
}

enum UdpPrctl::type UdpPrctl::getType() const noexcept
{
	return (enum UdpPrctl::type)_header.type;
}

uint32_t UdpPrctl::getSize() const noexcept
{
	return _header.size;
}

uint16_t UdpPrctl::getIndex() const noexcept
{
	return _header.index;
}

const struct UdpPrctl::udpHeader *UdpPrctl::getPackedData() const noexcept
{
	return &_header;
}
} // namespace cf