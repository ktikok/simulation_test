#include "DRsimDetectorConstruction.hh"
#include "DRsimCellParameterisation.hh"
#include "DRsimFilterParameterisation.hh"
#include "DRsimSiPMSD.hh"

#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"

#include "G4IntersectionSolid.hh"
#include "G4SDManager.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4GeometryManager.hh"

#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"

using namespace std;

G4ThreadLocal DRsimMagneticField* DRsimDetectorConstruction::fMagneticField = 0;
G4ThreadLocal G4FieldManager* DRsimDetectorConstruction::fFieldMgr = 0;

int DRsimDetectorConstruction::sNumBarrel = 52;
int DRsimDetectorConstruction::sNumEndcap = 40;
int DRsimDetectorConstruction::sNumZRot = 283;

DRsimDetectorConstruction::DRsimDetectorConstruction()
: G4VUserDetectorConstruction(), fMessenger(0), fMaterials(NULL) {
  DefineCommands();
  DefineMaterials();

  clad_C_rMin = 0.49*mm;
  clad_C_rMax = 0.50*mm;
  clad_C_Dz   = 2.5*m;
  clad_C_Sphi = 0.;
  clad_C_Dphi = 2.*M_PI;

  core_C_rMin = 0.*mm;
  core_C_rMax = 0.49*mm;
  core_C_Dz   = 2.5*m;
  core_C_Sphi = 0.;
  core_C_Dphi = 2.*M_PI;

  clad_S_rMin = 0.485*mm;
  clad_S_rMax = 0.50*mm;
  clad_S_Dz   = 2.5*m;
  clad_S_Sphi = 0.;
  clad_S_Dphi = 2.*M_PI;

  core_S_rMin = 0.*mm;
  core_S_rMax = 0.485*mm;
  core_S_Dz   = 2.5*m;
  core_S_Sphi = 0.;
  core_S_Dphi = 2.*M_PI;
  PMTT = 0.3*mm;
  filterT = 0.01*mm;

  theta_unit=0;
  phi_unit=0;
  fDThetaEndcap = fDThetaBarrel[52-1];

  fVisAttrOrange = new G4VisAttributes(G4Colour(1.0,0.5,0.,1.0));
  fVisAttrOrange->SetVisibility(true);
  fVisAttrBlue = new G4VisAttributes(G4Colour(0.,0.,1.0,1.0));
  fVisAttrBlue->SetVisibility(true);
  fVisAttrGray = new G4VisAttributes(G4Colour(0.3,0.3,0.3,0.3));
  fVisAttrGray->SetVisibility(true);
  fVisAttrGreen = new G4VisAttributes(G4Colour(0.3,0.7,0.3));
  fVisAttrGreen->SetVisibility(true);
  fVisAttrRed = new G4VisAttributes(G4Colour(1.,0.,0.,1.0));
  fVisAttrRed->SetVisibility(true);
  fVisAttrWhite = new G4VisAttributes(G4Colour(1.,1.,1.,1.0));
  fVisAttrWhite->SetVisibility(true);

}

DRsimDetectorConstruction::~DRsimDetectorConstruction() {
  delete fMessenger;
  delete fMaterials;

  delete fVisAttrOrange;
  delete fVisAttrBlue;
  delete fVisAttrGray;
  delete fVisAttrGreen;
  delete fVisAttrRed;
}

void DRsimDetectorConstruction::DefineMaterials() {
  fMaterials = DRsimMaterials::GetInstance();
}

G4VPhysicalVolume* DRsimDetectorConstruction::Construct() {
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  checkOverlaps = false;

  G4VSolid* worldSolid = new G4Box("worldBox",10.*m,10.*m,10.*m);
  worldLogical = new G4LogicalVolume(worldSolid,FindMaterial("G4_Galactic"),"worldLogical");
  G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0,false,0,checkOverlaps);
        //                               G4PVPlacement( pRotation, G4ThreeVector(posX, posY, posZ),pBoxLog, “aBoxPhys”, pMotherLog,0, copyNo); 

  innerR = 1800.;
  towerH = 2500.;
  fulltheta = 0.;
  phi_unit = 2*M_PI/(G4double)sNumZRot;

  fiber = new G4Tubs("fiber",0,clad_C_rMax,towerH/2.,0*deg,360.*deg);// S is the same
  fiberC = new G4Tubs("fiberC",0,core_C_rMax,towerH/2.,0*deg,360.*deg);
  fiberS = new G4Tubs("fiberS",0,core_S_rMax,towerH/2.,0*deg,360.*deg);
  fiberCopper = new G4Tubs("fiberCopper",0,core_C_rMax,towerH/2.,0*deg,360.*deg);

  // v4 = dimB->GetV4();
  copperPlane = new G4Box("copperPlane",
                          95.4625*mm-1.2*mm-1.0*mm, //x
                          0.25*mm, //y
                          towerH/2
                          ) ;
