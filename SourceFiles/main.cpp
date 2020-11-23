/*! \mainpage TMVA-2Jet-Analysis
 *
 * \section intro_sec Introduction
 *
 * This project has been developed as an assignment for the Computing (in HEP) exam.\n
 * The work is divided in three parts:
 * 1. Data reading
 * 2. Data manipulation
 * 3. TMVA algorithm implementation
 *
 * \section dataread_sec Data reading
 * 
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */

#include <TROOT.h>
#include <TApplication.h>
#include <TString.h>
#include "headers/TreeCreator.h"
#include "headers/TreeJetCreator.h"
#include "headers/SBTreeCreator.h"
#include "headers/SBTreeJetKinematicsCreator.h"
#include "headers/TMVAFactoryAnalysis.h"
#include "headers/TMVAReaderAnalysis.h"

//It can be useful to use these namespaces
using namespace std;
using namespace fastjet;

int main(int argc, char *argv[])
{
  // Input files and relative flags (1 for event file, 0 for unknown, -1 for background)
  vector<TString> filenames;
  vector<int> sbflags;
  filenames.push_back("events_anomalydetection_Z_XY_qqq");
  sbflags.push_back(1);
  filenames.push_back("events_anomalydetection");
  sbflags.push_back(0);
  filenames.push_back("events_LHCO2020_backgroundMC_Pythia");
  sbflags.push_back(-1);
  filenames.push_back("events_LHCO2020_BlackBox1");
  sbflags.push_back(0);
  filenames.push_back("lhc_anomalydetection_small");
  sbflags.push_back(0);

  // Methods that the user wants to use to do the MVA (search TMVA::Types to find the names)
  vector<TString> tmvamethods;
  tmvamethods.push_back("kDL");
  tmvamethods.push_back("kBDT");
  tmvamethods.push_back("kMLP");
  tmvamethods.push_back("kPDEFoam");

  // Name of output file
  string SBOutputfile = "SBOutput";
  string SBJetOutputfile = "SBJetOutput";
  string TMVAFactoryoutputname = "TMVAFactory";
  string TMVAReaderoutputname  = "WprimoEventClassification";

  // Number of jets that has to be clustered from event data
  unsigned long sbjetnumber = 100000, eventjetnumber = 100000;
  double_t R = 1.0, pT_min = 20;

  // Defining number of jets that has to be put in the TMVA factory
  vector<unsigned long int> tmvaevents;
  tmvaevents.push_back((unsigned long int)10000);
  tmvaevents.push_back((unsigned long int)10000);
  tmvaevents.push_back((unsigned long int)10000);
  tmvaevents.push_back((unsigned long int)10000);

  // Useful Variables
  int i = 0;
  vector<TString> question;
  string answer;

  question.push_back("Do you wish to analyze these files? (YES/NO)");
  PrintFuncInfo(question);
  question.clear();
  for (vector<TString>::iterator stringit = filenames.begin(); stringit != filenames.end(); ++stringit)
  {
    cout << "\t" << stringit->Data() << endl;
  }
  cout << endl;
  cin >> answer;

  //The user wants to analyze the files
  if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
  {
    question.push_back("Do you wish to transform these *.h5 files in *.root files? (YES/NO)");
    question.push_back("(Answer no if these root files exist already)");
    PrintFuncInfo(question);
    question.clear();
    cin >> answer;
    if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
    {
      for (vector<TString>::iterator stringit = filenames.begin(); stringit != filenames.end(); ++stringit)
      {
        //Converting *.h5 files to *.root files
        openh5(TString::Format("%s.h5", stringit->Data()));
        TreeCreator(*stringit);
        dataset_info_list.clear();
      }
      question.push_back("Do you wish to analyze these *.root files and distinguish signal/background/event? (YES/NO)");
      question.push_back("(Answer no if these root files have already been distinguished in a SBOutput.root file)");
      PrintFuncInfo(question);
      question.clear();
      cin >> answer;
      if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
      {
        for (vector<TString>::iterator stringit = filenames.begin(); stringit != filenames.end(); ++stringit, i++)
        {
          //Distinguishing signal from background and event and vice versa
          openh5(TString::Format("%s.h5", stringit->Data()));
          SBTreeCreator(TString::Format("OutputFiles/%s.root", stringit->Data()), TString::Format("OutputFiles/%s.root", SBOutputfile.data()), sbflags[i], i);
          dataset_info_list.clear();
        }
      }
    }
    else
    {
      question.push_back("Do you wish to analyze these already existing *.root files and distinguish signal/background/event? (YES/NO)");
      question.push_back("(Answer no if these root files have already been distinguished in a SBOutput.root file)");
      PrintFuncInfo(question);
      question.clear();
      cin >> answer;
      if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
      {
        for (vector<TString>::iterator stringit = filenames.begin(); stringit != filenames.end(); ++stringit)
        {
          //Distinguishing signal from background and event and vice versa*
          openh5(TString::Format("%s.h5", stringit->Data()));
          SBTreeCreator(TString::Format("OutputFiles/%s.root", stringit->Data()), TString::Format("OutputFiles/%s.root", SBOutputfile.data()), sbflags[i], i);
          dataset_info_list.clear();
        }
      }
    }
    question.push_back("Do you wish to create SBJetOutput.root file to store jet kinematic quantities? (YES/NO)");
    question.push_back(TString::Format("You will cluster %lu signal/background jet and %lu event jet. Are you ok? (YES/NO)", sbjetnumber, eventjetnumber));
    question.push_back("(Answer no if jets have already been clustered and stored in a SBJetOutput.root file)");
    PrintFuncInfo(question);
    question.clear();
    cin >> answer;
    if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
    {
      SBTreeJetKinematicsCreator(TString::Format("OutputFiles/%s.root", SBOutputfile.data()), TString::Format("OutputFiles/%s.root", SBJetOutputfile.data()), filenames.size(), sbjetnumber, eventjetnumber, R, pT_min);
    }
    question.push_back("Do you wish to use these methods to set up the TMVA Factory? (YES/NO)");
    question.push_back("(Answer no if you already have trained the algorithm using the sample jets)");
    PrintFuncInfo(question);
    question.clear();
    for (vector<TString>::iterator stringit = tmvamethods.begin(); stringit != tmvamethods.end(); ++stringit)
    {
      cout << "\t" << stringit->Data() << endl;
    }
    cout << endl;
    cin >> answer;
    if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
    {
      TMVAFactoryAnalysis(tmvamethods, tmvaevents, SBJetOutputfile, TMVAFactoryoutputname);
    }
    question.push_back("Do you wish to use these methods to set up the TMVA Reader? (YES/NO)");
    question.push_back("(Answer no if you don't want to do the multivariate analysis of the jets)");
    PrintFuncInfo(question);
    question.clear();
    for (vector<TString>::iterator stringit = tmvamethods.begin(); stringit != tmvamethods.end(); ++stringit)
    {
      cout << "\t" << stringit->Data() << endl;
    }
    cout << endl;
    cin >> answer;
    if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
    {
      TMVAReaderAnalysis(tmvamethods, SBJetOutputfile, TMVAReaderoutputname);
    }
    else
    {
      question.push_back("The user doesn't want to analyze those jets");
      PrintFuncInfo(question);
      question.clear();
    }
  }
  else
  {
    question.push_back("The user doesn't want to analyze those files");
    PrintFuncInfo(question);
    question.clear();
    return 0;
  }
  /*
  TFile *eventinputfile = TFile::Open("OutputFiles/SBJetOutput.root", "read");
  TFile *eventoutputfile = TFile::Open("TMVAResults/Outclassevent.root", "recreate");
  TTree *EventJet = (TTree *)eventinputfile->Get("EventJet");
  int event_entries = EventJet->GetEntries();
  Float_t MVAjet1_pT, MVAjet2_pT, MVAjet1_m, MVAjet2_m, MVAjet1_px, MVAjet2_px, MVAjet2_mjj;
  Double_t d_jet1_px, d_jet1_py, d_jet1_pz, d_jet1_E, d_jet2_px, d_jet2_py, d_jet2_pz, d_jet2_E;
  Double_t mjj;
  EventJet->SetBranchAddress("jet1_E", &d_jet1_E);
  EventJet->SetBranchAddress("jet1_px", &d_jet1_px);
  EventJet->SetBranchAddress("jet1_py", &d_jet1_py);
  EventJet->SetBranchAddress("jet1_pz", &d_jet1_pz);
  EventJet->SetBranchAddress("jet2_E", &d_jet2_E);
  EventJet->SetBranchAddress("jet2_px", &d_jet2_px);
  EventJet->SetBranchAddress("jet2_py", &d_jet2_py);
  EventJet->SetBranchAddress("jet2_pz", &d_jet2_pz);

  TMVA::Reader *reader = new TMVA::Reader("Color");
  Float_t jet1_px = (Float_t) d_jet1_px;
  Float_t jet1_py = (Float_t) d_jet1_py;
  Float_t jet1_pz = (Float_t) d_jet1_pz;
  Float_t jet1_E = (Float_t) d_jet1_E;
  Float_t jet2_px = (Float_t) d_jet2_px;
  Float_t jet2_py = (Float_t) d_jet2_py;
  Float_t jet2_pz = (Float_t) d_jet2_pz;
  Float_t jet2_E = (Float_t) d_jet2_E;
  reader->AddVariable("MVAjet1_pT := sqrt(pow(jet1_px,2) + pow(jet1_py,2))", &MVAjet1_pT);
  reader->AddVariable("MVAjet2_pT := sqrt(pow(jet2_px,2) + pow(jet2_py,2))", &MVAjet2_pT);
  reader->AddVariable("MVAjet1_m := sqrt( abs(pow(jet1_E,2) - pow(jet1_px,2) - pow(jet1_py,2) - pow(jet1_pz,2)))", &MVAjet1_m);
  reader->AddVariable("MVAjet2_m := sqrt( abs(pow(jet2_E,2) - pow(jet2_px,2) - pow(jet2_py,2) - pow(jet2_pz,2)))", &MVAjet2_m);
  reader->AddVariable("MVAjet_mjj := sqrt( abs(pow(jet1_E+jet2_E,2) - pow(jet1_px+jet2_px,2) - pow(jet1_py+jet2_py,2) - pow(jet1_pz+jet2_pz,2)))", &MVAjet2_mjj);
  reader->AddVariable("MVAjet1_px := jet1_px", &MVAjet1_px);
  reader->AddVariable("MVAjet2_px := jet2_px", &MVAjet2_px);
  reader->BookMVA("kPDEFoam", "TMVAResults/Wprimo/weights/TMVAClassification_PDEFoam1.weights.xml");

  TH1F *histMVA = new TH1F("MVA", "MVA", 100, -1, 1);
  TH1F *histMVAErr = new TH1F("MVAErr", "MVAErr", 100, -1, 1);
  TH1F *histMVASig = new TH1F("MVASig", "MVASig", 1000, 10000000000, 1000000000000);
  TH1F *hpTbackground = new TH1F("pTbackground", "pTbackground", 50, 1.1e3, 2.6 * 1e3);
  TH1F *hpTsignal = new TH1F("pTsignal", "pTsignal", 50, 1.1e3, 2.6 * 1e3);
  TH1F *hmjjbackground = new TH1F("mjj_total", "mjj_total", 50, 1e3, 7e3);
  TH1F *hmjjsignal = new TH1F("mjj_signal", "mjj_signal", 50, 1e3, 7e3);

  for (int readerindex = 0; readerindex < event_entries; readerindex++)
  {
    jet1_px = (Float_t) d_jet1_px;
    jet1_py = (Float_t) d_jet1_py;
    jet1_pz = (Float_t) d_jet1_pz;
    jet1_E = (Float_t) d_jet1_E;
    jet2_px = (Float_t) d_jet2_px;
    jet2_py = (Float_t) d_jet2_py;
    jet2_pz = (Float_t) d_jet2_pz;
    jet2_E = (Float_t) d_jet2_E;
    EventJet->GetEntry(readerindex);
    MVAjet1_pT = sqrt(pow(jet1_px, 2) + pow(jet1_py, 2));
    MVAjet2_pT = sqrt(pow(jet2_px, 2) + pow(jet2_py, 2));
    MVAjet1_m = sqrt( abs(pow(jet1_E,2) - pow(jet1_px,2) - pow(jet1_py,2) - pow(jet1_pz,2)));
    MVAjet2_m = sqrt( abs(pow(jet2_E,2) - pow(jet2_px,2) - pow(jet2_py,2) - pow(jet2_pz,2)));
    MVAjet1_px = jet1_px;
    MVAjet2_px = jet2_px;
    histMVA->Fill(reader->EvaluateMVA("kPDEFoam"));
    histMVAErr->Fill(reader->GetMVAError());
    histMVASig->Fill( (reader->EvaluateMVA("kPDEFoam")/(reader->GetMVAError() ) ) );
    mjj = (Double_t)sqrt(pow((jet1_E + jet2_E), 2) - pow((jet1_px + jet2_px), 2) - pow((jet1_py + jet2_py), 2) - pow((jet1_pz + jet2_pz), 2));
    if (reader->EvaluateMVA("kPDEFoam") > 0.3)
    {
      hpTsignal->Fill(MVAjet1_pT);
      hmjjsignal->Fill(mjj);
    }
    else
    {
      hpTbackground->Fill(MVAjet1_pT);
      hmjjbackground->Fill(mjj);
    }
  }
  //Stampo il numero di eventi di segnale trovato
  cout << "There are " << hmjjsignal->GetEntries() << " events containing a W' " << endl;

  //Drawing TMVAEvaluation histogram
  TCanvas *c0 = new TCanvas("c0", "c0", 1366, 768);
  c0->cd();
  histMVA->SetLineColor(kBlue);
  histMVA->SetFillColorAlpha(kBlue, 0.04);
  histMVA->SetTitle("MVAEvaluation");
  histMVA->GetXaxis()->SetTitle("EvaluateMVA \"kPDEFoam\"");
  histMVA->GetYaxis()->SetTitle("Occurences");
  histMVA->Draw();
  c0->Update();
  c0->SaveAs("MVAEvaluation.png");

  TCanvas *c0err = new TCanvas("c0err", "c0err", 1366, 768);
  c0err->cd();
  histMVAErr->SetLineColor(kBlue);
  histMVAErr->SetFillColorAlpha(kBlue, 0.04);
  histMVAErr->SetTitle("MVAEvaluation Error");
  histMVAErr->GetXaxis()->SetTitle("EvaluateMVA Error \"kPDEFoam\"");
  histMVAErr->GetYaxis()->SetTitle("Occurences");
  histMVAErr->Draw();
  c0err->Update();
  c0err->SaveAs("MVAEvaluationError.png");
  
  TCanvas *c0sig = new TCanvas("c0sig", "c0sig", 1366, 768);
  c0sig->cd();
  histMVASig->SetLineColor(kBlue);
  histMVASig->SetFillColorAlpha(kBlue, 0.04);
  histMVASig->SetTitle("MVAEvaluation Significance");
  histMVASig->GetXaxis()->SetTitle("EvaluateMVA Significance \"kPDEFoam\"");
  histMVASig->GetYaxis()->SetTitle("Occurences");
  histMVASig->Draw();
  c0sig->Update();
  c0sig->SaveAs("MVAEvaluationSignificance.png");

  //Inserisco gli istogrammi del pt e della massa in una collezione e li rappresento
  TCanvas *c1 = new TCanvas("c1", "c1", 1366, 768);
  c1->cd();
  THStack *hpTstack = new THStack("hs", "");
  hpTbackground->SetLineColor(kRed);
  hpTbackground->SetFillColor(kRed);
  hpTbackground->SetStats(kFALSE);
  hpTsignal->SetLineColor(kBlue);
  hpTsignal->SetFillColorAlpha(kBlue, 0.3);
  hpTsignal->SetStats(kFALSE);
  hpTstack->Add(hpTbackground);
  hpTstack->Add(hpTsignal);
  hpTstack->SetTitle("Leading jet transverse momentum: p_{T}[GeV]");
  hpTstack->Draw();

  //Adjusting the legend
  auto legend = new TLegend(0.65, 0.8, 0.9, 0.9);
  legend->SetHeader("Leading jet p_{T}","C"); // option "C" allows to center the header
  legend->AddEntry(hpTbackground, "Background", "f");
  legend->AddEntry(hpTsignal, "Signal", "f");
  legend->Draw("same");

  c1->Update();
  c1->SaveAs("hpTtotal.png");

  TCanvas *c2 = new TCanvas("c2", "c2", 1366, 768);
  c2->cd();
  hpTsignal->Draw("");
  c2->Update();
  c2->SaveAs("hpTsignal.png");
  
  TCanvas *c3 = new TCanvas("c3", "c3", 1366, 768);
  c3->cd();
  THStack *hmjjstack = new THStack("hsm", "");
  hmjjbackground->SetLineColor(kRed);
  hmjjbackground->SetFillColor(kRed);
  hmjjbackground->SetStats(kFALSE);
  hmjjsignal->SetLineColor(kBlue);
  hmjjsignal->SetFillColorAlpha(kBlue, 0.3);
  hmjjsignal->SetStats(kFALSE);
  hmjjstack->Add(hmjjbackground);
  hmjjstack->Add(hmjjsignal);
  hmjjstack->SetTitle("Combined jet mass: m_{jj}[GeV]");
  hmjjstack->Draw("");
  c3->Update();
  c3->SaveAs("hmjjtotal.png");

  TCanvas *c4 = new TCanvas("c4", "c4", 1366, 768);
  hmjjsignal->Draw("");
  c4->Update();
  c4->SaveAs("hmjjsignal.png");

  eventoutputfile->cd();
  histMVA->Write();
  histMVASig->Write();
  histMVAErr->Write();
  hpTbackground->Write();
  hpTsignal->Write();
  hmjjbackground->Write();
  hmjjsignal->Write();
  eventinputfile->Close();
  eventoutputfile->Close();
  delete reader;*/

  return 0;
}

    //TApplication *Analysisroot_app = new TApplication("Analysis", &argc, argv);
    /*Se l'utente vuole visionare i risultati subito si avvia un applicativo root*/
    /*std::cout << "\nWould you see the results now? [Y/N]" << std::endl;
    std::cin.get(str,256);
    if(strcmp(str,"Y") == 0)
    {
      hdestep->Draw();
      c1->Update();
      c1->SaveAs("c1.png");
      Analysisroot_app->Run();
    }*/