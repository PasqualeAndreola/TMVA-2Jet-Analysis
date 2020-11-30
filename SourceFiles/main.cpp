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
 * LHC Olympics give sample files with extension ".h5". It means that the user has to install
 * HDF5 library and use a script to interact with sample files. This project gives some function,
 * written in C++, useful to handle with *.h5 files.
 * 
 * \subsection read1 Step 1: Opening the box
 * 
 * Files formatted in ".h5" usually have three main sub-structures: groups, datasets and datatypes.\n
 * \ref openh5 let the user see the structure of the input file and store the information about
 * the dataset in a vector of class \ref DatasetInfo, which holds the name of the dataset, the token
 * that identifies it and its dimensions (dataset is supposed to be 2D).\n
 * \ref openh5 goes through the file iteratively, using the \ref opfunc operator , which get the type and
 * the info about the sub-structure stored in the input file.
 * 
 * \subsection read2 Step 2: Reading the dataset
 * Reading the dataset is the most critical part of the project. HDF5 library memory management at the core level
 * is "old fashioned": the user must provide a buffer of the same type of the dataset that has to read and buffer's
 * dimensions have to be in the "boundaries" of the dataset. To solve this problem and maximize the reading
 * efficiency, the user can use the function template \ref Dataset_2Dread.\n 
 * \ref Dataset_2Dread uses the template and the global variable "bufferdimension" to create an appropriate buffer to hold read data.
 * Setting "bufferdimension" as high as user RAM can store means higher reading speed.\n
 * 
 * \section datamanipulation_sec Data manipulation
 * 
 * \subsection mani1 Writing the buffer to a root file
 * This project uses ROOT framework, so it's useful to write read data to a *.root file. To write the buffer to a root file, user 
 * can call \ref TreeCreator, which set up the correct template for \ref Dataset_2Dread which writes read buffer to the chosen root file.\n
 * 
 * From now on, HDF5 is not needed.\n
 * 
 * \subsection mani2 Distinguishing signal, background and real event
 * Data written in the root files are parsed as suggested by LHC Olympics (700 hadrons described by their \f$ p_{T} \f$, \f$ \eta \f$, \f$ \Phi \f$).
 * To distinguish background and signal events dataset contain an extra column. When this column is not present, the user can set up an optional value 
 * "sbflag" in the \ref main, if the user knows additional information about dataset stored in the file. \ref SBTreeCreator creates
 * an output file storing signal/background/event kinematics of the hadrons in the various dataset.
 * 
 * \subsection mani3 Jet clustering
 * In the end, \ref SBTreeJetKinematicsCreator clusters the hadrons with transverse momentum greater than \f$ p_{T, min} \f$ with a jet radius set by the user.
 * Kinematics of the two most massive jets are stored in a root file.\n
 * 
 * \section tmvafactory TMVA analysis
 * 
 * These functions have to be customized by the user because mva methods have different parameters that have to be tuned.
 * 
 * \subsection The TMVA::Factory
 * \ref TMVAFactoryAnalysis set up a factory holding results of the user-defined algorithm analysis of the data sample.\n
 * 
 * \subsection The TMVA::Reader
 * \ref TMVAReaderAnalysis analyzes a data sample using user-defined algorithms and their relative weights stored in the TMVA::Factory set up by the \ref TMVAFactoryAnalysis
 * function. This reader generates pdf and root files, storing the result of the analysis.\n
 */

/*! 
 * \file main.cpp
 * \brief Main file
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
  string TMVAReaderoutputname = "WprimoEventClassification";

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

  return 0;
}