#include "Bogus.h"
#include "CommonArgs.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/Options.h"
#include "llvm/Option/ArgList.h"

using namespace clang::driver;
using namespace clang::driver::toolchains;
using namespace clang;
using namespace llvm::opt;

BogusToolChain::BogusToolChain(const Driver &D, const llvm::Triple &Triple,
                               const ArgList &Args)
    : ToolChain(D, Triple, Args) {
  // ProgramPaths are found via 'PATH' environment variable.
}

bool BogusToolChain::isPICDefault() const { return true; }

bool BogusToolChain::isPIEDefault(const llvm::opt::ArgList &Args) const { return false; }

bool BogusToolChain::isPICDefaultForced() const { return true; }

bool BogusToolChain::SupportsProfiling() const { return false; }

bool BogusToolChain::hasBlocksRuntime() const { return false; }
