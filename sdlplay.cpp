#include <cstdlib>
#include <cstring> /* for memset(), memcpy() */
#include <stdint.h>
#ifdef _MSC_VER
#define SDL_MAIN_HANDLED
#include <SDL.h>
#else
#include <SDL.h>
#endif

#include "pmdmini.h"
#include "pmdwinimport.h"

int audio_on = 0;

//
// PCM definitions ( BLOCK = samples )
//

#define PCM_BLOCK 2048
#define PCM_BYTE_PER_SAMPLE 2
#define PCM_CH  2
#define PCM_NUM_BLOCKS 4

//
// buffer size definitions
//

#define PCM_BLOCK_SAMPLES_CHANNELS (PCM_BLOCK * PCM_CH)
#define PCM_BUFFER_SAMPLES_CHANNELS (PCM_BLOCK_SAMPLES_CHANNELS * PCM_NUM_BLOCKS)
#define PCM_BLOCK_BYTES (PCM_BLOCK_SAMPLES_CHANNELS * PCM_BYTE_PER_SAMPLE)


//
// audio buffering
//

int buf_wpos = 0;
int buf_ppos = 0;

short buffer[ PCM_BUFFER_SAMPLES_CHANNELS ];

static void audio_callback( void *param , Uint8 *data , int len );
static int init_audio(void);
static void free_audio(void);
static void player_screen( void );
static void write_dword(uint8_t *p, uint32_t v);
static void write_word(uint8_t *p, uint16_t v);
static void audio_write_wav_header(SDL_RWops *file, long freq, long pcm_bytesize);
static void audio_loop_file(const char *outwav, const int len);
static void player_loop( const int len );
//static int split_dir( const char *file , char *dir );

static void audio_callback( void *param , Uint8 *data , int len )
{
    int i;

    short *pcm = (short *)data;

    if ( !audio_on )
    {
        std::memset( data , 0 , len );
        len = 0; /* statement cuts off following for loop */
    }

    for( i = 0; i < len / 2; i++ )
    {
        pcm[ i ] = buffer[ buf_ppos++ ];
        if ( buf_ppos >= PCM_BUFFER_SAMPLES_CHANNELS )
        {
            buf_ppos = 0;
        }
    }
}

//
// audio hardware functions
//

static int init_audio(void)
{
    SDL_AudioSpec af;

    if ( SDL_Init( SDL_INIT_AUDIO ) )
    {
        printf("Failed to Initialize!!\n");
        return 1;
    }

    af.freq = 44100;
    af.format = AUDIO_S16;
    af.channels = PCM_CH;
    af.samples = PCM_BLOCK;
    af.callback = audio_callback;
    af.userdata = NULL;

    if (SDL_OpenAudio(&af,NULL) < 0)
    {
        printf("Audio Error!!\n");
        return 1;
    }

    memset(buffer,0,sizeof(buffer));

    SDL_PauseAudio(0);
    return 0;
}

static void free_audio(void)
{
    SDL_CloseAudio();
}

static void player_screen( void )
{
    int i,n;
    int notes[32];

    n = pmd_get_tracks ( );

    // 画面の制限
    if (n > 8)
    {
        n = 8;
    }

    pmd_get_current_notes( notes , n );

    for ( i = 0; i < n; i ++ )
    {
        printf("%02x " , ( notes[i] & 0xff ) );
    }
    printf(" ");

}

//
// audio renderers
//

//
// WAVファイル系
//

static void write_dword(uint8_t *p, uint32_t v)
{
    p[0] = v & 0xff;
    p[1] = (v>>8) & 0xff;
    p[2] = (v>>16) & 0xff;
    p[3] = (v>>24) & 0xff;
}

static void write_word(uint8_t *p, uint16_t v)
{
    p[0] = v & 0xff;
    p[1] = (v>>8) & 0xff;
}

//
// audio_write_wav_header : ヘッダを出力する
// freq : 再生周波数
// pcm_bytesize : データの長さ
//

static void audio_write_wav_header(SDL_RWops *file, long freq, long pcm_bytesize)
{
    uint8_t hdr[0x80];
    
    if ( file == NULL )
        return;
    
    std::memcpy(hdr,"RIFF", 4);
    write_dword(hdr + 4, pcm_bytesize + 44);
    std::memcpy(hdr + 8,"WAVEfmt ", 8);
    write_dword(hdr + 16, 16); // chunk length
    write_word(hdr + 20, 01); // pcm id
    write_word(hdr + 22, PCM_CH); // ch
    write_dword(hdr + 24, freq); // freq
    write_dword(hdr + 28, freq * PCM_CH * PCM_BYTE_PER_SAMPLE); // bytes per sec
    write_word(hdr + 32, PCM_CH * PCM_BYTE_PER_SAMPLE); // bytes per frame
    write_word(hdr + 34, PCM_BYTE_PER_SAMPLE * 8 ); // bits

    std::memcpy(hdr + 36, "data",4);
    write_dword(hdr + 40, pcm_bytesize); // pcm size
    
    SDL_RWseek(file, 0, RW_SEEK_SET);
    SDL_RWwrite(file, hdr, 1, 44);
    
    SDL_RWseek(file, 0, RW_SEEK_END); 
    
}

