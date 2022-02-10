{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : Asks a last question in the Piaac survey for admin purposes
****************************************************************************************************************************************}
BLOCK BLastQ

   AUXFIELDS
      DayTxt   : STRING[9]
      DateTxt  : STRING[4]
      MthTxt   : STRING[9]
      YrTxt    : STRING[4]

   FIELDS
      MakeApt   "@/@/@S@Zi@Z If ^HHComponent.FlNmChos is not available for a PIAAC interview then
                 can you make an interview appointment for a later date.@S" : TYesApt
      AppDate   "@/@/@S@Zi@Z Please set an appointment date?@S" : TDate
                 {@/@/@S@Zi@Z Press the Alt Key together with the down arrow key to display the calender and select a date"}
      AptDtTxt  {This is a .Keep Field, not asked.
                 The value is collected at the Ask Field AppDate and converted to text string
                 for reference in AppNote question text and front end Tables} : STRING[30]
      AppTime   "@/@/@S@Zi@Z Please agree an appointment time@S" : TIMETYPE
      AppNote   "@/@/@S@Zi@Z Are there any relevant notes re this appointment
                 @/@/Appointment has been agreed for @S^AptDtTxt at ^AppTime o'clock@S" : STRING[150],EMPTY
      zzLanguage "@/@/@S@Zi@Z In what language will you be conducting the Doorstep interview with ^HHComponent.FlNmChos ?.@S" : TDSLang

   RULES
      IF (MainDetails.CanInterview = YES) AND (SetElig.Select = YES) THEN
         MakeApt
         IF (MakeApt = YES) THEN
             AppDate
             CHECK
             (AppDate >= MainDetails.StartDate) INVOLVING (AppDate)
             "@RError@R@/@XThe date you have entered is earlier than the screener start date.
              @/Please make an appointment for a later date.@X"
             AppTime
             IF (AppDate =  MainDetails.StartDate) INVOLVING (AppDate) THEN
                 CHECK
                (AppTime > MainDetails.StarTime) INVOLVING (AppDate)
                "@RError@R@/@XThe time you have entered is earlier than the screener start time.
                 @/Please agree a later appointment time.@X"
             ENDIF
             DayTxt.KEEP
             IF (AppDate.WEEKDAY  =  1) THEN
                DayTxt := 'Sunday'
             ELSEIF (AppDate.WEEKDAY = 2) THEN
                DayTxt := 'Monday'
             ELSEIF (AppDate.WEEKDAY = 3) THEN
                DayTxt := 'Tuesday'
             ELSEIF (AppDate.WEEKDAY = 4) THEN
                DayTxt := 'Wednesday'
             ELSEIF (AppDate.WEEKDAY = 5) THEN
                DayTxt := 'Thursday'
             ELSEIF (AppDate.WEEKDAY = 6) THEN
                DayTxt := 'Friday'
             ELSEIF (AppDate.WEEKDAY = 7) THEN
                DayTxt := 'Saturday'
             ENDIF
             DateTxt.KEEP
             IF (AppDate.DAY)  =  1 THEN
                DateTxt := '1st'
             ELSEIF (AppDate.DAY = 2) THEN
                DateTxt := '2nd'
             ELSEIF (AppDate.DAY = 3) THEN
                DateTxt := '3rd'
             ELSEIF (AppDate.DAY = 4) THEN
                DateTxt := '4th'
             ELSEIF (AppDate.DAY = 5) THEN
                DateTxt := '5th'
             ELSEIF (AppDate.DAY = 6) THEN
                DateTxt := '6th'
             ELSEIF (AppDate.DAY = 7) THEN
                DateTxt := '7th'
             ELSEIF (AppDate.DAY = 8) THEN
                DateTxt := '8th'
             ELSEIF (AppDate.DAY = 9) THEN
                DateTxt := '9th'
             ELSEIF (AppDate.DAY = 10) THEN
                DateTxt := '10th'
             ELSEIF (AppDate.DAY = 11) THEN
                DateTxt := '11th'
             ELSEIF (AppDate.DAY = 12) THEN
                DateTxt := '12th'
             ELSEIF (AppDate.DAY = 13) THEN
                DateTxt := '13th'
             ELSEIF (AppDate.DAY = 14) THEN
                DateTxt := '14th'
             ELSEIF (AppDate.DAY = 15) THEN
                DateTxt := '15th'
             ELSEIF (AppDate.DAY = 16) THEN
                DateTxt := '16th'
             ELSEIF (AppDate.DAY = 17) THEN
                DateTxt := '17th'
             ELSEIF (AppDate.DAY = 18) THEN
                DateTxt := '18th'
             ELSEIF (AppDate.DAY = 19) THEN
                DateTxt := '19th'
             ELSEIF (AppDate.DAY = 20) THEN
                DateTxt := '20th'
             ELSEIF (AppDate.DAY = 21) THEN
                DateTxt := '21st'
             ELSEIF (AppDate.DAY = 22) THEN
                DateTxt := '22nd'
             ELSEIF (AppDate.DAY = 23) THEN
                DateTxt := '23rd'
             ELSEIF (AppDate.DAY = 24) THEN
                DateTxt := '24th'
             ELSEIF (AppDate.DAY = 25) THEN
                DateTxt := '25th'
             ELSEIF (AppDate.DAY = 26) THEN
                DateTxt := '26th'
             ELSEIF (AppDate.DAY = 27) THEN
                DateTxt := '27th'
             ELSEIF (AppDate.DAY = 28) THEN
                DateTxt := '28th'
             ELSEIF (AppDate.DAY = 29) THEN
                DateTxt := '29th'
             ELSEIF (AppDate.DAY = 30) THEN
                DateTxt := '30th'
             ELSEIF (AppDate.DAY = 31) THEN
                DateTxt := '31st'
             ENDIF
             MthTxt.KEEP
             IF (AppDate.MONTH = 1) THEN
                 MthTxt := 'January'
             ELSEIF (AppDate.MONTH = 2) THEN
                 MthTxt := 'February'
             ELSEIF (AppDate.MONTH = 3) THEN
                 MthTxt := 'March'
             ELSEIF (AppDate.MONTH = 4) THEN
                 MthTxt := 'April'
             ELSEIF (AppDate.MONTH = 5) THEN
                 MthTxt := 'May'
             ELSEIF (AppDate.MONTH = 6) THEN
                 MthTxt := 'June'
             ELSEIF (AppDate.MONTH = 7) THEN
                 MthTxt := 'July'
             ELSEIF (AppDate.MONTH = 8) THEN
                 MthTxt := 'August'
             ELSEIF (AppDate.MONTH = 9) THEN
                 MthTxt := 'September'
             ELSEIF (AppDate.MONTH = 10) THEN
                 MthTxt := 'October'
             ELSEIF (AppDate.MONTH = 11) THEN
                 MthTxt := 'November'
             ELSEIF (AppDate.MONTH = 12) THEN
                 MthTxt := 'December'
             ENDIF
             YrTxt.KEEP
             YrTxt := STR(AppDate.YEAR)
             AptDtTxt.KEEP
             AptDtTxt := DayTxt + ' ' + DateTxt + ' ' + MthTxt + ' ' + YrTxt
             AppNote
            ELSEIF (MakeApt = DS) THEN
                   zzLanguage
         ENDIF
      ENDIF

      LAYOUT
         BEFORE AppNote NEWPAGE
         AFTER AppNote NEWPAGE
ENDBLOCK

FIELDS
   LastQ : BLastQ
