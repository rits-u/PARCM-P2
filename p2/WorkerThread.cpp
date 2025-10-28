#include "WorkerThread.h"

WorkerThread::WorkerThread(int id, IFinishedTask* onDone)
{
	this->id = id;
	this->onDone = onDone;
}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::AssignTask(IWorkerAction* task)
{
	this->task = task;
}

void WorkerThread::run()
{
	if (this->task != nullptr) {
		this->task->OnStartTask();
	}

	if (this->onDone != nullptr) {
		this->onDone->OnFinishedTask(this->id);
	}
}
