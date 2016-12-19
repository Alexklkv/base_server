#include "ClientsThread.h"

#include "IO.h"

ClientsThread::ClientsThread():
	Thread("Clients")
{}

void ClientsThread::add(IO *io, int socket)
{
	io->init_tcp(socket, this->get_loop());

	this->added.push(io);

	this->notify();
}

void ClientsThread::on_notify()
{
	IO *io = nullptr;
	while (this->added.try_pop(io))
		io->start_tcp();
}