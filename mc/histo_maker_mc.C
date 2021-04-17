#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include<fstream>
#include<string>
#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TObject.h"
#include <iostream>
//g++ -g  -Wno-deprecated histo_maker_mc.C -o process_mc.exe   -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs`

double PhiInRange(const double& phi) {
  double phiout = phi;

  if( phiout > 2*M_PI || phiout < -2*M_PI) {
    phiout = fmod( phiout, 2*M_PI);
  }
  if (phiout <= -M_PI) phiout += 2*M_PI;
  else if (phiout >  M_PI) phiout -= 2*M_PI;

  return phiout;
}

bool isCheckTight(double& eta, double& nhf, double& chf, double& nef, double& cef, double& muf, int& nnh, int& nch)
{
        float Eta = eta;
        float NHF = nhf; // pfjet->neutralHadronEnergyFraction();
        float NEMF = nef; //pfjet->neutralEmEnergyFraction();
        float CHF = chf; // pfjet->chargedHadronEnergyFraction();
        float MUF = muf; //pfjet->muonEnergyFraction();
        float CEMF = cef; //pfjet->chargedEmEnergyFraction();
        int NumConst = nnh + nch; //pfjet->chargedMultiplicity()+pfjet->neutralMultiplicity();
        int NumNeutralParticles =nnh; // pfjet->neutralMultiplicity();
        int CHM = nch;//pfjet->chargedMultiplicity(); 

        bool isJetIDLoose= false;

        if( fabs(Eta) <= 2.6){
                isJetIDLoose = (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF<0.80 && CHF>0 && CHM>0 && CEMF<0.80 );
        }
        else if( fabs(Eta)>2.6 && fabs(Eta)<=2.7){
                isJetIDLoose = (NHF<0.90 && NEMF<0.99 && MUF<0.80 && CHM>0 && CEMF<0.80 );
        }
        else if (fabs(eta)>2.7 && fabs(eta)<=3.0 ){
                isJetIDLoose = (NEMF>0.01 && NEMF<0.99 && NumNeutralParticles>1 );
        }
        else if (fabs(eta)>3.0 && fabs(eta) <= 5.0) {
                isJetIDLoose = (NHF> 0.2 && NEMF<0.90 && NumNeutralParticles>10 );
        }
        return isJetIDLoose;
}

