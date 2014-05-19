#ifndef __singleton_hh__
#define __singleton_hh__
#include <cassert>
class noncopyable
{
protected:
	noncopyable() {}
	~noncopyable() {}
private:
	noncopyable(const noncopyable&);
	const noncopyable& operator=( const noncopyable& );
};

class singleton_module : public noncopyable
{
public:
	static void lock()
	{
		get_lock() = true;
	}

	static void unlock()
	{
		get_lock() = false;		
	}

	static bool is_locked() {
		return get_lock();
	}
private:
	static bool& get_lock()
	{
		static bool lock_ = false;
		return lock_;
	}
};

template<class T>
class singleton_wrapper : public T
{
public:
	static bool destroyed_;
	~singleton_wrapper()
	{
		destroyed_ = true;
	}
};

template<class T>
bool singleton_wrapper< T >::destroyed_ = false;

template <class T>
class singleton : public singleton_module
{
public:
	static T& get_instance()
	{
		static singleton_wrapper< T > t;
		// refer to instance, causing it to be instantiated (and
		// initialized at startup on working compilers)
		assert(!singleton_wrapper< T >::destroyed_);
		use(instance_);
		return static_cast<T &>(t);
	}

	static bool is_destroyed()
	{
		return singleton_wrapper< T >::destroyed_;
	}

private:
	static T& instance_;
	//include this to provoke instantiation at pre-execution time
	static void use(T const &) {}
};

template<class T>
T& singleton< T >::instance_ = singleton< T >::get_instance();

#endif