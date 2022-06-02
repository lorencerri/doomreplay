## doomreplay

A fork of [@ggerganov/doomreplay](https://github.com/ggerganov/doomreplay), with some modifications.

**Changes**

-   Input is passed in as an argument instead of a text file
-   Output is either an image or gif of last X amount of frames of the replay
-   Option to generate an .mp4 video of the entire replay

**TODO**

-   [x] Change the input to be an argument instead of a text file
-   [ ] Add a way to generate a gif of the replay that only repeats once
-   [ ] Add an option to generate a video of the entire replay

**Requirements**

-   `doom1.wad` file (they're available on GitHub)
-   `make` if you want to build the library

**Usage**

```sh
doomreplay
	-iwad <doom1.wad file> # Path for the doom1.wad file
	-input <keys> # e.g. `-input "x,,e,,e,,e,,"`
	-render_frames <count> # The amount of frames to output (defaults to 1)
	-output <path> # Path for the output file. e.g. `-output ./doomreplay.png` or `-output ./doomreplay.gif`
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
