////////////////////////////////////////////////////////////////////////////////
//   muonRunAct.cc for Liz's 2018 winter project.                             //
//                                                                            //
//   Definitions of muonRunAct class's member functions. Details of user      //
// actions are here.                                                          //
//                                                                            //
//                    - 24. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <ctime>

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcommand.hh"

#include "muonRunAct.hh"
#include "muonAna.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
muonRunAct::muonRunAct() : G4UserRunAction()
{
	// Create analysis manager
	// The choice of analysis technology is done via selection of a namespace in muonAna.hh
	// We chose ROOT.
	G4AnalysisManager* AM = G4AnalysisManager::Instance();
	G4cout << "Using " << AM -> GetType() << G4endl;

	// Default settings
	// I don't like chatterbox...
	AM -> SetVerboseLevel(0);

	// Creating ntuple
	AM -> CreateNtuple("hits", "lifetime");
	AM -> CreateNtupleIColumn("eventID");  // Column ID = 0
	AM -> CreateNtupleDColumn("lifetime"); // Column ID = 1
	AM -> FinishNtuple();
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
muonRunAct::~muonRunAct()
{
	delete G4AnalysisManager::Instance();
}

//////////////////////////////////////////////////
//   Begin of run action                        //
//////////////////////////////////////////////////
void muonRunAct::BeginOfRunAction(const G4Run* run)
{
	// All actions defined here will be executed at the beginning of every run.
	// What is a run? You may type /run/beamOn someNumber.
	// Whenever you do this, "one run" runs.
	
	// Inform the runManager to save random number seed
	//G4RunManager::GetRunManager()->SetRandomNumberStore(true);

	// Get analysis manager
	G4AnalysisManager* AM = G4AnalysisManager::Instance();

	// Get current time to include it to file name
	// This time info is going to be used to generate output file name.
	time_t rawTime;
	struct tm* timeInfo;
	char buffer[80];
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%I-%M-%S", timeInfo);
	std::string sTime(buffer);

	// Get number of event
	G4int nEvent = run -> GetNumberOfEventToBeProcessed();

	// Open an output file
	// It can be overwritten in a macro.
	G4String fileName;
	fileName = "muon";
	fileName += "-";
	fileName += G4UIcommand::ConvertToString(nEvent);
	fileName += "-";
	fileName += sTime;

	AM -> OpenFile(fileName);
}

//////////////////////////////////////////////////
//   End of run action                          //
//////////////////////////////////////////////////
void muonRunAct::EndOfRunAction(const G4Run* /*run*/)
{
	// Save ntuple
	G4AnalysisManager* AM = G4AnalysisManager::Instance();
	// You must save ntuple. Otherwise, file will be just empty...
	AM -> Write();
	// You must close the file. Otherwise, file will be crashed...
	AM -> CloseFile();
}
