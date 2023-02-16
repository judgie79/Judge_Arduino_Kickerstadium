#ifndef __MATCH_H
#define __MATCH_H

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Callback.h"
#include <TriggerSensor.h>
#include "Team.h"

#define WIN_MATCH_SCORE 10

#define RED 0
#define BLUE 1

using GoalScored = std::function<void(long, byte, Team *)>;
using GoalScoredPtr = std::shared_ptr<GoalScored>;

using MatchWon = std::function<void(long, byte, Team *)>;
using MatchWonPtr = std::shared_ptr<MatchWon>;

using MatchStarted = std::function<void(long)>;
using MatchStartedPtr = std::shared_ptr<MatchStarted>;


using MatchPaused = std::function<void(long)>;
using MatchPausedPtr = std::shared_ptr<MatchPaused>;

using GoalCheck = std::function<bool(byte &)>;

class KickerMatch
{

private:
    byte goalsNeededToWin = WIN_MATCH_SCORE;

    Team *red;
    Team *blue;

    byte scoreRed = 0;
    byte scoreBlue = 0;
    long matchTime = 0;
    bool isStarted = false;
    bool isPaused = false;
    bool isFinished = false;

    Team * matchWinner = nullptr;

    bool score(byte side);
    void score(byte side, Team * team);

    void end(byte side, Team * winner, Team * looser);

    Callback<long, byte, Team*> gsListeners;
    Callback<long, byte, Team*> mwListeners;
    Callback<long> mpListeners;
    Callback<long> msListeners;

    GoalCheck goalcheckker;
    void * context;
public:
    KickerMatch(GoalCheck goalcheckker, byte goalsNeededToWin = WIN_MATCH_SCORE);
    ~KickerMatch();


    GoalScoredPtr addGoalScoredListener(GoalScored callback);
    MatchWonPtr addMatchWonListener(MatchWon callback);
    MatchPausedPtr addMatchPausedListener(MatchPaused callback);
    MatchStartedPtr addMatchStartedListener(MatchStarted callback);

    void removeGoalScoredListener(GoalScoredPtr callback);
    void removeMatchWonListener(MatchWonPtr callback);
    void removeMatchPausedListener(MatchPausedPtr callback);
    void removeMatchStartedListener(MatchStartedPtr callback);

    void start(Team *red, Team *blue);
    void pause();
    void end();
    void play();
    long getMatchTime();

    bool hasStarted();
    bool isRunning();
    bool hasFinished();
};


#include "Stadium.h"

#endif