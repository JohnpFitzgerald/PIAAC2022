{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : Creates the MainAdmin part of the PIAAC Pilot Admin survey
****************************************************************************************************************************************}
BLOCK BMainAdmin

   EXTERNALS {Meta data file .bmi}
      Screener   : ScrLookUp  ('C:\CSO\Piaac\Pilot\Piaac2022Scr')
      LookupData : SourceData ('C:\CSO\Piaac\Pilot\LookUps\PIAACLookupInt')

   AUXFIELDS
      AdminIntro  "This is the Admin for household @S^BlockNo ^LDUNo@S
                 @/@/Please press 1 to review or update Admin details for this household" : TStart, NODK, NORF
      FlNmChos   {Used as a fill in the summary question} : STRING[115]

   FIELDS
      BlockNo   "@/@/Please enter the four digit @BBlock@B number.
                 @/@/@S@Zi@Z Include leading zeros if appropriate.@S "  : STRING[4] {key}
      LDUNo    "@/@/Please enter the three digit @BHousehold@B number..
                 @/@/@S@Zi@Z Include leading zeros if appropriate.@S "  : STRING[3] {key}
      IntvwrNo  "@/@/Please enter your three digit @Binterviewer@B number..
                 @/@/@S@Zi@Z Include leading zeros if appropriate.@S "  : STRING[3]
      TeamID    "@/@/Please enter your two digit @BTeam ID@B number..
                 @/@/@S@Zi@Z Include leading zeros if appropriate.@S "  : STRING[2]
      Summary   "@/@S@Zi@Z This household is @B^BlockNo ^LDUNo
                 @/^FlNmChos
                 @/@/Press 1 to continue@S" : STRING[1]
      PersID        {This is the PersID calculated in the PiaacPilotScr database
                     and now copied in here for reference/fill purposes} : STRING[11]
      RefWk(SeqNo)  {Read in from Lookup File - used in piaacmenu.man} : 1..17

   RULES
      BlockNo.KEEP
      BlockNo.SHOW
      LDUNo.KEEP
      LDUNo.SHOW
      IntvwrNo.KEEP
      IF LookupData.SEARCH(BlockNo, LDUNo) THEN  {Reading from the Lookup file at household level}
         LookupData.READ
      ENDIF

      IF Screener.SEARCH(MainAdmin.BlockNo, MainAdmin.LDUNo) THEN
         Screener.READ                            {Reading from Screener using BlockNo and LDUNo from PiaacPilotAdmin Database}
      ENDIF

      IF (IntvwrNo = EMPTY) THEN
          IntvwrNo := LookUpData.IntvwrNo
      ENDIF
      IntvwrNo.SHOW

      TeamID.KEEP
      IF (TeamID = EMPTY) THEN
          TeamID := LookUpData.TeamID
      ENDIF

      TeamID.SHOW
      RefWk.Keep
      IF (RefWk = EMPTY) THEN
         RefWk := LookupData.SequenceNo
      ENDIF
      PersID.KEEP
      PersID := Screener.HHComponent.PersID
      IF (Screener.result = 0 AND Screener.SetElig.Select = YES) THEN   {Record in Screener and Select has been chosen as YES}
          FlNmChos := Screener.HHComponent.FlNmChos + ' is the PIAAC interviewee' + '  PersID is ' + PersID
      ENDIF
      IF (Screener.result = 0 AND Screener.SetElig.Select = NO) THEN    {Record in Screener and Select has been chosen as NO}
          FlNmChos := 'Household in the Screener but interviewee not yet chosen for this household'
      ENDIF
      IF (Screener.result = 0 AND Screener.SetElig.Select = EMPTY) THEN {Record in Screener and Select just hasn't been filled yet}
        IF (Screener.ConfirmAge.Ovr16Flg = 0 OR Screener.ConfirmAge.Ovr16Flg = EMPTY) THEN
          IF (Screener.MainDetails.CanInterview = YES) THEN
            IF (Screener.HHGrid.PersonId[Screener.MainDetails.NoPersons].Person.Age <> EMPTY) THEN
               FlNmChos := 'No One eligible for PIAAC' {Record in Screener & CanInterview is YES but select not answered no one >15}
            ELSEIF (Screener.HHGrid.PersonId[Screener.MainDetails.NoPersons].Person.Age = EMPTY) THEN {None >15 as all ages not yet filled}
               FlNmChos := 'Please check the screener. Either no one is eligible for PIAAC or all ages have not been filled into screener yet'
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      IF (Screener.result = 0 AND (Screener.MainDetails.CanInterview = NO OR Screener.MainDetails.CanInterview = EMPTY)) THEN
          FlNmChos := 'Household is in Screener but CanInterview is no or has not been answered yet'
      ENDIF  {Record in Screener and CanInterview is No}
      IF (Screener.Result = 0 AND
         (Screener.MainDetails.CanInterview = NO OR Screener.MainDetails.CanInterview = EMPTY) AND
          Screener.SetElig.Select = EMPTY AND
          Screener.ConfirmAge.Ovr16Flg > 0) THEN
             FlNmChos := 'Household is in the Screener but interviewee not yet chosen for this household'
      ENDIF  {Eligible people in household but not yet chosen}
      IF (Screener.result <> 0) THEN
          FlNmChos := 'This household has not been added to the screener yet'
      ENDIF  {Record is NOT in Screener}
      AdminIntro
      Summary
ENDBLOCK

FIELDS
   MainAdmin : BMainAdmin
