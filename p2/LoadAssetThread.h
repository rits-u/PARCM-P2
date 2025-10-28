#pragma once

#include <iostream>
#include "IETThread.h"
#include "IExecutionEvent.h"
#include "TextureManager.h"
#include "IWorkerAction.h"

class LoadAssetThread : public IWorkerAction 
{
public:
	LoadAssetThread() {}
	~LoadAssetThread() {}

	LoadAssetThread(int id, IExecutionEvent* callback);

	void SetBatchSize(int size);
	void SetMode(bool isBatch);

private:
	int id = 0;
	int batchSize;
	bool isBatch;
	//void run() override;
	void OnStartTask() override;
	IExecutionEvent* OnFinished;
};

