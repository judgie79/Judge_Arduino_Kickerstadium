#include "KickerMatch.h"



KickerMatch::KickerMatch(std::function<bool(byte &)> goalcheckker, byte goalsNeededToWin)
{
    this->goalsNeededToWin = goalsNeededToWin;
    this->goalcheckker = goalcheckker;
}

KickerMatch::~KickerMatch()
{
}

long KickerMatch::getMatchTime()
{
    return matchTime;
}

void KickerMatch::start(Team *red, Team *blue)
{
    this->red = red;
    this->blue = blue;
    scoreBlue = 0;
    scoreRed = 0;
    matchTime = 0;
    isPaused = false;
    isStarted = true;
    isFinished = false;
    matchWinner = nullptr;

    msListeners(matchTime);
}

void KickerMatch::end(byte side, Team * winner, Team * looser)
{
    winner->winMatch();
    looser->looseMatch();
    matchWinner = winner;

    mwListeners(matchTime, side, winner);

    end();
}

void KickerMatch::score(byte side, Team * team)
{
    gsListeners(matchTime, side, team);
}

bool KickerMatch::score(byte side)
{
    if (side == RED)
    {
        scoreRed++;
        score(side, red);

        if (scoreRed >= goalsNeededToWin)
        {
            end(side, red, blue);
            return true; // match has ended
        }
    }
    else
    {
        scoreBlue++;
        score(side, blue);
        if (scoreBlue >= goalsNeededToWin)
        {
            end(side, blue, red);
            return true; // match has ended
        }
    }
    
    return false;
}

void KickerMatch::play()
{
    if (!isStarted || isPaused)
        return;

    // update the match time
    matchTime = millis();

    // check for scored goals    
    byte side = 0;

    bool scored = goalcheckker(side);

    if (scored)
    {
        bool matchEnded = score(side);

        if (matchEnded)
            return;
    }
}

void KickerMatch::pause()
{
    isPaused = true;

    mpListeners(matchTime);
}

void KickerMatch::end()
{
    isStarted = false;
    isPaused = false;
    isFinished = true;
}

bool KickerMatch::hasStarted()
{
    return isStarted;
}

bool KickerMatch::isRunning()
{
    return isStarted && !isPaused;
}

bool KickerMatch::hasFinished()
{
    return isFinished;
}

GoalScoredPtr KickerMatch::addGoalScoredListener(GoalScored callback)
{
    return gsListeners.addListener(callback);
}

MatchWonPtr KickerMatch::addMatchWonListener(MatchWon callback)
{
    return mwListeners.addListener(callback);
}

MatchPausedPtr KickerMatch::addMatchPausedListener(MatchPaused callback)
{
    return mpListeners.addListener(callback);
}

MatchStartedPtr KickerMatch::addMatchStartedListener(MatchStarted callback)
{
    return msListeners.addListener(callback);
}

void KickerMatch::removeGoalScoredListener(GoalScoredPtr callback)
{
    gsListeners.removeListener(callback);
}

void KickerMatch::removeMatchWonListener(MatchWonPtr callback)
{
    mwListeners.removeListener(callback);
}

void KickerMatch::removeMatchPausedListener(MatchPausedPtr callback)
{
    mpListeners.removeListener(callback);
}

void KickerMatch::removeMatchStartedListener(MatchStartedPtr callback)
{
    msListeners.removeListener(callback);
}
