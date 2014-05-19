#pragma once
#include <mutex>
class LifeCircleMutexLocker   
{   
	std::mutex* mutex;  
public:   
	LifeCircleMutexLocker(std::mutex* aMutex) : mutex(aMutex)   
	{   
		mutex->lock();
	}   
	~LifeCircleMutexLocker()
	{   
		mutex->unlock();  
	}   
};   
#define LifeCircleMutexLock(mutex) LifeCircleMutexLocker __locker__(&mutex) 
extern std::mutex sharedNotificationQueueLock; 
extern std::mutex NetworkMessageQueueLock;