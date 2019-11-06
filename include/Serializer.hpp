#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include <BasicShape.hpp>
#include <Velocity.hpp>

#include "Protocole.hpp"
#include "Udp.h"
//#include "Asset.hpp"

namespace cf
{
class Serializer
{
      public:
	Serializer() noexcept;
	~Serializer() noexcept;
	Serializer(const Serializer &packet) noexcept;
	Serializer(const Serializer &packet, enum pktType_e pktType) noexcept;
	Serializer(const Serializer &packet, enum UdpPrctl::type type,
		   uint16_t index) noexcept;
	void clear() noexcept;
	void setHeader(enum pktType_e pktType) noexcept;
	bool set(const std::string &str) noexcept;
	bool set(const TcpPacketHeader &header) noexcept;
	//bool set(const Asset &asset) noexcept;
	bool set(const sf::Vector2f &v) noexcept;
	bool set(const sfs::Sprite &sprite) noexcept;
	bool set(const sfs::Velocity &velocity) noexcept;
	template <typename T> bool set(const std::vector<T> &vec)
	{
		if (!nativeSet(vec.size()))
			return false;
		for (auto &&i : vec)
			if (!set(i))
				return false;
		return true;
	}
	template <typename T> bool set(const T &nativeObject) noexcept
	{
		return nativeSet(nativeObject);
	}
	//bool get(const Asset &asset) noexcept;
	bool get(std::string &str) noexcept;
	bool get(void *dest, size_t len) noexcept;
	bool get(sf::Vector2f &v) noexcept;
	bool get(sfs::Sprite &sprite) noexcept;
	bool get(sfs::Velocity &velocity) noexcept;
	template <typename T> bool get(T &dest) noexcept
	{
		return get(&dest, sizeof(dest));
	}
	void *getNativeHandle() const noexcept;
	bool forceSize(size_t newSize) noexcept;
	template <typename T> bool forceSetFirst(const T &obj)
	{
		if (resizeForNewElement(sizeof(obj)) == -1)
			return false;
		std::memmove(_data + sizeof(obj), _data, _size);
		std::memcpy(_data, &obj, sizeof(obj));
		_size += sizeof(obj);
		return true;
	}
	int reserve(uint64_t size) noexcept;
	size_t getSize() const noexcept;

	bool nativeSet(const void *data, size_t len) noexcept
	{
		if (resizeForNewElement(len) == -1)
			return false;
		std::memcpy(_data + _size, data, len);
		_size += len;
		return true;
	}
	template <typename T> bool nativeSet(const T &obj) noexcept
	{
		return nativeSet(&obj, sizeof(obj));
	}

      private:
	int8_t *_data;
	size_t _size;
	size_t _alloc_size;
	int resizeForNewElement(size_t newElementSize) noexcept;
	void shift(size_t from) noexcept;
};
} // namespace cf
