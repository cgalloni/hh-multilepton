#ifndef hhAnalysis_multilepton_Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger_h
#define hhAnalysis_multilepton_Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger_h

#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_2tau_trigger.h"

class Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger
  : public Data_to_MC_CorrectionInterface_0l_2tau_trigger
{
public:
  Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger(const edm::ParameterSet & cfg);
  ~Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger();

  //-----------------------------------------------------------------------------
  // set hadTau pT, eta and decay mode
  // (to be called once per event, before calling any of the getSF.. functions)

  void
  setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta, int hadTau1_decayMode,
             int hadTau2_genPdgId, double hadTau2_pt, double hadTau2_eta, int hadTau2_decayMode);

  void
  setHadTaus(double hadTau1_pt, double hadTau1_eta, double hadTau1_phi, int hadTau1_decayMode,
             double hadTau2_pt, double hadTau2_eta, double hadTau2_phi, int hadTau2_decayMode,
             double hadTau3_pt, double hadTau3_eta, double hadTau3_phi, int hadTau3_decayMode,
             double hadTau4_pt, double hadTau4_eta, double hadTau4_phi, int hadTau4_decayMode);
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC correction for trigger efficiency 
  double
  getSF_triggerEff(TriggerSFsys central_or_shift) const;
  //-----------------------------------------------------------------------------

protected:

  bool
  check_triggerSFsys_opt(TriggerSFsys central_or_shift) const;

  // define states of tau leg of ditau trigger for each reconstructed tau
  enum { k2tau, kNot2tau };

  // define auxiliary functions
  TauTriggerSFValues
  getProb_tau(int tau_status,
              const TauTriggerSFValues & eff_2tau_tauLeg) const;

  //-----------------------------------------------------------------------------
  // data/MC corrections for trigger efficiencies in 2017 ReReco data and Summer17 MC

  int hadTau3_genPdgId_;
  double hadTau3_pt_;
  double hadTau3_eta_;
  double hadTau3_phi_;
  int hadTau3_decayMode_;

  int hadTau4_genPdgId_;
  double hadTau4_pt_;
  double hadTau4_eta_;
  double hadTau4_phi_;
  int hadTau4_decayMode_;
};

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_hh_0l_4tau_trigger_h
