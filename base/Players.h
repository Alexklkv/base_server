#pragma once

#include "Api.h"
#include "NoCopy.h"

#include <vector>

#include <concurrent_hash_map.h>

class BasePlayer;

class Players : private NoCopy
{
private:
	struct Pid
	{
		uint64_t net_id;
		Api::Type type;
	};

	struct PidHash
	{
		inline bool equal(const Pid &x, const Pid &y) const
		{
			return (x.type == y.type && x.net_id == y.net_id);
		}

		inline size_t hash(const Pid &x) const
		{
			return static_cast<size_t>(x.net_id);
		}
	};

	typedef tbb::concurrent_hash_map<uint32_t, BasePlayer*> players_t;
	typedef players_t::accessor players_accessor;
	typedef players_t::const_accessor players_const_accessor;

	typedef tbb::concurrent_hash_map<Pid, uint32_t, PidHash> pids_t;
	typedef pids_t::accessor pids_accessor;
	typedef pids_t::const_accessor pids_const_accessor;

	players_t players;
	pids_t pids;

	BasePlayer* add(BasePlayer *player);

public:
	~Players();

	BasePlayer* get(uint64_t net_id, Api::Type type, bool create = true);
	BasePlayer* get(uint32_t inner_id, bool load = true);
	void delete_player(uint32_t inner_id);

	void get(const std::vector<uint32_t> &inner_ids, std::vector<BasePlayer*> &players);
	void get(const std::vector<uint64_t> &net_ids, Api::Type type, std::vector<BasePlayer*> &players);
};