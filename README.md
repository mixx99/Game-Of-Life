# Game Of Life

This little game based on a cellular automaton devised by the British mathematician John Horton Conway [Wiki](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

---

## Rules
- Any live cell with fewer than two live neighbours dies, as if by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
---
## Building

#### Dependencies:
- SDL2
#### Compiling:
```bash
cmake -B build
cmake --build build
```
Build tested on:
- CMake 4.0.2
- g++ 15.1.1
- Clang 19.1.7
- GNU/Linux 6.14.9 (I use Arch btw)
---
## Run the game
```bash
./build/GameOfLife
```
#### Control:
- Step forward - 'n'
- Enable/Disable autoplay - 's'
- Reset position - 'r'
- Clean everything - 'c'
- Speed up(autoplay mode) - 'k'
- Speed down(autoplay mode) - 'j'
- LMB to fill/clear the cell

To set the grid size, pass the width and height as command-line arguments:
```bash
./build/GameOfLife 30 25
```
---

## Examples

### [Video example](https://youtu.be/gA6wwBq5jAM)

### 101

Found by Achim Flammenkamp in August 1994. The name was suggested by Bill Gosper, noting that the phase shown below displays the period in binary.

<img src="examples/example101.gif" width="480" height="360"/>

### Achim's p16. 

Found by Achim Flammenkamp, July 1994.

<img src="examples/exampleAchim.gif" width="480" height="360"/>