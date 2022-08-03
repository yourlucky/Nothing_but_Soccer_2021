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

#include "Representations/Communication/TeamData.h" //This makes to use TeamBehaviorStatus



CARD(CodeReleaseWalkCard,
{,
    CALLS(Activity),
    CALLS(LookForward),
    CALLS(Stand),
    CALLS(Say),
    CALLS(WalkAtRelativeSpeed),
 
    REQUIRES(RobotPose),

    REQUIRES(TeamBehaviorStatus),
    //REQUIRES(TeamData),



    DEFINES_PARAMETERS(
    {,
    (float)(0.8f) walkSpeed,
    (int)(1000) initialWaitTime,
    }),
});


class CodeReleaseWalkCard : public CodeReleaseWalkCardBase
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
    theActivitySkill(BehaviorStatus::codeReleaseWalk);

    initial_state(start)
    {
      transition
      {
        if(state_time > initialWaitTime)
          goto walkForward;
      }

      action
      {
        theSaySkill("new");
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
        if(theTeamBehaviorStatus.role.isGoalkeeper()) 
          goto Keepers;
      }
      action
      {
        theSaySkill("normal");
        theLookForwardSkill();
        theWalkAtRelativeSpeedSkill(Pose2f(0.f,0.8f,0.f));
      }
    }

    state(Keepers)
    action
    {
      theSaySkill("Keeper");
      theWalkAtRelativeSpeedSkill(Pose2f(0.f,0.f,0.1f));

    }
  }
};


MAKE_CARD(CodeReleaseWalkCard);