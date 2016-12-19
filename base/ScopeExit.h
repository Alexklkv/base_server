#pragma once

#include <functional>

class ScopeExit
{
	std::function<void()> on_exit;

public:
	explicit ScopeExit(const std::function<void()> &on_exit);
	virtual ~ScopeExit();
};

class FailExit
{
	std::function<void()> on_fail;
	bool failed;

public:
	explicit FailExit(const std::function<void()> &on_fail);
	virtual ~FailExit();

	void success();
};