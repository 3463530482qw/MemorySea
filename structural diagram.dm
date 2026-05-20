graph TD
A[libc] --> B[iall]
C[sdl3] --> H
D[youklx] --> B
B --> E[main]
D -.->|模块| F[window] 
A -.->|被依赖| D
G[inih] --> B
G -.->|被依赖| D
H[spine] --> B
I[stb] --> H
H -.->|被依赖| D
D -.->|模块| I[image] 