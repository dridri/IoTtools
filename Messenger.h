/*
 * IoTtools
 * Copyright (C) 2016 Adrien Aubry (drich)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef MESSENGER_H
#define MESSENGER_H

#include <unistd.h>
#include <map>
#include <functional>

#include "links/Link.h"
#include "Debug.h"

namespace IoT {

class Messenger
{
public:
	Messenger( Link* link );
	virtual ~Messenger();

	bool isConnected();
	Link* link();
	void loadConfig( const std::string& content );

	void RegisterCallback( uint32_t command, const std::function<void()>& fct );
	void Poll( uint32_t timeout_ms = 0 );

protected:
	Link* mLink;
	bool mConnected;
	bool mConnectionEstablished;

	static std::map< uint32_t, std::function<void()> > mCallbacks;
};

}; // IoT

#endif // MESSENGER_H
