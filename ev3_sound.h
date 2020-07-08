#ifdef __cplusplus
extern "C" {
#endif

#ifndef ev3_sound_h
#define ev3_sound_h

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

#include "ev3_constants.h"

typedef struct
{
   unsigned short Frequency;
   unsigned short Duration;
} Tone;

bool SoundInit();
bool SoundOpen();
bool SoundClose();
bool SoundExit();
bool SoundInitialized();

void PlayFileEx(char* pFileName, byte volume, bool loop);

#define PlayFile(_f) PlayFileEx((_f), 100, FALSE)

void PlayToneEx(unsigned short frequency, unsigned short duration, byte volume);

#define PlayTone(_f, _d) PlayToneEx((_f), (_d), 100)
void PlaySound(byte aCode);
void PlayTonesEx(Tone tones[], size_t size);

#define PlayTones(_tones) PlayTonesEx(_tones, sizeof(_tones)/sizeof(_tones[0]))

int SoundState();

void StopSound();

bool SoundTest();

void SoundReady();

void MuteSound();

void UnmuteSound();

void ClearSound();

#endif // ev3_sound_h

#ifdef __cplusplus
}
#endif