//  int numx = (int)(((v4.getX()*tan(phi_unit/2.)*2)-1.2*mm)/(1.01*mm)) + 1;
//  int numy = (int)((outerSide_half*2-1.2*mm)/(1.01*mm)) + 1;
  // barrel

  dimB = new dimensionB();
  dimB->SetInnerR(innerR);
  dimB->SetTower_height(towerH);
  dimB->SetNumZRot(sNumZRot);
  dimB->SetPMTT(PMTT+filterT);

  dimB->Rbool(1);
  fulltheta = 0.;
  Barrel(towerLogicalBR,PMTGLogicalBR,PMTfilterLogicalBR,PMTcellLogicalBR,PMTcathLogicalBR,fiberLogical_BR,fiberLogical_BR_,fTowerBR);

  // dimB->Rbool(0);
  // fulltheta = 0.;
  // Barrel(towerLogicalBL,PMTGLogicalBL,PMTfilterLogicalBL,PMTcellLogicalBL,PMTcathLogicalBL,fiberLogical_BL,fiberLogical_BL_,fTowerBL);
  // draw  left side of barrel towser

  // endcap
  // dimE = new dimensionE();
  // dimE->SetInnerR_new(3125.83);
  // dimE->SetTower_height(towerH);
  // dimE->SetNumZRot(sNumZRot);
  // dimE->SetDeltaTheta(fDThetaEndcap);
  // dimE->SetPMTT(PMTT+filterT);

  // fulltheta = 0.95717;
  // dimE->Rbool(1);

  // // Endcap(towerLogicalER,PMTGLogicalER,PMTfilterLogicalER,PMTcellLogicalER,PMTcathLogicalER,fiberLogical_ER,fiberLogical_ER_,fTowerER);
  // // draw  right side of endcap towser

  // // endcap L
  // fulltheta = 0.95717;
  // dimE->Rbool(0);

  // // Endcap(towerLogicalEL,PMTGLogicalEL,PMTfilterLogicalEL,PMTcellLogicalEL,PMTcathLogicalEL,fiberLogical_EL,fiberLogical_EL_,fTowerEL);
  // // draw  left side of endcap towser

  delete dimE;
  delete dimB;

  return worldPhysical;
}

void DRsimDetectorConstruction::ConstructSDandField() {
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String SiPMName = "SiPMSD";

  // Not a memory leak - SDs are deleted by G4SDManager. Deleting them manually will cause double delete!
  // for (int i = 0; i < sNumBarrel; i++) {
  // for (int i = 0; i < 1; i++) {
  //   DRsimSiPMSD* SiPMSDBR = new DRsimSiPMSD("BR"+std::to_string(i),"BRC"+std::to_string(i),fTowerBR.at(i));
  //   SDman->AddNewDetector(SiPMSDBR);
  //   PMTcathLogicalBR[i]->SetSensitiveDetector(SiPMSDBR);
  // }

  // for (int i = 0; i < sNumBarrel; i++) {
  //   DRsimSiPMSD* SiPMSDBL = new DRsimSiPMSD("BL"+std::to_string(i),"BLC"+std::to_string(i),fTowerBL.at(i));
  //   SDman->AddNewDetector(SiPMSDBL);
  //   PMTcathLogicalBL[i]->SetSensitiveDetector(SiPMSDBL);
  // }

  // for (int i = 0; i < sNumEndcap; i++) {
  //   DRsimSiPMSD* SiPMSDER = new DRsimSiPMSD("ER"+std::to_string(i),"ERC"+std::to_string(i),fTowerER.at(i));
  //   SDman->AddNewDetector(SiPMSDER);
  //   PMTcathLogicalER[i]->SetSensitiveDetector(SiPMSDER);
  // }

  // for (int i = 0; i < sNumEndcap; i++) {
  //   DRsimSiPMSD* SiPMSDEL = new DRsimSiPMSD("EL"+std::to_string(i),"ELC"+std::to_string(i),fTowerEL.at(i));
  //   SDman->AddNewDetector(SiPMSDEL);
  //   PMTcathLogicalEL[i]->SetSensitiveDetector(SiPMSDEL);
  // }
}

