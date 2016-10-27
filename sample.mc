read M[1];
read M[2];
read M[6];
store M[7] R0;
print (Factorial of)  M[1]  5(is)  M[7] (n) ;
label0
load R[2] M[4]; 
< R[2] 0;
if R2 goto 9;
goto  $ ;
store M[5] R2;

store M[5] R4;
load R[6] M[4]; 
> R[6] 0;goto  $ ;
load R0 M[4];
load R1 M[5];
mul R0 R0 R1;
store M[5] R6;
load R6 M[4];
mod R6 R6  1;
store M[4] R6;