using namespace std;
int main(int argc, char *argv[]){
  cout<<"Program started"<<endl;
        char fOut[50], fout1[50],fout2[50];
        string inputFile=argv[3];
        string path="sourceFiles/";
        if(inputFile=="FILELIST/QCD_HT50to100_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/QCD_HT50to100_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/QCD_HT100to200_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/QCD_HT100to200_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/QCD_HT200to300_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/QCD_HT200to300_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/QCD_HT300to500_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/QCD_HT300to500_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/QCD_HT500to700_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/QCD_HT500to700_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/QCD_HT700to1000_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/QCD_HT700to1000_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/QCD_HT1500to2000_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/QCD_HT1500to2000_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/QCD_HT2000toInf_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/QCD_HT2000toInf_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/QCD_HT1000to1500_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/QCD_HT1000to1500_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/TTTo2L2Nu_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/TTTo2L2Nu_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/TTToSemiLeptonic_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/TTToSemiLeptonic_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/TTToHadronic_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/TTToHadronic_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }
        else if(inputFile=="FILELIST/WJetsToLNu_EOY_16_04_2021.log"){
                sprintf(fOut,"HIST/WJetsToLNu_EOY_16_04_2021_%s_%s.root",argv[1],argv[2]);
        }



  TFile *fout = new TFile(fOut,"RECREATE");
  //ofstream out1, out2;
  //out1.open(fout1,ios::app);
  //***********************************************************************************************************************//
  //Histograms for leading jets
  TH1F *h_met = new TH1F("h_met", "h_met", 32, 300, 3500);
  TH1F *h_pumet = new TH1F("h_pumet", "h_pumet", 32, 300, 3500);
  TH1F *h_met_Recommended = new TH1F("h_met_Recommended", "h_met_Recommended", 32, 300, 3500);
  TH1F *h_pumet_Recommended = new TH1F("h_pumet_Recommended", "h_pumet_Recommended", 32, 300, 3500);

  TH1F *h_met_phi = new TH1F("h_met_phi", "h_met_phi", 25, -M_PI, M_PI);
  TH1F *h_pumet_phi = new TH1F("h_pumet_phi", "h_pumet_phi", 25, -M_PI, M_PI);
  TH1F *h_met_phi_Recommended = new TH1F("h_met_phi_Recommended", "h_met_phi_Recommended", 25, -M_PI, M_PI);
  TH1F *h_pumet_phi_Recommended = new TH1F("h_pumet_phi_Recommended", "h_pumet_phi_Recommended", 25, -M_PI, M_PI);

  TH1F *h_ht = new TH1F("h_ht", "h_ht", 40, 0, 2000);
  TH1F *h_ht_Recommended = new TH1F("h_ht_Recommended", "h_ht_Recommended", 40, 0, 2000);

  TH1I *h_evt = new TH1I("h_evt","h_evt",10, 0, 10);
  TH1F *h_tot = new TH1F("h_tot", "h_tot", 2, 0.0, 2.0);
  //*************************************************************************************************************************//

   int TotEvt=0,count=0;
   long int processedEvt=0;
   double weight = 1;

   string fileName;
   ifstream infile;
   infile.open(argv[3]);
   while(!infile.eof()){
   count = count+1;
   getline(infile,fileName);

   int L_lim = stof(argv[1]);
   int H_lim = stof(argv[2]);
   if(count<=L_lim)continue;
   if(count>H_lim)continue;
   TFile *f = TFile::Open(fileName.data());
   if(f==0) continue;

   cout<<fileName<<endl;

   TTree *met_tree;
   ULong64_t  evn, run, lumi;
   Double_t met, pumet, metphi, pumetphi, wt;
   Int_t nv;
   Bool_t          HLT;
   Bool_t          Flag_goodVertices;
   Bool_t          Flag_globalTightHalo2016Filter;
   Bool_t          Flag_globalSuperTightHalo2016Filter;
   Bool_t          Flag_HBHENoiseFilter;
   Bool_t          Flag_HBHENoiseIsoFilter;
   Bool_t          Flag_EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          Flag_BadPFMuonFilter;
   Bool_t          Flag_BadChargedCandidateFilter;
   Bool_t          Flag_eeBadScFilter;
   Bool_t          Flag_ecalBadCalibFilter;
   Bool_t          Flag_ecalLaserCorrFilter;
   Bool_t          Flag_hfNoisyHitsFilter;
   Bool_t          Flag_EcalDeadCellBoundaryEnergyFilter;
   Bool_t          PassecalBadCalibFilter_Update;
   Bool_t          PassecalLaserCorrFilter_Update;
   Bool_t          PassEcalDeadCellBoundaryEnergyFilter_Update;
   Bool_t          PassBadChargedCandidateFilter_Update;

   TH1F * h_wt = (TH1F*)f->Get("ntuplemakerminiaod/h_tot_gen_weights_2");
   h_tot->Add(h_wt);
   met_tree = (TTree*)f->Get("ntuplemakerminiaod/tree"); 

   met_tree->SetBranchAddress("_eventNb",  &evn);
   met_tree->SetBranchAddress("_runNb",  &run);
   met_tree->SetBranchAddress("_lumiBlock",  &lumi);

   met_tree->SetBranchAddress("_genWeight",&wt);
   //MET Variables
   met_tree->SetBranchAddress("_met",  &met);
   met_tree->SetBranchAddress("_met_phi",  &metphi);
   met_tree->SetBranchAddress("_puppimet",  &pumet);
   met_tree->SetBranchAddress("_puppimet_phi",  &pumetphi);


   //Filters
   met_tree->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices);
   met_tree->SetBranchAddress("Flag_globalTightHalo2016Filter", &Flag_globalTightHalo2016Filter);
   met_tree->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter);
   met_tree->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter);
   met_tree->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter);
   met_tree->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter);
   met_tree->SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter);
   met_tree->SetBranchAddress("Flag_BadChargedCandidateFilter", &Flag_BadChargedCandidateFilter);
   met_tree->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter);
   met_tree->SetBranchAddress("Flag_ecalBadCalibFilter", &Flag_ecalBadCalibFilter);
   met_tree->SetBranchAddress("Flag_hfNoisyHitsFilter", &Flag_hfNoisyHitsFilter);
   met_tree->SetBranchAddress("Flag_ecalLaserCorrFilter", &Flag_ecalLaserCorrFilter);
   met_tree->SetBranchAddress("Flag_EcalDeadCellBoundaryEnergyFilter", &Flag_EcalDeadCellBoundaryEnergyFilter);
   met_tree->SetBranchAddress("PassecalBadCalibFilter_Update", &PassecalBadCalibFilter_Update);
   met_tree->SetBranchAddress("PassecalLaserCorrFilter_Update", &PassecalLaserCorrFilter_Update);
   met_tree->SetBranchAddress("PassEcalDeadCellBoundaryEnergyFilter_Update", &PassEcalDeadCellBoundaryEnergyFilter_Update);
   met_tree->SetBranchAddress("PassBadChargedCandidateFilter_Update", &PassBadChargedCandidateFilter_Update);

   
   //HT variables
   double ht;
   met_tree->SetBranchAddress("_ht", &ht);

   //HLT Triggr
   bool hlt_1, hlt_2, hlt_3, hlt_4;
   met_tree->SetBranchAddress("HLT_PFMET110_PFMHT110_IDTight",&hlt_1);
   met_tree->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight",&hlt_2);
   met_tree->SetBranchAddress("HLT_PFMET130_PFMHT130_IDTight",&hlt_3);
   met_tree->SetBranchAddress("HLT_PFMET140_PFMHT140_IDTight",&hlt_4); 


   bool isTight = false;
   int nEntries = met_tree->GetEntries();
   for(int iEntry = 0; iEntry < nEntries; ++iEntry)
    {
       met_tree->GetEntry(iEntry);
       h_evt->Fill(1);
       if(hlt_1 || hlt_2 || hlt_3 || hlt_4)
         {
           h_evt->Fill(2);
           if (met < 300) continue;
           h_evt->Fill(3);
           h_met->Fill(met, wt); h_pumet->Fill(pumet, wt); h_met_phi->Fill(metphi, wt); h_pumet_phi->Fill(pumetphi, wt); h_ht->Fill(ht, wt);
           if(Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_eeBadScFilter && PassecalBadCalibFilter_Update && Flag_BadPFMuonFilter)
              {
                 h_met_Recommended->Fill(met, wt); h_pumet_Recommended->Fill(pumet, wt); h_met_phi_Recommended->Fill(metphi, wt); h_pumet_phi_Recommended->Fill(pumetphi, wt); h_ht_Recommended->Fill(ht, wt);h_evt->Fill(4);
             }
         }
    }
   f->Close();
   } 
    infile.close();
    fout->cd();
    fout->Write();
    h_evt->Write();
    h_met->Write();h_pumet->Write();h_met_phi->Write();h_pumet_phi->Write();h_ht->Write();
    h_met_Recommended->Write();h_pumet_Recommended->Write();h_met_phi_Recommended->Write();h_pumet_phi_Recommended->Write();h_ht_Recommended->Write();
    h_tot->Write();
    fout->Close();    
}














































