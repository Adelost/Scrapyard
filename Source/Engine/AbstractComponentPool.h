#pragma once

class AbstractComponentPool
{
public:
	virtual ~AbstractComponentPool() {}
	virtual void removeData(int id) {}
};