#pragma once

#include "IWorkerAction.h"
#include "IETThread.h"


class IFinishedTask {
public: 
	virtual void OnFinishedTask(int id) = 0;
};


class WorkerThread : public IETThread {
public:
	WorkerThread(int id, IFinishedTask* onDone);
	~WorkerThread();

	//assigns the task to be done
	void AssignTask(IWorkerAction* task);
	int GetID() { return id; }

private:
	void run() override;

	int id;
	IFinishedTask* onDone;
	IWorkerAction* task;
};