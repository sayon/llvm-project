add_llvm_component_library(LLVMBogusDisassembler
  BogusDisassembler.cpp

  LINK_COMPONENTS
  CodeGenTypes
  MC
  MCDisassembler
  Support
  BogusInfo

  ADD_TO_COMPONENT
  Bogus
  )
