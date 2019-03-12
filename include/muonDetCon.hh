#ifndef MUONDETCON_h
#define MUONDETCON_h 1

////////////////////////////////////////////////////////////////////////////////
//   muonDetCon.hh for Liz's 2018 winter project.                             //
//                                                                            //
//   This file is a header for muonDetCon class. It's for construction of     //
// whole geometry of simulation, which includes target geometry and detector  //
// geometry.                                                                  //
//                                                                            //
//                    - 10. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////


#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4EllipticalTube.hh"
class G4VPhysicalVolume;

class muonDetCon : public G4VUserDetectorConstruction
{
  public:
	muonDetCon();
	virtual ~muonDetCon();
	virtual G4VPhysicalVolume* Construct();

  private:
	void DefineDimensions();
	void ConstructMaterials();
	void DestructMaterials();

  private:
	// Elements
	// I prepared several elements and materials for you!
	// You just can use them.
	G4Element* m_ElH;
	G4Element* m_ElC;
	G4Element* m_ElN;
	G4Element* m_ElO;
	G4Element* m_ElF;
	G4Element* m_ElMg;
	G4Element* m_ElAl;
	G4Element* m_ElSi;
	G4Element* m_ElAr;
	G4Element* m_ElCr;
	G4Element* m_ElFe;
	G4Element* m_ElNi;
	G4Element* m_ElCu;
	G4Element* m_ElZn;
	G4Element* m_ElY;
	G4Element* m_ElSn;
	G4Element* m_ElCe;
	G4Element* m_ElLu;

	// Materials
	G4Material* m_AirMat;
	G4Material* m_CouMat;
	G4Material* m_VacMat;

	// Dimensions and detector setup
	G4double m_LabX, m_LabY, m_LabZ;
	G4double m_solidx, m_solidy, m_solidz;
	
	// Geometry objects
	G4Box* m_LabSolid;
	G4LogicalVolume* m_LabLV;
	G4VPhysicalVolume* m_LabPV;
	G4Box* m_solid;
	G4LogicalVolume* m_solidLV;
	 
};
#endif
