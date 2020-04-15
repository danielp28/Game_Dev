# Game_Dev
A repo for my practice in game dev in  cpp


# 3D Graphics Engine
This is a 3D graphics engine created in the Windows console using One Lone Coder's ConsoleGameEngine. Currently (4/14/2020), this project contains a rotating 3D cube, nothing special. It will be built on.

# Snake
This is a really simple Snake clone runnning in the Windows console. There are a few issues with this program, mainly the lack of double buffering causes severe screen flicker during gameplay. Was a fun intro into C++ and creating simple logic for games.


# Fun With Vertices
This is an extention of what I began in the 3D Graphics Engine directory. This is a fully 3D word modeled using One Lone Coder's ConsoleGameEngine. The letters were all created by passing sets of vertices to the engine to create right triangles, which in turn create the "3D" letters that we see in the console. This was fun practice for thinking in the 3D space, getting used to using cardinal directions in a virtual enviornment, and a solid introduction into OLC's engine and it's functionality.

# Tetris
This is an extremely basic version of the classic game Tetris recreated in the Windows console. The shapes are written out in an array of 7, and we handle rotation of the indivdual pieces by considering the game grid to be 2D array of contiguous memory. So if we want to get a specific slot, say 10, we can use the formula 
<br>
<br>
<br>
<bold>i = y * w + x</bold>
<br>
<br>
Where y is the y index of the 2D array, x is the x index, and w is the width of the array. So if we have a 2D array of contiguous memory that is four slots wide we can use our formula to get a specific value(10)<br>
i = 2 * 4 + 2 =  10.

Then all we have to do for our rotations is to modify the formula
0 degrees = i = y * w + x<br>
90 degrees = i = 12 + y - (x * 4)<br>
180 degrees = i = 15 - (y * 4) - x<br>
270 degrees = i = 3 + y + (x * 4)<br>



# Top Down Shooter
This is a clone of the classic game Asteroids. Again this game is utilizing One Lone Coder's Console Game Engine. The player is able to move around in a 2D plane, shoot, and will teleport on collision of the side of the window to the other side. The asteroids break into smaller asteroids, and add 100 to player score. Upon clearing the screen of asteroids, the player is rewarded 1000 points, and two new large asteroids are generated, offset from the player coordinates by a certain amount





# Twitch
Currently incomplete
