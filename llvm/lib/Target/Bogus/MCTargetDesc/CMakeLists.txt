add_llvm_component_library(LLVMBogusDesc
  BogusMCAsmInfo.cpp
  BogusMCTargetDesc.cpp
  BogusInstPrinter.cpp
  BogusMCCodeEmitter.cpp
  ADD_TO_COMPONENT
  Bogus
)
