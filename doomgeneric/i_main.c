//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	Main program, simply calls D_DoomMain high level loop.
//

//#include "config.h"

#include <stdio.h>
#include <stdlib.h>

//#include "doomtype.h"
//#include "i_system.h"
#include "m_argv.h"
#include "doomreplay.h"

//
// D_DoomMain()
// Not a globally visible function, just included for source reference,
// calls all startup code, parses command line options.
//

void D_DoomMain (void);

void M_FindResponseFile(void);

void dg_Create();


int main(int argc, char **argv)
{
    // save arguments

    myargc = argc;
    myargv = argv;

    replay_data_t replay_data;

    int pidx_input     = M_CheckParmWithArgs("-input", 1);
    int pidx_output    = M_CheckParmWithArgs("-output", 1);
    int pidx_framerate = M_CheckParmWithArgs("-framerate", 1);
    int pidx_nrecord   = M_CheckParmWithArgs("-nrecord", 1);

    if (!pidx_input) {
        fprintf(stderr, "Input file must be provided via '-input'\n");
        return -1;
    }

    if (!pidx_output) {
        fprintf(stderr, "Please specify output file for storing the generated video via '-output'\n");
        return -1;
    }

    replay_data.fname_output = myargv[pidx_output + 1];

    // framerate
    replay_data.framerate = 35;
    if (pidx_framerate) {
        replay_data.framerate = atoi(myargv[pidx_framerate + 1]);
    }

    if (replay_data.framerate <= 0 || replay_data.framerate > 60) {
        fprintf(stderr, "Invalid framerate: %d\n", replay_data.framerate);
        return -1;
    }

    // n frames to record at the end of the replay
    replay_data.n_frames_record = 10*replay_data.framerate;
    if (pidx_nrecord) {
        replay_data.n_frames_record = atoi(myargv[pidx_nrecord + 1]);
    }

    if (replay_data.n_frames_record <= 0) {
        fprintf(stderr, "Invalid nrecord: %d\n", replay_data.n_frames_record);
        return -1;
    }

    // render the current frame on the screen ?
    replay_data.render_frame = 0;
    if (M_CheckParm("-render_frame") > 0) {
        replay_data.render_frame = 1;
    }

    // render the current keyboard input on the screen ?
    replay_data.render_input = 0;
    if (M_CheckParm("-render_input") > 0) {
        replay_data.render_input = 1;
    }

    const char * param_input = myargv[pidx_input + 1];

    FILE *f = fopen(param_input, "rb");
    if (!f) {
        fprintf(stderr, "Cannot read input file '%s'", param_input);
        return -2;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *input = malloc(fsize + 1);
    fread(input, 1, fsize, f);
    fclose(f);

    replay_data.n_frames = 1;
    for (int i = 0; i < fsize; ++i) {
        switch (input[i]) {
            case ',': ++replay_data.n_frames; continue;
        };
    }

    replay_data.frames = malloc(replay_data.n_frames*sizeof(frame_data_t));

    int cur_frame = 0;
    for (int i = 0; i < fsize; ++i) {
        frame_data_t * frame = replay_data.frames + cur_frame;
        switch (input[i]) {
            case ',': ++cur_frame; continue;
            case 'x': frame->pressed[dr_key_escape] = 1; continue;
            case 'e': frame->pressed[dr_key_enter]  = 1; continue;
            case 'l': frame->pressed[dr_key_left]   = 1; continue;
            case 'r': frame->pressed[dr_key_right]  = 1; continue;
            case 'u': frame->pressed[dr_key_up]     = 1; continue;
            case 'd': frame->pressed[dr_key_down]   = 1; continue;
            case 'a': frame->pressed[dr_key_alt]    = 1; continue;
            case 's': frame->pressed[dr_key_shift]  = 1; continue;
            case 'p': frame->pressed[dr_key_use]    = 1; continue;
            case 'f': frame->pressed[dr_key_fire]   = 1; continue;
            case '0': frame->pressed[dr_key_0]      = 1; continue;
            case '1': frame->pressed[dr_key_1]      = 1; continue;
            case '2': frame->pressed[dr_key_2]      = 1; continue;
            case '3': frame->pressed[dr_key_3]      = 1; continue;
            case '4': frame->pressed[dr_key_4]      = 1; continue;
            case '5': frame->pressed[dr_key_5]      = 1; continue;
            case '6': frame->pressed[dr_key_6]      = 1; continue;
            case '7': frame->pressed[dr_key_7]      = 1; continue;
            case '8': frame->pressed[dr_key_8]      = 1; continue;
            case '9': frame->pressed[dr_key_9]      = 1; continue;
        };
    }

    DR_Init(replay_data);

    M_FindResponseFile();

    // start doom
    printf("Starting D_DoomMain\r\n");
    
	dg_Create();

	D_DoomMain ();

    return 0;
}

