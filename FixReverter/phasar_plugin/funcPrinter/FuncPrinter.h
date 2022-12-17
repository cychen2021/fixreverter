#ifndef FuncPrinter_H_
#define FuncPrinter_H_

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "phasar/PhasarLLVM/Plugins/Interfaces/IfdsIde/IFDSTabulationProblemPlugin.h"

namespace psr {
class ProjectIRDB;
class LLVMTypeHierarchy;
class LLVMBasedICFG;
class LLVMPointsToInfo;
} // namespace psr

struct MyFlowFact : public psr::FlowFactWrapper<const llvm::Value *> {

  using FlowFactWrapper::FlowFactWrapper;

  void print(std::ostream &OS,
             const llvm::Value *const &NonZeroFact) const override {
    OS << psr::llvmIRToShortString(NonZeroFact) << '\n';
  }
};

class FuncPrinter : public psr::IFDSTabulationProblemPlugin {
private:
  psr::FlowFactManager<MyFlowFact> FFManager;

public:
  FuncPrinter(const psr::ProjectIRDB *IRDB, const psr::LLVMTypeHierarchy *TH,
                const psr::LLVMBasedICFG *ICF, psr::LLVMPointsToInfo *PT,
                std::set<std::string> EntryPoints);

  ~FuncPrinter() override = default;

  const psr::FlowFact *createZeroValue() const override;

  FlowFunctionPtrType
  getNormalFlowFunction(const llvm::Instruction *curr,
                        const llvm::Instruction *succ) override;

  FlowFunctionPtrType getCallFlowFunction(const llvm::Instruction *callStmt,
                                       const llvm::Function *destMthd) override;

  FlowFunctionPtrType
  getRetFlowFunction(const llvm::Instruction *callSite,
                     const llvm::Function *calleeMthd,
                     const llvm::Instruction *exitStmt,
                     const llvm::Instruction *retSite) override;

  FlowFunctionPtrType
  getCallToRetFlowFunction(const llvm::Instruction *callSite,
                           const llvm::Instruction *retSite,
                           std::set<const llvm::Function *> callees) override;

  FlowFunctionPtrType
  getSummaryFlowFunction(const llvm::Instruction *callStmt,
                         const llvm::Function *destMthd) override;

  psr::InitialSeeds<n_t, d_t, l_t> initialSeeds() override;
};

extern "C" std::unique_ptr<psr::IFDSTabulationProblemPlugin>
makeFuncPrinter(const psr::ProjectIRDB *IRDB,
                  const psr::LLVMTypeHierarchy *TH,
                  const psr::LLVMBasedICFG *ICF, psr::LLVMPointsToInfo *PT,
                  std::set<std::string> EntryPoints);

#endif
