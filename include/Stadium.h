#ifndef __STADIUM_H
#define __STADIUM_H

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Callback.h"
#include <ButtonSensor.h>
#include "KickerMatch.h"
#include "Team.h"

class Stadium
{
private:
    ButtonSensor sensorRedGoal;
    ButtonSensor sensorBlueGoal;
    void readGoalSensors();

    Callback<long, byte, Team*> gsListeners;
    Callback<long, byte, Team*> mwListeners;
    Callback<long> mpListeners;
    Callback<long> msListeners;

    GoalScoredPtr goalScorePtr;
    MatchWonPtr matchWonPtr;
    MatchPausedPtr matchPausedPtr;
    MatchStartedPtr matchStartedPtr;
public:
    Stadium(byte sensorPinRedGoal, byte sensorPinBlueGoal);
    ~Stadium();

    KickerMatch *currentMatch = nullptr;
    Team *red = nullptr;
    Team *blue = nullptr;

    void prepareMatch(Team *red, Team *blue, byte goalsNeededToWin = WIN_MATCH_SCORE);
    void startMatch();

    bool matchInPlay();

    bool scored(byte &side);

    // EventHandler for Match
    void goalScored(long matchTime, byte side, Team * team);
    void matchPaused(long matchTime);
    void matchWon(long matchTime, byte side, Team * team);
    void matchStarted(long matchTime);

    GoalScoredPtr addGoalScoredListener(GoalScored callback);
    MatchWonPtr addMatchWonListener(MatchWon callback);
    MatchPausedPtr addMatchPausedListener(MatchPaused callback);
    MatchStartedPtr addMatchStartedListener(MatchStarted callback);

    void removeGoalScoredListener(GoalScoredPtr callback);
    void removeMatchWonListener(MatchWonPtr callback);
    void removeMatchPausedListener(MatchPausedPtr callback);
    void removeMatchStartedListener(MatchStartedPtr callback);

};



#endif