// ---------------------------------------------------------------------------
//	OPN/A/B interface with ADPCM support
//	Copyright (C) cisc 1998, 2003.
// ---------------------------------------------------------------------------
//	$Id: opna.h,v 1.33 2003/06/12 13:14:37 cisc Exp $

#ifndef FM_OPNA_H
#define FM_OPNA_H

#include "portability_fmgen.h"
#include "headers_fmgen.h"
#include "fmgen.h"
#include "fmtimer.h"
#include "file_fmgen.h"
#include "psg.h"

// ---------------------------------------------------------------------------
//	class OPN/OPNA
//	OPN/OPNA に良く似た音を生成する音源ユニット
//	
//	interface:
//	bool Init(uint32_t clock, uint32_t rate, bool, const TCHAR* path);
//		初期化．このクラスを使用する前にかならず呼んでおくこと．
//		OPNA の場合はこの関数でリズムサンプルを読み込む
//
//		clock:	OPN/OPNA/OPNB のクロック周波数(Hz)
//
//		rate:	生成する PCM の標本周波数(Hz)
//
//		path:	リズムサンプルのパス(OPNA のみ有効)
//				省略時はカレントディレクトリから読み込む
//				文字列の末尾には '\' や '/' などをつけること
//
//		返り値	初期化に成功すれば true
//
//	bool LoadRhythmSample(const TCHAR* path)
//		(OPNA ONLY)
//		Rhythm サンプルを読み直す．
//		path は Init の path と同じ．
//	
//	bool SetRate(uint32_t clock, uint32_t rate, bool)
//		クロックや PCM レートを変更する
//		引数等は Init を参照のこと．
//	
//	void Mix(FM_SAMPLETYPE* dest, int32_t nsamples)
//		Stereo PCM データを nsamples 分合成し， dest で始まる配列に
//		加える(加算する)
//		・dest には sample*2 個分の領域が必要
//		・格納形式は L, R, L, R... となる．
//		・あくまで加算なので，あらかじめ配列をゼロクリアする必要がある
//		・FM_SAMPLETYPE が short 型の場合クリッピングが行われる.
//		・この関数は音源内部のタイマーとは独立している．
//		  Timer は Count と GetNextEvent で操作する必要がある．
//	
//	void Reset()
//		音源をリセット(初期化)する
//
//	void SetReg(uint32_t reg, uint32_t data)
//		音源のレジスタ reg に data を書き込む
//	
//	uint32_t GetReg(uint32_t reg)
//		音源のレジスタ reg の内容を読み出す
//		読み込むことが出来るレジスタは PSG, ADPCM の一部，ID(0xff) とか
//	
//	uint32_t ReadStatus()/ReadStatusEx()
//		音源のステータスレジスタを読み出す
//		ReadStatusEx は拡張ステータスレジスタの読み出し(OPNA)
//		busy フラグは常に 0
//	
//	bool Count(uint32 t)
//		音源のタイマーを t [μ秒] 進める．
//		音源の内部状態に変化があった時(timer オーバーフロー)
//		true を返す
//
//	uint32 GetNextEvent()
//		音源のタイマーのどちらかがオーバーフローするまでに必要な
//		時間[μ秒]を返す
//		タイマーが停止している場合は ULONG_MAX を返す… と思う
//	
//	void SetVolumeFM(int32_t db)/SetVolumePSG(int32_t db) ...
//		各音源の音量を＋−方向に調節する．標準値は 0.
//		単位は約 1/2 dB，有効範囲の上限は 20 (10dB)
//
namespace FM
{
	//	OPN Base -------------------------------------------------------
	class OPNBase : public Timer
	{
	public:
		OPNBase();
		
		bool			Init(uint32_t c, uint32_t r);
		virtual void	Reset();
		
		void			SetVolumeFM(int32_t db);
		void			SetVolumePSG(int32_t db);
		void			SetLPFCutoff(uint32_t freq) {}	// obsolete
		
