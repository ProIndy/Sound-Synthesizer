#include "minisynth.h"

t_notes parse_note(char *note, float tempo, int newtrack)
{
	float c_freq[9] = { 16.35, 32.70, 65.41, 130.8, 261.6, 523.3, 1047, 2093, 4186};
	float cs_freq[9] = { 17.32, 34.65, 69.30, 138.6, 277.2, 554.4, 1109, 2217, 4435};
	float d_freq[9] = { 18.35, 36.71, 73.42, 146.8, 293.7, 587.3, 1175, 2349, 4699};
	float eb_freq[9] = {19.45, 38.89, 77.78, 155.6, 311.1, 622.3, 1245, 2489, 4978};
	float e_freq[9] = {20.60, 41.20, 82.41, 164.8, 329.6, 659.3, 1319, 2637, 5274};
	float f_freq[9] = {21.83, 43.65, 87.31, 174.6, 349.2, 698.5, 1397, 2794, 5588};
	float fs_freq[9] = {23.12, 46.25, 92.50, 185.0, 370.0, 740.0, 1480, 2960, 5920};
	float g_freq[9] = {24.50, 49.00, 98.00, 196.0, 392.0, 784.0, 1568, 3136, 6272};
	float gs_freq[9] = {25.96, 51.91, 103.83, 207.7, 415.3, 830.6, 1661, 3322, 6645};
	float a_freq[9] = {27.50, 55.00, 110.0, 220.0, 440.0, 880.0, 1760, 3520, 7040};
	float bb_freq[9] = {29.14, 58.27, 116.54, 233.1, 466.2, 932.3, 1865, 3729, 7459};
	float b_freq[9] = {30.87, 61.74, 123.5, 246.9, 493.9, 987.8, 1976, 3951, 7902};

	static int octave = 3;
	static float default_duration = 1.0f;
	float local_dur;
	int i;
	t_notes one_note;

	if (!newtrack)
	{
		octave = 4;
		default_duration = 1.0f;
		local_dur = 0.0f;
	}
	if (note[1] != '/')
	{
		if (ft_isdigit(note[1]))
			octave = atoi(&note[1]);
		if (ft_isdigit(note[2]))
			octave = atoi(&note[2]); 
	}	
	
	if (*note == 'c')
	{
		one_note.frequency = c_freq[octave];
		if (*(note + 1) == '#')
			one_note.frequency = cs_freq[octave];
	}
	if (*note == 'd')
			one_note.frequency = d_freq[octave];
	if (*note == 'e')
	{
		one_note.frequency = e_freq[octave];
		if (*(note + 1) == 'b')
			one_note.frequency = eb_freq[octave];
	}	
	if (*note == 'f')
	{
		one_note.frequency = f_freq[octave];
		
		if (*(note + 1) == '#')
			one_note.frequency = fs_freq[octave];
	}
	if (*note == 'g')
	{
		one_note.frequency = g_freq[octave];
		if(*(note + 1) == '#')
			one_note.frequency = gs_freq[octave];
	}
	if (*note == 'a')
			one_note.frequency = a_freq[octave];
	if (*note == 'b')
	{
		one_note.frequency = b_freq[octave];
		if(*(note + 1) == 'b')
			one_note.frequency = bb_freq[octave];
	}
	if (*note == 'r')
		one_note.frequency = 0;

	if (strchr(note, '/') != NULL)
	{
		local_dur += ((atof((strchr(note, '/') + 1))) / (tempo / 60));
		one_note.duration = local_dur;
		default_duration = ((atof((strchr(note, '/') + 1))) / (tempo / 60));
	}
	else
	{
		local_dur += (default_duration / (tempo / 60));
		one_note.duration = local_dur;
	}
	return (one_note);
}

int count_track_amount(char *buf)
{
	int i = 0;
	int commas = 0;

	while (buf[i] != '\n')
	{
		++i;
		if (buf[i] == ',')
			++commas;
	}
	return (commas + 1);
}


int count_notes(char **notes)
{
	int i= 0;

	while (notes[i])
		++i;
	return (i);
}

int is_note(char c)
{
	if (c == 'a' || c == 'b' || c == 'c' || c == 'e' || 
	c == 'f' || c == 'd' || c == 'g' || c == 'r')
		return (1);

	return (0);
}

