add_llvm_component_group(Bogus)

set(LLVM_TARGET_DEFINITIONS Bogus.td)

tablegen(LLVM BogusGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM BogusGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM BogusGenCodeEmitter.inc -gen-emitter)
tablegen(LLVM BogusGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM BogusGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM BogusGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM BogusGenCallingConv.inc -gen-callingconv)
tablegen(LLVM BogusGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM BogusGenMCPseudoLowering.inc -gen-pseudo-lowering)

add_public_tablegen_target(BogusCommonTableGen)

add_llvm_target(BogusCodeGen
  BogusAsmPrinter.cpp
  BogusFrameLowering.cpp
  BogusInstrInfo.cpp
  BogusISelLowering.cpp
  BogusRegisterInfo.cpp
  BogusSubtarget.cpp
  BogusTargetObjectFile.cpp
  BogusISelDAGToDAG.cpp
  BogusTargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  IPO
  MC
  Passes
  Scalar
  SelectionDAG
  Support
  Target
  TransformUtils

  ADD_TO_COMPONENT
  Bogus

)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
