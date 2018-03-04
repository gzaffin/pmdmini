//=============================================================================
//	Professional Music Driver [P.M.D.] version 4.8
//			DLL Import Header
//			Programmed By M.Kajihara
//			Windows Converted by C60
//=============================================================================

#ifndef PMDWINIMPORT_H
#define PMDWINIMPORT_H

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include "sys/types.h"
#endif
#ifdef ENABLE_COM_INTERFACE
# include "PCMMusDriver.h"
#endif

#ifdef _WIN32
# include <windows.h>
#ifdef USE_DLL
    #ifdef BUILDING_PROJECT
        #define API_ATTRIBUTE __declspec(dllexport)
    #else
        #define API_ATTRIBUTE __declspec(dllimport)
    #endif
#else
    #define API_ATTRIBUTE
#endif
#else
# include "compat.h"
#ifndef _MAX_PATH
# define _MAX_PATH FILENAME_MAX
#endif
#endif

#define	InterfaceVersion			117		// �壱�塧major, �����塧minor version

//	DLL �� ��??��
#define	PMDWIN_OK				  0		// ��??��λ
#define	ERR_OPEN_MUSIC_FILE			  1		// �� �ǡ����򳫤��ʤ��ä�
#define	ERR_WRONG_MUSIC_FILE		 	  2		// PMD �ζʥǡ����ǤϤʤ��ä�
#define	ERR_OPEN_PPC_FILE		 	  3		// PPC �򳫤��ʤ��ä�
#define	ERR_OPEN_P86_FILE		 	  4		// P86 �򳫤��ʤ��ä�
#define	ERR_OPEN_PPS_FILE		 	  5		// PPS �򳫤��ʤ��ä�
#define	ERR_OPEN_PPZ1_FILE		 	  6		// PPZ1 �򳫤��ʤ��ä�
#define	ERR_OPEN_PPZ2_FILE		 	  7		// PPZ2 �򳫤��ʤ��ä�
#define	ERR_WRONG_PPC_FILE		 	  8		// PPC/PVI �ǤϤʤ��ä�c
#define	ERR_WRONG_P86_FILE		 	  9		// P86 �ǤϤʤ��ä�
#define	ERR_WRONG_PPS_FILE		 	 10		// PPS �ǤϤʤ��ä�
#define	ERR_WRONG_PPZ1_FILE		 	 11		// PVI/PZI �ǤϤʤ��ä�(PPZ1)
#define	ERR_WRONG_PPZ2_FILE		 	 12		// PVI/PZI �ǤϤʤ��ä�(PPZ2)
#define	WARNING_PPC_ALREADY_LOAD		 13		// PPC �Ϥ��Ǥ��ɤ�??��??�Ƥ�??
#define	WARNING_P86_ALREADY_LOAD		 14		// P86 �Ϥ��Ǥ��ɤ�??��??�Ƥ�??
#define	WARNING_PPS_ALREADY_LOAD		 15		// PPS �Ϥ��Ǥ��ɤ�??��??�Ƥ�??
#define	WARNING_PPZ1_ALREADY_LOAD		 16		// PPZ1 �Ϥ��Ǥ��ɤ�??��??�Ƥ�??
#define	WARNING_PPZ2_ALREADY_LOAD		 17		// PPZ2 �Ϥ��Ǥ��ɤ�??��??�Ƥ�??

#define	ERR_WRONG_PARTNO			 30		// �ѡ����ֹ椬��Ŭ
//#define ERR_ALREADY_MASKED			 31		// ��??�ѡ��ȤϤ��Ǥ˥ޥ�����??�Ƥ�??
#define	ERR_NOT_MASKED				 32		// ��??�ѡ��Ȥϥޥ�����??�Ƥ��ʤ�
#define	ERR_MUSIC_STOPPED			 33		// �ʤ��ߤޤäƤ�??�Τ˥ޥ�������򤷤�
#define	ERR_EFFECT_USED				 34		// ���̲��ǻ�����ʤΤǥޥ���������Ǥ��ʤ�

#define	ERR_OUT_OF_MEMORY			 99		// �������ݤǤ��ʤ��ä�
#define	ERR_OTHER				999		// ����¾�Υ��顼


#define	SOUND_55K			  55555
#define	SOUND_48K			  48000
#define	SOUND_44K			  44100
#define	SOUND_22K			  22050
#define	SOUND_11K			  11025

