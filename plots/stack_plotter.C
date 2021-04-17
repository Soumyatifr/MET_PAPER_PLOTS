#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "THStack.h"
#include "TLegend.h"
#include "TMinuit.h"
#include "TMath.h"
#include "TProfile.h"
#include "TPaveStats.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include "TString.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include <utility>
#include <algorithm>
#include <functional>
#include "TEfficiency.h"


using namespace std;


void stack_plotter()
{

	double lumi = 41500.0;

        TFile *f1 = new TFile("JetHT_Run2017__.root", "read");
        //QCD
        TFile *f2 = new TFile("QCD_HT50to100_EOY_16_04_2021__.root", "read");
        TFile *f3 = new TFile("QCD_HT100to200_EOY_16_04_2021__.root", "read");
        TFile *f4 = new TFile("QCD_HT200to300_EOY_16_04_2021__.root", "read");
        TFile *f5 = new TFile("QCD_HT300to500_EOY_16_04_2021__.root", "read");
        TFile *f6 = new TFile("QCD_HT500to700_EOY_16_04_2021__.root", "read");
        TFile *f7 = new TFile("QCD_HT700to1000_EOY_16_04_2021__.root", "read");
        TFile *f8 = new TFile("QCD_HT1000to1500_EOY_16_04_2021__.root", "read"); 
	TFile *f9 = new TFile("QCD_HT1500to2000_EOY_16_04_2021__.root", "read");
        TFile *f10 = new TFile("QCD_HT2000toInf_EOY_16_04_2021__.root", "read");
        //TT
        TFile *f11 = new TFile("TTTo2L2Nu_EOY_16_04_2021__.root", "read");
        TFile *f12 = new TFile("TTToSemiLeptonic_EOY_16_04_2021__.root", "read");
        TFile *f13 = new TFile("TTToHadronic_EOY_16_04_2021__.root", "read");
        //WJets
        TFile *f14 = new TFile("WJetsToLNu_EOY_16_04_2021__.root", "read");
       
  

   TLegend *leg1 = new TLegend(0.58, 0.55, 0.82, 0.85);
   leg1->SetTextFont(42);
   leg1->SetLineColor(0);
   leg1->SetTextSize(0.045);
   leg1->SetFillStyle(0);


	gStyle->SetLineWidth(2);
   TCanvas *c = new TCanvas("c", "c",241,94,800,727);
   c->Range(-23.5781,-0.1522388,160.8859,1.35);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetGridx();
   c->SetGridy();
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.1215539);
   c->SetRightMargin(0.03884712);
   c->SetBottomMargin(0.1232092);
   c->SetFrameLineWidth(2);
   c->SetFrameBorderMode(0);


   TPad *pad1 = new TPad("pad1", "pad1",0,0.3,1,1);
      pad1->Draw();
      pad1->Range(-148.318,2.314742,1071.865,8.438788);
      pad1->SetFillColor(0);
      pad1->SetBorderMode(0);
      pad1->SetBorderSize(2);
      pad1->SetLogy();
      pad1->SetGridx();
      pad1->SetGridy();
      pad1->SetTickx(1);
      pad1->SetTicky(1);
      pad1->SetLeftMargin(0.1215539);
      pad1->SetRightMargin(0.05889724);
      pad1->SetBottomMargin(0.02);
      pad1->SetFrameBorderMode(0);
      pad1->SetFrameBorderMode(0);


      TPad *pad2 = new TPad("pad2", "newpad",0,0,1,0.3);
      pad2->Draw();
      pad2->Range(-148.318,-0.4344828,1071.865,1.009655);
      pad2->SetGridx();
      pad2->SetGridy();
      pad2->SetTickx(1);
      pad2->SetTicky(1);
      pad2->SetFillColor(0);
      pad2->SetBorderMode(0);
      pad2->SetBorderSize(2);
      pad2->SetLeftMargin(0.1215539);
      pad2->SetRightMargin(0.06015038);
      pad2->SetTopMargin(0.035);
      pad2->SetBottomMargin(0.3008596);
      pad2->SetFrameBorderMode(0);
      pad2->SetFrameBorderMode(0);



	TH1F *h1 = (TH1F*) f1->Get("h_met_phi_Recommended");
	TH1F *h2 = (TH1F*) f2->Get("h_met_phi_Recommended");
	TH1F *h3 = (TH1F*) f3->Get("h_met_phi_Recommended");
	TH1F *h4 = (TH1F*) f4->Get("h_met_phi_Recommended");
	TH1F *h5 = (TH1F*) f5->Get("h_met_phi_Recommended");
	TH1F *h6 = (TH1F*) f6->Get("h_met_phi_Recommended");
	TH1F *h7 = (TH1F*) f7->Get("h_met_phi_Recommended");
	TH1F *h8 = (TH1F*) f8->Get("h_met_phi_Recommended");
	TH1F *h9 = (TH1F*) f9->Get("h_met_phi_Recommended");
        TH1F *h10 = (TH1F*) f10->Get("h_met_phi_Recommended");

        TH1F *h_2 = (TH1F*) f2->Get("h_tot");
        TH1F *h_3 = (TH1F*) f3->Get("h_tot");
        TH1F *h_4 = (TH1F*) f4->Get("h_tot");
        TH1F *h_5 = (TH1F*) f5->Get("h_tot");
        TH1F *h_6 = (TH1F*) f6->Get("h_tot");
        TH1F *h_7 = (TH1F*) f7->Get("h_tot");
        TH1F *h_8 = (TH1F*) f8->Get("h_tot");
        TH1F *h_9 = (TH1F*) f9->Get("h_tot");
        TH1F *h_10 = (TH1F*) f10->Get("h_tot");

        TH1F *h11 = (TH1F*) f11->Get("h_met_phi_Recommended");
        TH1F *h12 = (TH1F*) f12->Get("h_met_phi_Recommended");
        TH1F *h13 = (TH1F*) f13->Get("h_met_phi_Recommended");
        TH1F *h_11 = (TH1F*) f11->Get("h_tot");
        TH1F *h_12 = (TH1F*) f12->Get("h_tot");
        TH1F *h_13 = (TH1F*) f13->Get("h_tot");

        TH1F *h14 = (TH1F*) f14->Get("h_met_phi_Recommended");
        TH1F *h_14 = (TH1F*) f14->Get("h_tot");

	double fact2 = (lumi*185300000)/h_2->GetBinContent(2); 
	double fact3 = (lumi*23700000)/h_3->GetBinContent(2);
	double fact4 = (lumi*1547000)/h_4->GetBinContent(2);
	double fact5 = (lumi*322600)/h_5->GetBinContent(2);
	double fact6 = (lumi*29980)/h_6->GetBinContent(2);
	double fact7 = (lumi*6334)/h_7->GetBinContent(2);
	double fact8 = (lumi*1088)/h_8->GetBinContent(2);
	double fact9 = (lumi*99.11)/h_9->GetBinContent(2);
        double fact10 = (lumi*20.23)/h_10->GetBinContent(2);

        double fact11 = (lumi*88.29)/h_11->GetBinContent(2); 
        double fact12 = (lumi*365.34)/h_12->GetBinContent(2);
        double fact13 = (lumi*377.96)/h_13->GetBinContent(2);
 
        double fact14 = (lumi*61526.7)/h_14->GetBinContent(2);


	THStack *hs = new THStack("hs","");


	pad1->cd();
	h2->Scale(fact2);
	h3->Scale(fact3);
	h4->Scale(fact4);
	h5->Scale(fact5);
	h6->Scale(fact6);
	h7->Scale(fact7);
	h8->Scale(fact8);
	h9->Scale(fact9);
        h10->Scale(fact10);        
        h11->Scale(fact11);
        h12->Scale(fact12);
        h13->Scale(fact13);
        h14->Scale(fact14);

	h2->Add(h3);
        h2->Add(h4);
	h2->Add(h5);
	h2->Add(h6);
        h2->Add(h7);
        h2->Add(h8);
        h2->Add(h9);
        h2->Add(h10);

        h11->Add(h12);
        h11->Add(h13);

	h2->SetFillColor(kRed);
        h11->SetFillColor(kBlue);
        h14->SetFillColor(kCyan);

        hs->Add(h14, "hist");
  	//hs->Add(h11, "hist");
        //hs->Add(h2, "hist");
   

	h1->SetTitle("");
	h1->SetStats(0);
        //h1->GetXaxis()->SetRangeUser(0,300);
	h1->GetXaxis()->SetLabelSize(0.);
        h1->GetYaxis()->SetLabelSize(0.045);
	h1->SetLineColor(kBlack);
        h1->SetMarkerColor(kBlack);
        h1->SetMarkerSize(0.8);
	h1->SetMarkerStyle(20);
	hs->Draw("");
	hs->GetXaxis()->SetLabelSize(0.);
        hs->GetYaxis()->SetLabelSize(0.045);
	hs->GetYaxis()->SetTitle("Events / 5 GeV");
        hs->GetYaxis()->SetTitleSize(0.05);
        hs->GetYaxis()->SetTitleOffset(1.00);
	//hs->GetXaxis()->SetRangeUser(0,300);
	hs->SetMaximum(50000);
	h1->Draw("ep:sames");

	TLatex *t2a = new TLatex(0.55,0.91,"#bf{CMS} #it{Preliminary}                                                        41.5 fb^{-1} (13 TeV)  ");
        t2a->SetNDC();
        t2a->SetTextFont(42);
        t2a->SetTextSize(0.04);
        t2a->SetTextAlign(20);
        t2a->Draw("same");


	leg1->AddEntry(h2, "QCD", "f");
	leg1->Draw("sames");

	c->cd();


	pad2->cd();
	TH1F *h_dat = (TH1F*)  h1->Clone();

	TH1F *h_mc = (TH1F*)  h2->Clone();

	h_dat->Divide(h_mc);
	h_dat->SetTitle("");
	//h_dat->GetXaxis()->SetRangeUser(0, 300);
	h_dat->GetXaxis()->SetTitle("MET (GeV)");
	h_dat->GetXaxis()->SetTitleSize(0.13);
	h_dat->GetYaxis()->SetTitle("Data/MC");
	h_dat->GetYaxis()->SetTitleOffset(0.35);
	h_dat->GetYaxis()->SetTitleSize(0.12);
	h_dat->GetXaxis()->SetLabelSize(0.1);
	h_dat->GetYaxis()->SetLabelSize(0.1);
	h_dat->GetXaxis()->SetTickLength(0.075);
	h_dat->GetYaxis()->SetNdivisions(505);
        h_dat->GetYaxis()->SetRangeUser(0.,2.);
        h_dat->SetStats(0);
	h_dat->SetLineColor(kBlack);
	h_dat->SetMarkerColor(kBlack);
        h_dat->SetMarkerSize(0.8);
        h_dat->SetMarkerStyle(20);
        h_dat->Draw("ep");

	TLine *line = new TLine(0, 1.,300, 1.);
        line->SetLineColor(kBlack);
        line->SetLineWidth(1.);
        line->Draw("same");

	c->cd();
	c->SaveAs("leadelept_2.pdf");
	c->SaveAs("leadelept_2.png");


}
