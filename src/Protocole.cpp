#include "Protocole.hpp"
#include "trace.hpp"
#include "colors.h"

namespace cf
{
const char *pktTypeToString[] = {
	"Login",
	"Logout",
	"Create GameRoom",
	"Delete GameRoom",
	"Get GameRooms List",
	"Join GameRoom",
	"Leave GameRoom",
	"Get GameRoom Players List",
	"Send Message",
	"Receive Message",
	"Toggle Ready",
	"Assets requirement",
	"Assets Loader",
	"Game Started",
	"Ack",
};

TcpPacketHeader::TcpPacketHeader(enum pktType_e type, uint64_t pktLen) noexcept
{
	_header.magic = cf::MAGIC;
	_header.pktType = type;
	_header.pktLen = pktLen;
}

uint64_t TcpPacketHeader::getLen() const noexcept
{
	return _header.pktLen;
}

uint32_t TcpPacketHeader::getType() const noexcept
{
	return _header.pktType;
}

uint32_t TcpPacketHeader::getMagic() const noexcept
{
	return _header.magic;
}

bool TcpPacketHeader::isCorrect() const noexcept
{
	return _header.magic == cf::MAGIC && _header.pktType <= cf::ACK;
}

pktTcpHeader_t &TcpPacketHeader::getNativeHandle() noexcept
{
	return _header;
}

const pktTcpHeader_t &TcpPacketHeader::getNativeHandle() const noexcept
{
	return _header;
}

void TcpPacketHeader::display(bool rcv) const noexcept
{
	trace(true,
	      "%c-%sTcpPacket%s: {%smagic%s: %s0x%x%s, %spktLen%s: %s% -3lu%s, %spktType%s: \"%s%s%s\"}\n",
	      (rcv == true) ? '<' : '>', MAGENTA, RESET, YELLOW, RESET, CYAN,
	      _header.magic, RESET, YELLOW, RESET, CYAN, _header.pktLen, RESET,
	      YELLOW, RESET, CYAN, cf::pktTypeToString[_header.pktType], RESET);
}
} // namespace cf