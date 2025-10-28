#pragma once

#include <iostream>
#include "IETThread.h"
#include "IExecutionEvent.h"
#include "TextureManager.h"
#include "IWorkerAction.h"
#include <semaphore>

class LoadAssetThread : public IWorkerAction 
{
public:
	LoadAssetThread() {}
	~LoadAssetThread() {}

	LoadAssetThread(int id, IExecutionEvent* callback);

	void SetBatchSize(int size);
	void SetMode(bool isBatch);
	void SetNumAsset(int num);

private:

	int id = 0;
	int batchSize;
	int numAssets;
	bool isBatch;
	//void run() override;
	void OnStartTask() override;
	IExecutionEvent* OnFinished;
};

