#include "Scoreboard.h"

ScoreBoard::ScoreBoard(/* args */)
{
}

void ScoreBoard::setup()
{
  gslc_InitDebug(&DebugOut);
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN20X32,GSLC_FONTREF_PTR,NULL,4)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,((gslc_tsColor){18,18,18}));

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // Create SCORE_RED runtime modifiable text
  static char m_sDisplayText1[3] = "00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,SCORE_RED,E_PG_MAIN,(gslc_tsRect){234,104,48,32},
    (char*)m_sDisplayText1,3,E_BUILTIN20X32);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,((gslc_tsColor){228,228,229}));
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){228,228,229}),((gslc_tsColor){18,18,18}),GSLC_COL_BLACK);
  m_score_red = pElemRef;
  
  // Create SCORE_BLUE runtime modifiable text
  static char m_sDisplayText2[3] = "00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,SCORE_BLUE,E_PG_MAIN,(gslc_tsRect){60,104,48,32},
    (char*)m_sDisplayText2,3,E_BUILTIN20X32);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,((gslc_tsColor){228,228,229}));
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){228,228,229}),((gslc_tsColor){18,18,18}),GSLC_COL_BLACK);
  m_score_blue = pElemRef;
  
  // Create E_ELEM_TEXT4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT4,E_PG_MAIN,(gslc_tsRect){148,104,24,32},
    (char*)":",0,E_BUILTIN20X32);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,((gslc_tsColor){228,228,229}));
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){228,228,229}),((gslc_tsColor){18,18,18}),GSLC_COL_BLACK);
  
  // Create MATCH_TIME runtime modifiable text
  static char m_sDisplayText5[8] = "00 : 00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,MATCH_TIME,E_PG_MAIN,(gslc_tsRect){76,10,168,32},
    (char*)m_sDisplayText5,8,E_BUILTIN20X32);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,((gslc_tsColor){228,228,229}));
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){228,228,229}),((gslc_tsColor){18,18,18}),GSLC_COL_BLACK);
  m_match_time = pElemRef;
  gslc_Update(&m_gui);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::setTime(long time)
{
    long matchInSeconds = time / 1000;
    unsigned int matchMinutes = matchInSeconds / 60;
    unsigned int matchSeconds = matchInSeconds % 60;
    char buffer[7];
    sprintf(buffer, "%02d : %02d", matchMinutes, matchSeconds);

    gslc_tsElem* pElem = gslc_GetElemFromRefD(&m_gui, m_match_time, __LINE__);

    if (!pElem) return;

    // Check for read-only status (in case the string was
    // defined in Flash/PROGMEM)
    if (pElem->nStrBufMax == 0) {
      // String was read-only, so abort now
      return;
    }

    // To avoid unnecessary redraw / flicker, only a change in
    // the text content will drive a redraw

    if (strncmp(pElem->pStrBuf, buffer, pElem->nStrBufMax)) {
      gslc_StrCopy(pElem->pStrBuf, buffer,pElem->nStrBufMax);
      gslc_ElemSetRedraw(&m_gui, m_match_time, GSLC_REDRAW_INC);
    }
}

void ScoreBoard::setScore(byte redScore, byte blueScore)
{
    char bufferRed[2];
    sprintf(bufferRed, "%02d", redScore);
    gslc_tsElem* pElemRed = gslc_GetElemFromRefD(&m_gui, m_score_red, __LINE__);

    if (!pElemRed) return;

    // Check for read-only status (in case the string was
    // defined in Flash/PROGMEM)
    if (pElemRed->nStrBufMax == 0) {
      // String was read-only, so abort now
      return;
    }

    // To avoid unnecessary redraw / flicker, only a change in
    // the text content will drive a redraw

    if (strncmp(pElemRed->pStrBuf, bufferRed, pElemRed->nStrBufMax)) {
      gslc_StrCopy(pElemRed->pStrBuf, bufferRed, pElemRed->nStrBufMax);
      gslc_ElemSetRedraw(&m_gui, m_score_red, GSLC_REDRAW_INC);
    }



    char bufferBlue[2];
    sprintf(bufferBlue, "%02d", blueScore);
    gslc_tsElem* pElemBlue = gslc_GetElemFromRefD(&m_gui, m_score_blue, __LINE__);

    if (!pElemBlue) return;

    // Check for read-only status (in case the string was
    // defined in Flash/PROGMEM)
    if (pElemBlue->nStrBufMax == 0) {
      // String was read-only, so abort now
      return;
    }

    // To avoid unnecessary redraw / flicker, only a change in
    // the text content will drive a redraw

    if (strncmp(pElemBlue->pStrBuf, bufferBlue, pElemBlue->nStrBufMax)) {
      gslc_StrCopy(pElemBlue->pStrBuf, bufferBlue, pElemBlue->nStrBufMax);
      gslc_ElemSetRedraw(&m_gui, m_score_blue, GSLC_REDRAW_INC);
    }
}

void ScoreBoard::update()
{
  gslc_Update(&m_gui);
}