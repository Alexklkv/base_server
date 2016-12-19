/*
 * Формирование серверного пакета для передачи "указателей" клиенту,
 * клиент его в свою очередь отображает и присылает ответ при переходе игрока по ним.
 */
#pragma once

#include "server/Group.h"
#include "server/Packet.h"

class Pointers;

namespace server
{

class ActivePointers : public Packet
{
	SERVER_PACKET_HEADER(ActivePointers)

public:
	
	ActivePointers(Pointers* pointers);
};

}