/*!
 *
 */

/*!
 *
 */

#include "headers/TMVAReaderAnalysis.h"

void TMVAReaderAnalysis(vector<TString> tmvamethods, string SBJetOutputFilename, string TMVAOutputFilename)
{
    TFile *eventinputfile = TFile::Open(TString::Format("OutputFiles/%s.root", SBJetOutputFilename.data()), "read");
    TFile *eventoutputfile = TFile::Open(TString::Format("TMVAResults/%s.root", TMVAOutputFilename.data()), "recreate");
    TTree *EventJet = (TTree *)eventinputfile->Get("EventJet");
    int event_entries = EventJet->GetEntries();
    Float_t MVAjet1_pT, MVAjet2_pT, MVAjet1_m, MVAjet2_m, MVAjet1_px, MVAjet2_px, MVAjet_mjj;
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

    Float_t jet1_px = (Float_t)d_jet1_px;
    Float_t jet1_py = (Float_t)d_jet1_py;
    Float_t jet1_pz = (Float_t)d_jet1_pz;
    Float_t jet1_E = (Float_t)d_jet1_E;
    Float_t jet2_px = (Float_t)d_jet2_px;
    Float_t jet2_py = (Float_t)d_jet2_py;
    Float_t jet2_pz = (Float_t)d_jet2_pz;
    Float_t jet2_E = (Float_t)d_jet2_E;

    TH1F *histMVA = new TH1F("MVA", "MVA", 100, -1, 1);
    TH1F *histMVAErr = new TH1F("MVAErr", "MVAErr", 100, -1, 1);
    TH1F *histMVASig = new TH1F("MVASig", "MVASig", 1000, 0, 100);
    TH1F *hpTbackground = new TH1F("pTbackground", "pTbackground", 100, 1.1e3, 2.6e3);
    TH1F *hpTsignal = new TH1F("pTsignal", "pTsignal", 100, 1.1e3, 2.6e3);
    TH1F *hpTtotal = new TH1F("pTtotal", "pTtotal", 100, 1.1e3, 2.6e3);
    TH1F *hmjjbackground = new TH1F("mjj_background", "mjj_background", 100, 1e3, 7e3);
    TH1F *hmjjsignal = new TH1F("mjj_signal", "mjj_signal", 100, 1e3, 7e3);
    TH1F *hmjjtotal = new TH1F("mjj_total", "mjj_total", 100, 1e3, 7e3);
    TCanvas *c0 = new TCanvas("c0", "c0", 1366, 768);
    c0->Print("MVAEvaluation.pdf[");
    TCanvas *c0err = new TCanvas("c0err", "c0err", 1366, 768);
    c0err->Print("MVAEvaluationError.pdf[");
    TCanvas *c0sig = new TCanvas("c0sig", "c0sig", 1366, 768);
    c0sig->Print("MVAEvaluationSignificance.pdf[");
    TCanvas *c1 = new TCanvas("c1", "c1", 1366, 768);
    c1->Print("hpTtotal.pdf[");
    TCanvas *c2 = new TCanvas("c2", "c2", 1366, 768);
    c2->Print("hpTsignal.pdf[");
    TCanvas *c3 = new TCanvas("c3", "c3", 1366, 768);
    c3->Print("hmjjtotal.pdf[");
    TCanvas *c4 = new TCanvas("c4", "c4", 1366, 768);
    c4->Print("hmjjsignal.pdf[");

    //String containing the name of the file currently examined
    string currentfilename;
    int methoditerationindex = 0;

    for (vector<TString>::iterator stringit = tmvamethods.begin(); stringit != tmvamethods.end(); ++stringit)
    {
        //Looking for any weight of the specified method in the folder containing the training results
        for (auto& p: filesystem::directory_iterator("TMVAResults/Wprimo/weights"))
        {   
            currentfilename = p.path().filename();
            if (currentfilename.find(stringit->Data(), 0, 3) != string::npos && currentfilename.find(".xml", 0, 4) != string::npos)
            {
                cout << "Analyzing file " << currentfilename << " with method tag " << stringit->Data() << endl;
                TString::Format("TMVAResults/Wprimo/weights/%s", currentfilename.data());
                methoditerationindex = currentfilename.find(stringit->Data());

                //Defining the reader that should do the MVA evaluation
                TMVA::Reader *reader = new TMVA::Reader("Color");
                reader->AddVariable("MVAjet1_pT := sqrt(pow(jet1_px,2) + pow(jet1_py,2))", &MVAjet1_pT);
                reader->AddVariable("MVAjet2_pT := sqrt(pow(jet2_px,2) + pow(jet2_py,2))", &MVAjet2_pT);
                reader->AddVariable("MVAjet1_m := sqrt( abs(pow(jet1_E,2) - pow(jet1_px,2) - pow(jet1_py,2) - pow(jet1_pz,2)))", &MVAjet1_m);
                reader->AddVariable("MVAjet2_m := sqrt( abs(pow(jet2_E,2) - pow(jet2_px,2) - pow(jet2_py,2) - pow(jet2_pz,2)))", &MVAjet2_m);
                reader->AddVariable("MVAjet_mjj := sqrt( abs(pow(jet1_E+jet2_E,2) - pow(jet1_px+jet2_px,2) - pow(jet1_py+jet2_py,2) - pow(jet1_pz+jet2_pz,2)))", &MVAjet_mjj);
                reader->AddVariable("MVAjet1_px := jet1_px", &MVAjet1_px);
                reader->AddVariable("MVAjet2_px := jet2_px", &MVAjet2_px);
                reader->BookMVA(stringit->Data(), TString::Format("TMVAResults/Wprimo/weights/%s", currentfilename.data()));

                //Cleaning already filled histograms
                histMVA->Reset();
                histMVAErr->Reset();
                histMVASig->Reset();
                hpTbackground->Reset();
                hpTsignal->Reset();
                hpTtotal->Reset();
                hmjjbackground->Reset();
                hmjjsignal->Reset();
                hmjjtotal->Reset();

                //Checking that input tree is read from the right file, because histograms are written to a different file
                eventinputfile->cd();
                for (int readerindex = 0; readerindex < event_entries; readerindex++)
                {
                    jet1_px = (Float_t)d_jet1_px;
                    jet1_py = (Float_t)d_jet1_py;
                    jet1_pz = (Float_t)d_jet1_pz;
                    jet1_E = (Float_t)d_jet1_E;
                    jet2_px = (Float_t)d_jet2_px;
                    jet2_py = (Float_t)d_jet2_py;
                    jet2_pz = (Float_t)d_jet2_pz;
                    jet2_E = (Float_t)d_jet2_E;
                    EventJet->GetEntry(readerindex);
                    MVAjet1_pT = sqrt(pow(jet1_px, 2) + pow(jet1_py, 2));
                    MVAjet2_pT = sqrt(pow(jet2_px, 2) + pow(jet2_py, 2));
                    MVAjet1_m = sqrt(abs(pow(jet1_E, 2) - pow(jet1_px, 2) - pow(jet1_py, 2) - pow(jet1_pz, 2)));
                    MVAjet2_m = sqrt(abs(pow(jet2_E, 2) - pow(jet2_px, 2) - pow(jet2_py, 2) - pow(jet2_pz, 2)));
                    MVAjet1_px = jet1_px;
                    MVAjet2_px = jet2_px;
                    MVAjet_mjj = sqrt(pow((jet1_E + jet2_E), 2) - pow((jet1_px + jet2_px), 2) - pow((jet1_py + jet2_py), 2) - pow((jet1_pz + jet2_pz), 2));
                    histMVA->Fill(reader->EvaluateMVA(stringit->Data()));
                    histMVAErr->Fill(reader->GetMVAError());
                    histMVASig->Fill((reader->EvaluateMVA(stringit->Data()) / (reader->GetMVAError())));
                    mjj = (Double_t)sqrt(pow((jet1_E + jet2_E), 2) - pow((jet1_px + jet2_px), 2) - pow((jet1_py + jet2_py), 2) - pow((jet1_pz + jet2_pz), 2));
                    if (reader->EvaluateMVA(stringit->Data()) > 0 && stringit->CompareTo("kBDT") == 0)
                    {
                        hpTsignal->Fill(MVAjet1_pT);
                        hmjjsignal->Fill(mjj);                        
                    }
                    else if (reader->EvaluateMVA(stringit->Data()) > 0.5)
                    {
                        hpTsignal->Fill(MVAjet1_pT);
                        hmjjsignal->Fill(mjj);
                    }
                    else
                    {
                        hpTbackground->Fill(MVAjet1_pT);
                        hmjjbackground->Fill(mjj);
                    }
                    hpTtotal->Fill(MVAjet1_pT);
                    hmjjtotal->Fill(mjj);
                }

                //Stampo il numero di eventi di segnale trovato
                cout << endl << "There are " << hmjjsignal->GetEntries() << " events containing a W' " << endl << endl;

                //Drawing TMVAEvaluation histogram
                c0->cd();
                histMVA->SetLineColor(kBlue);
                histMVA->SetFillColorAlpha(kBlue, 0.04);
                histMVA->SetTitle(TString::Format("MVAEvaluation using method %s", currentfilename.substr(methoditerationindex, stringit->Length()+1).data() ) );
                histMVA->GetXaxis()->SetTitle("EvaluateMVA");
                histMVA->GetYaxis()->SetTitle("Occurences");
                histMVA->Draw();
                c0->Update();
                c0->Print("MVAEvaluation.pdf");

                c0err->cd();
                histMVAErr->SetLineColor(kBlue);
                histMVAErr->SetFillColorAlpha(kBlue, 0.04);
                histMVAErr->SetTitle(TString::Format("MVAEvaluation error using method %s", currentfilename.substr(methoditerationindex, stringit->Length()+1).data() ) );
                histMVAErr->GetXaxis()->SetTitle("EvaluateMVA Error");
                histMVAErr->GetYaxis()->SetTitle("Occurences");
                histMVAErr->Draw();
                c0err->Update();
                c0err->Print("MVAEvaluationError.pdf");

                c0sig->cd();
                histMVASig->SetLineColor(kBlue);
                histMVASig->SetFillColorAlpha(kBlue, 0.04);
                histMVASig->SetTitle(TString::Format("MVAEvaluation significance using method %s", currentfilename.substr(methoditerationindex, stringit->Length()+1).data() ) );
                histMVASig->GetXaxis()->SetTitle("EvaluateMVA Significance");
                histMVASig->GetYaxis()->SetTitle("Occurences");
                histMVASig->Draw();
                c0sig->Update();
                c0sig->Print("MVAEvaluationSignificance.pdf");

                //Adding signal and background to histogram stack
                c1->cd();
                THStack *hpTstack = new THStack("LeadingpT_total", "LeadingpT_total");
                hpTbackground->SetLineColor(kRed);
                hpTbackground->SetFillColor(kRed);
                hpTbackground->SetStats(kFALSE);
                hpTsignal->SetLineColor(kBlue);
                hpTsignal->SetFillColorAlpha(kBlue, 0.3);
                hpTsignal->SetStats(kFALSE);
                hpTstack->Add(hpTbackground);
                hpTstack->Add(hpTsignal);
                hpTstack->Draw("");
                hpTstack->SetTitle(TString::Format("Leading jet transverse momentum: p_{T} (method %s)", currentfilename.substr(methoditerationindex, stringit->Length()+1).data() ) );
                hpTstack->GetXaxis()->SetTitle("Leading jet transverse momentum: p_{T}[GeV]");
                hpTstack->GetYaxis()->SetTitle("Occurences");

                //Adjusting the legend
                auto legend = new TLegend(0.65, 0.8, 0.9, 0.9);
                legend->SetHeader("Leading jet p_{T}", "C"); // option "C" allows to center the header
                legend->AddEntry(hpTbackground, "Background", "f");
                legend->AddEntry(hpTsignal, "Signal", "f");
                legend->Draw("same");

                c1->Update();
                c1->Print("hpTtotal.pdf");

                c2->cd();
                hpTsignal->Draw("");
                hpTsignal->SetTitle(TString::Format("Leading jet transverse momentum: p_{T} reconstructed with method %s", currentfilename.substr(methoditerationindex, stringit->Length()+1).data() ) );
                hpTsignal->GetXaxis()->SetTitle("Leading jet transverse momentum: p_{T}[GeV]");
                hpTsignal->GetYaxis()->SetTitle("Occurences");
                c2->Update();
                c2->Print("hpTsignal.pdf");

                c3->cd();
                THStack *hmjjstack = new THStack("mjj_total", "mjj_total");
                hmjjbackground->SetLineColor(kRed);
                hmjjbackground->SetFillColor(kRed);
                hmjjbackground->SetStats(kFALSE);
                hmjjsignal->SetLineColor(kBlue);
                hmjjsignal->SetFillColorAlpha(kBlue, 0.3);
                hmjjsignal->SetStats(kFALSE);
                hmjjstack->Add(hmjjbackground);
                hmjjstack->Add(hmjjsignal);
                hmjjstack->Draw("");
                hmjjstack->SetTitle(TString::Format("Combined jet mass: m_{jj} (method %s)", currentfilename.substr(methoditerationindex, stringit->Length()+1).data() ) );
                hmjjstack->GetXaxis()->SetTitle("Combined jet mass: m_{jj}[GeV]");
                hmjjstack->GetYaxis()->SetTitle("Occurences");

                //Adjusting the legend
                auto legendm = new TLegend(0.65, 0.8, 0.9, 0.9);
                legendm->SetHeader("Combined jet mass: m_{jj}", "C"); // option "C" allows to center the header
                legendm->AddEntry(hmjjbackground, "Background", "f");
                legendm->AddEntry(hmjjsignal, "Signal", "f");
                legendm->Draw("same");

                c3->Update();
                c3->Print("hmjjtotal.pdf");

                //Fitting the new structure
                Double_t larghezza = 500;
                Double_t fitmjjmin = 3500-larghezza, fitmjjmax = 3500+larghezza;
                TF1 *fitsignalmass = new TF1("fitmass", [](double *x, double *p){return p[0]*exp(-0.5*pow((x[0]-p[1]),2)/pow(p[2],2))+p[3]; }, fitmjjmin, fitmjjmax, 4);
                fitsignalmass->SetParName(0, "Amplitude");
                fitsignalmass->SetParameter(0, 1000);
                fitsignalmass->SetParName(1, "Mean");
                fitsignalmass->SetParameter(1, 3500);
                fitsignalmass->SetParName(2, "Width");
                fitsignalmass->SetParameter(2, 100);
                fitsignalmass->SetParName(3, "ConstantBias");
                fitsignalmass->SetParameter(3, 10);

                //Plotting the dijet mass supposed to be the signal
                c4->cd();
                hmjjsignal->SetTitle(TString::Format("W' mass reconstructed with method %s", currentfilename.substr(methoditerationindex, stringit->Length()+1).data() ) );
                hmjjsignal->GetXaxis()->SetTitle("Combined jet mass: m_{jj}[GeV]");
                hmjjsignal->GetYaxis()->SetTitle("Occurences");
                hmjjsignal->Fit(fitsignalmass, "", "", fitmjjmin, fitmjjmax);
                hmjjsignal->SetStats(kTRUE);
                hmjjsignal->Draw();
                gStyle->SetOptStat();
                c4->Update();
                TPaveStats *mjjsignalstats = (TPaveStats*)c4->GetPrimitive("stats");
                mjjsignalstats->SetX1NDC(0.7);
                mjjsignalstats->SetY1NDC(0.6);
                mjjsignalstats->SetX2NDC(0.9);
                mjjsignalstats->SetY2NDC(0.9);
                mjjsignalstats->SetOptFit(1111);
                mjjsignalstats->Draw("SAME");
                //hmjjsignal->SetStats(0);
                //c4->Modified();
                c4->Print("hmjjsignal.pdf");

                eventoutputfile->cd();
                histMVA->Write();
                histMVASig->Write();
                histMVAErr->Write();
                hpTbackground->Write();
                hpTsignal->Write();
                hpTtotal->Write();
                hmjjbackground->Write();
                hmjjsignal->Write();
                hmjjtotal->Write();

                //Freeing memory allocated for the reader
                delete reader;
            }
        }
    }
    c0->Print("MVAEvaluation.pdf]");
    c0err->Print("MVAEvaluationError.pdf]");
    c0sig->Print("MVAEvaluationSignificance.pdf]");
    c1->Print("hpTtotal.pdf]");
    c2->Print("hpTsignal.pdf]");
    c3->Print("hmjjtotal.pdf]");
    c4->Print("hmjjsignal.pdf]");   
    eventinputfile->Close();
    eventoutputfile->Close();
}