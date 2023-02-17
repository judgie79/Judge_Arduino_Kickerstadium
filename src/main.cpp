#include <Arduino.h>
#if ESP32 
#include "Preferences.h"
#endif

// #include <SPI.h>
// #include <SD.h>


// Define debug message function
// static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

#include "Stadium.h"
#include "Team.h"
#include "Player.h"
#include "KickerMatch.h"

Stadium stadium(GPIO_NUM_34, GPIO_NUM_35);

Player player1(1, "Michael");
Player player2(2, "Giovanni");
Player player3(3, "Bernd");
Player player4(4, "Elmar");
Player players2[2] = { player3, player4 };

Team teamRed(0, "Team Rot", &player1, &player2);

Team teamBlue(0, "Team Blau", &player3, &player4);

void goalScored(long matchTime, byte side, Team* team);
void matchWon(long matchTime, byte side, Team* team);
void matchStarted(long matchTime);
void matchPaused(long matchTime);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("init");
  stadium.setup();
  // put your setup code here, to run once:
 stadium.prepareMatch(&teamRed, &teamBlue);

  
  Serial.println("add listeners");
  stadium.addGoalScoredListener(goalScored);
  stadium.addMatchPausedListener(matchPaused);
  stadium.addMatchStartedListener(matchStarted);
  stadium.addMatchWonListener(matchWon);
}

void loop() {
  // put your main code here, to run repeatedly:

   if (!stadium.matchInPlay()) 
   {
     Serial.println("not started");
     stadium.startMatch();
   } else {
     stadium.update();
   }
}



void goalScored(long matchTime, byte side, Team* team)
{
  long matchInSeconds = stadium.currentMatch->getMatchTime() / 1000;
  uint matchMinutes = matchInSeconds / 60;
  uint matchSeconds = matchInSeconds % 60;
  char buffer[40];
  sprintf(buffer, "main goalScored at %i:%i", matchMinutes, matchInSeconds);
  Serial.println(buffer);
}

void matchWon(long matchTime, byte side, Team* team)
{
  Serial.println("main matchWon");
}

void matchPaused(long matchTime)
{
  Serial.println("main matchPaused");
}

void matchStarted(long matchTime)
{
  Serial.println("main matchStarted");
}