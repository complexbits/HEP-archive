#include "lm_access/strip_util.hpp"

#include "TBranch.h"
#include "TLeaf.h"
#include <iostream>

int downloadLBN(LumFileMap& f_map, const std::string& fileID, 
		TTree& lbn_tree) {

  TBranch* B_LBN = lbn_tree.GetBranch("lm_id");
  if (! B_LBN) {
    std::cerr << "ERROR " 
	      << "strip_util: int downloadLBN(LumFileMap, string, lbn_tree)"
	      << " - cannot find lm_id branch" << std::endl;
    exit(1);
  }
  lbn_tree.SetBranchStatus("*", 0);
  lbn_tree.SetBranchStatus("lm_id", 1);
  
  TLeaf* _L_lbnid = B_LBN->GetLeaf("lbnid");
  Int_t lbnid;
  _L_lbnid->SetAddress(&lbnid);

  int n_good = 0;
  Stat_t n_lbn = lbn_tree.GetEntries();
  for(int i = 0; i < n_lbn; i++) {
    lbn_tree.GetEntry(i);
    n_good += f_map.downloadLBN(fileID, lbnid);
  }

  return n_good;
}
