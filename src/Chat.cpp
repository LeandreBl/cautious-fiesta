#include <Offset.hpp>
#include <Padder.hpp>
#include "InputHandler.hpp"
#include "Chat.hpp"

namespace cf {
void Chat::start(sfs::Scene &scene) noexcept
{
	_font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	_chatBox = &addChild<sfs::InputBox>(scene, *_font, sf::Vector2f(0, 0), "send message");
	if (_messageQueu == 3)
		_chatBox->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(0, 1040));
	else
		_chatBox->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(25, 970));

	_gameManager = scene.getGameObjects<GameManager>()[0];

	scene.subscribe(*this, sf::Event::KeyPressed);
}

void Chat::receiveMessage(Serializer &s) noexcept
{
	std::string name;
	std::string message;

	s >> name;
	s >> message;
	message = name + " : " + message;

	sf::Vector2f newPos;
	if (_chatMessages.empty() == true)
		newPos = sf::Vector2f(_chatBox->getPosition().x, _chatBox->getPosition().y - 20);
	else {
		for (auto &i : _chatMessages) {
			auto pos = i->getOffset();
			pos.y -= 25;
			i->setOffset(pos);
		}
		auto pos = _chatMessages[_chatMessages.size() - 1]->getOffset();
		pos.y += 25;
		newPos = pos;
	}
	sf::Color color = sf::Color::White;
	if (_gameManager->_gameStarted == true)
		color = sf::Color::Black;
	_chatMessages.emplace_back(&addComponent<sfs::Text>(*_font, message, color, 20, newPos));
	if (_chatMessages.size() > _messageQueu) {
		_chatMessages.front()->destroy();
		_chatMessages.erase(_chatMessages.begin());
	}
}

void Chat::handleSendMessage(Serializer &s) noexcept
{
	bool isOk = 0;

	s >> isOk;
	if (_gameManager->_gameStarted == false)
		_chatBox->toggle(true);
}

void Chat::eraseChat() noexcept
{
	for (auto &i : _chatMessages)
		i->destroy();
	_chatMessages.clear();
}

void Chat::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::KeyPressed) {
		if (_chatBox->getSelected() == true)
			scene.unsubscribe(*scene.getGameObjects<InputHandler>()[0],
					  sf::Event::KeyPressed);
		else
			scene.subscribe(*scene.getGameObjects<InputHandler>()[0],
					sf::Event::KeyPressed);
		if (event.key.code == sf::Keyboard::Return && _chatBox->getSelected() == true) {
			_chatBox->toggle(false);
			_gameManager->_tcp->sendMessage(_chatBox->string());
			_chatBox->string("");
		}
	}
}
} // namespace cf
