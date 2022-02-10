{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0


 Description    : Selecting person to be interviewed in the PIAAC survey
****************************************************************************************************************************************}
BLOCK BHHComponent
   LOCALS
      H, I, J : INTEGER

   AUXFIELDS
       StrgLine  {Used in the calculation of the PiaacID} : STRING[3]
       StartID   {Used in the calculation of the PiaacID} : STRING[10]
       StrgVal   {Used in the calculation of the PiaacID} : ARRAY [1..10] OF STRING[1]
       StrgNum   {Used in the calculation of the PiaacID} : ARRAY [1..10] OF INTEGER
       IDTot     {Used in the calculation of the PiaacID} : 1..180
       FrstDigt  {Used in the calculation of the PiaacID} : INTEGER
       ChkDigit  {Used in the calculation of the PiaacID} : STRING[1]

   FIELDS
      EligFlg     : 0..20, NODK, NORF
      RndChose    : INTEGER[4]
      PersChosen  : 1..20
      PiaacID      {This is the reference number that will be used (RENAMED TO PersID below) to interface with the PIAAC Survey
                    - This has been set up to be calculated for every person in the household,
                      the ID for the person selected has been copied to household level.
                      PersID is copied from PiaacID and is whats referenced for manipluas etc. } : STRING[11]
      FlNmChos    : STRING[37]
      NameChos    : STRING[14]
      AgeChos       {Used for display in the Contact Block} : STRING[3]
      AgeWhenChosen {Used for reference to track changes in keying ages after selection} : STRING[3]
      PersID        {Admin Field - To be output to the VMWare Questionnaire} : STRING[11]
      SexChos     : TSex
      MnOneTwo    : INTEGER
      Mn          : ARRAY [1..10] OF INTEGER
      CI_PersID   : INTEGER[12]
      CI_Name     : STRING[14]
      CI_Age      : 0..110
      CI_Gender   : TSex

   RULES
      EligFlg.KEEP
      IF (SetElig.Select = YES) THEN
          EligFlg := 0
          FOR I := 1 TO MainDetails.NoPersons DO
              IF (SetElig.Eligible[I].Eligible = YES) THEN
                  EligFlg := EligFlg + 1
              ENDIF
          ENDDO
          IF (EligFlg >= 1) THEN
              RndChose.KEEP
              PersID.KEEP
              PersChosen.KEEP
              FlNmChos.KEEP
              NameChos.KEEP
              AgeChos.KEEP

              IF (MainDetails.NoPersons >=2) THEN             {If 2 or more in household person selected as follows}
                  MnOneTwo.KEEP
                  MnOneTwo := MIN (SetElig.Eligible[1].RndLine1, SetElig.Eligible[2].RndLine1)

                  IF (MainDetails.NoPersons = 2) THEN
                      RndChose := MnOneTwo
                  ENDIF

                  IF (MainDetails.NoPersons > 2) THEN
                      FOR I := 3 TO MainDetails.NoPersons DO
                          H := I - 1
                          J := I + 1

                          IF I = 3 THEN
                             Mn[I] := MIN (MnOneTwo, SetElig.Eligible[I].RndLine1)
                          ENDIF

                          IF I >= 4 THEN
                             Mn[I] := MIN (Mn[H], SetElig.Eligible[I].RndLine1)
                          ENDIF

                          RndChose := Mn[I]
                      ENDDO
                  ENDIF
                  IF (MainDetails.NoPersons >=2) THEN
                      FOR I := 1 TO MainDetails.NoPersons DO
                         IF (RndChose = SetElig.Eligible[I].RndLine1) THEN
                             PersChosen := I
                         ENDIF
                      ENDDO
                  ENDIF
              ENDIF
              IF (MainDetails.NoPersons = 1) THEN               {If only 1 in household then that person is selected & assigned as follows}
                     RndChose := SetElig.Eligible[1].RndLine1 {The Select filter above deals with the eligibility}
                     PersChosen := 1
              ENDIF
          ENDIF
          IF (HHGrid.PersonID[PersChosen].Person.Line >= 10) THEN             {Convert to String so substring function }
              StrgLine := '0' + STR(HHGrid.PersonID[PersChosen].Person.Line)  {can spilt for CheckDigit calculations}
          ELSEIF (HHGrid.PersonID[PersChosen].Person.Line < 10) THEN
              StrgLine := '00' + STR(HHGrid.PersonID[PersChosen].Person.Line) {As above for CheckDigit}
          ENDIF
          StartID := MainDetails.BlockNo + MainDetails.LDUNo + StrgLine
          FOR I := 1 TO 10 DO
              StrgVal[I] := SubString(StartID,I,1) {Substrings of StartID.......there are 10 digits in StartID}
              StrgNum[I] := Val(StrgVal[i])        {are converted to numeric for use in CheckDigit calculations}
          ENDDO
          IDTot := ((StrgNum[1] + StrgNum[3] + StrgNum[5] + StrgNum[7] + StrgNum[9]) * 3) +
                    (StrgNum[2] + StrgNum[4] + StrgNum[6] + StrgNum[8] + StrgNum[10]) {Calculate a total for Mod calculation}
          FrstDigt := IDTot Mod 10      {Modulo 10 of the IDTot i.e. the remainder after the Total has been divided by 10}
          IF (FrstDigt = 0) THEN        {If the result is 0 then the checkdigit is to be 0..........}
              Frstdigt = 0              {but if greater than 0, must be subtracted from 10 and that value becomes the checkdigit}
          ELSEIF (FrstDigt >0) THEN
              Frstdigt := 10 - Frstdigt
          ENDIF
          ChkDigit := STR(FrstDigt)
          PiaacID := StartID + ChkDigit {Consists of block, ldu & persons line number plus checkdigit calculated above}

          IF (PersChosen >= 1) THEN
              FlNmChos := HHGrid.PersonID[PersChosen].Person.Name + ' ' + HHGrid.PersonID[PersChosen].Person.Surname
              NameChos := HHGrid.PersonID[PersChosen].Person.Name
              AgeChos  := STR(HHGrid.PersonID[PersChosen].Person.Age)
              PersID   := PiaacID
              SexChos  := HHGrid.PersonID[PersChosen].Person.Gender
              IF (EligFlg = 0 OR EligFlg = EMPTY OR EligFlg = DK OR EligFlg = RF) THEN
                  FlNmChos := 'No One eligible for PIAAC'
                  AgeChos :=  'NR'
              ENDIF
          ENDIF
          AgeWhenChosen.KEEP
          IF (SetElig.Select = YES AND AgeChos <> EMPTY AND AgeWhenChosen = EMPTY) THEN
             AgeWhenChosen := AgeChos   {For reference only, this is the age for person chosen when select = Yes }
          ENDIF                         {if age is changed later this one doesnt change}
          CI_Name   := NameChos
          CI_PERSID := VAL(PersID)
          CI_Age    := VAL(AgeChos)
          CI_Gender := SexChos
      ENDIF
ENDBLOCK

FIELDS
      HHComponent : BHHComponent