#define	PPZ8_i0				  44100
#define	PPZ8_i1				  33080
#define	PPZ8_i2				  22050
#define	PPZ8_i3				  16540
#define	PPZ8_i4				  11025
#define	PPZ8_i5				   8270
#define	PPZ8_i6				   5513
#define	PPZ8_i7				   4135

#define	MAX_PCMDIR			     64
#define	MAX_MEMOBUF			   1024

#define	NumOfFMPart			      6
#define	NumOfSSGPart		   	      3
#define	NumOfADPCMPart			      1
#define	NumOFOPNARhythmPart		      1
#define	NumOfExtPart			      3
#define	NumOfRhythmPart			      1
#define	NumOfEffPart			      1
#define	NumOfPPZ8Part			      8
#define	NumOfAllPart			(NumOfFMPart+NumOfSSGPart+NumOfADPCMPart+NumOFOPNARhythmPart+NumOfExtPart+NumOfRhythmPart+NumOfEffPart+NumOfPPZ8Part)

typedef unsigned char uchar;
typedef unsigned short ushort;
#ifndef __ANDROID__
 typedef unsigned int uint;
#endif
#ifndef __cplusplus
typedef unsigned char bool;
#endif


/******************************************************************************
;	WORK AREA
******************************************************************************/


//	������Υǡ�����??��
typedef struct qqtag {
	uchar		*address;			//	2 ���󥽥����奦 �� ����??��
	uchar		*partloop;			//	2 ���󥽥� �� ��??�å��ȥ� �� ���??����
	int		leng;				//	1 �Υ�?? LENGTH
	int		qdat;				//	1 gatetime (q/Q�ͤ�׻�������)
	uint		fnum;				//	2 ���󥽥����奦 �� BLOCK/FNUM
	int		detune;				//	2 �ǥ��塼??
	int		lfodat;				//	2 LFO DATA
	int		porta_num;			//	2 ��??�����Ȥβø��͡����Ρ�
	int		porta_num2;			//	2 ��??�����Ȥβø��͡�??���
	int		porta_num3;			//	2 ��??�����Ȥβø��͡�;���
	int		volume;				//	1 VOLUME
	int		shift;				//	1 ���󥫥� ���ե� �� ������
	int		delay;				//	1 LFO	[DELAY] 
	int		speed;				//	1	[SPEED]
	int		step;				//	1	[STEP]
	int		time;				//	1	[TIME]
	int		delay2;				//	1	[DELAY_2]
	int		speed2;				//	1	[SPEED_2]
	int		step2;				//	1	[STEP_2]
	int		time2;				//	1	[TIME_2]
	int		lfoswi;				//	1 LFOSW. B0/tone B1/vol B2/Ʊ?? B3/porta
							//	         B4/tone B5/vol B6/Ʊ??
	int		volpush;			//	1 Volume PUSHarea
	int		mdepth;				//	1 M depth
	int		mdspd;				//	1 M speed
	int		mdspd2;				//	1 M speed_2
	int		envf;				//	1 PSG ENV. [START_FLAG] / -1��extend
	int		eenv_count;			//	1 ExtendPSGenv/No=0 AR=1 DR=2 SR=3 RR=4
	int		eenv_ar;			//	1 	/AR		/??pat
	int		eenv_dr;			//	1	/DR		/??pv2
	int		eenv_sr;			//	1	/SR		/??pr1
	int		eenv_rr;			//	1	/RR		/??pr2
	int		eenv_sl;			//	1	/SL
	int		eenv_al;			//	1	/AL
	int		eenv_arc;			//	1	/AR�Υ�����	/??patb
	int		eenv_drc;			//	1	/DR�Υ�����
	int		eenv_src;			//	1	/SR�Υ�����	/??pr1b
	int		eenv_rrc;			//	1	/RR�Υ�����	/??pr2b
	int		eenv_volume;			//	1	/Volume��(0��15)/??penv
	int		extendmode;			//	1 B1/Detune B2/LFO B3/Env Normal/Extend
	int		fmpan;				//	1 FM Panning + AMD + PMD
	int		psgpat;				//	1 PSG PATTERN [TONE/NOISE/MIX]
	int		voicenum;			//	1 ������??
	int		loopcheck;			//	1 ??���פ����飱 ��λ�����飳
	int		carrier;			//	1 FM Carrier
	int		slot1;				//	1 SLOT 1 �� TL
	int		slot3;				//	1 SLOT 3 �� TL
	int		slot2;				//	1 SLOT 2 �� TL
	int		slot4;				//	1 SLOT 4 �� TL
	int		slotmask;			//	1 FM slotmask
	int		neiromask;			//	1 FM ����??����maskdata
	int		lfo_wave;			//	1 LFO���ȷ�
	int		partmask;			//	1 PartMask b0:��?? b1:���̲� b2:NECPCM��
							//	   b3:none b4:PPZ/ADE�� b5:s0?? b6:m b7:????
	int		keyoff_flag;			//	1 Keyoff�������ɤ�����Flag
	int		volmask;			//	1 ����LFO�Υޥ���
	int		qdata;				//	1 q����
	int		qdatb;				//	1 Q����
	int		hldelay;			//	1 HardLFO delay
	int		hldelay_c;			//	1 HardLFO delay Counter
	int		_lfodat;			//	2 LFO DATA
	int		_delay;				//	1 LFO	[DELAY] 
	int		_speed;				//	1		[SPEED]
	int		_step;				//	1		[STEP]
	int		_time;				//	1		[TIME]
	int		_delay2;			//	1		[DELAY_2]
	int		_speed2;			//	1		[SPEED_2]
	int		_step2;				//	1		[STEP_2]
	int		_time2;				//	1		[TIME_2]
	int		_mdepth;			//	1 M depth
	int		_mdspd;				//	1 M speed
	int		_mdspd2;			//	1 M speed_2
	int		_lfo_wave;			//	1 LFO���ȷ�
	int		_volmask;			//	1 ����LFO�Υޥ���
	int		mdc;				//	1 M depth Counter (��ư��)
	int		mdc2;				//	1 M depth Counter
	int		_mdc;				//	1 M depth Counter (��ư��)
	int		_mdc2;				//	1 M depth Counter
	int		onkai;				//	1 ������β����ǡ��� (0ffh:rest)
	int		sdelay;				//	1 Slot delay
	int		sdelay_c;			//	1 Slot delay counter
	int		sdelay_m;			//	1 Slot delay Mask
	int		alg_fb;				//	1 ������alg/fb
	int		keyon_flag;			//	1 ������/����ǡ������??������inc
	int		qdat2;				//	1 q �����ݾ���
	int		onkai_def;			//	1 ������β����ǡ��� (žĴ��??�� / ?fh:rest)
	int		shift_def;			//	1 �ޥ�����žĴ��
	int		qdat3;				//	1 q Random
} QQ;


