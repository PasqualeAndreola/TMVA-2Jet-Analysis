/*!
 * \file jetdict.h
 * \brief Header file for all pragma directives needed by rootcling.
 * 
 * All these directives are referred to ROOT internal compiler: rootcling. Note that these directives have to be correctly ordered.\n 
 * These commands are used to correctly write a dictionary to let a structure be writable to a tree.\n
 * The + which ends every pragma call let rootcling use the new I/O system of root.
 * 
 */

#include <vector>
#include <PseudoJet.hh>
#include <SharedPtr.hh>
#include <PseudoJetStructureBase.hh>

#pragma link C++ class vector+;
#pragma link C++ class fastjet::PseudoJet+;
#pragma link C++ class fastjet::PseudoJet::structure_ptr+;
#pragma link C++ class fastjet::SharedPtr+;
#pragma link C++ class fastjet::PseudoJetStructureBase+;
#pragma link C++ class fastjet::PseudoJet::UserInfoBase+;
#pragma link C++ class fastjet::SharedPtr<fastjet::PseudoJetStructureBase>+;
#pragma link C++ class fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>+;
#pragma link C++ class fastjet::SharedPtr<fastjet::PseudoJet::UserInfoBase>::__SharedCountingPtr+;
#pragma link C++ class fastjet::SharedPtr<fastjet::PseudoJetStructureBase>::__SharedCountingPtr+;
#pragma link C++ class vector<fastjet::PseudoJet>+;