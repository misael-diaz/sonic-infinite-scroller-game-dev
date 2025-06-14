# Sonic Infinite Scroller Game Dev

**Academic Purpose Game Development Only**

The inspiration to build a sonic game came in part from Paul Cockcrell's
[codecamp](https://github.com/paulcockrell/sonic-infinite-scroller). He shows how to
build a infinite scroller sonic game with the KaPlay library that runs on the browser.
Even though I am not using his source code, I have read some of his learning resources
for building this game.

## Motivation

My drive is not to build a game because I like games but to build a game because I
want to get the experience of writing code in an area outside of my field of expertise.
And also because there are no games that interest me right now, so instead of investing
some of my free time on playing games I rather invest that time in building a game
and learn something useful. Developing a game basically from the ground up without
relying on (game-dev) frameworks is challenging and that is something that I wanted to
do for a long time to test myself.

Other reasons for doing this takes me back to one conversation I had with my uncle
when I was a teen, he said that if liked games so much I should consider creating my own
games. Even though that conversation and many others did not direct me towards a computer
science related field (I did not even liked computers back then) his advice has remained
to this day ... and now after years of writing code I can now attempt to build my own
game.

And there are of course legendary devs like the primeagen whose advice is to go build
something for yourself to acquire knowledge, skills, and experience. Certainly, as
basic as this game may be, building it has required me to research topics that I have not
considered before like the X11 window system and some Linux kernel documentation for
handling keyboard events (even if the latter is not actually used in this game it was a
good experience to study the respective documentation).

## Credits

This fan made game would not have been possible without the Sonic Team efforts and Sega.
Therefore, I want to express my gratitude to the Sonic Team and Sega for creating such
amazing games that have left a long lasting impression on so many gamers. For me it is
a wonderful experience to try to develop a game that aims to resemble (if at least in
spirit) the original games that they made for Sega Genesis.

## Graphics/Sprites/Assets

Sega owns the copyright for all the game graphics borrowed from the original Sega Genesis
games.

We do *not* host the graphics needed to run this game. If you would like to play this
game you may download the graphics from the
[sprites database](https://www.spritedatabase.net/) and also you will have to read
some of the source code to organize them in the way that the code expects. I know,
sounds like a lot of work for someone who just wants to play a game but that's how this
has to be done to avoid legal issues.

You may also want to check Paul's game-dev
[codecamp](https://github.com/paulcockrell/sonic-infinite-scroller) to get an idea of
the ordering. You can also play his game in your browser if you would like to get a
feeling of how this game plays.
Cheers!

## Game Features

The following features are implemented in this game:

- projectile motion
- entity collision detection
- implements parallax effect
- efficient entity drawing, only visible entities are drawn on the screen
- game clocks nearly at a framerate of 60 Hz
- handles player keyboard input

These features were implemented with basic algorithms and data structures so this
could be used as a demo that show students how can they apply what they learn in
their first algorithms and computer programming courses to build something fun
for themselves.

## Playing the Game

The game requires the following libraries and build tools for compiling the game:

- Xlib
- libpng
- make
- gcc

Under GNU/Linux all that you probably have to install is the `libpng` library, for the
other ones are installed by default.

In debian based distros you may install it (as root) via the package manager:

```sh
apt install libpng-dev
```

To compile the game source code open a terminal and execute the following commands:

Use the following command to build the game from source code with GNU make:

```sh
make clean && make
```

and to play the game just execute:

```sh
./bin/sonic-infinite-scroller-game.bin
```

The path here is important because the game expects the graphics to be located at the
`public/graphics` directory, which must be present at the top level of this repository.
Please look at the `gmdefs.h` header file for more info.
As mentioned earlier you must supply them yourself as these are not hosted here.

The game starts right away, there's no menu, and there's just the one level that never
ends (hence the use of infinity for naming this game) as shown in the videos below.
Enjoy!

## Game Controls

This is a game that has two modes, the normal mode which allows you to control sonic
to some extent and the camera mode which allows you to move the camera around. The
latter mode is useful for debugging the game and maybe has some use for level design.

**Normal mode controls:**

In this mode you can make sonic morph into a ball or jump.

- arrow-right-key: sonic runs
- arrow-down-key: sonic spins
- tab-key: sonic jumps
- m-key: toggles between normal and camera modes

As you see you can practically play the game with just the `tab-key`. This is quite
limiting in comparison to the original Sega Genesis games but the intention was never to
create a clone of those games.

**Camera mode controls:**

In this mode you control the camera placement as the world remains static:

- the arrow keys move the camera in the respective directions
- b-key: places at the camera at the beacon just above sonic
- e-key: cycles the camera position over the enemies
- p-key: cycles the camera position over the platforms
- m-key: toggles between normal and camera modes

## References

I am using the [Xlib Programming Manual](https://tronche.com/gui/x/xlib/) as the main
resource for producing graphics/animations and for handling player input.

I am also reading the GNU/Linux [man pages](https://man7.org/linux/man-pages/) for
consulting the GLIBC and libpng APIs.

Code was either borrowed or adapted from the following GitHub repositories:
- [Quake-III-Arena](https://github.com/id-Software/Quake-III-Arena)
- [xlib-learning](https://github.com/Faison/xlib-learning)
- [Xlib-demo](https://github.com/QMonkey/Xlib-demo)

These were instrumental for the development of this game, and therefore, they deserve
to be awknowledged.

## Phases

My first sonic animation, watch on youtube by clicking on the image below:

[![Watch the Video](https://img.youtube.com/vi/sbTZkZByafw/hqdefault.jpg)](https://youtu.be/sbTZkZByafw)

The animation was done with the code at commit [655f4af0eb658ab04cfa2320609df662605ff15b](https://github.com/misael-diaz/sonic-infinite-scroller-game-dev/commit/655f4af0eb658ab04cfa2320609df662605ff15b).

The player can switch from a running/spinning animation with the right/down arrow keys.

My second animation, sonic running on an infinite platform:

[![Watch the Video](https://img.youtube.com/vi/Lz_PlsWDygE/hqdefault.jpg)](https://youtu.be/Lz_PlsWDygE)

The animation was done with the code at commit [16200609797955a9da826eefcbb8437388fb2671](https://github.com/misael-diaz/sonic-infinite-scroller-game-dev/commit/16200609797955a9da826eefcbb8437388fb2671).

My third animation, sonic jumping and running on an infinite platform:

[![Watch the Video](https://img.youtube.com/vi/kQrb8HPSllk/hqdefault.jpg)](https://youtu.be/kQrb8HPSllk)

The animation was done with the code at commit [511c5c339a4f27fcdbddad1420df0b1aef55dd2c](https://github.com/misael-diaz/sonic-infinite-scroller-game-dev/commit/511c5c339a4f27fcdbddad1420df0b1aef55dd2c).

My fourth animation, sonic jumping off a platform:

[![Watch the Video](https://img.youtube.com/vi/gpQOFEkzxYg/hqdefault.jpg)](https://youtu.be/gpQOFEkzxYg)

The animation was done with the code at commit [d1c00fa9fad4549984be17578ade355874171320](https://github.com/misael-diaz/sonic-infinite-scroller-game-dev/commit/d1c00fa9fad4549984be17578ade355874171320).

My fifth animation, sonic destroying a motobug:

[![Watch the Video](https://img.youtube.com/vi/qsgNFFoKFGs/hqdefault.jpg)](https://youtu.be/qsgNFFoKFGs)

The animation was done with the code at commit [3fc8e80bb0a7108f000110d7d98e82d2bb0797f1](https://github.com/misael-diaz/sonic-infinite-scroller-game-dev/commit/3fc8e80bb0a7108f000110d7d98e82d2bb0797f1).

My sixth animation, sonic destroying multiple motobugs without landing:

[![Watch the Video](https://img.youtube.com/vi/SNlcBOAgi9k/hqdefault.jpg)](https://youtu.be/SNlcBOAgi9k)

The animation was done with the code at commit [a90ece4649ebeaeef3c1e15abeba03b26b6462aa](https://github.com/misael-diaz/sonic-infinite-scroller-game-dev/commit/a90ece4649ebeaeef3c1e15abeba03b26b6462aa).

My seventh animation, Sonic sliding on the platform ceilings:

[![Watch the Video](https://img.youtube.com/vi/fSwVrGqClfA/hqdefault.jpg)](https://youtu.be/fSwVrGqClfA)

The animation was done with the code at commit [08aa15b1f2bfb4fbdbcae97067ee775f67b952f0](https://github.com/misael-diaz/sonic-infinite-scroller-game-dev/commit/08aa15b1f2bfb4fbdbcae97067ee775f67b952f0).

My last animation, shows how to beat the infinity level:

[![Watch the Video](https://img.youtube.com/vi/knG9F3NxYLg/hqdefault.jpg)](https://youtu.be/knG9F3NxYLg)

The animation was done with the code at commit [6305b22f608e34fd8eb6f5ee1aca891c40c4d7f1](https://github.com/misael-diaz/sonic-infinite-scroller-game-dev/commit/6305b22f608e34fd8eb6f5ee1aca891c40c4d7f1).