//
// audio_loop_file : 音声をデータ化する
// outwav : 出力WAVファイル名
// len : 長さ(秒)
//

static void audio_loop_file(const char *outwav, const int len)
{
    SDL_RWops *file = NULL;

    int total;
    int sec,old_sec;
    int sec_sample;
    const int freq  = 44100;
    
    // ファイル
    if ( ( outwav != NULL ) && ( outwav[0] != 0 ) )
    {
        file = SDL_RWFromFile(outwav, "wb");
        if (!file)
        {       
            printf("Can't write a WAV/PCM file!\n");
            return;
        }
    }
    
    audio_write_wav_header(file, freq, 0);

    old_sec = total = sec = sec_sample = 0;

    do
    {
        pmd_renderer ( buffer + 0, ( freq / 10 ) );
        SDL_RWwrite(file, buffer, PCM_CH * PCM_BYTE_PER_SAMPLE, ( freq / 10 ));

        total += ( freq / 10 );
        sec_sample += ( freq / 10 );

        while ( sec_sample >= freq )
        {
            sec_sample -= freq;
            sec++;
        }

        if ( sec != old_sec )
        {
            old_sec = sec;
            if ( sec > len )
            {
                fadeout(10);
            }
        }

    } while(sec < (len + 5));

    audio_write_wav_header(file, freq, freq * (len + 5) * PCM_CH * PCM_BYTE_PER_SAMPLE);

    if (file)
    {
        SDL_RWclose(file);
    }

}

//
// player_loop
//

static void player_loop( const int len )
{
    int total;
    int sec,old_sec;
    int sec_sample;
    const int freq  = 44100;

    old_sec = total = sec = sec_sample = 0;

    do
    {

        if ( ( ( buf_ppos < buf_wpos ) && ( ( PCM_BUFFER_SAMPLES_CHANNELS - buf_wpos + buf_ppos ) >= PCM_BLOCK_SAMPLES_CHANNELS ) )
            ||
            ( ( buf_ppos > buf_wpos ) && ( ( buf_ppos - buf_wpos ) >= PCM_BLOCK_SAMPLES_CHANNELS ) ) )
        {
            if ( buf_wpos >= PCM_BUFFER_SAMPLES_CHANNELS )
            {
                buf_wpos = 0;
            }

            pmd_renderer ( buffer + buf_wpos, PCM_BLOCK );

            buf_wpos += PCM_BLOCK_SAMPLES_CHANNELS;

            total += PCM_BLOCK;
            sec_sample += PCM_BLOCK;

            while ( sec_sample >= freq )
            {
                sec_sample -= freq;
                sec++;
            }

            if ( sec != old_sec )
            {
                old_sec = sec;
                if ( sec > len )
                {
                    fadeout(10);
                }
            }

            player_screen();
            printf("Time : %02d:%02d / %02d:%02d\r\r", \
                sec / 60 , sec % 60 , len / 60,len % 60);
            fflush(stdout);
        }
        else
        {
            SDL_Delay(1);
        }

    } while(sec < (len + 5));

}

//
// path splitter
//

//static int split_dir( const char *file , char *dir )
//{
//    char *p;
//    int len = 0;

//    p = strrchr( (char *)file , '/' );

//    if ( p )
//    {
//        len = (int)( p - file );
//        std::strncpy ( dir , file , len );
//    }
//    dir[ len ] = 0;

//    return len;
//}

//
// entry point
//

int main ( int argc, char *argv[] )
{
    printf( "PMDPLAY on SDL Version 2011-10-21\n" );

    if ( argc < 2 )
    {
        printf("Usage pmdplay <file>\n");
        printf("or    pmdplay <file> <output.wav>\n");
        return 1;
    }
    else if ( argc == 3 )
    {
        printf("pmdplay ouput WAV file format %s\n", argv[2]);

        memset(buffer,0,sizeof(buffer));
    }

    if ( argc == 2 )
    {
        if ( init_audio() )
        {
            return 1;
        }
    }

    char buf[1024];
#ifdef _MSC_VER
    char* pcmdir = std::getenv("USERPROFILE");
#else
    char* pcmdir = std::getenv("HOME");
#endif

    if (pcmdir)
    {
        std::strcpy(buf,pcmdir);
#ifdef _MSC_VER
        strcat(buf, "\\.pmdplay\\");
#else
        strcat(buf,"/.pmdplay/");
#endif
    }
    else
    {
        buf[0] = 0;
    }

    pmd_init( buf );

    if ( pmd_play( argv[1] , buf ) )
    {
        printf("File open error\n");
        free_audio();
        return 1;
    }
    audio_on = 1;

    if ( argc == 2 )
    {
        player_loop( pmd_length_sec() );

        free_audio();
    }
    else
    {
        audio_loop_file( argv[2], pmd_length_sec() );
    }

    pmd_stop();

    return 0;
}
