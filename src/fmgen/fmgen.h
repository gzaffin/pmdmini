// ---------------------------------------------------------------------------
//	FM Sound Generator
//	Copyright (C) cisc 1998, 2001.
// ---------------------------------------------------------------------------
//	$Id: fmgen.h,v 1.37 2003/08/25 13:33:11 cisc Exp $

#ifndef FM_GEN_H
#define FM_GEN_H

#include "portability_fmgen.h"


// ---------------------------------------------------------------------------
//	出力サンプルの型
//
#define FM_SAMPLETYPE	int32_t				// int16 or int32

// ---------------------------------------------------------------------------
//	定数その１
//	静的テーブルのサイズ

#define FM_LFOBITS		8					// 変更不可
#define FM_TLBITS		7

// ---------------------------------------------------------------------------

#define FM_TLENTS		(1 << FM_TLBITS)
#define FM_LFOENTS		(1 << FM_LFOBITS)
#define FM_TLPOS		(FM_TLENTS/4)

//	サイン波の精度は 2^(1/256)
#define FM_CLENTS		(0x1000 * 2)	// sin + TL + LFO

// ---------------------------------------------------------------------------

namespace FM
{	
	//	Types ----------------------------------------------------------------
	typedef FM_SAMPLETYPE		Sample;
	typedef int32_t				ISample;
	
	enum						OpType { typeN=0, typeM=1 };
	
	void						StoreSample(ISample& dest, int32_t data);
	
	class Chip;
	
	//	Operator -------------------------------------------------------------
	class Operator
	{
	public:
		Operator(Chip* chip, OpType type);
		void					SetChip(Chip* chip) { chip_ = chip; }
		
		static void				MakeTimeTable(uint32_t ratio);
		
		ISample					Calc(ISample in);
		ISample					CalcL(ISample in);
		ISample					CalcFB(uint32_t fb);
		ISample					CalcFBL(uint32_t fb);
		ISample					CalcN(uint32_t noise);
		void					Prepare();
		void					KeyOn();
		void					KeyOff();
		void					Reset();
		void					ResetFB();
		int32_t						IsOn();
		
		void					SetDT(uint32_t dt);
		void					SetDT2(uint32_t dt2);
		void					SetMULTI(uint32_t multi);
		void					SetTL(uint32_t tl, bool csm);
		void					SetKS(uint32_t ks);
		void					SetAR(uint32_t ar);
		void					SetDR(uint32_t dr);
		void					SetSR(uint32_t sr);
		void					SetRR(uint32_t rr);
		void					SetSL(uint32_t sl);
		void					SetSSGEC(uint32_t ssgec);
		void					SetFNum(uint32_t fnum);
		void					SetDPBN(uint32_t dp, uint32_t bn);
		void					SetMode(bool modulator);
		void					SetAMON(bool on);
		void					SetMS(uint32_t ms);
		void					Mute(bool);
		
//		static void				SetAML(uint32_t l);
//		static void				SetPML(uint32_t l);
		
		int32_t						Out() { return out_; }
		
		int32_t						dbgGetIn2() { return in2_; }
		void					dbgStopPG() { pg_diff_ = 0; pg_diff_lfo_ = 0; }
		
	private:
		typedef uint32_t		Counter;
		
		Chip*					chip_;
		ISample					out_, out2_;
		ISample					in2_;
		
	//	Phase Generator ------------------------------------------------------
		uint32_t				PGCalc();
		uint32_t				PGCalcL();
		
		uint32_t					dp_;		// ΔP
		uint32_t					detune_;		// Detune
		uint32_t					detune2_;	// DT2
		uint32_t					multiple_;	// Multiple
		uint32_t				pg_count_;	// Phase 現在値
		uint32_t				pg_diff_;	// Phase 差分値
		int32_t					pg_diff_lfo_;	// Phase 差分値 >> x
		
	//	Envelop Generator ---------------------------------------------------
		enum					EGPhase { next, attack, decay, sustain, release, off };
		
		void					EGCalc();
		void					EGStep();
		void					ShiftPhase(EGPhase nextphase);
		void					SSGShiftPhase(int32_t mode);
		void					SetEGRate(uint32_t);
		void					EGUpdate();
		int32_t						FBCalc(int32_t fb);
		ISample					LogToLin(uint32_t a);
		
		
		OpType					type_;		// OP の種類 (M, N...)
		uint32_t					bn_;		// Block/Note
		int32_t						eg_level_;	// EG の出力値
		int32_t						eg_level_on_next_phase_;	// 次の eg_phase_ に移る値
		int32_t						eg_count_;		// EG の次の変移までの時間
		int32_t						eg_count_diff_;	// eg_count_ の差分
		int32_t						eg_out_;		// EG+TL を合わせた出力値
		int32_t						tl_out_;		// TL 分の出力値
//		int32_t						pm_depth_;		// PM depth
//		int32_t						am_depth_;		// AM depth
		int32_t						eg_rate_;
		int32_t						eg_curve_count_;
		int32_t						ssg_offset_;
		int32_t						ssg_vector_;
		int32_t						ssg_phase_;
		
		
		uint32_t					key_scale_rate_;		// key scale rate
		EGPhase					eg_phase_;
		uint32_t*					ams_;
		uint32_t					ms_;
		
