#include "hhAnalysis/multilepton/interface/Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger.h"

#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFs2017.h" // TauTriggerSFs2017

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // TriggerSFsys, getTriggerSF_option()

#include <TString.h> // Form()
#include <TMath.h> // TMath::Abs()

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with()

#include <cassert> // assert()

Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger::Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger(const edm::ParameterSet & cfg)
  : Data_to_MC_CorrectionInterface_0l_2tau_trigger(cfg)
  , hadTau3_genPdgId_(0)
  , hadTau3_pt_(0.)
  , hadTau3_eta_(0.)
  , hadTau3_phi_(0.)
  , hadTau3_decayMode_(0)
  , hadTau4_genPdgId_(0)
  , hadTau4_pt_(0.)
  , hadTau4_eta_(0.)
  , hadTau4_phi_(0.)
  , hadTau4_decayMode_(0)
{}

Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger::~Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger()
{}

void
Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger::setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta, int hadTau1_decayMode,
                                                              int hadTau2_genPdgId, double hadTau2_pt, double hadTau2_eta, int hadTau2_decayMode)
{
  throw cmsException(this, __func__, __LINE__) << "Invalid call";
}

void
Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger::setHadTaus(double hadTau1_pt, double hadTau1_eta, double hadTau1_phi, int hadTau1_decayMode,
                                                              double hadTau2_pt, double hadTau2_eta, double hadTau2_phi, int hadTau2_decayMode,
                                                              double hadTau3_pt, double hadTau3_eta, double hadTau3_phi, int hadTau3_decayMode,
                                                              double hadTau4_pt, double hadTau4_eta, double hadTau4_phi, int hadTau4_decayMode)
{
  hadTau1_pt_        = hadTau1_pt;
  hadTau1_eta_       = hadTau1_eta;
  hadTau1_phi_       = hadTau1_phi;
  hadTau1_decayMode_ = hadTau1_decayMode;

  hadTau2_pt_        = hadTau2_pt;
  hadTau2_eta_       = hadTau2_eta;
  hadTau2_phi_       = hadTau2_phi;
  hadTau2_decayMode_ = hadTau2_decayMode;

  hadTau3_pt_        = hadTau3_pt;
  hadTau3_eta_       = hadTau3_eta;
  hadTau3_phi_       = hadTau3_phi;
  hadTau3_decayMode_ = hadTau3_decayMode;

  hadTau4_pt_        = hadTau4_pt;
  hadTau4_eta_       = hadTau4_eta;
  hadTau4_phi_       = hadTau4_phi;
  hadTau4_decayMode_ = hadTau4_decayMode;
}

