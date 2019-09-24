#ifndef _DISCORD_APP_HPP_
#define _DISCORD_APP_HPP_

#include <discord_rpc.h>
#include <string>

class DiscordRP
{
      public:
	DiscordRP(const std::string &clientId) noexcept;
	~DiscordRP() noexcept;
	void update() noexcept;

      private:
	std::string _id;
	DiscordEventHandlers _handlers;
	DiscordUser _user;
	DiscordRichPresence _discordPresence;
};

#endif /* !_DISCORD_APP_HPP_ */