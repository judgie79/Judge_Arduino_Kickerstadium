#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "GUIslice.h"
#include "GUIslice_drv.h"
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

  // ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN};
enum {E_ELEM_TEXT4,MATCH_TIME,SCORE_BLUE,SCORE_RED};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN20X32,MAX_FONT};
//<Enum !End!>

#define MAX_STR 100

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                1

#define MAX_ELEM_PG_MAIN 4 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM
//<ElementDefines !End!>

static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

class ScoreBoard
{
private:

  // ------------------------------------------------
  // Create element storage
  // ------------------------------------------------
  gslc_tsGui                      m_gui;
  gslc_tsDriver                   m_drv;
  gslc_tsFont                     m_asFont[MAX_FONT];
  gslc_tsPage                     m_asPage[MAX_PAGE];

  //<GUI_Extra_Elements !Start!>
  gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
  gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];

  gslc_tsElemRef* m_match_time;
  gslc_tsElemRef* m_score_blue;
  gslc_tsElemRef* m_score_red;
public:
  ScoreBoard();
  ~ScoreBoard();
  void setup();
  void update();

  void setScore(byte redScore, byte blueScore);
  void setTime(long time);
};

#endif