typedef struct OpenWorktag {
	QQ		*MusPart[NumOfAllPart];		// �ѡ���??�����Υݥ���
	uchar		*mmlbuf;			//	Musicdata��address+1
	uchar		*tondat;			//	Voicedata��address
	uchar		*efcdat;			//	FM  Effecdata��address
	uchar		*prgdat_adr;			//	�ʥǡ����治���ǡ�����Ƭ����
	ushort		*radtbl;			//	R part offset table ��Ƭ����
	uchar		*rhyadr;			//	R part ����������
	int		rhythmmask;			//	Rhythm�����Υޥ��� x8c/10h��bit����??
	int		fm_voldown;			//	FM voldown ����
	int		ssg_voldown;			//	PSG voldown ����
	int		pcm_voldown;			//	ADPCM voldown ����
	int		rhythm_voldown;			//	RHYTHM voldown ����
	int		prg_flg;			//	�ʥǡ����˲������ޤ�??�Ƥ�??��flag
	int		x68_flg;			//	OPM flag
	int		status;				//	status1
	int		status2;			//	status2
	int		tempo_d;			//	tempo (TIMER-B)
	int		fadeout_speed;			//	Fadeout®��
	int		fadeout_volume;			//	Fadeout����
	int		tempo_d_push;			//	tempo (TIMER-B) / ��¸��
	int		syousetu_lng;			//	�����Ĺ��
	int		opncount;			//	��û���䥫����
	int		TimerAtime;			//	TimerA������
	int		effflag;			//	PSG���̲�ȯ��on/off flag(�桼��������??)
	int		psnoi;				//	PSG noise??��??
	int		psnoi_last;			//	PSG noise??��??(�Ǹ��??����������)
	int		pcmstart;			//	PCM������start��
	int		pcmstop;			//	PCM������stop��
	int		rshot_dat;			//	??���಻�� shot flag
	int		rdat[6];			//	??���಻�� ����/�ѥ�ǡ���
	int		rhyvol;				//	??����ȡ���????��??
	int		kshot_dat;			//	�ӣӣ�??��?? shot flag
	int		play_flag;			//	play flag
	int		fade_stop_flag;			//	Fadeout?? MSTOP��??���ɤ����Υե饰
	bool		kp_rhythm_flag;			//	K/Rpart��Rhythm�������Ĥ餹��flag
	int		pcm_gs_flag;			//	ADPCM���� ���ĥե饰 (0�ǵ���)
	int		slot_detune1;			//	FM3 Slot Detune�� slot1
	int		slot_detune2;			//	FM3 Slot Detune�� slot2
	int		slot_detune3;			//	FM3 Slot Detune�� slot3
	int		slot_detune4;			//	FM3 Slot Detune�� slot4
	int		TimerB_speed;			//	TimerB�θ�����(=ff_tempo�ʤ�ff??)
	int		fadeout_flag;			//	��������fout��ƤӽФ���??1
	int		revpan;				//	PCM86����flag
	int		pcm86_vol;			//	PCM86�β��̤�SPB�˹�??��??��?
	int		syousetu;			//	���ᥫ����
	int		port22h;			//	OPN-PORT 22H �˺Ǹ�˽��Ϥ�����(hlfo)
	int		tempo_48;			//	���ߤΥƥ��(clock=48 t����)
	int		tempo_48_push;			//	���ߤΥƥ��(Ʊ??/��¸��)
	int		_fm_voldown;			//	FM voldown ���� (��¸��)
	int		_ssg_voldown;			//	PSG voldown ���� (��¸��)
	int		_pcm_voldown;			//	PCM voldown ���� (��¸��)
	int		_rhythm_voldown;		//	RHYTHM voldown ���� (��¸��)
	int		_pcm86_vol;			//	PCM86�β��̤�SPB�˹�??��??��? (��¸��)
	int		rshot_bd;			//	??���಻�� shot inc flag (BD)
	int		rshot_sd;			//	??���಻�� shot inc flag (SD)
	int		rshot_sym;			//	??���಻�� shot inc flag (CYM)
	int		rshot_hh;			//	??���಻�� shot inc flag (HH)
	int		rshot_tom;			//	??���಻�� shot inc flag (TOM)
	int		rshot_rim;			//	??���಻�� shot inc flag (RIM)
	int		rdump_bd;			//	??���಻�� dump inc flag (BD)
	int		rdump_sd;			//	??���಻�� dump inc flag (SD)
	int		rdump_sym;			//	??���಻�� dump inc flag (CYM)
	int		rdump_hh;			//	??���಻�� dump inc flag (HH)
	int		rdump_tom;			//	??���಻�� dump inc flag (TOM)
	int		rdump_rim;			//	??���಻�� dump inc flag (RIM)
	int		ch3mode;			//	ch3 Mode
	int		ppz_voldown;			//	PPZ8 voldown ����
	int		_ppz_voldown;			//	PPZ8 voldown ���� (��¸��)
	int		TimerAflag;			//	TimerA��????���桩�ե饰�ʡ����ס���
	int		TimerBflag;			//	TimerB��????���桩�ե饰�ʡ����ס���

	// for PMDWin
	int		rate;				//	PCM ����??��??(11k, 22k, 44k, 55k)
	bool		ppz8ip;				//	PPZ8 ���䴰��??��
	bool		ppsip;				//	PPS  ���䴰��??��
	bool		p86ip;				//	P86  ���䴰��??��
	bool		use_p86;			//	P86  ����Ѥ��Ƥ�??��
	int		fadeout2_speed;			//	fadeout(�ⲻ��)speed(>0�� fadeout)
	char		mus_filename[_MAX_PATH];	//	�ʤ�FILE̾�Хåե�
	char		ppcfilename[_MAX_PATH];		//	PPC ��FILE̾�Хåե�
	char		pcmdir[MAX_PCMDIR+1][_MAX_PATH];//	PCM �����ǥ�??����??
} OPEN_WORK;