void DRsimDetectorConstruction::Barrel(G4LogicalVolume* towerLogical[], G4LogicalVolume* PMTGLogical[], G4LogicalVolume* PMTfilterLogical[], G4LogicalVolume* PMTcellLogical[],
  G4LogicalVolume* PMTcathLogical[], std::vector<G4LogicalVolume*> fiberLogical[], std::vector<G4LogicalVolume*> fiberLogical_[], std::vector<DRsimInterface::DRsimTowerProperty>& towerProps) {

  for (int i = 0; i < 1; i++) {
  // for (int i = 0; i < 1; i++) {
    float towerTheta = fulltheta + fDThetaBarrel[i]/2.;
    dimB->SetDeltaTheta(fDThetaBarrel[i]);
    dimB->SetThetaOfCenter(towerTheta);
    dimB->CalBasic();
    dimB->Getpt(pt);
    towerName = setTowerName(dimB->GetRbool(), "B", i);

    // fulltheta = fulltheta+fDThetaBarrel[i];

    //if ( i != 51 ) continue;
    //if ( i < 51) continue;
    // to compute fulltheta

    tower = new G4Trap("TowerB",pt);
    towerLogical[i] = new G4LogicalVolume(tower,FindMaterial("G4_AIR"),towerName);
    // towerLogical[i] = new G4LogicalVolume(tower,FindMaterial("Copper"),towerName);
    // towerLogical[i] = new G4LogicalVolume(tower,FindMaterial("Lead"),towerName);
    // towerLogical[i] = new G4LogicalVolume(tower,FindMaterial("Tungsten"),towerName);
    // towerLogical[i] = new G4LogicalVolume(tower,FindMaterial("Iron"),towerName);

    dimB->Getpt_PMTG(pt);
    pmtg = new G4Trap("PMTGB",pt);
    PMTGLogical[i] = new G4LogicalVolume(pmtg,FindMaterial("G4_AIR"),towerName);

    for(int j=0;j<1;j++){
      new G4PVPlacement(dimB->GetRM(j),dimB->GetOrigin(j),towerLogical[i],towerName,worldLogical,false,j,checkOverlaps);
      new G4PVPlacement(dimB->GetRM(j),dimB->GetOrigin_PMTG(j),PMTGLogical[i],towerName,worldLogical,false,j,checkOverlaps);
        //G4PVPlacement( pRotation, G4ThreeVector(posX, posY, posZ),pBoxLog, “aBoxPhys”, pMotherLog,0, copyNo); 
    
    }

    std::cout << i << ">> x : " <<  dimB->GetOrigin(0).x() << ", y : " <<dimB->GetOrigin(0).y()  << ", z : " <<dimB->GetOrigin(0).z() << " center_distance : " <<dimB->GetOrigin(0).mag() << std::endl;
    G4cout << i << ">> x : " <<  dimB->GetOrigin(0).x() << " y : " <<dimB->GetOrigin(0).y()  << " z : " <<dimB->GetOrigin(0).z() << " center_distance : " <<dimB->GetOrigin(0).mag() << G4endl;

    dimB->Getpt(pt);
    fiberBarrel(i,fDThetaBarrel[i],towerLogical,fiberLogical,fiberLogical_);
    // applying fiber

    int iTheta = dimB->GetRbool() ? i : -i-1;
    float signedTowerTheta = dimB->GetRbool() ? towerTheta : -towerTheta;
    DRsimInterface::DRsimTowerProperty towerProp;
    towerProp.towerXY = fTowerXY;
    towerProp.towerTheta = std::make_pair(iTheta,signedTowerTheta);
    towerProp.innerR = dimB->GetInnerR_new();
    towerProp.towerH = towerH;
    towerProp.dTheta = fDThetaBarrel[i];
    towerProps.push_back(towerProp);

    // //sipm
    // G4VSolid* SiPMlayerSolid = new G4Box("SiPMlayerSolid",fTowerXY.first*1.5/2.*mm,fTowerXY.second*1.5/2.*mm,PMTT/2.);
    // G4LogicalVolume* SiPMlayerLogical = new G4LogicalVolume(SiPMlayerSolid,FindMaterial("G4_AIR"),"SiPMlayerLogical");
    // new G4PVPlacement(0,G4ThreeVector(0.,0.,filterT/2.),SiPMlayerLogical,"SiPMlayerPhysical",PMTGLogical[i],false,0,checkOverlaps);

    // G4VSolid* filterlayerSolid = new G4Box("filterlayerSolid",fTowerXY.first*1.5/2.*mm,fTowerXY.second*1.5/2.*mm,filterT/2.);
    // G4LogicalVolume* filterlayerLogical = new G4LogicalVolume(filterlayerSolid,FindMaterial("Glass"),"filterlayerLogical");
    // new G4PVPlacement(0,G4ThreeVector(0.,0.,-PMTT/2.),filterlayerLogical,"filterlayerPhysical",PMTGLogical[i],false,0,checkOverlaps);

    // G4VSolid* PMTcellSolid = new G4Box("PMTcellSolid",1.2/2.*mm,1.2/2.*mm,PMTT/2.);
    // PMTcellLogical[i] = new G4LogicalVolume(PMTcellSolid,FindMaterial("Glass"),"PMTcellLogical");

    // DRsimCellParameterisation* PMTcellParam = new DRsimCellParameterisation(fTowerXY.first,fTowerXY.second);
    // G4PVParameterised* PMTcellPhysical = new G4PVParameterised("PMTcellPhysical",PMTcellLogical[i],SiPMlayerLogical,kXAxis,fTowerXY.first*fTowerXY.second,PMTcellParam);

    // G4VSolid* PMTcathSolid = new G4Box("PMTcathSolid",1.2/2.*mm,1.2/2.*mm,0.01/2.*mm);
    // PMTcathLogical[i] = new G4LogicalVolume(PMTcathSolid,FindMaterial("Silicon"),"PMTcathLogical");
    // new G4PVPlacement(0,G4ThreeVector(0.,0.,(PMTT-0.01)/2.*mm),PMTcathLogical[i],"PMTcathPhysical",PMTcellLogical[i],false,0,checkOverlaps);
    // new G4LogicalSkinSurface("Photocath_surf",PMTcathLogical[i],FindSurface("SiPMSurf"));

    // G4VSolid* filterSolid = new G4Box("filterSolid",1.2/2.*mm,1.2/2.*mm,filterT/2.);
    // PMTfilterLogical[i] = new G4LogicalVolume(filterSolid,FindMaterial("Gelatin"),"PMTfilterLogical");

    // DRsimFilterParameterisation* filterParam = new DRsimFilterParameterisation(fTowerXY.first,fTowerXY.second);
    // G4PVParameterised* filterPhysical = new G4PVParameterised("filterPhysical",PMTfilterLogical[i],filterlayerLogical,kXAxis,fTowerXY.first*fTowerXY.second/2,filterParam);
    // new G4LogicalBorderSurface("filterSurf",filterPhysical,PMTcellPhysical,FindSurface("FilterSurf"));

    // PMTcathLogical[i]->SetVisAttributes(fVisAttrGreen);
    // PMTfilterLogical[i]->SetVisAttributes(fVisAttrOrange);
  }
}

