#include "Stadium.h"

Stadium::Stadium(byte sensorPinRedGoal, byte sensorPinBlueGoal) : sensorRedGoal(0, SensorType::Trigger, SensorTriggerType::Force, sensorPinRedGoal),
                                                                  sensorBlueGoal(1, SensorType::Trigger, SensorTriggerType::Force, sensorPinBlueGoal),
                                                                  ticker{[this](){this->onTimer();}, 1000, 0, MILLIS}
{
}

Stadium::~Stadium()
{
    if (currentMatch != nullptr)
    {
        free(currentMatch);
    }
}

void Stadium::setup()
{
    // gslc_InitDebug(LOG_DEBUG));

    // ------------------------------------------------
    // Create graphic elements
    // ------------------------------------------------
    scoreboard.setup();
}


void Stadium::update()
{
    if (matchInPlay()) {
        currentMatch->play();
        ticker.update();
    }
}


void Stadium::onTimer()
{
    if (matchInPlay())
    {
        scoreboard.setTime(this->currentMatch->getMatchTime());
        scoreboard.update();
    }
}

void Stadium::prepareMatch(Team *red, Team *blue, byte goalsNeededToWin)
{
    Serial.println("prepare match");

    this->red = red;
    this->blue = blue;
    currentMatch = new KickerMatch(std::bind(&Stadium::scored, this, std::placeholders::_1), goalsNeededToWin);
    goalScorePtr = currentMatch->addGoalScoredListener(std::bind(&Stadium::goalScored, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    matchPausedPtr = currentMatch->addMatchPausedListener(std::bind(&Stadium::matchPaused, this, std::placeholders::_1));
    matchStartedPtr = currentMatch->addMatchStartedListener(std::bind(&Stadium::matchStarted, this, std::placeholders::_1));
    matchWonPtr = currentMatch->addMatchWonListener(std::bind(&Stadium::matchWon, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    Serial.println("match prepared");
}
void Stadium::startMatch()
{
    Serial.println("start match");
    currentMatch->start(red, blue);

    ticker.start();
}

bool Stadium::matchInPlay()
{
    if (currentMatch == nullptr)
    {
        return false;
    }

    return currentMatch->isRunning();
}

void Stadium::readGoalSensors()
{
    sensorRedGoal.read();
    sensorBlueGoal.read();
}

long lastGoal = 0;
bool Stadium::scored(byte &side)
{
    readGoalSensors();

    if (sensorBlueGoal.wasTriggered() && millis() - lastGoal > 2000)
    {
        lastGoal = millis();
        side = RED;
        return true;
    }
    else if (sensorRedGoal.wasTriggered() && millis() - lastGoal > 2000)
    {
        lastGoal = millis();
        side = BLUE;
        return true;
    }

    return false;
}

void Stadium::goalScored(long matchTime, byte side, Team *team)
{
    String scorer = side == RED ? "red" : "blue";

    Serial.println("goal scored " + scorer);

    scoreboard.setScore(currentMatch->currentScoreRed(), currentMatch->currentScoreBlue());
    
    const double distance = 0.02;
    long timeInSeconds = 0;
    if (side == RED)
    {
        unsigned long t = sensorRedGoal.lastCollisionDuration();
        Serial.println(t);
        timeInSeconds = sensorRedGoal.lastCollisionDuration() / 1000; //Convert miliseconds to seconds
    } else {
        unsigned long t = sensorRedGoal.lastCollisionDuration();
        Serial.println(t);
        timeInSeconds = sensorBlueGoal.lastCollisionDuration() / 1000; //Convert miliseconds to seconds
    }

    float speedOfObject = distance / timeInSeconds; //Calculate speed in metres per second



    scoreboard.update();

    // inform stadium listeners
    gsListeners(matchTime, side, team);

    Serial.println("Speed " + String(speedOfObject));
}

void Stadium::matchPaused(long matchTime)
{
    Serial.println("match paused");
    ticker.pause();

    // inform stadium listeners
    mpListeners(matchTime);
}

void Stadium::matchStarted(long matchTime)
{
    Serial.println("match started");

    // inform stadium listeners
    msListeners(matchTime);

    scoreboard.setTime(0);
    scoreboard.setScore(0, 0);

    scoreboard.update();
}

void Stadium::matchWon(long matchTime, byte side, Team *team)
{
    String winner = side == RED ? "red" : "blue";

    Serial.println("match won " + winner);
    mwListeners(matchTime, side, team);

    // cleanup current session
    currentMatch->removeGoalScoredListener(goalScorePtr);
    currentMatch->removeMatchPausedListener(matchPausedPtr);
    currentMatch->removeMatchStartedListener(matchStartedPtr);
    currentMatch->removeMatchWonListener(matchWonPtr);

    ticker.stop();

}

GoalScoredPtr Stadium::addGoalScoredListener(GoalScored callback)
{
    return currentMatch->addGoalScoredListener(callback);
}

MatchWonPtr Stadium::addMatchWonListener(MatchWon callback)
{
    return currentMatch->addMatchWonListener(callback);
}

MatchPausedPtr Stadium::addMatchPausedListener(MatchPaused callback)
{
    return currentMatch->addMatchPausedListener(callback);
}

MatchStartedPtr Stadium::addMatchStartedListener(MatchStarted callback)
{
    return currentMatch->addMatchStartedListener(callback);
}

void Stadium::removeGoalScoredListener(GoalScoredPtr callback)
{
    currentMatch->removeGoalScoredListener(callback);
}

void Stadium::removeMatchWonListener(MatchWonPtr callback)
{
    currentMatch->removeMatchWonListener(callback);
}

void Stadium::removeMatchPausedListener(MatchPausedPtr callback)
{
    currentMatch->removeMatchPausedListener(callback);
}

void Stadium::removeMatchStartedListener(MatchStartedPtr callback)
{
    currentMatch->removeMatchStartedListener(callback);
}