	protected:
		void			SetParameter(Channel4* ch, uint32_t addr, uint32_t data);
		void			SetPrescaler(uint32_t p);
		void			RebuildTimeTable();
		
		int32_t				fmvolume;
		
		uint32_t		clock;				// OPN クロック
		uint32_t		rate;				// FM 音源合成レート
		uint32_t		psgrate;			// FMGen  出力レート
		uint32_t		status;
		Channel4*		csmch;
		size_t			csmch_ch;
		
		
		uint32_t		lfotable[8];		// OPNA/B 用
		
	private:
		void			TimerA();
		uint8_t			prescale;
		
	protected:
		Chip			chip;
		PSG				psg;
	};
	
	//	OPN2 Base ------------------------------------------------------
	class OPNABase : public OPNBase
	{
	public:
		OPNABase();
		virtual ~OPNABase();
		
		uint32_t		ReadStatus() { return status & 0x03; }
		uint32_t		ReadStatusEx();
		void			SetChannelMask(uint32_t mask);
		
	private:
		virtual void	Intr(bool) {}
		
		void			MakeTable2();
		
	protected:
		bool			Init(uint32_t c, uint32_t r, bool);
		bool			SetRate(uint32_t c, uint32_t r, bool);
		
		void			Reset();
		void			SetReg(uint32_t addr, uint32_t data);
		void			SetADPCMBReg(uint32_t reg, uint32_t data);
		uint32_t		GetReg(uint32_t addr);	
		
	protected:
		void			FMMix(Sample* buffer, int32_t nsamples);
		void 			Mix6(Sample* buffer, int32_t nsamples, int32_t activech);
		
		void			MixSubS(int32_t activech, ISample**);
		void			MixSubSL(int32_t activech, ISample**);
		
		void			SetStatus(uint32_t bit);
		void			ResetStatus(uint32_t bit);
		void			UpdateStatus();
		void			LFO();
		
		void			DecodeADPCMB();
		void			ADPCMBMix(Sample* dest, uint32_t count);
		
		void			WriteRAM(uint32_t data);
		uint32_t		ReadRAM();
		int32_t				ReadRAMN();
		int32_t				DecodeADPCMBSample(uint32_t);
		
	// FM 音源関係
		uint8_t			pan[6];
		uint8_t			fnum2[9];
		
		uint8_t			reg22;
		uint32_t		reg29;			// OPNA only?
		
		uint32_t		stmask;
		uint32_t		statusnext;
		
		uint32_t		lfocount;
		uint32_t		lfodcount;
		
		uint32_t		fnum[6];
		uint32_t		fnum3[3];
		
	// ADPCM 関係
		uint8_t*		adpcmbuf;		// ADPCM RAM
		uint32_t		adpcmmask;		// メモリアドレスに対するビットマスク
		uint32_t		adpcmnotice;	// ADPCM 再生終了時にたつビット
		uint32_t		startaddr;		// Start address
		uint32_t		stopaddr;		// Stop address
		uint32_t		memaddr;		// 再生中アドレス
		uint32_t		limitaddr;		// Limit address/mask
		int32_t				adpcmlevel;		// ADPCM 音量
		int32_t				adpcmvolume;
		int32_t				adpcmvol;
		uint32_t		deltan;			// ⊿N
		int32_t				adplc;			// 周波数変換用変数
		int32_t				adpld;			// 周波数変換用変数差分値
		uint32_t		adplbase;		// adpld の元
		int32_t				adpcmx;			// ADPCM 合成用 x
		int32_t				adpcmd;			// ADPCM 合成用 ⊿
		int32_t				adpcmout;		// ADPCM 合成後の出力
		int32_t				apout0;			// out(t-2)+out(t-1)
		int32_t				apout1;			// out(t-1)+out(t)
		
		uint32_t		adpcmreadbuf;	// ADPCM リード用バッファ
		bool			adpcmplay;		// ADPCM 再生中
		int8_t			granuality;
		bool			adpcmmask_;
		
