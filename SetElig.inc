{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : This block had been placed within the person block of the HHGrid table, calculating an eligible and
                  a RndLine1 value for each person within that table. This caused problems in the field when a person
                  was accidentally keyed in as over 15 then when changed back to a non eligible under 15 the RndLine1
                  wasn't changed to reflect the new eligibility, Taking this out of the table and introducing a lead
                  in question / confirmation question for the selection should hopefully fix this
****************************************************************************************************************************************}
BLOCK BSetElig

   LOCALS
       I : INTEGER

   BLOCK BEligible

      FIELDS {For Block Eligible}
         Eligible   : TYesNo
         RndLine    : INTEGER[4]     {Result of the random function used with RndInd field}
         RndLine1   : INTEGER[4]     {1 added to RndLine to make sure 0 is not selected}

      RULES  {For Block Eligible}
      Eligible.KEEP
         IF (SetElig.Select = YES) THEN
             IF (Eligible = EMPTY) THEN
                 IF (HHGrid.PersonId[I].Person.Age <> EMPTY) THEN
                    IF (HHGrid.PersonId[I].Person.Age >= 16 AND HHGrid.PersonId[I].Person.Age <= 65) THEN
                         Eligible := YES
                    ENDIF
                    IF (HHGrid.PersonId[I].Person.Age <=15 OR HHGrid.PersonId[I].Person.Age >=66)
                        OR (HHGrid.PersonId[I].Person.Age = DK) OR (HHGrid.PersonId[I].Person.Age = RF)
                        OR (HHGrid.PersonId[I].Person.Age = EMPTY) THEN
                        Eligible := NO
                    ENDIF
                 ENDIF
             ENDIF

             RndLine.KEEP
             IF (Eligible <> EMPTY) THEN
                 IF (RndLine = EMPTY) THEN
                    IF (Eligible = YES) THEN
                        RndLine := RANDOM(1000)
                    ELSEIF (Eligible = NO) THEN
                        RndLine := 1000
                    ENDIF
                 ENDIF
                 RndLine1.KEEP                      {This is the RANDOM NUMBER selected for each person}
                 IF (RndLine <> EMPTY AND RndLine1 = EMPTY) THEN
                     RndLine1 := RndLine + 1        {Add 1 to the random number chosen so that 0 excluded and highest number included}
                 ENDIF
             ENDIF
         ENDIF
   ENDBLOCK

FIELDS {For Block SetElig}
   Select "@S@Zi@Z Once you answer YES to this question then the random person cannot be changed.
           @/····Please make sure the household details listed below are correct before continuing.
           @/····If you need to change details then go back and change ages or names.@S
           @/@/······Are you ready to select the person to be interviewed for PIAAC?
           @/@/······This household is @S^MainDetails.BlockNo ^MainDetails.LDUNo.@S @S^MainDetails.Txt_Pers@S in the household.
           @/@/@S^HHGrid.PersonId[1].Person.Txt_Name ^HHGrid.PersonId[1].Person.Txt_Age ^HHGrid.PersonId[1].Person.Txt_Elig
           @/^HHGrid.PersonId[2].Person.Txt_Name ^HHGrid.PersonId[2].Person.Txt_Age ^HHGrid.PersonId[2].Person.Txt_Elig
           @/^HHGrid.PersonId[3].Person.Txt_Name ^HHGrid.PersonId[3].Person.Txt_Age ^HHGrid.PersonId[3].Person.Txt_Elig
           @/^HHGrid.PersonId[4].Person.Txt_Name ^HHGrid.PersonId[4].Person.Txt_Age ^HHGrid.PersonId[4].Person.Txt_Elig
           @/^HHGrid.PersonId[5].Person.Txt_Name ^HHGrid.PersonId[5].Person.Txt_Age ^HHGrid.PersonId[5].Person.Txt_Elig
           @/^HHGrid.PersonId[6].Person.Txt_Name ^HHGrid.PersonId[6].Person.Txt_Age ^HHGrid.PersonId[6].Person.Txt_Elig
           @/^HHGrid.PersonId[7].Person.Txt_Name ^HHGrid.PersonId[7].Person.Txt_Age ^HHGrid.PersonId[7].Person.Txt_Elig
           @/^HHGrid.PersonId[8].Person.Txt_Name ^HHGrid.PersonId[8].Person.Txt_Age ^HHGrid.PersonId[8].Person.Txt_Elig
           @/^HHGrid.PersonId[9].Person.Txt_Name ^HHGrid.PersonId[9].Person.Txt_Age ^HHGrid.PersonId[9].Person.Txt_Elig
           @/^HHGrid.PersonId[10].Person.Txt_Name ^HHGrid.PersonId[10].Person.Txt_Age ^HHGrid.PersonId[10].Person.Txt_Elig
           @/^HHGrid.PersonId[11].Person.Txt_Name ^HHGrid.PersonId[11].Person.Txt_Age ^HHGrid.PersonId[11].Person.Txt_Elig
           @/^HHGrid.PersonId[12].Person.Txt_Name ^HHGrid.PersonId[12].Person.Txt_Age ^HHGrid.PersonId[12].Person.Txt_Elig
           @/^HHGrid.PersonId[13].Person.Txt_Name ^HHGrid.PersonId[13].Person.Txt_Age ^HHGrid.PersonId[13].Person.Txt_Elig
           @/^HHGrid.PersonId[14].Person.Txt_Name ^HHGrid.PersonId[14].Person.Txt_Age ^HHGrid.PersonId[14].Person.Txt_Elig
           @/^HHGrid.PersonId[15].Person.Txt_Name ^HHGrid.PersonId[15].Person.Txt_Age ^HHGrid.PersonId[15].Person.Txt_Elig
           @/^HHGrid.PersonId[16].Person.Txt_Name ^HHGrid.PersonId[16].Person.Txt_Age ^HHGrid.PersonId[16].Person.Txt_Elig
           @/^HHGrid.PersonId[17].Person.Txt_Name ^HHGrid.PersonId[17].Person.Txt_Age ^HHGrid.PersonId[17].Person.Txt_Elig
           @/^HHGrid.PersonId[18].Person.Txt_Name ^HHGrid.PersonId[18].Person.Txt_Age ^HHGrid.PersonId[18].Person.Txt_Elig
           @/^HHGrid.PersonId[19].Person.Txt_Name ^HHGrid.PersonId[19].Person.Txt_Age ^HHGrid.PersonId[19].Person.Txt_Elig
           @/^HHGrid.PersonId[20].Person.Txt_Name ^HHGrid.PersonId[20].Person.Txt_Age@S
           ^HHGrid.PersonId[20].Person.Txt_Elig" : TYesNo, NODK, NORF
   Eligible : Array [1..20] OF BEligible

RULES {For Block SetElig}
   Select.KEEP
   IF (Select = EMPTY OR Select = NO) THEN
       Select
   ELSEIF (Select <> EMPTY) THEN
       Select.SHOW
   ENDIF

   FOR I := 1 TO MainDetails.NoPersons DO
       Eligible[I]
   ENDDO

   LAYOUT {For Block SetElig}
      BEFORE Select
         INFOPANE SelectPers
      AFTER Select
         INFOPANE Survey

ENDBLOCK

FIELDS
   SetElig : BSetElig
