#include <cstring>
#include <iostream>

#include "Serializer.hpp"

namespace cf
{
Serializer::Serializer() noexcept : _data(nullptr), _size(0), _alloc_size(0)
{
}

Serializer::~Serializer() noexcept
{
	delete[] _data;
}

Serializer::Serializer(const Serializer &packet,
		       enum pktType_e pktType) noexcept
    : _data(nullptr), _size(0), _alloc_size(0)
{
	TcpPacketHeader header(pktType, packet._size);
	nativeSet(header);
	nativeSet(packet._data, packet._size);
}

Serializer::Serializer(const Serializer &packet) noexcept
    : _data(nullptr), _size(0), _alloc_size(0)
{
	nativeSet(packet._data, packet._size);
}

void Serializer::setHeader(enum pktType_e pktType) noexcept
{
	TcpPacketHeader header(pktType, _size);
	header.display(false);
	forceSetFirst(header);
}

void Serializer::shift(size_t from) noexcept
{
	std::memmove(_data, _data + from, _size - from);
	_size -= from;
}

void Serializer::clear() noexcept
{
	_size = 0;
}
int Serializer::resizeForNewElement(size_t newElementSize) noexcept
{
	if (_alloc_size - _size >= newElementSize)
		return 0;
	size_t newAllocSize = _size + newElementSize;
	int8_t *newBuffer = new int8_t[newAllocSize];
	if (newBuffer == nullptr)
		return -1;
	std::memcpy(newBuffer, _data, _size);
	_alloc_size = newAllocSize;
	delete[] _data;
	_data = newBuffer;
	return 0;
}

bool Serializer::set(const std::string &str) noexcept
{
	uint64_t len = (uint64_t)str.length();

	return nativeSet(len) && nativeSet(str.c_str(), len);
}
/*
bool Serializer::set(const Asset &asset) noexcept
{
	std::ifstream file(asset.getFileName(), std::ios::binary);

	if (!file.is_open())
		return false;
	if (!nativeSet(asset.getFileSize()) || !set(asset.getFileName())
	    || !nativeSet(asset.getChksum()))
		return false;
	if (reserve(asset.getFileSize()) != 0)
		return false;
	for (uint64_t size = 0; size < asset.getFileSize(); ++size) {
		char buffer[512];
		std::streamsize rd;
		rd = file.readsome(buffer, sizeof(buffer));
		if (rd <= 0)
			return false;
		if (!nativeSet(buffer, rd))
			return false;
		size += rd;
	}
	file.close();
	return true;
}*/

bool Serializer::set(const TcpPacketHeader &header) noexcept
{
	const auto data = header.getNativeHandle();

	return nativeSet(data);
}

bool Serializer::get(std::string &str) noexcept
{
	size_t len;

	if (get(len) == false)
		return false;
	if (_size < len)
		return false;
	str.assign((char *)_data, len);
	shift(len);
	return true;
}

bool Serializer::get(void *dest, size_t len) noexcept
{
	if (_size < len)
		return false;
	std::memcpy(dest, _data, len);
	shift(len);
	return true;
}

void *Serializer::getNativeHandle() const noexcept
{
	return _data;
}

int Serializer::reserve(uint64_t size) noexcept
{
	return resizeForNewElement(size);
}

bool Serializer::forceSize(size_t newSize) noexcept
{
	if (newSize > _alloc_size)
		return false;
	_size = newSize;
	return true;
}

size_t Serializer::getSize() const noexcept
{
	return _size;
}
} // namespace cf