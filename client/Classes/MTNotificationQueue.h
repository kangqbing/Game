#include <string>
#include "cocos2d.h"
#include "../game_lib/singleton.h"
using std::string;
using std::vector;
USING_NS_CC;
class MTNotificationQueue : public Node
{   
private:
	typedef struct   
	{   
		string name;   
		Ref* object;   
	} NotificationArgs;   

	vector<NotificationArgs> notifications;   
public:   
	static MTNotificationQueue* sharedNotificationQueue(); 
	void updateNotifications(); 
	void postNotification(const char* name, Ref* object);
}; 