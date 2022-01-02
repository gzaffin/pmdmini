// ---------------------------------------------------------------------------
//	FM sound generator common timer module
//	Copyright (C) cisc 1998, 2000.
// ---------------------------------------------------------------------------
//	$Id: fmtimer.h,v 1.2 2003/04/22 13:12:53 cisc Exp $

#ifndef FM_TIMER_H
#define FM_TIMER_H

#include "portability_fmgen.h"

// ---------------------------------------------------------------------------

namespace FM
{
	class Timer
	{
	public:
		Timer();
		virtual ~Timer();
		
		void	Reset();
		bool	Count(int32_t us);
		int32_t	GetNextEvent();
		
	protected:
		virtual void SetStatus(uint32_t bit) = 0;
		virtual void ResetStatus(uint32_t bit) = 0;
		
		void	SetTimerBase(uint32_t clock);
		void	SetTimerA(uint32_t addr, uint32_t data);
		void	SetTimerB(uint32_t data);
		void	SetTimerControl(uint32_t data);
		
		uint8_t	status;
		uint8_t	regtc;
		
	private:
		virtual void TimerA() {}
		uint8_t	regta[2];
		
		int32_t	timera, timera_count;
		int32_t	timerb, timerb_count;
		int32_t	timer_step;
	};

// ---------------------------------------------------------------------------
//	初期化
//
inline void Timer::Reset()
{
	timera_count = 0;
	timerb_count = 0;
}

} // namespace FM

#endif // FM_TIMER_H
