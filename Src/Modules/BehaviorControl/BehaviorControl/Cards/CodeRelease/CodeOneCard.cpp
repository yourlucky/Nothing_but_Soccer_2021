/**
 * @file CodeReleaseKickAtGoalCard.cpp
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

CARD(CodeOneCard,
{,
    CALLS(Activity),
    CALLS(LookForward),
    CALLS(Stand),
    CALLS(Say),
    CALLS(WalkAtRelativeSpeed),
    REQUIRES(RobotPose),
    DEFINES_PARAMETERS(
    {,
    (float)(0.8f) walkSpeed,
    (int)(1000) initialWaitTime,
    }),
});


class CodeOneCard : public CodeOneCardBase
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
    //theActivitySkill(BehaviorStatus::codeReleaseWalk);

    initial_state(start)
    {
      transition
      {
        if(state_time > initialWaitTime)
          goto walkForward;
      }

      action
      {
        theSaySkill("Code One");
        theLookForwardSkill();
        theStandSkill();
      }
    }

    state(walkForward)
    {
      transition
      {
        if(state_time+1000000 < initialWaitTime)
          goto start;
      }
      action
      {
        theSaySkill("Code One");
        theLookForwardSkill();
        theWalkAtRelativeSpeedSkill(Pose2f(0.f,0.8f,0.f));
      }
    }
  }
};


MAKE_CARD(CodeOneCard);