void DRsimDetectorConstruction::Endcap(G4LogicalVolume* towerLogical[], G4LogicalVolume* PMTGLogical[], G4LogicalVolume* PMTfilterLogical[], G4LogicalVolume* PMTcellLogical[],
  G4LogicalVolume* PMTcathLogical[], std::vector<G4LogicalVolume*> fiberLogical[], std::vector<G4LogicalVolume*> fiberLogical_[], std::vector<DRsimInterface::DRsimTowerProperty>& towerProps) {

//  for(int i=0;i<sNumEndcap;i++) {
//  // for(int i=0;i<1;i++) {
//    float towerTheta = fulltheta + fDThetaEndcap/2.;
//    dimE->SetThetaOfCenter(towerTheta);
//    dimE->CalBasic();
//    dimE->Getpt(pt);
//    towerName = setTowerName(dimE->GetRbool(), "E", i);

//    tower = new G4Trap("TowerE",pt);
//    towerLogical[i] = new G4LogicalVolume(tower,FindMaterial("Copper"),towerName);

//    dimE->Getpt_PMTG(pt);
//    pmtg = new G4Trap("PMTGE",pt);
//    // PMTGLogical[i] = new G4LogicalVolume(pmtg,FindMaterial("G4_AIR"),towerName);

//    for(int j=0;j<1;j++){
//      new G4PVPlacement(dimE->GetRM(j),dimE->GetOrigin(j),towerLogical[i],towerName,worldLogical,false,j,checkOverlaps);
//      // new G4PVPlacement(dimE->GetRM(j),dimE->GetOrigin_PMTG(j),PMTGLogical[i],towerName,worldLogical,false,j,checkOverlaps);
//    }


//     std::cout << "-------------------------------------endcap-----------------------------------------"<< std::endl;
//     std::cout << i << ">> x : " <<  dimE->GetOrigin(0).x() << ", y : " <<dimE->GetOrigin(0).y()  << ", z : " <<dimE->GetOrigin(0).z() << " center_distance : " <<dimE->GetOrigin(0).mag() << std::endl;
//     G4cout << i << ">> x : " <<  dimE->GetOrigin(0).x() << " y : " <<dimE->GetOrigin(0).y()  << " z : " <<dimE->GetOrigin(0).z() << " center_distance : " <<dimE->GetOrigin(0).mag() << G4endl;


//    dimE->Getpt(pt);
//    // fiberEndcap(i,fDThetaEndcap,towerLogical,fiberLogical,fiberLogical_);

//    int iTheta = dimE->GetRbool() ? i+52 : -i-52-1;
//    float signedTowerTheta = dimE->GetRbool() ? towerTheta : -towerTheta;
//    DRsimInterface::DRsimTowerProperty towerProp;
//    towerProp.towerXY = fTowerXY;
//    towerProp.towerTheta = std::make_pair(iTheta,signedTowerTheta);
//    towerProp.innerR = dimE->GetInnerR_new();
//    towerProp.towerH = towerH;
//    towerProp.dTheta = fDThetaEndcap;
//    towerProps.push_back(towerProp);

//    // G4VSolid* SiPMlayerSolid = new G4Box("SiPMlayerSolid",fTowerXY.first*1.5/2.*mm,fTowerXY.second*1.5/2.*mm,PMTT/2.);
//    // G4LogicalVolume* SiPMlayerLogical = new G4LogicalVolume(SiPMlayerSolid,FindMaterial("G4_AIR"),"SiPMlayerLogical");
//    // new G4PVPlacement(0,G4ThreeVector(0.,0.,filterT/2.),SiPMlayerLogical,"SiPMlayerPhysical",PMTGLogical[i],false,0,checkOverlaps);

//    // G4VSolid* filterlayerSolid = new G4Box("filterlayerSolid",fTowerXY.first*1.5/2.*mm,fTowerXY.second*1.5/2.*mm,filterT/2.);
//    // G4LogicalVolume* filterlayerLogical = new G4LogicalVolume(filterlayerSolid,FindMaterial("Glass"),"filterlayerLogical");
//    // new G4PVPlacement(0,G4ThreeVector(0.,0.,-PMTT/2.),filterlayerLogical,"filterlayerPhysical",PMTGLogical[i],false,0,checkOverlaps);

//    // G4VSolid* PMTcellSolid = new G4Box("PMTcellSolid",1.2/2.*mm,1.2/2.*mm,PMTT/2.);
//    // PMTcellLogical[i] = new G4LogicalVolume(PMTcellSolid,FindMaterial("Glass"),"PMTcellLogical");

//    // DRsimCellParameterisation* PMTcellParam = new DRsimCellParameterisation(fTowerXY.first,fTowerXY.second);
//    // G4PVParameterised* PMTcellPhysical = new G4PVParameterised("PMTcellPhysical",PMTcellLogical[i],SiPMlayerLogical,kXAxis,fTowerXY.first*fTowerXY.second,PMTcellParam);

//    // G4VSolid* PMTcathSolid = new G4Box("PMTcathSolid",1.2/2.*mm,1.2/2.*mm,0.01/2.*mm);
//    // PMTcathLogical[i] = new G4LogicalVolume(PMTcathSolid,FindMaterial("Silicon"),"PMTcathLogical");
//    // new G4PVPlacement(0,G4ThreeVector(0.,0.,(PMTT-0.01)/2.*mm),PMTcathLogical[i],"PMTcathPhysical",PMTcellLogical[i],false,0,checkOverlaps);
//    // new G4LogicalSkinSurface("Photocath_surf",PMTcathLogical[i],FindSurface("SiPMSurf"));

//    // G4VSolid* filterSolid = new G4Box("filterSolid",1.2/2.*mm,1.2/2.*mm,filterT/2.);
//    // PMTfilterLogical[i] = new G4LogicalVolume(filterSolid,FindMaterial("Gelatin"),"PMTfilterLogical");

//    // DRsimFilterParameterisation* filterParam = new DRsimFilterParameterisation(fTowerXY.first,fTowerXY.second);
//    // G4PVParameterised* filterPhysical = new G4PVParameterised("filterPhysical",PMTfilterLogical[i],filterlayerLogical,kXAxis,fTowerXY.first*fTowerXY.second/2,filterParam);
//    // new G4LogicalBorderSurface("filterSurf",filterPhysical,PMTcellPhysical,FindSurface("FilterSurf"));

//    fulltheta = fulltheta+fDThetaEndcap;

//    // PMTcathLogical[i]->SetVisAttributes(fVisAttrGreen);
//    // PMTfilterLogical[i]->SetVisAttributes(fVisAttrOrange);
//  }
}

