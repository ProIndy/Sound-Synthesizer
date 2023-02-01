#ifndef RAYLIB_SYNTH_H
# define RAYLIB_SYNTH_H

# define BUFFSIZE 1000000
# define SAMPLE_RATE 44100
# define SAMPLE_DURATION 1/SAMPLE_RATE
# define STREAM_BUFFER_SIZE 1024

typedef struct  s_notes
{
    float   frequency;
    float   duration;
} t_notes;

typedef struct 
{
    float   phase;
    float   phase_stride;
} Oscillator;

# include "libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include "raylib.h"

#endif
