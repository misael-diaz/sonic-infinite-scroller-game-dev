# Sonic Infinite Scroller Game Dev

The inspiration to build a sonic game came from Paul Cockcrell's
[codecamp](https://github.com/paulcockrell/sonic-infinite-scroller). He shows how to
build a infinite scroller sonic game with the KaPlay library that runs on the browser.
Even though I am not using his source code, I have read the learning resources for
building the game.

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
