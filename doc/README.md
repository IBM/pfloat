## Some more docs
The EXCEL file contains visualizations of all currently analyzed pfloat types.
You might also check the pdf files in this directory for details.

### pfloat16, pfloat32, pfloat64
For CNN simulations, it can be beneficial to have 
consecutive 16->32->64-bit types, where each 
'higher type' has 2x the dynamic range and more 
than 2x the number of mantissa bits.

### pfloat16d, pfloat32d, pfloat64d
For approximate computing, it is relevant 
that the full dynamic range is available when 
calculating (coarsely) with lower bit numbers. 
The `pfloat[x]d` types all have the same full
dynamic range as `double` for that reason.
