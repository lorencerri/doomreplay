## doomreplay

A fork of [@ggerganov/doomreplay](https://github.com/ggerganov/doomreplay), with some modifications.

**Changes**

-   Input is passed in as an argument instead of a text file
-   Output is either an image or gif of last X amount of frames of the replay
-   Option to generate an .mp4 video of the entire replay

**TODO**

-   [ ] Change the input to be a text file instead of an argument
-   [ ] Add a way to generate a gif of the replay that only repeats once
-   [ ] Add an option to generate a video of the entire replay

**Requirements**

-   `doom1.wad` file (they're available on GitHub)
-   make if you to build the library

**Usage**

```
doomreplay -iwad ./doom1.wad -input "...keys" -render_last_frame -output output.png
```
