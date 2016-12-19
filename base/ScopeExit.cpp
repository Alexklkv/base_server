#include "ScopeExit.h"

ScopeExit::ScopeExit(const std::function<void()> &on_exit):
	on_exit(on_exit)
{}

ScopeExit::~ScopeExit()
{
	this->on_exit();
}

FailExit::FailExit(const std::function<void()> &on_fail):
	on_fail(on_fail), failed(true)
{}

FailExit::~FailExit()
{
	if (!this->failed)
		return;

	this->on_fail();
}

void FailExit::success()
{
	this->failed = false;
}