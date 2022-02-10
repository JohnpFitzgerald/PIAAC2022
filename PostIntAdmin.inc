{Author Name    : Norma O Connell
 Date written   : December 2019
 Version        : 1.0

 Description    : Asks post interview questions in the Piaac survey Admin section.
***************************************************************************************************************************************}
BLOCK BPostIntAdmin "Post Interview"

   LOCALS
      I, LastVisNo : INTEGER



   FIELDS
      ZZ1a {OtherPersInt}  "@/@/@S@Zi@ZA few questions about the Interviewing experience@S
                            @/@/Please select the option or options below that best describe(s) the presence of a person other than you or the respondent during the interview." : TOtherPersPres
      ZZ1b "@/@/Please select the option or options below that best describe(s) whether the respondent received assistance from anyone in answering any of the following?" : SET OF TOthAssist
      ZZ2 "@/@/Overall, did you feel that the respondent understood the questions in the background questionnaire?" : TRespUnder
      ZZ3  "@/@/Did you assist the respondent with the tablet skills and/or the tablet tutorial when the respondent was working independently?" : TYesNo
      ZZ4   "@/@/Did the respondent ask for assistance in using the features of the tablet (e.g. asked where to enter a response on the tablet) when working independently on the Exercise?" : TYesNo
      ZZ5  "@/@/Did the respondent ask for assistance on any questions while completing the locator, the components and/or the assessment (please exclude questions related to using the tablet features)?" : TYesNo
      ZZ6  "@/@/During the locator, components and/or assessment, was there background (ambient) noise from any of the following sources?" : SET OF TBkgNoise
      ZZ7  "@/@/Did the respondent stop working on the locator, components and/or assessment  at any point?" : TRespStop
      ZZ8 "@/@/Did the respondent complain that the Exercise was taking too long or taking too much time?" : TYesNo
      ZZ9  "@/@/Where did the Exercise mainly take place?" : TWhereInt
      ZZ10 "@/@/If you have additional comments on the interview, please write them in the space below." : STRING [255]



   RULES
      ZZ1a
      IF (ZZ1a = BQ OR ZZ1a = TS OR ZZ1a = RS) THEN
         ZZ1b
      ELSE
         ZZ2
         ZZ3
         ZZ4
         ZZ5
         ZZ6
         ZZ7
         ZZ8
         ZZ9
         ZZ10
      ENDIF
ENDBLOCK

FIELDS
   PostIntAdmin : BPostIntAdmin