//=============================================================================
//	COM ?? interface class
//=============================================================================
#ifdef ENABLE_COM_INTERFACE
interface IPMDWIN : public IFMPMD {
	virtual void WINAPI setppsuse(bool value) = 0;
	virtual void WINAPI setrhythmwithssgeffect(bool value) = 0;
	virtual void WINAPI setpmd86pcmmode(bool value) = 0;
	virtual bool WINAPI getpmd86pcmmode(void) = 0;
	virtual void WINAPI setppsinterpolation(bool ip) = 0;
	virtual void WINAPI setp86interpolation(bool ip) = 0;
	virtual int WINAPI maskon(int ch) = 0;
	virtual int WINAPI maskoff(int ch) = 0;
	virtual void WINAPI setfmvoldown(int voldown) = 0;
	virtual void WINAPI setssgvoldown(int voldown) = 0;
	virtual void WINAPI setrhythmvoldown(int voldown) = 0;
	virtual void WINAPI setadpcmvoldown(int voldown) = 0;
	virtual void WINAPI setppzvoldown(int voldown) = 0;
	virtual int WINAPI getfmvoldown(void) = 0;
	virtual int WINAPI getfmvoldown2(void) = 0;
	virtual int WINAPI getssgvoldown(void) = 0;
	virtual int WINAPI getssgvoldown2(void) = 0;
	virtual int WINAPI getrhythmvoldown(void) = 0;
	virtual int WINAPI getrhythmvoldown2(void) = 0;
	virtual int WINAPI getadpcmvoldown(void) = 0;
	virtual int WINAPI getadpcmvoldown2(void) = 0;
	virtual int WINAPI getppzvoldown(void) = 0;
	virtual int WINAPI getppzvoldown2(void) = 0;
	virtual char* WINAPI getmemo(char *dest, uchar *musdata, int size, int al) = 0;
	virtual char* WINAPI getmemo2(char *dest, uchar *musdata, int size, int al) = 0;
	virtual char* WINAPI getmemo3(char *dest, uchar *musdata, int size, int al) = 0;
	virtual int	WINAPI fgetmemo(char *dest, char *filename, int al) = 0;
	virtual int	WINAPI fgetmemo2(char *dest, char *filename, int al) = 0;
	virtual int	WINAPI fgetmemo3(char *dest, char *filename, int al) = 0;
	virtual char* WINAPI getppcfilename(char *dest) = 0;
	virtual char* WINAPI getppsfilename(char *dest) = 0;
	virtual char* WINAPI getp86filename(char *dest) = 0;
	virtual int WINAPI ppc_load(char *filename) = 0;
	virtual int WINAPI pps_load(char *filename) = 0;
	virtual int WINAPI p86_load(char *filename) = 0;
	virtual int WINAPI ppz_load(char *filename, int bufnum) = 0;
	virtual OPEN_WORK* WINAPI getopenwork(void) = 0;
	virtual QQ* WINAPI getpartwork(int ch) = 0;
};


