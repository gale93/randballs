#pragma once

namespace GameEvent
{
	struct Teleport
	{
		Teleport(unsigned int who, unsigned int where) : who(who), where(where)
		{
		}

		unsigned int who, where;
	};
};
