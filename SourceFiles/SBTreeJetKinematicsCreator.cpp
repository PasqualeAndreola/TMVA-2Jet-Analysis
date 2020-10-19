/*! \file SBTreeJetKinematicsCreator.cpp
 *  \brief Source file for \ref SBTreeJetKinematicsCreator function implementation.
 */

/*! \fn SBTreeJetKinematicsCreator(const char *filename, const char *jetfilename, int numberoffiles, unsigned long int sbjetnumber, unsigned long int eventjetnumber, double_t R, double_t pT_min) "";

 *  \brief Function that creates a *.root file containing signal/background/event kinematic quantities of the two most massive jets
 *  \author Pasquale Andreola
 * 
 *  This function is designed to create as much trees as initial files.\n
 *  These trees will store the kinematic quantities (px, py, pz, E) of the two most massive jets.\n
 *  These jets are clustered using \c R as jet radius. The \c pT_min is the minimum transverse momentum accepted by user analysis.\n
 *  Jets are created by the \ref JetCreator function, so please refer to its documentation to find the characteristics of the algorithm.\n
 *  Returns 0 if there is no error during execution.
 * 
 *  \param *filename        Name of the *.root file that include trees with signal/background/event kinematics
 *  \param *jetfilename     Name of the *.root file that will store signal/background/event jet kinematics 
 *  \param numberoffiles    Number of files that user has analyzed in this session
 *  \param sbjetnumber      Number of signal/background jet that the users wants to cluster
 *  \param eventjetnumber   Number of real event jet that the users wants to cluster
 *  \param R                Jet radius, usually related to the angular reach of the jet. Can be found in the anti-kT algorithm formula
 *  \param pT_min           Minimum transverse jet momentum that is accepted for user's analysis
 */

#include "headers/SBTreeJetKinematicsCreator.h"

/*These namespaces can be useful*/
using namespace std;
using namespace fastjet;

