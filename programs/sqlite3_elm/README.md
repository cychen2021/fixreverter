
# Run FixReverter on the program sqlite3_elm

## IMPORTANT NOTE

Go to `/phasar/lib/PhasarLLVM/Pointer/LLVMBasedPointsToAnalysis.cpp` and change line 115 to

```c++
AA.registerFunctionAnalysis<llvm::CFLSteensAA>();
```

and rebuild and reinstall Phasar.

Don't know why but the original Anders alias analysis will stuck the whole pointer analysis process.

## TBD

TBD