int get_tempo (char *buf)
{
	char *temp;

	temp = ft_strstr(buf, "tempo");
	while (!ft_isdigit(*temp))
		++temp;
	return (atoi(temp));
}

t_notes **make_array_of_tracks(char *filename)
{
	t_notes **song;
	t_notes *track;
	char **split_lines;
	char **split_notes;
	int fd;
	int newtrack;
	float tempo;
	int j;
	int amount_of_tracks;
	int index;
	int track_nbr;
	char buf[BUFFSIZE];

	fd = open(filename, O_RDONLY);
	read(fd, &buf, BUFFSIZE);

	tempo = get_tempo(buf);
	amount_of_tracks = count_track_amount(strstr(buf, "tracks"));
	

	split_lines = ft_strsplit(buf, '\n');
	
	song = (t_notes **)ft_memalloc(sizeof(t_notes *) * (amount_of_tracks) + 1);
	
	j = 0;
	track_nbr = 0;
	while (track_nbr < amount_of_tracks)
	{
		while (atoi(split_lines[j]) != (track_nbr + 1))
			++j;
		split_notes = ft_strsplit(split_lines[j], ' ');
		song[track_nbr] = (t_notes *)ft_memalloc(sizeof(t_notes) * count_notes(split_notes) + 1);
		
		
		
		newtrack = 0;
		index = 0;
		while (*split_notes)
		{
			if (is_note(**split_notes))
			{
				song[track_nbr][index] = parse_note(*split_notes, tempo, newtrack++);
				++index;
			}
			++split_notes;
		}
		++track_nbr;
	}
	return(song);
}

float   update_freq(t_notes *track, int cur_note)
{
	float	wave_frequency;

    wave_frequency = track[cur_note].frequency;
    return (wave_frequency);
}

void    update_triangle(float *signal, Oscillator *wave, float cur_freq)
{
    size_t  t;

    t = 0;
	wave->phase_stride = cur_freq * SAMPLE_DURATION;
    while (t < STREAM_BUFFER_SIZE)
    {
        wave->phase += wave->phase_stride;
        if (wave->phase >= 1.0f)
            wave->phase -= 1.0f;
        if (wave->phase < 1.0f)
            wave->phase += 1.0f;
        if (wave->phase < 0.5f)
			signal[t] = (wave->phase * 2.0f) - 0.5f;
		else
			signal[t] = (wave->phase * -2.0f) + 1.5f;
        t++;
    }
}

void	update_saw(float *signal, Oscillator *wave, float cur_freq)
{
    size_t  t;

    t = 0;
	wave->phase_stride = cur_freq * SAMPLE_DURATION;
    while (t < STREAM_BUFFER_SIZE)
    {
        wave->phase += wave->phase_stride;
		if (wave->phase >= 1.0f)
            wave->phase -= 1.0f;
    	if (wave->phase < 1.0f)
            wave->phase += 1.0f;
        signal[t] = (wave->phase * 1.0f) - 0.5f;
        t++;
    }
}

void    update_square(float *signal, Oscillator *wave, float cur_freq)
{
    size_t  t;

    t = 0;
    while (t < 1024)
    {
        wave->phase += wave->phase_stride;
        if (wave->phase >= 1.0f)
            wave->phase -= 2.0f;
        if (wave->phase > 0)
            signal[t] = 1.0f;
        else
            signal[t] = -1.0f;
        t++;
    }
}

void	update_sine(float *signal, Oscillator *wave, float cur_freq)
{
    size_t  t;

    t = 0;
	wave->phase_stride = cur_freq * SAMPLE_DURATION;
    while (t < STREAM_BUFFER_SIZE)
    {
        wave->phase += wave->phase_stride;
        if (wave->phase >= 1.0f)
            wave->phase -= 1.0f;
        if (wave->phase < 1.0f)
            wave->phase += 1.0f;
        signal[t] = sinf(2.0f * PI * wave->phase);
        t++;
    }
}

int	get_am_tracks(int *tracks)
{
	int	i;

	while (tracks[i] != 0)
		i++;
	return (i);
}

