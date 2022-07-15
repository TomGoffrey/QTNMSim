#ifndef QTTrajectory_h
#define QTTrajectory_h 1

#include "G4Allocator.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4TrajectoryPoint.hh"
#include "G4VTrajectory.hh"
#include "G4ios.hh"
#include "globals.hh"
#include <stdlib.h>
#include <vector>
#include <utility>

class QTTrajectory : public G4VTrajectory
{
public:
  QTTrajectory(const G4Track* aTrack, std::vector<G4ThreeVector>& pos);
  virtual ~QTTrajectory();

  virtual void ShowTrajectory(std::ostream& os = G4cout) const;
  virtual void DrawTrajectory() const;
  virtual void AppendStep(const G4Step* aStep);
  virtual void MergeTrajectory(G4VTrajectory* secondTrajectory);

  inline void* operator new(size_t);
  inline void  operator delete(void*);
  inline int   operator==(const QTTrajectory& right) const { return (this == &right); }

  // access; MISSING n antenna storage, not just one
  std::vector<std::pair<double,double>> getVT() {return fVT;};

private:
  std::pair<double,double> convertToVT(G4ThreeVector p);

  std::vector<std::pair<double,double>> fVT;    // Cyclotron radiation
  std::vector<G4ThreeVector>&   fPositions;     // from geometry
};

extern G4ThreadLocal G4Allocator<QTTrajectory>* myTrajectoryAllocator;

inline void* QTTrajectory::operator new(size_t)
{
  if(myTrajectoryAllocator == nullptr)
  {
    myTrajectoryAllocator = new G4Allocator<QTTrajectory>;
  }
  return (void*) myTrajectoryAllocator->MallocSingle();
}

inline void QTTrajectory::operator delete(void* aTrajectory)
{
  myTrajectoryAllocator->FreeSingle((QTTrajectory*) aTrajectory);
}

#endif
