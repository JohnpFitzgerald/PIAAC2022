{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : This block records the various calls made to the household until completion of the PIAAC case
****************************************************************************************************************************************}
BLOCK BHHCall
   LOCALS
      I : INTEGER

   TABLE TCallGrid {Household composition block}

      LOCALS
         I : INTEGER

         BLOCK BCall

            FIELDS
               Dat1     {Used for checking dates are within the reference period} : TDate
               VisitNo1 {Visit number assigned from I, assigns values to question text, eg. '1st Visit' etc} : INTEGER,EMPTY
               Visit    {Visit is text value calculated using VisitNo1 and used as fill in question texts}   : STRING[10],EMPTY
               Day      "@/@/Please enter the day of the @B^Visit@B"  : STRING[9],EMPTY
               DayNo    {Used to assign values to Day field} : INTEGER[1],EMPTY
               Date      "@/@/Please enter the date of the @B^Visit@B
                          @/@/@S@Zi@Z To enter data on subsequent visits to this household, re-enter the Admin screen for this case and
                          @/change ‘2’ to ‘1’ in the NewVisit field (Do you want to add details for another visit?).
                          @/Proceed to record detail for subsequent visits to household.@S" : TDate
               Time      "@/@/Please enter the time of the @B^Visit@B" : TIMETYPE
               Interim     "Please code the outcome of this call to the household.
                         @/@/@S@Zi@Z Please use Option 8 if you have made contact
                         with the household and completed the Screener.@S" : TIntm
               Screener      "Please code the PIAAC Screener Outcome
                                @/@/@S@Zi@Z Please enter a code from the list below@S" : TScr
               Initial     "Has the Case Initialisation been completed?
                         @/@/@S@Zi@Z Please enter a code from the list below@S"   : TBQInit
               InterviewType  "@/Was this a PIAAC Interview or Doorstep Interview?"          : TExType
               Doorstep "Please code the outcome of the Doorstep Interview
                            @/@/@S@Zi@Z Please enter a code from the list below@S" : TDoorstep
               BackgroundQuestionnaire  "Please code the outcome of the Background Questionnaire
                                        @/@/@S@Zi@Z Please enter a code from the list below@S" : TBQInit
               Locator     "Please code the PIAAC Locator Outcome
                                @/@/@S@Zi@Z Please enter a code from the list below@S"
                         {@/@/@S@Zi@Z This applies to either the Computer OR Paper Assessments exercise@S"} : TCore
               Exercise     "Please code the PIAAC Direct Assessment Outcome
                                @/@/@S@Zi@Z Please enter a code from the list below@S" : TExcr
               CallType      "Please enter the type of call that you made with this household or person" : TContact
               Duration "@/Please enter the approximate duration of the PIAAC Interview or Doorstep Interview in minutes.
                            @/@/@S@Zi@Z Please enter a numeric value between 0 and 240@S"  : 0..240
               NewVisit   "@/Do you want to add details for another visit?"   : TYesNo, NODK, NORF
               {CallBack   "@/Do you want to add details for another visit?"   : TYesNo, NODK, NORF}

            RULES
               VisitNo1 := I
               Visit.KEEP
               IF (VisitNo1 = 1) THEN
                   Visit := '1st Visit'
               ELSEIF (VisitNo1 = 2) THEN
                   Visit := '2nd Visit'
               ELSEIF (VisitNo1 = 3) THEN
                   Visit := '3rd Visit'
               ELSEIF (VisitNo1 = 4) THEN
                   Visit := '4th Visit'
               ELSEIF (VisitNo1 = 5) THEN
                   Visit := '5th Visit'
               ELSEIF (VisitNo1 = 6) THEN
                   Visit := '6th Visit'
               ELSEIF (VisitNo1 = 7) THEN
                   Visit := '7th Visit'
               ELSEIF (VisitNo1 = 8) THEN
                   Visit := '8th Visit'
               ELSEIF (VisitNo1 = 9) THEN
                   Visit := '9th Visit'
               ELSEIF (VisitNo1 = 10) THEN
                   Visit := '10th Visit'
               ENDIF
               Visit.SHOW
               Date
               Dat1.KEEP
               Dat1 := TODATE(10,01,01)
               IF (Date <> EMPTY) THEN
                  SIGNAL
                  (Date >= Dat1) INVOLVING (Date)
                  "@RWarning.@R
                   @/@/@XInterviewer The date you have entered is earlier than the reference period for
                   the survey.
                   @/@/Please enter another date.@X"
                   SIGNAL
                   JULIAN(Date) <= JULIAN(SYSDATE)
                  "@RWarning@R
                   @/@/@XThe date you have entered is in the future. Please enter another date.@X"
               ENDIF
               IF (Date = RESPONSE) THEN
                   DayNo := (Date.WEEKDAY)
                   IF (DayNo = 1) THEN
                      Day := 'Sunday'
                   ELSEIF (DayNo = 2) THEN
                      Day := 'Monday'
                   ELSEIF (DayNo = 3) THEN
                      Day := 'Tuesday'
                   ELSEIF (DayNo = 4) THEN
                       Day := 'Wednesday'
                   ELSEIF (DayNo = 5) THEN
                      Day := 'Thursday'
                   ELSEIF (DayNo  = 6) THEN
                      Day  := 'Friday'
                   ELSEIF (DayNo = 7) THEN
                      Day  := 'Saturday'
                   ENDIF
                   Day.SHOW
               ENDIF
               Time
               CallType
               IF (CallType = NC) THEN
                   Interim.KEEP
                   Interim := CB
                   Interim.SHOW
               ELSE
                  Interim
                  IF (Interim = OT) THEN
                     Screener
                  ENDIF
                  IF (Screener = C1 OR Screener = LP) THEN
                      Initial
                  ENDIF
               	  IF (Initial = CP OR Initial = LP) THEN
                      InterviewType
                  ENDIF
                  IF (Screener = LP) OR (Initial = LP) THEN
                  SIGNAL
                  (InterviewType = P) INVOLVING (InterviewType)
                  "@RWarning.@R
                   @/@/@XLanguage barrier was selected for previous questions. Are you sure you want to continue with the PIAAC Interview?@X"
                  ENDIF
                  IF (InterviewType = P) THEN
                      Doorstep
                  ENDIF
                  IF (InterviewType = C) THEN
                      BackgroundQuestionnaire
                  ENDIF
				  IF (BackgroundQuestionnaire = CP) THEN
                      Locator
                  ENDIF
                 {IF (Assessments = C OR Assessments = N) THEN
                     (i.e. if 'complete' or if 'no computer experience, paper route selected')
                      New codes provided by business area but no code for 'no computer experience ...' as above so
                      new routing as follows ......}
                  IF (Locator = CP) THEN
                      Exercise
                  ENDIF
    	          IF (Exercise = CP OR Exercise = PB) OR (Doorstep = CP)THEN
                      Duration
                  ENDIF
                  SIGNAL
                 (Duration < 150) INVOLVING (Duration)
                  "@RWarning.@R
                   @/@/@XAre you sure this interview took longer than 2 and a half hours?@X"
                  SIGNAL
                 (Duration < 180) INVOLVING (Duration)
                 "@RWarning.@R
                  @/@/@XAre you sure this interview took longer than 3 hours?@X"
                  SIGNAL
                 (Duration < 240) INVOLVING (Duration)
                 "@RWarning.@R
                  @/@/@XAre you sure this interview took longer than 4 hours?@X"
               ENDIF
               NewVisit
        ENDBLOCK

      FIELDS {For Table TCallGrid}
         Call    : ARRAY [1 .. 10] OF BCall
         MorFlag : STRING[1]

      RULES {For Table TCallGrid}
         MorFlag := 'Y'
         FOR I := 1 to 10 DO
            IF (MorFlag = 'Y') THEN
                Call[I]
            ENDIF
            IF (Call[I].NewVisit = NO) THEN
                MorFlag := 'N'
            ENDIF
         ENDDO
   ENDTABLE

   FIELDS {Fields for Block HHCall}
       CallGrid : TCallGrid

   RULES {Rules for Block HHCall}
      CallGrid

   LAYOUT BEFORE CallGrid INFOPANE CallGrid
ENDBLOCK

FIELDS
   HHCall : BHHCall
