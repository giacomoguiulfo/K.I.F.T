#ifndef RECITER_C
#define RECITER_C
# include <stdint.h>
//int TextToPhonemes(char *input, char *output);

int TextToPhonemes(char *input);
void WriteWav(char* filename, char* buffer, int bufferlength);
void OutputSound();
void PrintUsage();
void MixAudio(void *unused, uint8_t *stream, int len);

#endif

