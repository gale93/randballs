
## What is this ?
Balls ! Just a playground for testing stuff and performances.
Each ball randomly changes its color. On collision if they have the same color they merge, otherwise bounce. [Try it now](https://github.com/gale93/randballs/releases)

A short video about this:

[![Randballs video url](https://img.youtube.com/vi/J6dccS9BE6c/0.jpg)](https://www.youtube.com/watch?v=J6dccS9BE6c "Randballs video")

I am using [SFML](https://github.com/SFML/SFML) for rendering and [EnTT](https://github.com/skypjack/entt) for entities management and some few handmade classes that act like an "engine".

## Controls
**[Left Mouse]** Press and direct to spawn balls<br/> 
**[A]** Spawn 500 balls<br/>
**[Space]** Delete balls in an Zone<br/>
**[Middle Mouse]** Spawn a portal<br/>
**[Right Mouse]** Collapse balls in a zone<br/>
**[Q]** Hold and cast away all balls in a zone<br/>
**[T]** Toggle text<br/>


## Todo List

* ~~Implement Quadtree for collisions check~~ It's rudimental and handmade but for now is fast enough. [Check it here](https://github.com/gale93/randballs/blob/master/systems/collisionsystem.cpp#L88)
* Endorse graphic ( switching to textures ? )
* Improve spawn balls options
* Add obstacles
* ~~Add Portals~~
* Add special effect based on color
* Add a mass based on shape size. [This is pretty bad handled atm](https://github.com/gale93/randballs/blob/master/systems/collisionsystem.cpp#L52)
* Let the physics variables be scriptable from the user such as [these](https://github.com/gale93/randballs/blob/master/components/body.hpp#L18)
* Add any cool effect I can think about
* ~~Implement a more-likely-real collision response~~
* ~~Interactive way to spawn balls~~


## How to build

I'll add a VS solution later, but it's pretty simple: Just [link sfml](https://www.sfml-dev.org/tutorials/2.5/) and include EnTT folder into Headers



