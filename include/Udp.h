#pragma once

#include <cstdint>
#include <SFML/System.hpp>

namespace cf
{

constexpr uint16_t UDP_MAGIC = 0x0b3a;

class UdpPrctl
{
      public:
	enum type { POSITION, VELOCITY, SPRITE, SPAWN, INPUT, TIME, UNKNOWN };
	struct udpHeader {
		uint32_t type;  // packet type
		uint32_t size;  // packet payload size
		uint16_t magic; // packet magic number
		uint16_t index; // packet index
	} __attribute__((packed));
	struct udpPosition {
		uint32_t objectIndex;
		sf::Vector2f position;
	};
	struct udpVelocity {
		uint32_t objectIndex;
		sf::Vector2f speed;
		sf::Vector2f acceleration;
	};
	struct udpSprite {
		uint32_t objectIndex;
		sf::Vector2f offset;
		sf::Vector2f scale;
		float rotation;
	};
	enum objType {

	};
	struct udpSpawnObject {
		uint32_t type;
		uint32_t customIndex;
		// extra data depending on type
	};
	enum inputType {

	};
	struct udpInput {
		uint32_t type;
		// extra data depending on type
	};
	enum timeType {
		REALTIME = 0,
		TIMESCALE,
	};
	struct udpTime {
		uint32_t type;
		// extra data depending on type
	};
	enum stateType {

	};
	struct udpSetState {
		enum stateType type;
		uint32_t objectIndex;
		// extra data depending on type;
	};
	struct udpDestroy {
		uint32_t objectIndex;
	};
	UdpPrctl(enum type type, uint32_t size, uint16_t index) noexcept;
	bool isCorrect() const noexcept;
	enum type getType() const noexcept;
	uint32_t getSize() const noexcept;
	uint16_t getIndex() const noexcept;
	const struct udpHeader *getPackedData() const noexcept;

      protected:
	struct udpHeader _header;
};
} // namespace cf