int SBTreeJetKinematicsCreator(const char *filename, const char *jetfilename, int numberoffiles, unsigned long int sbjetnumber, unsigned long int eventjetnumber, double_t R, double_t pT_min)
{
    /*Printing fastjet banner*/
    ClusterSequence::print_banner();

    /*Variables to adjust the print formatting and banner print*/
    int ncolumns2beprinted = 100;
    vector<TString> str2beprinted;
    TString author = "P. Andreola";
    TString license = "This function is provided without warranty under the GNU GPL v3 or higher";
    str2beprinted.push_back("SBTreeJetKinematicsCreator");
    str2beprinted.push_back(TString::Format("Opens the SBOutputfile and clusters jet, saving its kinematics to SBJetOutput"));
    str2beprinted.push_back(author);
    str2beprinted.push_back(license);
    PrintFuncInfo(str2beprinted);
    str2beprinted.clear();

    /*Opening the *.root file containing the signal/background/event quantities*/
    TFile SBOutputroot(filename, "read");
    TFile SBJetOutputroot(jetfilename, "update");

    /*Defining some useful variables and the structure of output trees*/
    vector<TString> Tree_names;
    Tree_names.push_back("BackTrainingKinematics");
    Tree_names.push_back("SignalTrainingKinematics");
    Tree_names.push_back("EventKinematics");
    Double_t jet1_pT, jet1_E, jet1_px, jet1_py, jet1_pz;
    Double_t jet2_pT, jet2_E, jet2_px, jet2_py, jet2_pz;
    TTree EventJet("EventJet", "EventJet");
    TBranch *jet1_E_branch = EventJet.Branch("jet1_E", &jet1_E);
    TBranch *jet1_px_branch = EventJet.Branch("jet1_px", &jet1_px);
    TBranch *jet1_py_branch = EventJet.Branch("jet1_py", &jet1_py);
    TBranch *jet1_pz_branch = EventJet.Branch("jet1_pz", &jet1_pz);
    TBranch *jet2_E_branch = EventJet.Branch("jet2_E", &jet2_E);
    TBranch *jet2_px_branch = EventJet.Branch("jet2_px", &jet2_px);
    TBranch *jet2_py_branch = EventJet.Branch("jet2_py", &jet2_py);
    TBranch *jet2_pz_branch = EventJet.Branch("jet2_pz", &jet2_pz);
    TTree SignalJet("SignalJet", "SignalJet");
    TBranch *s_jet1_E_branch = SignalJet.Branch("jet1_E", &jet1_E);
    TBranch *s_jet1_px_branch = SignalJet.Branch("jet1_px", &jet1_px);
    TBranch *s_jet1_py_branch = SignalJet.Branch("jet1_py", &jet1_py);
    TBranch *s_jet1_pz_branch = SignalJet.Branch("jet1_pz", &jet1_pz);
    TBranch *s_jet2_E_branch = SignalJet.Branch("jet2_E", &jet2_E);
    TBranch *s_jet2_px_branch = SignalJet.Branch("jet2_px", &jet2_px);
    TBranch *s_jet2_py_branch = SignalJet.Branch("jet2_py", &jet2_py);
    TBranch *s_jet2_pz_branch = SignalJet.Branch("jet2_pz", &jet2_pz);
    TTree BackgroundJet("BackgroundJet", "BackgroundJet");
    TBranch *b_jet1_E_branch = BackgroundJet.Branch("jet1_E", &jet1_E);
    TBranch *b_jet1_px_branch = BackgroundJet.Branch("jet1_px", &jet1_px);
    TBranch *b_jet1_py_branch = BackgroundJet.Branch("jet1_py", &jet1_py);
    TBranch *b_jet1_pz_branch = BackgroundJet.Branch("jet1_pz", &jet1_pz);
    TBranch *b_jet2_E_branch = BackgroundJet.Branch("jet2_E", &jet2_E);
    TBranch *b_jet2_px_branch = BackgroundJet.Branch("jet2_px", &jet2_px);
    TBranch *b_jet2_py_branch = BackgroundJet.Branch("jet2_py", &jet2_py);
    TBranch *b_jet2_pz_branch = BackgroundJet.Branch("jet2_pz", &jet2_pz);

    Double_t pT, eta, phi;
    vector<PseudoJet> particles;
    vector<PseudoJet> jets;

    /*Going through alla signal/background/event trees of all files*/
    for (vector<TString>::iterator stringit = Tree_names.begin(); stringit != Tree_names.end(); ++stringit)
    {
        for (int treenumber = 0; treenumber < numberoffiles; treenumber++)
        {
            /*Getting particles' kinematic quantities*/
            SBOutputroot.cd();
            TTree *Kinematics = (TTree *)SBOutputroot.Get(TString::Format("%s%d", stringit->Data(), treenumber));
            cout << endl << TString::Format("Now working on %s%d tree", stringit->Data(), treenumber) << endl;
            TBranch *pT_branch = Kinematics->GetBranch("pT");
            pT_branch->SetAddress(&pT);
            TBranch *eta_branch = Kinematics->GetBranch("eta");
            eta_branch->SetAddress(&eta);
            TBranch *phi_branch = Kinematics->GetBranch("phi");
            phi_branch->SetAddress(&phi);

            /*There are 700 particles per row*/
            unsigned long int jetnumber = sbjetnumber * 700;
            unsigned long int nentries = (unsigned long int)Kinematics->GetEntries();
            cout << TString::Format("%s%d", stringit->Data(), treenumber) << " stores " << nentries << " entries" << endl;
            if (nentries != 0)
            {
                if (stringit->CompareTo("EventKinematics") == 0)
                    jetnumber = eventjetnumber * 700;
                for (unsigned long int i = 0; i < min(jetnumber, nentries); i += 700)
                {
                    for (int j = 0; j < 700; ++j)
                    {
                        pT_branch->GetEntry(i + j);
                        eta_branch->GetEntry(i + j);
                        phi_branch->GetEntry(i + j);
                        particles.push_back(PseudoJet(pT * cos(phi), pT * sin(phi), pT * sinh(eta), pT * cosh(eta)));
                    }

                    /*Particles' vector is clustered*/
                    jets = JetCreator(particles, R, pT_min);
                    particles.clear();
                    jet1_E = jets[0].e();
                    jet1_px = jets[0].px();
                    jet1_py = jets[0].py();
                    jet1_pz = jets[0].pz();
                    jet2_E = jets[1].e();
                    jet2_px = jets[1].px();
                    jet2_py = jets[1].py();
                    jet2_pz = jets[1].pz();

                    /*If there is any previous tree, it is going to be overwritten!*/
                    if (stringit->CompareTo("BackTrainingKinematics") == 0)
                    {
                        BackgroundJet.Fill();
                        SBJetOutputroot.cd();
                        BackgroundJet.Write("", TObject::kOverwrite);
                    }
                    else if (stringit->CompareTo("SignalTrainingKinematics") == 0)
                    {
                        SignalJet.Fill();
                        SBJetOutputroot.cd();
                        SignalJet.Write("", TObject::kOverwrite);
                    }
                    else if (stringit->CompareTo("EventKinematics") == 0)
                    {
                        EventJet.Fill();
                        SBJetOutputroot.cd();
                        EventJet.Write("", TObject::kOverwrite);
                    }
                    else
                        break;
                    jets.clear();
                    if (i % 700000 == 0 && i>0)
                    {
                        cout << "Working on jet number: " << i / 700 << endl;
                    }
                }
            }
        }
    }
    SBOutputroot.Close();
    SBJetOutputroot.Close();
    return 0;
}