//=============================================================================
//	Interface ID(IID) & Class ID(CLSID)
//=============================================================================

// GUID of IPMDWIN Interface ID
interface	__declspec(uuid("C07008F4-CAE0-421C-B08F-D8B319AFA4B4")) IPMDWIN;	

// GUID of PMDWIN Class ID
class		__declspec(uuid("97C7C3F0-35D8-4304-8C1B-AA926E7AEC5C")) PMDWIN;

const IID	IID_IPMDWIN	= _uuidof(IPMDWIN);	// IPMDWIN Interface ID
const CLSID	CLSID_PMDWIN	= _uuidof(PMDWIN);	// PMDWIN Class ID
#endif /* ENABLE_COM_INTERFACE */

//=============================================================================
//	DLL Export Functions
//=============================================================================

#ifdef __cplusplus
extern "C" {
#endif

API_ATTRIBUTE int WINAPI getversion(void);
API_ATTRIBUTE int WINAPI getinterfaceversion(void);
API_ATTRIBUTE bool WINAPI pmdwininit(char *path);
API_ATTRIBUTE bool WINAPI loadrhythmsample(char *path);
API_ATTRIBUTE bool WINAPI setpcmdir(char **path);
API_ATTRIBUTE void WINAPI setpcmrate(int rate);
API_ATTRIBUTE void WINAPI setppzrate(int rate);
API_ATTRIBUTE void WINAPI setppsuse(bool value);
API_ATTRIBUTE void WINAPI setrhythmwithssgeffect(bool value);
API_ATTRIBUTE void WINAPI setpmd86pcmmode(bool value);
API_ATTRIBUTE bool WINAPI getpmd86pcmmode(void);
API_ATTRIBUTE int WINAPI music_load(char *filename);
API_ATTRIBUTE int WINAPI music_load2(uchar *musdata, int size);
API_ATTRIBUTE void WINAPI music_start(void);
API_ATTRIBUTE void WINAPI music_stop(void);
API_ATTRIBUTE void WINAPI fadeout(int speed);
API_ATTRIBUTE void WINAPI fadeout2(int speed);
API_ATTRIBUTE void WINAPI getpcmdata(short *buf, int nsamples);
API_ATTRIBUTE void WINAPI setfmcalc55k(bool flag);
API_ATTRIBUTE void WINAPI setppsinterpolation(bool ip);
API_ATTRIBUTE void WINAPI setp86interpolation(bool ip);
API_ATTRIBUTE void WINAPI setppzinterpolation(bool ip);
API_ATTRIBUTE char * WINAPI getmemo(char *dest, uchar *musdata, int size, int al);
API_ATTRIBUTE char * WINAPI getmemo2(char *dest, uchar *musdata, int size, int al);
API_ATTRIBUTE char * WINAPI getmemo3(char *dest, uchar *musdata, int size, int al);
API_ATTRIBUTE char * WINAPI fgetmemo(char *dest, char *filename, int al);
API_ATTRIBUTE char * WINAPI fgetmemo2(char *dest, char *filename, int al);
API_ATTRIBUTE char * WINAPI fgetmemo3(char *dest, char *filename, int al);
API_ATTRIBUTE char * WINAPI getmusicfilename(char *dest);
API_ATTRIBUTE char * WINAPI getpcmfilename(char *dest);
API_ATTRIBUTE char * WINAPI getppcfilename(char *dest);
API_ATTRIBUTE char * WINAPI getppsfilename(char *dest);
API_ATTRIBUTE char * WINAPI getp86filename(char *dest);
API_ATTRIBUTE char * WINAPI getppzfilename(char *dest, int bufnum);
API_ATTRIBUTE int WINAPI ppc_load(char *filename);
API_ATTRIBUTE int WINAPI pps_load(char *filename);
API_ATTRIBUTE int WINAPI p86_load(char *filename);
API_ATTRIBUTE int WINAPI ppz_load(char *filename, int bufnum);
API_ATTRIBUTE int WINAPI maskon(int ch);
API_ATTRIBUTE int WINAPI maskoff(int ch);
API_ATTRIBUTE void WINAPI setfmvoldown(int voldown);
API_ATTRIBUTE void WINAPI setssgvoldown(int voldown);
API_ATTRIBUTE void WINAPI setrhythmvoldown(int voldown);
API_ATTRIBUTE void WINAPI setadpcmvoldown(int voldown);
API_ATTRIBUTE void WINAPI setppzvoldown(int voldown);
API_ATTRIBUTE int WINAPI getfmvoldown(void);
API_ATTRIBUTE int WINAPI getfmvoldown2(void);
API_ATTRIBUTE int WINAPI getssgvoldown(void);
API_ATTRIBUTE int WINAPI getssgvoldown2(void);
API_ATTRIBUTE int WINAPI getrhythmvoldown(void);
API_ATTRIBUTE int WINAPI getrhythmvoldown2(void);
API_ATTRIBUTE int WINAPI getadpcmvoldown(void);
API_ATTRIBUTE int WINAPI getadpcmvoldown2(void);
API_ATTRIBUTE int WINAPI getppzvoldown(void);
API_ATTRIBUTE int WINAPI getppzvoldown2(void);
API_ATTRIBUTE void WINAPI setpos(int pos);
API_ATTRIBUTE void WINAPI setpos2(int pos);
API_ATTRIBUTE int WINAPI getpos(void);
API_ATTRIBUTE int WINAPI getpos2(void);
API_ATTRIBUTE bool WINAPI getlength(char *filename, int *length, int *loop);
API_ATTRIBUTE bool WINAPI getlength2(char *filename, int *length, int *loop);
API_ATTRIBUTE int WINAPI getloopcount(void);
API_ATTRIBUTE void WINAPI setfmwait(int nsec);
API_ATTRIBUTE void WINAPI setssgwait(int nsec);
API_ATTRIBUTE void WINAPI setrhythmwait(int nsec);
API_ATTRIBUTE void WINAPI setadpcmwait(int nsec);
API_ATTRIBUTE OPEN_WORK * WINAPI getopenwork(void);
API_ATTRIBUTE QQ * WINAPI getpartwork(int ch);

#ifdef ENABLE_COM_INTERFACE
API_ATTRIBUTE HRESULT WINAPI pmd_CoCreateInstance(
  REFCLSID rclsid,     //Class identifier (CLSID) of the object
  LPUNKNOWN pUnkOuter, //Pointer to whether object is or isn't part 
                       // of an aggregate
  DWORD dwClsContext,  //Context for running executable code
  REFIID riid,         //Reference to the identifier of the interface
  LPVOID * ppv         //Address of output variable that receives 
                       // the interface pointer requested in riid
);
#endif /* ENABLE_COM_INTERFACE */


#ifdef __cplusplus
}
#endif


#endif // PMDWINIMPORT_H
