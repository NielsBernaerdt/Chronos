Niels Bernaerdt - Digital Arts & Entertainments

A 2D Game Engine.

The following patterns have been used:
	- Commands to bind input to player actions
	- State Pattern for the animations
	- Observer to keep track of the current game state (score, hp, ..)
	- EventQueue for the AudioManager

The AudioManager also has its own thread, where it gets passed data via a ringbuffer.
