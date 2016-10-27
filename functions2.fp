CONSTANTS { x 1 }

FUNCTIONS
{ facto val return retval
    { if {< val 0}
      then {= retval -1} 
    }
}

MAIN
{print (Factorial of) x (is) f}

