/**
 * @file NoTeamCard.cpp
 *
 * This file implements card that is active in situations where there is no team behavior.
 *
 * @author Arne Hasselbring
 */

#include "Representations/BehaviorControl/TeamSkills.h"
#include "Tools/BehaviorControl/Framework/Card/TeamCard.h"
#include "Representations/Communication/TeamData.h" 

#include <iostream>

TEAM_CARD(NoTeamCard,
{,
  CALLS(Role),
  CALLS(TeamActivity),
  CALLS(TeammateRoles),
  CALLS(TimeToReachBall),

  //REQUIRES(TeamBehaviorStatus),


});

class NoTeamCard : public NoTeamCardBase
{
  bool preconditions() const override
  {
    return true;
  }

  bool postconditions() const override
  {
    return true;
  }

  void execute() override
  {
    theTeamActivitySkill(TeamBehaviorStatus::noTeam);
    theTimeToReachBallSkill(TimeToReachBall());
    theTeammateRolesSkill(TeammateRoles());

    //theTeamBehaviorStatus.role = goalkeeper;

    
    theRoleSkill(PlayerRole());

    
    //std::cout<<theTeamBehaviorStatus.role.role<<std::endl;
    //std::cout<<"hi"<<std::endl;
    //print(PlayerRole.role);

   /* 
    Role role;
    role.isGoalkeeper = false;
    role.playBall = false;
    role.supporterIndex = -1;
    role.numOfActiveSupporters = 0;
    theRoleSkill(role);
    */

  }
};

MAKE_TEAM_CARD(NoTeamCard);