		uint32_t					tl_;			// Total Level	 (0-127)
		uint32_t					tl_latch_;		// Total Level Latch (for CSM mode)
		uint32_t					ar_;			// Attack Rate   (0-63)
		uint32_t					dr_;			// Decay Rate    (0-63)
		uint32_t					sr_;			// Sustain Rate  (0-63)
		uint32_t					sl_;			// Sustain Level (0-127)
		uint32_t					rr_;			// Release Rate  (0-63)
		uint32_t					ks_;			// Keyscale      (0-3)
		uint32_t					ssg_type_;	// SSG-Type Envelop Control
		
		bool					keyon_;
		bool					amon_;		// enable Amplitude Modulation
		bool					param_changed_;	// パラメータが更新された
		bool					mute_;
		
	//	Tables ---------------------------------------------------------------
		static Counter			rate_table[16];
		static uint32_t			multable[4][16];
		
		static const uint8_t	notetable[128];
		static const int8_t		dttable[256];
		static const int8_t		decaytable1[64][8];
		static const int32_t		decaytable2[16];
		static const int8_t		attacktable[64][8];
		static const int32_t		ssgenvtable[8][2][3][2];
		
		static uint32_t				sinetable[1024];
		static int32_t			cltable[FM_CLENTS];
		
		static bool				tablehasmade;
		static void				MakeTable();
		
		
		
	//	friends --------------------------------------------------------------
		friend class			Channel4;
		friend void __stdcall	FM_NextPhase(Operator* op);
		
	public:
		int32_t						dbgopout_;
		int32_t						dbgpgout_;
		static const int32_t*	dbgGetClTable() { return cltable; }
		static const uint32_t*		dbgGetSineTable() { return sinetable; }
	};
	
	//	4-op Channel ---------------------------------------------------------
	class Channel4
	{
	public:
		Channel4(Chip* chip, OpType type);
		virtual ~Channel4();
		void					SetChip(Chip* chip);
		void					SetType(OpType type);
		
		ISample					Calc();
		ISample					CalcL();
		ISample					CalcN(uint32_t noise);
		ISample					CalcLN(uint32_t noise);
		void					SetFNum(uint32_t fnum);
		void					SetFB(uint32_t fb);
		void					SetKCKF(uint32_t kc, uint32_t kf);
		void					SetAlgorithm(uint32_t algo);
		int32_t						Prepare();
		void					KeyControl(uint32_t key);
		void					Reset();
		void					SetMS(uint32_t ms);
		void					Mute(bool);
		void					Refresh();
		
		void					dbgStopPG() { for (int32_t i=0; i<4; i++) op[i]->dbgStopPG(); }
		
	private:
		static const uint8_t	fbtable[8];
		uint32_t					fb;
		int32_t						buf[4];
		int32_t*					in[3];			// 各 OP の入力ポインタ
		int32_t*					out[3];			// 各 OP の出力ポインタ
		int32_t*					pms;
		int32_t						algo_;
		Chip*					chip_;
		
		static void				MakeTable();
		
		static bool				tablehasmade;
		static int32_t				kftable[64];
		
		
	public:
		Operator*				op[4];
	};
	
	//	Chip resource
	class Chip
	{
	public:
		Chip();
		void					SetRatio(uint32_t ratio);
		void					SetAML(uint32_t l);
		void					SetPML(uint32_t l);
		void					SetPMV(int32_t pmv) { pmv_ = pmv; }
		
		uint32_t				GetMulValue(uint32_t dt2, uint32_t mul) { return multable_[dt2][mul]; }
		uint32_t					GetAML() { return aml_; }
		uint32_t					GetPML() { return pml_; }
		int32_t						GetPMV() { return pmv_; }
		uint32_t					GetRatio() { return ratio_; }
		
	private:
		void					MakeTable();
		
		uint32_t					ratio_;
		uint32_t					aml_;
		uint32_t					pml_;
		int32_t						pmv_;
		OpType					optype_;
		uint32_t				multable_[4][16];
	};
}

#endif // FM_GEN_H
