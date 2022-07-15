#ifndef QTTrackingAction_h
#define QTTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "G4ThreeVector.hh"
#include <vector>

class QTTrackingAction : public G4UserTrackingAction
{
public:
  QTTrackingAction();
  virtual ~QTTrackingAction(std::vector<G4ThreeVector>&){};

  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);

private:
  std::vector<G4ThreeVector>& positions;
};

#endif
