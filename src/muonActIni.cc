////////////////////////////////////////////////////////////////////////////////
//   muonActIni.cc for Liz's 2018 winter project.                             //
//                                                                            //
//   Definitions of muonActIni class's member functions.                      //
// All actions must be initialized here in order to use multi thread.         //
// Currently we only have primary generator action. But you will add your own //
// user actions someday.                                                      //
//                                                                            //
//                    - 10. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "muonActIni.hh"
#include "muonPriGenAct.hh"
#include "muonRunAct.hh"
#include "muonEveAct.hh"
#include "muonSteAct.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
muonActIni::muonActIni() : G4VUserActionInitialization()
{
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
muonActIni::~muonActIni()
{
}

//////////////////////////////////////////////////
//   Build for master                           //
//////////////////////////////////////////////////
void muonActIni::BuildForMaster() const
{
	// So, this part is for master. This program is possible to do multithread.
	// A thread will care things as a master.

	// New line! Our run action class is set here.
	SetUserAction(new muonRunAct());
}

//////////////////////////////////////////////////
//   Build                                      //
//////////////////////////////////////////////////
void muonActIni::Build() const
{
	SetUserAction(new muonPriGenAct());

	// Our new actions
	SetUserAction(new muonRunAct());
	muonEveAct* muonEA = new muonEveAct();
	SetUserAction(muonEA);
	SetUserAction(new muonSteAct(muonEA));
}