void	player(t_notes **song, int *tracks)
{
	int			am_tracks = get_am_tracks(tracks);
	AudioStream	stream;
	Oscillator	wave[am_tracks];
	float		wave_signal[am_tracks + 1][1024];
	float		tot_dur[am_tracks];
	float		cur_freq[am_tracks];
	float		runtime;
	int			cur_note[am_tracks];
	const int   screen_width = 1024;
    const int   screen_height = 768;
	int			i;
	int			j;
	int			t;
	int			cur_loop;
    int         loop_count;

	InitWindow(screen_width, screen_height, "Synth");
    SetTargetFPS(60);
    InitAudioDevice();
    SetMasterVolume(0.05f);
    SetAudioStreamBufferSizeDefault(STREAM_BUFFER_SIZE);
	i = 0;
	stream = LoadAudioStream(SAMPLE_RATE, 32, 1);
	i++;
	PlayAudioStream(stream);
	i++;
	i = 0;
	while (i < am_tracks)
	{
		wave[i].phase = 0.0f;
		wave[i].phase_stride = song[i][0].frequency * SAMPLE_DURATION;
		tot_dur[i] = song[i][0].duration;
		cur_freq[i] = song[i][0].frequency;
		cur_note[i] = 0;
		i++;
	}
	loop_count = 0;
	runtime = 0.0f;
	while (!WindowShouldClose())
	{
		runtime = GetTime();
		printf("%f\n", runtime);
		if (IsAudioStreamProcessed(stream))
		{
			j = 0;
			while (j < 1024)
			{
				wave_signal[am_tracks][j] = 0.0f;
				j++;
			}
			i = 0;
			while (i < am_tracks)
			{
				if (runtime > song[i][cur_note[i]].duration)
				{
					while (runtime > song[i][cur_note[i]].duration)
						cur_note[i]++;
				}
				cur_freq[i] = update_freq(song[i], cur_note[i]);
				wave[i].phase_stride = song[i][cur_note[i]].frequency * SAMPLE_DURATION;
				if (tracks[i] == 4)
					update_sine(wave_signal[i], &wave[i], cur_freq[i]);
				if (tracks[i] == 1)
					update_square(wave_signal[i], &wave[i], cur_freq[i]);
				if (tracks[i] == 2)
					update_saw(wave_signal[i], &wave[i], cur_freq[i]);
				if (tracks[i] == 3)
					update_triangle(wave_signal[i], &wave[i], cur_freq[i]);
				j = 0;
				while (j < 1024)
				{
					wave_signal[am_tracks][j] += wave_signal[i][j];
					j++;
				}
				i++;
			}
			UpdateAudioStream(stream, wave_signal[am_tracks], STREAM_BUFFER_SIZE);
		}
		BeginDrawing();
		ClearBackground(BLACK);
		i = 0;
		while (i < am_tracks)
		{
			t = 0;
			while (t < STREAM_BUFFER_SIZE)
			{
				DrawPixel(t, ((786/(am_tracks+1))*(i+1)) + (int)(wave_signal[i][t] * (100 / am_tracks)), RED);
				t++;
			}
			i++;
		}
		EndDrawing();
		loop_count++;
	}
	UnloadAudioStream(stream);
    CloseAudioDevice();
    CloseWindow();
}

int *get_waveform (char *filename)
{
    int fd;
    int *superarray;
    char *temp;
    char buf[BUFFSIZE + 1];
    int i;


    fd = open(filename, O_RDONLY);
    read(fd, &buf, BUFFSIZE);

    temp = strstr(buf, "\ntracks ");

    while (*temp != ' ')
    {
        ++temp;
    }
    superarray = (int *)ft_memalloc(sizeof(int) * 70);
    i = 0;
    while (*temp != '\n')
    {
        ++temp;
        superarray[i] = 4;                                // Sine = 4
        if (*(temp ) == 's' && *(temp + 1) == 'q')     // Square = 1
            superarray[i] = 1;
        if (*(temp) == 's' && *(temp + 1) == 'a')    // Saw = 2
            superarray[i] = 2;
        if (*(temp) == 't' && *(temp + 1) == 'r')     // triangle = 3
            superarray[i] = 3;
        if (*(temp) == 'k')                         // Kick = 5
             superarray[i] = 5;
        if (*(temp) == 's' && *(temp + 1) == 'n')     // Snare = 6
            superarray[i] = 6;
        while (*temp != ',' && *temp != '\n')
			++temp;
		++i;
    }
    return (superarray);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_notes **song;
		int	*tracks;
		int	i;

		song = make_array_of_tracks(argv[1]);
		tracks = get_waveform(argv[1]);
		player(song, tracks);
	}
	else
	{
		write(1, "usage: ./minisynth <file>\n", 26);
	}
	return (0);
}