		uint8_t			control1;		// ADPCM コントロールレジスタ１
		uint8_t			control2;		// ADPCM コントロールレジスタ２
		uint8_t			adpcmreg[8];	// ADPCM レジスタの一部分
		
		int32_t				rhythmmask_;
		
		Channel4*		ch[6];
		
		static void		BuildLFOTable();
		static int32_t		amtable[FM_LFOENTS];
		static int32_t		pmtable[FM_LFOENTS];
		static int32_t	tltable[FM_TLENTS+FM_TLPOS];
		static bool		tablehasmade;
	};
	
	//	YM2203(OPN) ----------------------------------------------------
	class OPN : public OPNBase
	{
	public:
		OPN();
		virtual ~OPN();
		
		bool			Init(uint32_t c, uint32_t r, bool=false, const TCHAR* =0);
		bool			SetRate(uint32_t c, uint32_t r, bool=false);
		
		void			Reset();
		void			Mix(Sample* buffer, int32_t nsamples);
		void			SetReg(uint32_t addr, uint32_t data);
		uint32_t		GetReg(uint32_t addr);
		uint32_t		ReadStatus() { return status & 0x03; }
		uint32_t		ReadStatusEx() { return 0xff; }
		
		void			SetChannelMask(uint32_t mask);
		
		int32_t				dbgGetOpOut(int32_t c, int32_t s) { return ch[c]->op[s]->dbgopout_; }
		int32_t				dbgGetPGOut(int32_t c, int32_t s) { return ch[c]->op[s]->dbgpgout_; }
		Channel4*		dbgGetCh(int32_t c) { return ch[c]; }
		
	private:
		virtual void	Intr(bool) {}
		
		void			SetStatus(uint32_t bit);
		void			ResetStatus(uint32_t bit);
		
		uint32_t		fnum[3];
		uint32_t		fnum3[3];
		uint8_t			fnum2[6];
		
		Channel4*		ch[3];
	};
	
	//	YM2608(OPNA) ---------------------------------------------------
	class OPNA : public OPNABase
	{
	public:
		OPNA(IFILEIO* pfileio);
		virtual ~OPNA();
		void		setfileio(IFILEIO* pfileio);
		
		bool		Init(uint32_t c, uint32_t r, bool = false, const TCHAR* rhythmpath=0);
		bool		LoadRhythmSample(const TCHAR*);
		
		bool		SetRate(uint32_t c, uint32_t r, bool = false);
		void		Mix(Sample* buffer, int32_t nsamples);
		
		void		Reset();
		void		SetReg(uint32_t addr, uint32_t data);
		uint32_t	GetReg(uint32_t addr);
		
		void		SetVolumeADPCM(int32_t db);
		void		SetVolumeRhythmTotal(int32_t db);
		void		SetVolumeRhythm(int32_t index, int32_t db);
		
		uint8_t*	GetADPCMBuffer() { return adpcmbuf; }
		
		int32_t			dbgGetOpOut(int32_t c, int32_t s) { return ch[c]->op[s]->dbgopout_; }
		int32_t			dbgGetPGOut(int32_t c, int32_t s) { return ch[c]->op[s]->dbgpgout_; }
		Channel4*	dbgGetCh(int32_t c) { return ch[c]; }
		
	private:
		IFILEIO* pfileio;							// ファイルアクセス関連のクラスライブラリ
		
		struct Rhythm
		{
			uint8_t		pan;		// ぱん
			int8_t		level;		// おんりょう
			int32_t			volume;		// おんりょうせってい
			int16_t*	sample;		// さんぷる
			uint32_t	size;		// さいず
			uint32_t	pos;		// いち
			uint32_t	step;		// すてっぷち
			uint32_t	rate;		// さんぷるのれーと
		};
		
		void	RhythmMix(Sample* buffer, uint32_t count);
		
