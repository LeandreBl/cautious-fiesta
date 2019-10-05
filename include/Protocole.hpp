#ifndef _CF_PROTOCOLE_HPP_
#define _CF_PROTOCOLE_HPP_

#include <cstdint>

namespace cf
{
constexpr uint32_t MAGIC = 0x0b3a4;

typedef struct pktTcpHeader_s {
	uint32_t magic;
	uint32_t pktType;
	uint64_t pktLen;
} pktTcpHeader_t;

enum pktType_e {
	LOGIN = 0,
	LOGOUT,
	CREATE_GAMEROOM,
	DELETE_GAMEROOM,
	GET_GAMEROOMS_LIST,
	JOIN_GAMEROOM,
	LEAVE_GAMEROOM,
	GET_GAMEROOM_PLAYERS_LIST,
	SEND_MESSAGE,
	RECEIVE_MESSAGE,
	TOGGLE_READY,
	ASSETS_REQUIREMENT,
	ASSETS_SEND,
	GAME_STARTED,
	ACK, /* this should stay the last enum type */
};

extern const char *pktTypeToString[];

class TcpPacketHeader
{
      public:
	TcpPacketHeader() noexcept = default;
	TcpPacketHeader(enum pktType_e type, uint64_t pktLen = 0) noexcept;
	~TcpPacketHeader() noexcept = default;
	uint64_t getLen() const noexcept;
	uint32_t getType() const noexcept;
	uint32_t getMagic() const noexcept;
	bool isCorrect() const noexcept;
	pktTcpHeader_t &getNativeHandle() noexcept;
	const pktTcpHeader_t &getNativeHandle() const noexcept;
	void display(bool recv = true) const noexcept;

      private:
	pktTcpHeader_t _header;
};
} // namespace cf

#endif /* !_CF_PROTOCOLE_HPP_ */