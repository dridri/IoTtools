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

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "Messenger.h"

using namespace IoT;

std::map< uint32_t, std::function<void(Packet&)> > Messenger::mCallbacks;

Messenger::Messenger( Link* link )
	: mLink( link )
	, mConnected( false )
	, mConnectionEstablished( false )
{
	fDebug( link );
}


Messenger::~Messenger()
{
	fDebug();
}


bool Messenger::isConnected()
{
	fDebug();
	return ( mLink and mLink->isConnected() and mConnectionEstablished );
}


Link* Messenger::link()
{
	fDebug();
	return mLink;
}


void Messenger::loadConfig( const std::string& content )
{
	fDebug( "[...]" );
}


void Messenger::RegisterCallback( uint32_t command, const std::function<void(Packet&)>& fct )
{
	fDebug( command, "#ptr" );

	if ( mCallbacks.find( command ) != mCallbacks.end() ) {
		// TODO : trigger "already registered" error
	} else {
		mCallbacks.emplace( std::make_pair( command, fct ) );
	}
}


void Messenger::Poll( uint32_t timeout_ms )
{
	fDebug( timeout_ms );

	if ( not mLink ) {
		return;
	}
	if ( not mLink->isConnected() ) {
		if ( mLink->Connect() < 0 ) {
			gDebug() << "Connection failed !";
			usleep( 1000 * 500 );
			return;
		}
	}

	Packet packet;
	int ret = mLink->Read( &packet, timeout_ms );

	if ( ret > 0 ) {
		uint32_t command = 0;
		if ( packet.ReadU32( &command ) > 0 and mCallbacks.find( command ) != mCallbacks.end() ) {
			mCallbacks.at( command )( packet );
		}
	}
}
