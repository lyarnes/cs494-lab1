# CS494 - Lab1: Jgraph
## Spirograph Generator: created by Lucas Yarnes

### Compiling
In order to compile, simply call `make` and the executable will be created in **bin**

### Parameters
The program **spiro** can be called with either 4 or 7 parameters, which are as follows:
`spiro outer-radius inner-radius distance-to-center print-guide r-color[OPT] g-color[OPT] b-color[OPT]`
which have the following meanings:
- `outer-radius`: the radius of the outer circle in the spirograph
- `inner-radius`: the radius of the inner circle in the spirograph
- `distance-to-center`: a value between [0,`inner-radius`] which describes the position of the pen in reference to the center of the inner circle of the spirograph. 0 means the pen is at the center of the inner circle, and a value `inner-radius` would indicate the pen is at the edge of the inner circle
- `print-guide` : a boolean (can be 0 or 1) that indicates if the outer circle should be printed in addition to the spirograph. It can help visualize how changes in the parameters affect the resulting graph
- `r-color`: an optional parameter ( [0,1] ) to specify the amount of red that should be present in the color of the graph
- `g-color`: an optional parameter ( [0,1] ) to specify the amount of green that should be present in the color of the graph
- `b-color`: an optional parameter ( [0,1] ) to specify the amount of blue that should be present in the color of the graph
