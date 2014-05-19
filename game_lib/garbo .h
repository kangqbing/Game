#ifndef garbo_h
#define garbo_h

template<class T>
class CGarbo 
{
public:
	void autoRelease(T* t)
	{
		_instance = t;
	}
	~CGarbo() 
	{
		if (_instance != nullptr) 
		{
			delete _instance;
		}		
	}
	T* _instance;
};
#endif

