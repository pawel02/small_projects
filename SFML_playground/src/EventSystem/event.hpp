#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <algorithm>
#include <SFML/Window.hpp>

class BasicEvent
{
public:
	const bool& isHandled() const noexcept { return _handled;  }

private:
	bool _handled = false;
};

/*
This manager will fire off any functions that are subscribed to a certain type of event
*/
class EventsManager
{
public:
	using func = std::function<void(std::shared_ptr<BasicEvent>)>;
	using callbackContainer = std::unique_ptr<std::vector<func>>;

	/*
	 * Subscribes to the specified event
	 */
	void subscribe(sf::Event::EventType eventType, func handler) noexcept
	{
		const std::unordered_map<sf::Event::EventType, callbackContainer>::iterator element = callbacks.find(eventType);
		if (element != std::end(callbacks))
		{
			element->second->emplace_back(handler);
		}
		else
		{
			callbacks.emplace(std::pair<sf::Event::EventType, callbackContainer>(eventType, 
				std::make_unique<std::vector<func>>(std::vector<func>{handler})));
		}
	}

	/*
	 *Unsubscribes from the specified event
	 */
	void unsubscribe(sf::Event::EventType eventType, func handler)
	{
		const std::unordered_map<sf::Event::EventType, callbackContainer>::iterator element = callbacks.find(eventType);
		if (element != std::end(callbacks))
		{
			const auto found = std::find_if(std::begin(*(element->second)), std::end(*(element->second)), [&](const func& item) {
				if (item.target<std::shared_ptr<BasicEvent>>() == handler.target<std::shared_ptr<BasicEvent>>())
				{
					return true;
				}
				return false;
			});
			if (found != element->second->end())
			{
				element->second->erase(found);
			}
		}
	}

	/*
	 * Notifies all the subscribers of the event
	 */
	void dispatch(sf::Event::EventType eventType, std::shared_ptr<BasicEvent> ev)
	{
		const std::unordered_map<sf::Event::EventType, callbackContainer>::iterator element = callbacks.find(eventType);
		if (element != std::end(callbacks))
		{
			for (auto& func : *(element->second))
			{
				func(ev);
			}
		}
	}

private:
	std::unordered_map<sf::Event::EventType, callbackContainer> callbacks;
};
