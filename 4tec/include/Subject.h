#ifndef SUBJECT_INCLUDE
#define SUBJECT_INCLUDE

#include <Observer.h>
#include <vector>

class Subject
{
public:
	Subject() = default;
	~Subject() = default;

	/// <summary>
	/// Allows the subject to add observers to the pool 
	/// these observers will be notified when the subject wishes to
	/// notify them 
	/// </summary>
	/// <param name="obs"> Recipient of the notification </param>
	virtual void addObserver(Observer* obs)
	{
		m_observers.push_back(obs);
	}

	/// <summary>
	/// Allows the observer to unsubscribe from the notification
	/// after this function they will be removed from the list 
	/// </summary>
	/// <param name="obs"> Obserever that wishes to not receive info </param>
	virtual void removeObserver(Observer* obs)
	{
		auto it = m_observers.begin();
		auto end = m_observers.end();
		for (; it != end; ++it)
		{
			if (*it == obs)
			{
				m_observers.erase(it);
				break;
			}
		}
	}

	/// <summary>
	/// function that will pass the move onto all 
	/// subscribers, It will also pass on what colour the player is
	/// </summary>
	/// <param name="t_move"> The move that will be passed on</param>
	virtual void notify(Move t_info, Player t_type)
	{
		for (auto& obs : m_observers)
			obs->onNotify(t_info, t_type);
	}

protected:
	std::vector<Observer*> m_observers;
};


#endif