	// リズム音源関係
		Rhythm	rhythm[6];
		int8_t	rhythmtl;		// リズム全体の音量
		int32_t		rhythmtvol;
		uint8_t	rhythmkey;		// リズムのキー
	};
	
	//	YM2610/B(OPNB) ---------------------------------------------------
	class OPNB : public OPNABase
	{
	public:
		OPNB();
		virtual ~OPNB();
		
		bool	Init(uint32_t c, uint32_t r, bool = false,
					 uint8_t *_adpcma = 0, int32_t _adpcma_size = 0,
					 uint8_t *_adpcmb = 0, int32_t _adpcmb_size = 0);
		
		bool	SetRate(uint32_t c, uint32_t r, bool = false);
		void 	Mix(Sample* buffer, int32_t nsamples);
		
		void	Reset();
		void 	SetReg(uint32_t addr, uint32_t data);
		uint32_t	GetReg(uint32_t addr);
		uint32_t	ReadStatusEx();
		
		void	SetVolumeADPCMATotal(int32_t db);
		void	SetVolumeADPCMA(int32_t index, int32_t db);
		void	SetVolumeADPCMB(int32_t db);
		
//		void	SetChannelMask(uint32_t mask);
		
	private:
		struct ADPCMA
		{
			uint8_t	pan;		// ぱん
			int8_t	level;		// おんりょう
			int32_t		volume;		// おんりょうせってい
			uint32_t	pos;		// いち
			uint32_t	step;		// すてっぷち
			
			uint32_t	start;		// 開始
			uint32_t	stop;		// 終了
			uint32_t	nibble;		// 次の 4 bit
			int32_t		adpcmx;		// 変換用
			int32_t		adpcmd;		// 変換用
		};
		
		int32_t		DecodeADPCMASample(uint32_t);
		void	ADPCMAMix(Sample* buffer, uint32_t count);
		static void InitADPCMATable();
		
	// ADPCMA 関係
		uint8_t*	adpcmabuf;		// ADPCMA ROM
		int32_t		adpcmasize;
		ADPCMA	adpcma[6];
		int8_t	adpcmatl;		// ADPCMA 全体の音量
		int32_t		adpcmatvol;
		uint8_t	adpcmakey;		// ADPCMA のキー
		int32_t		adpcmastep;
		uint8_t	adpcmareg[32];
		
		static int32_t jedi_table[(48+1)*16];
		
		Channel4* ch[6];
	};
	
	//	YM2612/3438(OPN2) ----------------------------------------------------
	class OPN2 : public OPNBase
	{
	public:
		OPN2();
		virtual ~OPN2() {}
		
		bool	Init(uint32_t c, uint32_t r, bool=false, const TCHAR* =0);
		bool	SetRate(uint32_t c, uint32_t r, bool);
		
		void	Reset();
		void 	Mix(Sample* buffer, int32_t nsamples);
		void 	SetReg(uint32_t addr, uint32_t data);
		uint32_t	GetReg(uint32_t addr);
		uint32_t	ReadStatus() { return status & 0x03; }
		uint32_t	ReadStatusEx() { return 0xff; }
		
		void	SetChannelMask(uint32_t mask);
		
	private:
		virtual void Intr(bool) {}
		
		void	SetStatus(uint32_t bit);
		void	ResetStatus(uint32_t bit);
		
		uint32_t	fnum[3];
		uint32_t	fnum3[3];
		uint8_t	fnum2[6];
		
	// 線形補間用ワーク
		int32_t	mixc, mixc1;
		
		Channel4* ch[3];
	};
}

// ---------------------------------------------------------------------------

inline void FM::OPNBase::RebuildTimeTable()
{
	int32_t p = prescale;
	prescale = -1;
	SetPrescaler(p);
}

inline void FM::OPNBase::SetVolumePSG(int32_t db)
{
	psg.SetVolume(db);
}

#endif // FM_OPNA_H
