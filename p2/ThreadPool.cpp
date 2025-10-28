#include "ThreadPool.h"

ThreadPool::ThreadPool(int workerCount)
{
	this->workerCount = workerCount;
	
	//initialize our workers
	for (int i = 0; i < workerCount; i++) {
		// hire/create our workers (no tasks yet, is idle)
		InactiveThreads.push(new WorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::StartScheduling()
{
	this->isRunning = true;
	this->start();
}

void ThreadPool::StopScheduling()
{
	this->isRunning = false;
}

void ThreadPool::ScheduleTasks(IWorkerAction* task)
{
	this->PendingTasks.push(task);
}

void ThreadPool::run()
{
	while (this->isRunning) {
		if (!this->PendingTasks.empty()) {	//if you have a pending task
			if (!this->InactiveThreads.empty()) {	//there is an inactive / available thread
				

				auto workerThread = this->InactiveThreads.front();	//get the latest inactive thread
				this->InactiveThreads.pop();	//remove thread from inactive queue

				this->ActiveThreads[workerThread->GetID()] = workerThread;		//assign to unordered map
			
				auto task = this->PendingTasks.front();		//get first task in queue
				this->PendingTasks.pop();		//remove task from queue
				workerThread->AssignTask(task);		//assign task in thread

				workerThread->start();		//start thread
			
			}
		}
	}
}

void ThreadPool::OnFinishedTask(int id)
{
	if (this->ActiveThreads[id] != nullptr) {
		//remove and delete done threads
		delete this->ActiveThreads[id];
		this->ActiveThreads.erase(id);

		//create a replacement for id
		InactiveThreads.push(new WorkerThread(id, this));
	}
}
