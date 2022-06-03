## doomreplay

A fork of [@ggerganov/doomreplay](https://github.com/ggerganov/doomreplay), with some modifications.

**Changes**

-   Input is an argument instead of a file
-   Added `-renderNthFrame <number>` option
-   Added `.gif` output support
-   Added `.png` output support
    -   Will only render one frame. If you want to render the last frame, set `-nrecord 1`

**Usage**

```sh
doomreplay
	-iwad <doom1.wad file> # Path for the doom1.wad file (you can find this somewhere else on GitHub)
	-input <keys> # e.g. `-input "x,,e,,e,,e,,"`
	-nrecord <number> # Maximum amount of frames from ending to output e.g. `-nrecord 10` would record the last 10 frames
	-framerate <number> # Amount of frames rendered per second for FFMPEG e.g. `-framerate 30`
	-renderNthFrame <number> # Render every Nth frame e.g. `-renderNthFrame 10` would render every 2nd frame.
	# If you set -nrecord, you can get a static framecount
	# e.g. `-nrecord 1000 -renderNthFrame 10` would render the last 1000 frames, but only every 10th frame of the replay.
	-output <path> # Path for the output file. e.g. `-output ./doomreplay.png` or `-output ./doomreplay.gif`
	-render_frame # Required
	-render_input # Required
	-render_username # Required
```

**Build**

```
cd doomgeneric
make -f Makefile.dr
```

**Input**

```
,   - new frame
x   - escape
e   - enter
l   - left
r   - right
u   - up
d   - down
a   - alt
s   - shift
p   - use
f   - fire
t   - tab
y   - yes
n   - no
<   - strafe left
>   - strafe right
2-7 - weapons
```
