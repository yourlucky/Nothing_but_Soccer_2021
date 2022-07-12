/**
 * @file CodeReleaseOneTwoCard.cpp
 *
 * This file implements a basic striker behavior for the code release.
 *
 * @author Arne Hasselbring
 */

#include "Representations/BehaviorControl/FieldBall.h"
#include "Representations/BehaviorControl/Skills.h"
#include "Representations/Configuration/FieldDimensions.h"
#include "Representations/Modeling/RobotPose.h"
#include "Tools/BehaviorControl/Framework/Card/Card.h"
#include "Tools/BehaviorControl/Framework/Card/CabslCard.h"
#include "Tools/Math/BHMath.h"

#include "Representations/Communication/RobotInfo.h"

CARD(CodeReleaseOneTwoCard,
{,
  CALLS(Activity),
  CALLS(GoToBallAndKick),
  CALLS(LookForward),
  CALLS(Stand),
  CALLS(WalkAtRelativeSpeed),
  CALLS(WalkToPose),
  CALLS(Say),
  REQUIRES(FieldBall),
  REQUIRES(FieldDimensions),
  REQUIRES(RobotPose),
  REQUIRES(RobotInfo),
  DEFINES_PARAMETERS(
  {,
    (float)(0.8f) walkSpeed,
    (int)(1000) initialWaitTime,
    (int)(7000) ballNotSeenTimeout,
  }),
});

class CodeReleaseOneTwoCard : public CodeReleaseOneTwoCardBase
{
  bool preconditions() const override
  {
    return true;
  }

  bool postconditions() const override
  {
    return true;
  }

  option
  {
    //theActivitySkill(BehaviorStatus::CodeReleaseOneTwoCard);
    initial_state(start)
    {
      transition
      {
        if(state_time > initialWaitTime)
          goto moveTurn;
      }

      action
      {
        theLookForwardSkill();
        theStandSkill();
      }
    }

    state(moveTurn)
    {
      
      action
      {
        theWalkAtRelativeSpeedSkill(Pose2f(0.f,walkSpeed,0.f));
        theSaySkill("hahahaha");
      }
    }
  }
};

MAKE_CARD(CodeReleaseOneTwoCard);
