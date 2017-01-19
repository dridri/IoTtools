/*
 * BCFlight
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

Messenger::Messenger( Link* link )
	: mLink( link )
	, mConnected( false )
	, mConnectionEstablished( false )
{
}


Messenger::~Messenger()
{
}


void Messenger::loadConfig( const std::string& content )
{
}


void Messenger::RegisterCallback( uint32_t command, const std::function<void()>& fct )
{
}


void Messenger::Poll( uint32_t timeout_ms )
{
}
