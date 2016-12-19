#include "Players.h"

#include "BaseDatabase.h"
#include "BasePlayer.h"
#include "BaseServer.h"

Players::~Players()
{
	for (auto iter : this->players)
		delete iter.second;
}

BasePlayer* Players::get(uint64_t net_id, Api::Type type, bool create)
{
	Pid pid = {net_id, type};

	pids_const_accessor acc_pid;
	if (this->pids.find(acc_pid, pid))
	{
		uint32_t inner_id = acc_pid->second;

		players_const_accessor acc_player;
		if (this->players.find(acc_player, inner_id))
			return acc_player->second;
	}
	acc_pid.release();

	pids_accessor acc_pid_lock;
	this->pids.insert(acc_pid_lock, pid);

	BasePlayer *player = base_database()->load_player(net_id, type, create);
	if (player == nullptr)
		return nullptr;

	acc_pid_lock->second = player->inner_id;
	acc_pid_lock.release();

	return this->add(player);
}

BasePlayer* Players::get(uint32_t inner_id, bool load)
{
	players_const_accessor acc_player;
	if (this->players.find(acc_player, inner_id))
		return acc_player->second;

	if (!load)
		return nullptr;

	BasePlayer *player = base_database()->load_player(inner_id);
	if (player == nullptr)
		return nullptr;

	return this->add(player);
}

void Players::delete_player(uint32_t inner_id)
{
	players_accessor acc_player;
	if (this->players.find(acc_player, inner_id))
	{
		acc_player->second->type = Api::TYPE_BOT;
		delete acc_player->second;
		this->players.erase(acc_player);
	}
}

void Players::get(const std::vector<uint32_t> &inner_ids, std::vector<BasePlayer*> &players)
{
	if (inner_ids.empty())
		return;

	std::vector<uint32_t> load;
	load.reserve(inner_ids.size());

	for (auto iter : inner_ids)
	{
		players_const_accessor acc;
		if (!this->players.find(acc, iter))
		{
			load.push_back(iter);
			continue;
		}

		players.push_back(acc->second);
	}

	if (load.empty())
		return;

	std::vector<BasePlayer*> loaded;
	loaded.reserve(load.size());

	base_database()->load_players(load, loaded);

	for (auto iter : loaded)
	{
		BasePlayer *player = this->add(iter);
		players.push_back(player);
	}
}

void Players::get(const std::vector<uint64_t> &net_ids, Api::Type type, std::vector<BasePlayer*> &players)
{
	if (net_ids.empty())
		return;

	std::vector<uint64_t> load;
	load.reserve(net_ids.size());

	std::vector<uint32_t> inner_ids;
	inner_ids.reserve(net_ids.size());

	for (auto iter : net_ids)
	{
		Pid pid = {iter, type};

		pids_const_accessor acc_pid;
		if (this->pids.find(acc_pid, pid))
			inner_ids.push_back(acc_pid->second);
		else
			load.push_back(pid.net_id);
	}

	base_database()->load_players_ids(load, type, inner_ids);

	this->get(inner_ids, players);
}

BasePlayer* Players::add(BasePlayer *player)
{
	players_accessor acc_player;
	if (!this->players.insert(acc_player, player->inner_id))
	{
		delete player;
		return acc_player->second;
	}

	Pid pid = {player->net_id, player->type};
	this->pids.insert(std::pair<Pid, uint32_t>(pid, player->inner_id));

	acc_player->second = player;

	acc_player.release();

	player->on_load();

	return player;
}