import FWCore.ParameterSet.Config as cms
import os

from tthAnalysis.HiggsToTauTau.configs.recommendedMEtFilters_cfi import *
from tthAnalysis.HiggsToTauTau.configs.EvtYieldHistManager_cfi import *

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.analyze_hh_2l_2tau = cms.PSet(
    treeName = cms.string('Events'),

    Process = cms.string(''),
    histogramDir = cms.string(''),
    era = cms.string(''),

    triggers_1e = cms.vstring(),
    use_triggers_1e = cms.bool(True),
    triggers_2e = cms.vstring(),
    use_triggers_2e = cms.bool(True),
    triggers_1mu = cms.vstring(),
    use_triggers_1mu = cms.bool(True),
    triggers_2mu = cms.vstring(),
    use_triggers_2mu = cms.bool(True),
    triggers_1e1mu = cms.vstring(),
    use_triggers_1e1mu = cms.bool(True),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(True),

    electronSelection = cms.string(''),
    muonSelection = cms.string(''),
    lep_mva_cut = cms.double(1.),
    apply_leptonGenMatching = cms.bool(True),
    leptonChargeSelection = cms.string(''),

    hadTauChargeSelection = cms.string(''),
    hadTauGenMatch = cms.string('all'),
    hadTauSelection = cms.string(''),
    apply_hadTauGenMatching = cms.bool(False),

    chargeSumSelection = cms.string(''),

    applyFakeRateWeights = cms.string(""),
    leptonFakeRateWeight = cms.PSet(
        inputFileName = cms.string(""),
        histogramName_e = cms.string(""),
        histogramName_mu = cms.string("")
    ),
    hadTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string(""),
        lead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True)
        ),
        sublead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True)
        )
    ),

    isMC = cms.bool(True),
    central_or_shift = cms.string(''),
    lumiScale = cms.double(1.),
    apply_genWeight = cms.bool(True),
    apply_hlt_filter = cms.bool(False),
    apply_met_filters = cms.bool(True),
    cfgMEtFilter = cms.PSet(),
    apply_hadTauFakeRateSF = cms.bool(False),

    fillGenEvtHistograms = cms.bool(False),
    cfgEvtYieldHistManager = cms.PSet(),

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_hadTaus = cms.string('Tau'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('MET'),
    branchName_memOutput = cms.string(''),

    branchName_genLeptons = cms.string('GenLep'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genPhotons = cms.string('GenPhoton'),
    branchName_genJets = cms.string('GenJet'),
    redoGenMatching = cms.bool(True),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string(''),

    useNonNominal = cms.bool(False),
    isDEBUG = cms.bool(False),
    hasLHE = cms.bool(True),

    selectBDT = cms.bool(False), ## Set it to true for making BDT training Ntuples
    ## ".xml -> Odd train:Even test" to be used for even evt no.  
    BDT_xml_FileName_even = cms.string("hhAnalysis/multilepton/data/2l_2tau_HH_dR03mvaVLoose_oversampling_finalVars_allMasses_Train_all_Masses_2l_2tau_diagnostics_with_reweighting_XGB_evtLevelSUM_HH_2l_2tau_res_10Var_odd_latest.xml"),
    ## ".xml -> Even train:Odd test" to be used for odd evt no.  
    BDT_xml_FileName_odd = cms.string("hhAnalysis/multilepton/data/2l_2tau_HH_dR03mvaVLoose_oversampling_finalVars_allMasses_Train_all_Masses_2l_2tau_diagnostics_with_reweighting_XGB_evtLevelSUM_HH_2l_2tau_res_10Var_even_latest.xml"),
    gen_mHH = cms.vdouble(250,260,270,280,300,350,400,450,500,550,600,650,700,750,800,850,900,1000), ## Set the signal mass range used in the BDT .pkl and .xml files
    ## ".pkl -> Odd train:Even test" to be used for even evt no.  
    pkl_FileName_even = cms.string("hhAnalysis/multilepton/data/2l_2tau_HH_dR03mvaVLoose_oversampling_finalVars_allMasses_Train_all_Masses_2l_2tau_diagnostics_with_reweighting_XGB_evtLevelSUM_HH_2l_2tau_res_10Var_odd_latest.pkl"),
    ## ".pkl -> Even train:Odd test" to be used for odd evt no.  
    pkl_FileName_odd = cms.string("hhAnalysis/multilepton/data/2l_2tau_HH_dR03mvaVLoose_oversampling_finalVars_allMasses_Train_all_Masses_2l_2tau_diagnostics_with_reweighting_XGB_evtLevelSUM_HH_2l_2tau_res_10Var_even_latest.pkl"),

    fitFunctionFileName = cms.string('hhAnalysis/multilepton/data/TProfile_signal_fit_func_InputVar_AllMassTraining.root'),

    evtWeight = cms.PSet(
        apply = cms.bool(False),
        histogramFile = cms.string(''),
        histogramName = cms.string(''),
        branchNameXaxis = cms.string(''),
        branchNameYaxis = cms.string(''),
        branchTypeXaxis = cms.string(''),
        branchTypeYaxis = cms.string(''),
    ),
)
