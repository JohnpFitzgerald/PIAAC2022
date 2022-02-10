{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : Creates the MainDetails part of the PIAAC Pilot Screener survey
****************************************************************************************************************************************}
BLOCK BMainDetails

   EXTERNALS {Meta data file .bmi}
      LookupData  : SourceData  ('C:\CSO\Piaac\Pilot\LookUps\PIAACLookupInt')

   LOCALS
      I : INTEGER

   AUXFIELDS
      ScrIntro  "This is the screener for the selected household.
                 @/@/Please press 1 to review or update details for this household." : TStart,NODK, NORF
      Txt_Pers  {Used as fill in select question}   : STRING[19]
      SampleTxt {Used as a fill in Sample question} : STRING[23]
      PostLen     : INTEGER
      PostalTest  : ARRAY [1..120] OF STRING[1]
      PostProbFlg : ARRAY [1..120] OF STRING[1]
      PstProbChar : ARRAY [1..120] OF STRING[9]

   FIELDS
      BlockNo   "@/@/Please enter the four digit @SBlock@S number.
                 @/@/@S@Zi@Z Include leading zeros if appropriate.@S " : STRING[4], NODK, NORF {key}
      LDUNo    "@/@/Please enter the three digit @SHousehold Ldu@S number.
                 @/@/@S@Zi@Z Include leading zeros if appropriate.@S " : STRING[3], NODK, NORF {key}
      IntvwrNo  "@/@/Please enter your three digit @SInterviewer@S number.
                 @/@/@S@Zi@Z Include leading zeros if appropriate.@S " : STRING[3]
      TeamID    "@/@/Please enter your two digit @STeam ID@S number.
                 @/@/@S@Zi@Z Include leading zeros if appropriate.@S " : STRING[2]
      {BookID_PPC {Read from lookup, pased to xml file by manipula CreatePiaacInputZipFile.Msu CreatePiaacZip procedure} : STRING[8]
      BookID_PP1 {Read from lookup, pased to xml file by manipula CreatePiaacInputZipFile.Msu CreatePiaacZip procedure} : STRING[8]
      BookID_PP2 {Read from lookup, pased to xml file by manipula CreatePiaacInputZipFile.Msu CreatePiaacZip procedure} : STRING[8]
      BookID_PRC {Read from lookup, pased to xml file by manipula CreatePiaacInputZipFile.Msu CreatePiaacZip procedure} : STRING[8]
            Sample     {"@/@/This household ·@S^BlockNo ^LDUNo@S ·is ·@S^SampleTxt@S"}  : STRING[13],EMPTY    }
      Postal    "@/@/@S@Zi@Z Please confirm the postal address of this household and make changes if necessary.
                 @/@/ADDRESS : ^Postal" : STRING[120],EMPTY, NODK, NORF
      CanInterview   "@/@/May I continue to interview this household?
                 @/@/You are now entering information for @S^BlockNo ^LDUNo@S" : TYesNo, NODK, NORF
      StartDate  "Admin field to be held in the background" : DATETYPE
      StarTime   "Admin field to be held in the background" : TIMETYPE
      NoPersons   "@/@/Please enter the total number of persons currently resident in this household, including children.
                 @/@/@S@Zi@Z This is required to get an accurate picture of the household composition. @S" : 1..20, NODK, NORF

   RULES
      BlockNo.KEEP
      BlockNo.SHOW
      LDUNo.KEEP
      LDUNo.SHOW
      IntvwrNo.KEEP

      IF LookupData.SEARCH(BlockNo,LDUNo) THEN
         LookupData.READ
      ENDIF
      ScrIntro
      IF (IntvwrNo = EMPTY) THEN
          {IntvwrNo := LookUpData.PiaacLkpInt}
          IntvwrNo := LookUpData.IntvwrNo
      ENDIF
      IntvwrNo.SHOW

      TeamID.KEEP
      IF (TeamID = EMPTY) THEN
          TeamID := LookUpData.TeamID
      ENDIF
      TeamID.SHOW
      {BookID_PPC.KEEP
      IF (BookID_PPC = EMPTY) THEN
         BookID_PPC := LookupData.BookID_PPC
      ENDIF
      BookID_PP1.KEEP
      IF (BookID_PP1 = EMPTY) THEN
         BookID_PP1 := LookupData.BookID_PP1
      ENDIF
      BookID_PP2.KEEP
      IF (BookID_PP2 = EMPTY) THEN
         BookID_PP2 := LookupData.BookID_PP2
      ENDIF
      BookID_PRC.KEEP
      IF (BookID_PRC = EMPTY) THEN
         BookID_PRC := LookupData.BookID_PRC
      ENDIF
      Sample.KEEP
      IF (Sample = EMPTY) THEN
         Sample := LookupData.Sample
      ENDIF
      Sample.SHOW  }
      Postal.KEEP
      IF (Postal = EMPTY) THEN
          Postal := LookupData.Address
      ENDIF
      Postal
      PostLen := LEN(Postal)
      {FOR I := 1 TO 120 DO                                           {Problems with certain characters when reading in the }
          IF I <= PostLen THEN                                       {address field to the xml file needed to open the vm piaac}
             PostalTest[I] := SUBSTRING(Postal,I,1)                  {@ " > < & cause probs also fadas in names}
             IF (PostalTest[I] >= 'A' AND PostalTest[I] <= 'Z') OR   {Can remove the offending chars from the lookup but interviewers}
                (PostalTest[I] >= 'a' AND PostalTest[I] <= 'z') OR   {could still accidentally key incorrect chars. To avoid this}
                (PostalTest[I] >= '0' AND PostalTest[I] <= '9') OR   {There are checks on Postal to tie down to a-z, }
                (PostalTest[I] = '.') OR                             {A-Z, 0-9, . , and space}
                (PostalTest[I] = ',') OR
                (PostalTest[I] = ' ') THEN
                 PostProbFlg[I] := 'O'
             ELSE
                 PostProbFlg[I] := 'P'
                 PstProbChar[I] := PostalTest[I]
                 IF PstProbChar[I] = '@' THEN               {The @ character doesn't show in the Check text so added 'character'}
                    PstProbChar[I] := 'character'           {instead of having a blank appear}
                 ENDIF
             ENDIF
             CHECK
             (PostProbFlg[I] = 'O') INVOLVING (Postal)
             "@RError@R @XThere is a problem in the postal address field.
              @/The @w^PstProbChar[I]@w keyed at position @w^I@w is not allowed.
              @/@/@wPlease edit the address field to remove the ^PstProbChar[I]
              @/Also please make sure the rest of the address only contains Letters, Numbers, Full Stops or Commas@w.
              @/@/Unfortunately no other punctuation e.g. apostrophe or fadas etc. can be accomodated.
              @/These symbols cause problems when loading the address into the PIAAC questionnaire. @X"
          ENDIF
      ENDDO}
      CanInterview.KEEP
      IF CanInterview = YES THEN
         CanInterview.SHOW
      ELSEIF (CanInterview = EMPTY OR CanInterview = NO) THEN
         CanInterview
      ENDIF
      IF (CanInterview = YES) THEN
          StartDate.KEEP
          StarTime.KEEP
          IF (StartDate = EMPTY) THEN
              StartDate := SYSDATE
          ENDIF
          IF (StarTime = EMPTY) THEN
              StarTime  := SYSTIME
          ENDIF
          NoPersons
          IF (NoPersons = 1) THEN
              Txt_Pers := 'There is' + ' ' + STR(NoPersons) + ' person'
          ELSEIF (NoPersons > 1) THEN
              Txt_Pers := 'There are ' + STR(NoPersons) + ' people'
          ENDIF
      ENDIF

      LAYOUT
          BEFORE Postal INFOPANE Contact
                        FIELDPANE Contact
                        GRID Contact
          AFTER Postal  NEWPAGE
                        INFOPANE DefaultInfoPane
                        FIELDPANE DefaultFieldPane
                        GRID DefaultGrid
          AFTER CanInterview NEWPAGE
                        FIELDPANE Contact
          AFTER NoPersons NEWPAGE
ENDBLOCK

FIELDS
   MainDetails : BMainDetails
