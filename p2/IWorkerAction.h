#pragma once

class IWorkerAction {

// threads' run function
public:
	virtual void OnStartTask() = 0;

};