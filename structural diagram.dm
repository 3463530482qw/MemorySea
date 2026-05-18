graph TD
A[libc] --> B[iall]
C[RGFW] --> B
D[youklx] --> B
B --> E[main]
D -.->|模块| F[window] 
A -.->|被依赖| D
C -.->|被依赖| D