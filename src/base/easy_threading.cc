#include "easy_threading.h"

#ifndef easy_exception_h__
#include "easy_exception.h"
#endif //easy_exception_h__

namespace easy
{

	EasyThreadPriority::EasyThreadPriority()
	{

	}

	EasyThread::EasyThread()
	{
#ifdef __WINDOWS
		thread_handle_ = INVALID_HANDLE_VALUE;
		thread_id_ = -1;
#elif __LINUX
#endif
		Start();
	}

	void EasyThread::Start()
	{
#ifdef __WINDOWS
		uintptr_t res = _beginthreadex( NULL, 0, &_ThreadFunction, this, 0, &thread_id_ );
		if (0 == res)
		{
			EASY_EXCEPTION( EasyException::kErrorInvalidParams, "_beginthreadex exception!", "_beginthreadex", kExceptionLevText );
		}
		thread_handle_ = (HANDLE)res;
#elif __LINUX
		pthread_create(&thread_id_,NULL,_ThreadFunction,this);
#endif
	}

	void EasyThread::Suspend()
	{
#ifdef __WINDOWS
		SuspendThread(thread_handle_);
#elif __LINUX

#endif //__WINDOWS
	}

	void EasyThread::Resume()
	{
#ifdef __WINDOWS
		ResumeThread(thread_handle_);
#elif __LINUX

#endif //__WINDOWS
	}

	easy_bool EasyThread::Wait( easy_uint32 time_out ) const
	{
		easy_bool res = false;
#ifdef __WINDOWS
		easy_ulong32 result = ::WaitForSingleObject(thread_handle_,time_out);
		if (WAIT_TIMEOUT == result)
		{
			res = false;
		}
		else if (WAIT_OBJECT_0 == res)
		{
			res = true;
		}
#elif __LINUX

#endif //__WINDOWS
		return res;
	}

	void EasyThread::set_priority( easy_int32 prority )
	{
#ifdef __WINDOWS
		if (!SetThreadPriority(thread_handle_,prority))
		{
			EASY_EXCEPTION( EasyException::kErrorInvalidParams, "SetPriority exception!", "SetPriority", kExceptionLevText );
		}
#elif __LINUX
#endif
	}

	easy_int32 EasyThread::priority() const
	{
#ifdef __WINDOWS
		return  GetThreadPriority(thread_handle_);
#elif __LINUX
#endif
	}

	void EasyThread::Stop()
	{
#ifdef __WINDOWS
		_endthreadex(0);
#elif __LINUX
#endif
	}

#ifdef __WINDOWS
	unsigned int EasyThread::_ThreadFunction( void* p )
#elif __LINUX
	void* EasyThread::_ThreadFunction( void* p )
#endif 
	{
		if (!p)
		{
			return 0;
		}
		EasyThread* _this = (EasyThread*)p;
		if (_this)
		{
			_this->_Run(p);
		}
		_this->Stop();
		return 0;
	}

	EasyThread::~EasyThread()
	{
#ifdef __WINDOWS
		CloseHandle(thread_handle_);
#elif __LINUX
#endif
	}

}