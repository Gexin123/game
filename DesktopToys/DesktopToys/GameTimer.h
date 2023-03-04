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
	//����ʱ����
	void SetTimeval(unsigned int timeval)
	{
		m_timeval = timeval;
	}
	//������һ��ʱ��
	void SetLastTimer()
	{
		m_timeLast = GetTickCount();
	}
	//������ʼʱ��Ϊ��ǰʱ��
	void StartTimer()
	{
		m_timeStart = ::GetTickCount();
		m_times = 0;
	}
	//�����ܳ�ʱʱ��
	void SetTimeout(unsigned int timeout)
	{
		m_timeout = timeout;
	}
	//�ж��Ƿ�ʱ
	bool IsTimeout() const
	{
		return (GetTickCount() - m_timeLast) >= m_timeout;
	}
	//�ж��Ƿ�ﵽ��ʱ����������Ƿ���¡�
	bool IsTimeval(bool bUpdate = true)
	{
		if ((GetTickCount() - m_timeLast) >= m_timeval) {
			if (bUpdate) {
				m_timeLast = GetTickCount();
				m_times++;//��¼�����˶��ٴ�
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

//�ж�ʱ����
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
				m_times++;//��¼�����˶��ٴ�
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
