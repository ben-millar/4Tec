#ifndef OBSERVER_INCLUDE
#define OBSERVER_INCLUDE

#include <iostream>
#include <GameData.h>
#include <Input.h>

class Observer
{
public:
	/// <summary>
	/// Function that will be called when the subject receives a move
	/// from the opposing player
	/// </summary>
	/// <param name="t_move"> The move that was played</param>
	/// <param name="t_player"> The player that played the move </param>
	virtual void onNotify(Move t_move, Player t_player) = 0;
};

#endif 