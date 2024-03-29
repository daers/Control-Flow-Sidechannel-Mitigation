#include "llvm/Pass.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Support/Format.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/BlockFrequencyInfo.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/ADT/SetOperations.h"
#include "llvm/Support/Debug.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Analysis/LoopInfo.h"

#include "llvm/Analysis/Loads.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopIterator.h"
#include "llvm/Analysis/LoopPass.h"

#include "llvm/Transforms/Utils/Local.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/Analysis/DominanceFrontier.h"

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace llvm;
using std::unordered_set; using std::unordered_map; using std::vector;
using std::queue;



namespace {
    struct ControlDependentBlocks{
        ControlDependentBlocks(BasicBlock* taken_, BasicBlock* notTaken_): taken(taken_), notTaken(notTaken_){}

        BasicBlock* taken;
        BasicBlock* notTaken;
    };

    ControlDependentBlocks detectIfStatement(Loop *L){
        for(auto* bb: L->getBlocksVector()){
            //find the BB with two predecessors
            if (bb->hasNPredecessors(2) && bb != L->getHeader()){
                BasicBlock* taken = *(pred_begin(bb));
                BasicBlock* notTaken = *(++(pred_begin(bb)));
                if (taken->getSinglePredecessor() == notTaken->getSinglePredecessor()){
                    ControlDependentBlocks found(taken, notTaken);
                    return found;
                }
            }
        }
        return ControlDependentBlocks(nullptr, nullptr);
    }

    void hoistOut(Loop* L, Instruction &I, BasicBlock* preIf){
        //make copy of instruction
        //instert instruction before terminator
        auto* newInst = I.clone();

        auto uses = I.uses();
        for (auto use = uses.begin(); use != uses.end(); ++use){
            use->set(newInst);
            // errs() << **use << "\n";
        }
        newInst->insertBefore(preIf->getTerminator());
        I.eraseFromParent();
        return;
    }

    vector<Instruction*> createInstList(BasicBlock* bb){
        vector<Instruction*> instlist;
        for(Instruction& I : *bb){
            instlist.push_back(&I);
        }
        return instlist;
    }

    void moveInstToBottomOfBB(BasicBlock* bb, Instruction& inst) {
    	auto* suppInst(inst.clone());
	inst.replaceAllUsesWith(suppInst);
	inst.eraseFromParent();
	suppInst->insertBefore(bb->getTerminator());
    }

    bool moveRDTSCToBlockTerminator(BasicBlock* loopBody) {
    	for (auto it = loopBody->begin(); it != loopBody->end(); ++it) {
		if (isa<CallInst>(*it)) {
			for (int i = 0; i < 5; ++i) {
				moveInstToBottomOfBB(loopBody, *it++);
			}
			errs() << *loopBody << "\n";
			return true;	
		}
	}
	errs() << "did NOT move call instruction\n";
	return false;
    }

    void findBrPredicateInst(BasicBlock* loopBody) {
    	for (auto it = loopBody->begin(); it != loopBody->end(); ++it) {
        	if (isa<ICmpInst>(*it)) {
               		errs() << "ICmp inst: " << *it << "\n";
        		auto* binOp(BinaryOperator::CreateNot(dyn_cast<Value>(&*it)));
			errs() << "binOp: " << *binOp << "\n";	
			binOp->insertBefore(loopBody->getTerminator());
		}
        }
    }

    bool hoistInstr(Loop* L, ControlDependentBlocks& change){
        //first, hoist the instructions in the first basic BLOCKS
        errs() << *change.taken << "\n";
        BasicBlock* preIf = change.taken->getSinglePredecessor();


        auto taken = createInstList(change.taken);
        auto notTaken = createInstList(change.notTaken);

        for (Instruction* I : taken) {
            if (I->getOpcode() != Instruction::Store){
                hoistOut(L, *I, preIf);
            } else {
                break;
            }
        }

        for (Instruction* I : notTaken) {
            if (I->getOpcode() != Instruction::Store) {
                hoistOut(L, *I, preIf);
            } else {
                break;
            }
        }
	moveRDTSCToBlockTerminator(preIf);
	errs() << "final:\n" << *preIf << "\n";
	return true;
    }

    

  struct CF_SEC : public LoopPass {
  public:

   static char ID;
   CF_SEC() : LoopPass(ID) {}
   virtual void getAnalysisUsage(AnalysisUsage &AU) const override;
   virtual bool runOnLoop(Loop *L, LPPassManager &LPM) override;

 private:

 };

 void CF_SEC::getAnalysisUsage(AnalysisUsage &AU) const {

 }

 bool CF_SEC::runOnLoop(Loop *L, LPPassManager &LPM) {
  ControlDependentBlocks change = detectIfStatement(L);
  if (change.taken != nullptr){
      //we have some bb's to change!
      auto result = hoistInstr(L, change);
      errs() << "Loop blocks after pass:\n";
      for (auto* bb : L->getBlocks()) {
	      errs() << *bb << "\n";
      }
      return result;
  }
  return false;
}

} // namespace

char CF_SEC::ID = 0;

static RegisterPass<CF_SEC> X("cf_sec", "Control Flow Security Pass by Jakiegona");

static void registerStatisticsPass(const PassManagerBuilder &,
 legacy::PassManagerBase &PM) {
  PM.add(new BranchProbabilityInfoWrapperPass());
  PM.add(new BlockFrequencyInfoWrapperPass());
  PM.add(new CF_SEC());
}
static RegisterStandardPasses
RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
 registerStatisticsPass);
