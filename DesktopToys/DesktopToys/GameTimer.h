#pragma once
#include <windows.h>
class CGameTimer
{
private:
	unsigned int m_timeStart{ ::GetTickCount() };
	unsigned int m_timeout{ 3000 };
	unsigned int m_timeLast{ m_timeStart };
	unsigned int m_timeval{ 300 };
	unsigned int m_times{ 0 };
public:
	explicit CGameTimer(unsigned int timeout = 3000, unsigned int timeval = 300) :m_timeout(timeout), m_timeval(timeval)
	{
	}
	virtual ~CGameTimer(){}
	//设置时间间隔
	void SetTimeval(unsigned int timeval)
	{
		m_timeval = timeval;
	}
	//设置上一次时间
	void SetLastTimer()
	{
		m_timeLast = GetTickCount();
	}
	//重设起始时间为当前时间
	void StartTimer()
	{
		m_timeStart = ::GetTickCount();
		m_times = 0;
	}
	//设置总超时时间
	void SetTimeout(unsigned int timeout)
	{
		m_timeout = timeout;
	}
	//判断是否超时
	bool IsTimeout() const
	{
		return (GetTickCount() - m_timeLast) >= m_timeout;
	}
	//判断是否达到了时间间隔：到达，是否更新、
	bool IsTimeval(bool bUpdate = true)
	{
		if ((GetTickCount() - m_timeLast) >= m_timeval) {
			if (bUpdate) {
				m_timeLast = GetTickCount();
				m_times++;//记录更新了多少次
			}
			return true;
		}
		else { return false; }
	}
	size_t GetTimes() const
	{
		return m_times;
	 }
};

//判断时间间隔
class CGameTimeval
{
private:
	unsigned int m_timeLast{ GetTickCount() };
	unsigned int m_timeval{ 300 };
	unsigned int m_times{ 0 };
public:
	explicit CGameTimeval(unsigned int timeval=300)
		:m_timeval(timeval){}
	virtual ~CGameTimeval(){}
	void Restart()
	{
		m_timeLast = GetTickCount();
		m_times = 0;
	}
	void SetTimeval(unsigned int timeval)
	{
		m_timeval = timeval;
	}
	void SetLastTime()
	{
		m_timeLast = GetTickCount();
	}
	bool IsTimeval(bool bUpdate = true)
	{
		if ((GetTickCount() - m_timeLast) >= m_timeval) {
			if (bUpdate) {
				m_timeLast = GetTickCount();
				m_times++;//记录更新了多少次
			}
			return true;
		}
		else { return false; }
	}
	size_t GetTimes() const
	{
		return m_times;
	}
};