double
Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger::getSF_triggerEff(TriggerSFsys central_or_shift) const
{
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << '\n';
  }
  assert(check_triggerSFsys_opt(central_or_shift));

  TauTriggerSFValues eff_2tau_tauLeg1_data;
  TauTriggerSFValues eff_2tau_tauLeg1_mc;
  TauTriggerSFValues eff_2tau_tauLeg2_data;
  TauTriggerSFValues eff_2tau_tauLeg2_mc;
  TauTriggerSFValues eff_2tau_tauLeg3_data;
  TauTriggerSFValues eff_2tau_tauLeg3_mc;
  TauTriggerSFValues eff_2tau_tauLeg4_data;
  TauTriggerSFValues eff_2tau_tauLeg4_mc;

  if(std::fabs(hadTau1_eta_) <= 2.1 && aux::hasDecayMode(allowedDecayModes_, hadTau1_decayMode_))
  {
    eff_2tau_tauLeg1_data = effTrigger_tauLeg_.getTauTriggerEvalData(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_, hadTau1_decayMode_);
    eff_2tau_tauLeg1_mc   = effTrigger_tauLeg_.getTauTriggerEvalMC  (hadTau1_pt_, hadTau1_eta_, hadTau1_phi_, hadTau1_decayMode_);
  }

  if(std::fabs(hadTau2_eta_) <= 2.1 && aux::hasDecayMode(allowedDecayModes_, hadTau2_decayMode_))
  {
    eff_2tau_tauLeg2_data = effTrigger_tauLeg_.getTauTriggerEvalData(hadTau2_pt_, hadTau2_eta_, hadTau2_phi_, hadTau2_decayMode_);
    eff_2tau_tauLeg2_mc   = effTrigger_tauLeg_.getTauTriggerEvalMC  (hadTau2_pt_, hadTau2_eta_, hadTau2_phi_, hadTau2_decayMode_);
  }

  if(std::fabs(hadTau3_eta_) <= 2.1 && aux::hasDecayMode(allowedDecayModes_, hadTau3_decayMode_))
  {
    eff_2tau_tauLeg3_data = effTrigger_tauLeg_.getTauTriggerEvalData(hadTau3_pt_, hadTau3_eta_, hadTau3_phi_, hadTau3_decayMode_);
    eff_2tau_tauLeg3_mc   = effTrigger_tauLeg_.getTauTriggerEvalMC  (hadTau3_pt_, hadTau3_eta_, hadTau3_phi_, hadTau3_decayMode_);
  }

  if(std::fabs(hadTau4_eta_) <= 2.1 && aux::hasDecayMode(allowedDecayModes_, hadTau4_decayMode_))
  {
    eff_2tau_tauLeg4_data = effTrigger_tauLeg_.getTauTriggerEvalData(hadTau4_pt_, hadTau4_eta_, hadTau4_phi_, hadTau4_decayMode_);
    eff_2tau_tauLeg4_mc   = effTrigger_tauLeg_.getTauTriggerEvalMC  (hadTau4_pt_, hadTau4_eta_, hadTau4_phi_, hadTau4_decayMode_);
  }

  TauTriggerSFValues prob_data;
  TauTriggerSFValues prob_mc;

  for(int tau1_status = k2tau; tau1_status <= kNot2tau; ++tau1_status)
  {
    const TauTriggerSFValues prob_tau1_data = getProb_tau(tau1_status, eff_2tau_tauLeg1_data);
    const TauTriggerSFValues prob_tau1_mc   = getProb_tau(tau1_status, eff_2tau_tauLeg1_mc);

    for(int tau2_status = k2tau; tau2_status <= kNot2tau; ++tau2_status)
    {
      const TauTriggerSFValues prob_tau2_data = getProb_tau(tau2_status, eff_2tau_tauLeg2_data);
      const TauTriggerSFValues prob_tau2_mc   = getProb_tau(tau2_status, eff_2tau_tauLeg2_mc);

      for(int tau3_status = k2tau; tau3_status <= kNot2tau; ++tau3_status)
      {
        const TauTriggerSFValues prob_tau3_data = getProb_tau(tau3_status, eff_2tau_tauLeg3_data);
        const TauTriggerSFValues prob_tau3_mc   = getProb_tau(tau3_status, eff_2tau_tauLeg3_mc);

        for(int tau4_status = k2tau; tau4_status <= kNot2tau; ++tau4_status)
        {
          const TauTriggerSFValues prob_tau4_data = getProb_tau(tau4_status, eff_2tau_tauLeg4_data);
          const TauTriggerSFValues prob_tau4_mc   = getProb_tau(tau4_status, eff_2tau_tauLeg4_mc);

	  int nTrig_2tau_tauLeg = 0;
	  if(tau1_status == k2tau)
	  {
	    ++nTrig_2tau_tauLeg;
	  }
	  if(tau2_status == k2tau)
          {
	    ++nTrig_2tau_tauLeg;
	  }
	  if(tau3_status == k2tau)
          {
            ++nTrig_2tau_tauLeg;
          }
          if(tau4_status == k2tau)
          {
            ++nTrig_2tau_tauLeg;
          }

          const bool isTrig_2tau_toy = nTrig_2tau_tauLeg >= 2;

          if(isTriggered_2tau_ == isTrig_2tau_toy)
          {
            prob_data += prob_tau1_data * prob_tau2_data * prob_tau3_data * prob_tau4_data;
            prob_mc   += prob_tau1_mc   * prob_tau2_mc   * prob_tau3_mc   * prob_tau4_mc;
          }
        }
      }
    }
  }

  if(isDEBUG_)
  {
    std::cout << "hadTau (lead):    pT = " << hadTau1_pt_ << ", eta = " << hadTau1_eta_ << "\n"
                 "hadTau (sublead): pT = " << hadTau2_pt_ << ", eta = " << hadTau2_eta_ << "\n"
                 "hadTau (third):   pT = " << hadTau3_pt_ << ", eta = " << hadTau3_eta_ << "\n"
                 "hadTau (fourth):  pT = " << hadTau4_pt_ << ", eta = " << hadTau4_eta_ << "\n"
                 "eff (X_tau1): data = " << eff_2tau_tauLeg1_data   << ", MC = " << eff_2tau_tauLeg1_mc   << "\n"
                 "eff (X_tau2): data = " << eff_2tau_tauLeg2_data   << ", MC = " << eff_2tau_tauLeg2_mc   << "\n"
                 "eff (X_tau3): data = " << eff_2tau_tauLeg3_data   << ", MC = " << eff_2tau_tauLeg3_mc   << "\n"
                 "eff (X_tau4): data = " << eff_2tau_tauLeg4_data   << ", MC = " << eff_2tau_tauLeg4_mc   << '\n'
    ;
  }

  const double sf = aux::compSF(prob_data, prob_mc, central_or_shift);
  if(isDEBUG_)
  {
    const int idxCase = isTriggered_2tau_ ? 1 : 0;
    const std::string text_2tau = isTriggered_2tau_ ? "ditau trigger doesn't fire" : "ditau trigger fires";
    std::cout << "case " << idxCase << ": " << text_2tau << "\n"
                 " eff: data = " << prob_data << ", MC = " << prob_mc << " --> SF = " << sf << '\n'
    ;
  }

  return sf;
}
 
TauTriggerSFValues
Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger::getProb_tau(int tau_status,
                                                               const TauTriggerSFValues & eff_2tau_tauLeg) const
{
  TauTriggerSFValues prob;
  switch(tau_status)
  {
    case k2tau:    prob = eff_2tau_tauLeg;      break;
    case kNot2tau: prob = 1. - eff_2tau_tauLeg; break;
    default:       assert(0);
  }
  return prob;
}

bool
Data_to_MC_CorrectionInterface_hh_0l_4tau_trigger::check_triggerSFsys_opt(TriggerSFsys central_or_shift) const
{
  return
    central_or_shift == TriggerSFsys::central          ||
    central_or_shift == TriggerSFsys::shiftUp          ||
    central_or_shift == TriggerSFsys::shiftDown        ||
    central_or_shift == TriggerSFsys::shift_0l2tauUp   ||
    central_or_shift == TriggerSFsys::shift_0l2tauDown
  ;
}
