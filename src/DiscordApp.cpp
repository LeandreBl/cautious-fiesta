#include <cstring>

#include <Trace.hpp>

#include "DiscordApp.hpp"

static void DrpEvtReady(const DiscordUser *request) noexcept
{
	trace(true, "Discord: Connected to user %s#%s - %s\n",
	      request->username, request->discriminator, request->userId);
}

static void DrpEvtDisconnect(int errcode, const char *message) noexcept
{
	trace(true, "Discord: Disconnected (%d: %s)\n", errcode, message);
}

static void DrpEvtErrored(int errcode, const char *message) noexcept
{
	trace(true, "Discord: Error (%d: %s)\n", errcode, message);
}

static void DrpEvtJoinGame(const char *joinSecret) noexcept
{
	(void)joinSecret;
}

static void DrpEvtSpectateGame(const char *spectateSecret) noexcept
{
	(void)spectateSecret;
}

static void DrpEvtJoinRequest(const DiscordUser *request) noexcept
{
	(void)request;
}

DiscordRP::DiscordRP(const std::string &id) noexcept : _id(id)
{
	std::memset(&_handlers, 0, sizeof(_handlers));
	std::memset(&_discordPresence, 0, sizeof(_discordPresence));
	_handlers.ready = &DrpEvtReady;
	_handlers.disconnected = &DrpEvtDisconnect;
	_handlers.errored = &DrpEvtErrored;
	_handlers.joinGame = &DrpEvtJoinGame;
	_handlers.spectateGame = &DrpEvtSpectateGame;
	_handlers.joinRequest = &DrpEvtJoinRequest;
	_discordPresence.startTimestamp = time(NULL);
	trace(true, "%sDiscord%s: Rich Presence started\n", CYAN, RESET);
	Discord_Initialize(_id.c_str(), &_handlers, 1, nullptr);
}
DiscordRP::~DiscordRP() noexcept
{
	Discord_Shutdown();
}
void DiscordRP::update() noexcept
{
	char state[128];
	char details[128];

	memset(&_discordPresence, 0, sizeof(_discordPresence));
	snprintf(state, sizeof(state), "GameSessions");
	_discordPresence.state = state;
	// snprintf(details, sizeof(details), "Running on port %u",
	//	 _server.getTcpPort());
	_discordPresence.details = details;
	_discordPresence.startTimestamp = time(NULL);
	_discordPresence.largeImageKey = "server";
	_discordPresence.largeImageText =
		"Je suis le plus beau serveur de jeu :3";
	//_discordPresence.partySize = _server.getGameSessions().size();
	_discordPresence.partyMax = 64;
	trace(true, "%sDiscord%s: Rich Presence updated\n", CYAN, RESET);
	Discord_UpdatePresence(&_discordPresence);
}