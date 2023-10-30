add_llvm_component_library(LLVMBogusDesc
  BogusELFObjectWriter.cpp
  BogusELFStreamer.cpp
  BogusInstPrinter.cpp
  BogusMCAsmInfo.cpp
  BogusMCCodeEmitter.cpp
  BogusMCTargetDesc.cpp
  BogusTargetStreamer.cpp
  BogusAsmBackend.cpp
  ADD_TO_COMPONENT
  Bogus

  LINK_COMPONENTS
  MC
  BogusInfo
  Support
  TargetParser
)
