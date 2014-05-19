#include "MTNotificationQueue.h"
#include "LifeCircleMutexLock.h"

void MTNotificationQueue::updateNotifications()   
{   
	LifeCircleMutexLock(sharedNotificationQueueLock);   

	for(unsigned int i = 0; i < notifications.size(); i++) 
	{   
		NotificationArgs &arg = notifications[i]; 
		NotificationCenter::getInstance()-> 
			postNotification(arg.name.c_str(), arg.object);  
	}   
	notifications.clear();   
}

void MTNotificationQueue::postNotification(const char* name, Ref* object) 
{   
	LifeCircleMutexLock(sharedNotificationQueueLock);   

	NotificationArgs arg;   
	arg.name = name;   

	if(object != NULL)   
		arg.object = object;   
	else   
		arg.object = NULL;   

	notifications.push_back(arg);   
}   