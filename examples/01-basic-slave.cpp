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

#include <Messenger.h>
#include <Socket.h>

using namespace IoT;

#define EXAMPLE_COMMAND 42

void ExampleCommand( Packet& packet )
{
	std::cout << "Received message : \"" << packet.ReadString() << "\"\n";
}


int main( int ac, char** av )
{
	Debug::setEnabled( true );

	// Setup link, connect to master at address 127.0.0.1 (localhost) on TCP port 4242
	Link* link = new Socket( "127.0.0.1", 4242, Socket::TCP );

	// Create new Messenger instance using the link created above
	Messenger* messenger = new Messenger( link );

	//Register command callback
	messenger->RegisterCallback( EXAMPLE_COMMAND, ExampleCommand );

	while ( 1 ) {
		// Wait for master to send commands
		messenger->Poll();
	}

	return 0;
}
