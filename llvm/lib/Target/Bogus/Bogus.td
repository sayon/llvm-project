include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions, Register information, etc
//===----------------------------------------------------------------------===//

include "BogusSchedule.td"
include "BogusRegisterInfo.td"
include "BogusCallingConv.td"
include "BogusInstrInfo.td"

def BogusInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// Bogus processors supported
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic",  NoSchedModel, []>;

def BogusAsmWriter : AsmWriter {
  string AsmWriterClassName = "InstPrinter";
  bit isMCAsmWriter = 1;
}

def Bogus : Target {
  let InstructionSet = BogusInstrInfo;
  let AssemblyWriters = [BogusAsmWriter];

}