void DRsimDetectorConstruction::DefineCommands() {}

void DRsimDetectorConstruction::fiberBarrel(G4int i, G4double deltatheta_,G4LogicalVolume* towerLogical[], std::vector<G4LogicalVolume*> fiberLogical[], std::vector<G4LogicalVolume*> fiberLogical_[]) {

 fFiberX.clear();
 fFiberY.clear();
 fFiberWhich.clear();

 v1 = dimB->GetV1();
 v2 = dimB->GetV2();
 v3 = dimB->GetV3();
 v4 = dimB->GetV4();

 innerSide_half = dimB->GetInnerR_new()*tan(deltatheta_/2.);
 outerSide_half = (dimB->GetInnerR_new()+towerH)*tan(deltatheta_/2.);

//  int numx = (int)(((v4.getX()*tan(phi_unit/2.)*2)-1.2*mm)/(1.5*mm)) + 1;
//  int numy = (int)((outerSide_half*2-1.2*mm)/(1.5*mm)) + 1;
 int numx = (int)(((v4.getX()*tan(phi_unit/2.)*2)-1.2*mm)/(1.0*mm)) + 1;
 int numy = (int)((outerSide_half*2-1.2*mm)/(1.5*mm)) + 1;

  std::cout << "x length : " << (v4.getX()*tan(phi_unit/2.)*2)  << std::endl;

 
 fTowerXY = std::make_pair(numx,numy);

 G4bool fWhich = false;
 for (int j = 0; j < numy; j++) {//y-axis
    // std::cout << j << "y : " << fWhich  << std::endl;
    // if( j%2 == 0 ){
    //   G4float fX = 0
    //   G4float fY = -1.5*mm*(numy/2) + j*1.5*mm + ( numy%2==0 ? 0.75*mm : 0 ) - 0.25*mm;

    //   fFiberX.push_back(fX);
    //   fFiberY.push_back(fY);
    //   fFiberWhich.push_back(fWhich);
    // }
   for (int k = 0; k < numx; k++) {//x-axis
     G4float fX = -1.0*mm*(numx/2) + k*1.0*mm + ( numx%2==0 ? 0.50*mm : 0 ); // radius of fiber is 0.5
      G4float fY = -1.5*mm*(numy/2) + j*1.5*mm + ( numy%2==0 ? 0.75*mm : 0 );

    //  G4float fX = -1.5*mm*(numx/2) + k*1.5*mm + ( numx%2==0 ? 0.75*mm : 0 );
    //  G4float fY = -1.5*mm*(numy/2) + j*1.5*mm + ( numy%2==0 ? 0.75*mm : 0 );
    //  fWhich = !fWhich;
     fFiberX.push_back(fX);
     fFiberY.push_back(fY);
     fFiberWhich.push_back(fWhich);
   }
   fWhich = !fWhich;
   
  //  if ( numx%2==0 ) { fWhich = !fWhich; }
  //  else{  fWhich = !fWhich; }
 }

 int fiberOrCopper = 1;
 for (unsigned int j = 0; j<fFiberX.size();j++) {
    // std::cout <<"j:"<<j<< std::endl;

   if (j == 0){
        intersect = new G4IntersectionSolid("copperPlane",copperPlane,tower,0,G4ThreeVector(0,-fFiberY.at(j)-0.75*mm,0.));
        intersect_logical = new G4LogicalVolume(intersect,FindMaterial("Copper"),name);
        new G4PVPlacement(0,G4ThreeVector(0,fFiberY.at(j)-0.75*mm,0),intersect_logical,name,towerLogical[i],false,j,checkOverlaps);
        intersect_logical->SetVisAttributes(fVisAttrWhite);
   }
   if ( !fFiberWhich.at(j) ) { //0, c fibre if false
      if (j > 0){
        if ( fFiberWhich.at(j-1) ) { fiberOrCopper = 1; 
        intersect = new G4IntersectionSolid("copperPlane",copperPlane,tower,0,G4ThreeVector(0,-fFiberY.at(j)-0.75*mm,0.));
        intersect_logical = new G4LogicalVolume(intersect,FindMaterial("Copper"),name);
        new G4PVPlacement(0,G4ThreeVector(0,fFiberY.at(j)-0.75*mm,0),intersect_logical,name,towerLogical[i],false,j,checkOverlaps);
        intersect_logical->SetVisAttributes(fVisAttrWhite);
        }
      }
      

      if ( fiberOrCopper ) { // put fiber
        // std::cout <<"j:"<<j<< ", c fiber " << std::endl;

        
        intersect = new G4IntersectionSolid("fiber_",fiber,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
        fiberLogical[i].push_back(new G4LogicalVolume(intersect,FindMaterial("FluorinatedPolymer"),name));
        new G4PVPlacement(0,G4ThreeVector(fFiberX.at(j),fFiberY.at(j),0),fiberLogical[i].at(j),name,towerLogical[i],false,j,checkOverlaps);
        fiberLogical[i].at(j)->SetVisAttributes(fVisAttrGray);

        intersect_ = new G4IntersectionSolid("fiber_",fiberC,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
        fiberLogical_[i].push_back(new G4LogicalVolume(intersect_,FindMaterial("PMMA"),name));
        new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),fiberLogical_[i].at(j),name,fiberLogical[i].at(j),false,j,checkOverlaps);
        fiberLogical_[i].at(j)->SetVisAttributes(fVisAttrBlue);

        fiberOrCopper = 0;
      }
      else{ //put copper
        // std::cout <<"j:"<<j<< ", c fiber, copper " << std::endl;


        intersect = new G4IntersectionSolid("fiber_",fiber,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
        fiberLogical[i].push_back(new G4LogicalVolume(intersect,FindMaterial("Copper"),name));
        new G4PVPlacement(0,G4ThreeVector(fFiberX.at(j),fFiberY.at(j),0),fiberLogical[i].at(j),name,towerLogical[i],false,j,checkOverlaps);

        intersect_ = new G4IntersectionSolid("fiber_",fiberCopper,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
        fiberLogical_[i].push_back(new G4LogicalVolume(intersect_,FindMaterial("Copper"),name));
        // new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),fiberLogical_[i].at(j),name,fiberLogical[i].at(j),false,j,checkOverlaps);

        fiberLogical[i].at(j)->SetVisAttributes(fVisAttrWhite);
        // fiberLogical_[i].at(j)->SetVisAttributes(fVisAttrWhite);


        fiberOrCopper = 1;
      }

   } else { // s fibre
      if (j > 0){
        if ( !fFiberWhich.at(j-1) ) { fiberOrCopper = 0; 
        intersect = new G4IntersectionSolid("copperPlane",copperPlane,tower,0,G4ThreeVector(0,-fFiberY.at(j)-0.75*mm,0.));
        intersect_logical = new G4LogicalVolume(intersect,FindMaterial("Copper"),name);
        new G4PVPlacement(0,G4ThreeVector(0,fFiberY.at(j)-0.75*mm,0),intersect_logical,name,towerLogical[i],false,j,checkOverlaps);
        intersect_logical->SetVisAttributes(fVisAttrWhite);}
      }

      if ( fiberOrCopper ) { // put fiber
        // std::cout <<"j:"<<j<< ", s fiber " << std::endl;

        intersect = new G4IntersectionSolid("fiber_",fiber,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
        // std::cout <<"j:"<<j<< ", s fiber clad" << std::endl;
        fiberLogical[i].push_back(new G4LogicalVolume(intersect,FindMaterial("PMMA"),name));
        // std::cout <<"j:"<<j<< ", s fiber clad" << std::endl;
        new G4PVPlacement(0,G4ThreeVector(fFiberX.at(j),fFiberY.at(j),0),fiberLogical[i].at(j),name,towerLogical[i],false,j,checkOverlaps);
        // std::cout <<"j:"<<j<< ", s fiber clad" << std::endl;

        intersect_ = new G4IntersectionSolid("fiber_",fiberS,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
        fiberLogical_[i].push_back(new G4LogicalVolume(intersect_,FindMaterial("Polystyrene"),name));
        new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),fiberLogical_[i].at(j),name,fiberLogical[i].at(j),false,j,checkOverlaps);
        // std::cout <<"j:"<<j<< ", s fiber core" << std::endl;

        fiberLogical[i].at(j)->SetVisAttributes(fVisAttrGray);
        fiberLogical_[i].at(j)->SetVisAttributes(fVisAttrRed);
        // std::cout <<"j:"<<j<< ", s fiber vis" << std::endl;

        fiberOrCopper = 0;
      }
      else{ //put copper
        // std::cout <<"j:"<<j<< ", s fiber, copper " << std::endl;

        ///////////////////////////////////

        intersect = new G4IntersectionSolid("fiber_",fiber,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
        fiberLogical[i].push_back(new G4LogicalVolume(intersect,FindMaterial("Copper"),name));
        new G4PVPlacement(0,G4ThreeVector(fFiberX.at(j),fFiberY.at(j),0),fiberLogical[i].at(j),name,towerLogical[i],false,j,checkOverlaps);

        intersect_ = new G4IntersectionSolid("fiber_",fiberCopper,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
        fiberLogical_[i].push_back(new G4LogicalVolume(intersect_,FindMaterial("Copper"),name));
        // new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),fiberLogical_[i].at(j),name,fiberLogical[i].at(j),false,j,checkOverlaps);

        fiberLogical[i].at(j)->SetVisAttributes(fVisAttrWhite);
        // fiberLogical_[i].at(j)->SetVisAttributes(fVisAttrWhite);


        fiberOrCopper = 1;
      }
   }
  if ( j == fFiberX.size()-1){
    intersect = new G4IntersectionSolid("copperPlane",copperPlane,tower,0,G4ThreeVector(0,-fFiberY.at(j)+0.75*mm,0.));
    intersect_logical = new G4LogicalVolume(intersect,FindMaterial("Copper"),name);
    new G4PVPlacement(0,G4ThreeVector(0,fFiberY.at(j)+0.75*mm,0),intersect_logical,name,towerLogical[i],false,j,checkOverlaps);
    intersect_logical->SetVisAttributes(fVisAttrWhite);
  }
  
 }
  }

void DRsimDetectorConstruction::fiberEndcap(G4int i, G4double deltatheta_, G4LogicalVolume* towerLogical[], std::vector<G4LogicalVolume*> fiberLogical[], std::vector<G4LogicalVolume*> fiberLogical_[]) 
{

//  fFiberX.clear();
//  fFiberY.clear();
//  fFiberWhich.clear();
//
//  v1 = dimE->GetV1();
//  v2 = dimE->GetV2();
//  v3 = dimE->GetV3();
//  v4 = dimE->GetV4();
//
//  innerSide_half = dimE->GetInnerR_new()*tan(deltatheta_/2.);
//  outerSide_half = (dimE->GetInnerR_new()+towerH)*tan(deltatheta_/2.);
//
//  int numx = (int)(((v4.getX()*tan(phi_unit/2.)*2)-1.2*mm)/(1.5*mm)) + 1;
//  int numy = (int)((outerSide_half*2-1.2*mm)/(1.5*mm)) + 1;
//  fTowerXY = std::make_pair(numx,numy);
//
//  G4bool fWhich = false;
//  for (int j = 0; j < numy; j++) {
//    for (int k = 0; k < numx; k++) {
//      G4float fX = -1.5*mm*(numx/2) + k*1.5*mm + ( numx%2==0 ? 0.75*mm : 0 );
//      G4float fY = -1.5*mm*(numy/2) + j*1.5*mm + ( numy%2==0 ? 0.75*mm : 0 );
//      fWhich = !fWhich;
//      fFiberX.push_back(fX);
//      fFiberY.push_back(fY);
//      fFiberWhich.push_back(fWhich);
//    }
//    if ( numx%2==0 ) { fWhich = !fWhich; }
//  }
//
//  for (unsigned int j = 0; j<fFiberX.size();j++) {
//    // determine z value for center of fibre
//
//    if ( !fFiberWhich.at(j) ) { //c fibre
//      intersect = new G4IntersectionSolid("fiber_",fiber,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
//      fiberLogical[i].push_back(new G4LogicalVolume(intersect,FindMaterial("FluorinatedPolymer"),name));
//      new G4PVPlacement(0,G4ThreeVector(fFiberX.at(j),fFiberY.at(j),0),fiberLogical[i].at(j),name,towerLogical[i],false,j,checkOverlaps);
//
//      intersect_ = new G4IntersectionSolid("fiber_",fiberC,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
//      fiberLogical_[i].push_back(new G4LogicalVolume(intersect_,FindMaterial("PMMA"),name));
//      new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),fiberLogical_[i].at(j),name,fiberLogical[i].at(j),false,j,checkOverlaps);
//
//      fiberLogical[i].at(j)->SetVisAttributes(fVisAttrGray);
//      fiberLogical_[i].at(j)->SetVisAttributes(fVisAttrBlue);
//    } else { // s fibre
//      intersect = new G4IntersectionSolid("fiber_",fiber,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
//      fiberLogical[i].push_back(new G4LogicalVolume(intersect,FindMaterial("PMMA"),name));
//      new G4PVPlacement(0,G4ThreeVector(fFiberX.at(j),fFiberY.at(j),0),fiberLogical[i].at(j),name,towerLogical[i],false,j,checkOverlaps);
//
//      intersect_ = new G4IntersectionSolid("fiber_",fiberS,tower,0,G4ThreeVector(-fFiberX.at(j),-fFiberY.at(j),0.));
//      fiberLogical_[i].push_back(new G4LogicalVolume(intersect_,FindMaterial("Polystyrene"),name));
//      new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),fiberLogical_[i].at(j),name,fiberLogical[i].at(j),false,j,checkOverlaps);
//
//      fiberLogical[i].at(j)->SetVisAttributes(fVisAttrGray);
//      fiberLogical_[i].at(j)->SetVisAttributes(fVisAttrOrange);
//    }
//  }
}
