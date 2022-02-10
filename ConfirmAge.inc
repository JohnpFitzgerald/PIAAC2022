{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : The confirm block is asked before the HHComponent Block
                  ie. before the random person is chosen.
                  Its function is to allow the interviewer confirm the age before the random person is chosen.
 ****************************************************************************************************************************************}
TABLE TConfirmAge

   LOCALS
      I : INTEGER

   BLOCK BConfPers

      AUXFIELDS
         ConfName     {Used as a dispay for confirming ages before random selection} : STRING[40]
         ConfAge     {Used as a dispay for confirming ages before random selection} : 0..110
         ShowEligible {Used as a fill when confirming ages}                          : STRING[35]
         NameAndAge   {Used as a dispay for confirming ages before random selection} : STRING[52]

      FIELDS
         ConfirmAge "Household @S^MainDetails.BlockNo ^MainDetails.LDUNo@S
                     @/The number of people in this household is @S^MainDetails.NoPersons@S
                     @/Can you please confirm the ages for each person in the household @SBEFORE@S moving on to the next section.
                     @/@/These are the ages that will be used to choose the random person for interview.
                     Once the random person is chosen it cannot be changed. " : TYesNo, NODK, NORF
         ConfVal    "This is the age i.e. Age value keyed for the person at the time the PIAAC person is selected." : 0..110,EMPTY

      RULES
         ConfName := HHGrid.PersonId[I].Person.Name
         ConfAge := HHGrid.PersonId[I].Person.Age
         ShowEligible := SUBSTRING(HHGrid.PersonId[I].Person.Txt_Elig,4,46)
         ShowEligible.SHOW
         IF (NameAndAge = EMPTY) THEN
            NameAndAge := 'Please confirm that ' + HHGrid.PersonId[I].Person.Name +' is ' + STR(HHGrid.PersonId[I].Person.Age) + ' years old'
         ENDIF
         NameAndAge.SHOW
         ConfirmAge.KEEP
         IF (ConfirmAge = EMPTY OR ConfirmAge = NO) THEN
             ConfirmAge
         ENDIF
         SIGNAL
         IF (ConfirmAge <> EMPTY) THEN
            (ConfirmAge = YES) INVOLVING (HHGrid.PersonId[I].Person.Age, ConfirmAge)
            "@RWarning@R@/@X@/Please arrow to the persons age below, then choose GoTo
             @/then key in the correct age before moving on to the random selection section.
             @/When you have made your change press @wEnter then END@w to confirm the amended age and move on.@X"
         ENDIF
         ConfVal.KEEP
         IF (ConfirmAge = YES AND ConfVal = EMPTY) THEN
             ConfVal := HHGrid.PersonId[I].Person.Age  {This is the Age val keyed in when the age is confirmed}
         ENDIF                                         {Age could be changed later this is for comparison}
   ENDBLOCK

   FIELDS {Table Fields}
      Ovr16Flg {Used in checking that there is an over 15 person in the household
                eligible field is Ageulated after select Ovr16Flg is used to route to ConfPers & Select} : 0..20
      Ovr65Flg {Used in checking that there is an under 66 person in the household
                eligible field is Ageulated after select Ovr65Flg is used to route to ConfPers & Select} : 0..20
      AgeFlg   {Used in checking that there is an over 15 person in the household}                        : 0..1
      ConfPers {Declaring the Block BConfPers as a field ConfPers}                   : ARRAY [1..20] OF BConfPers

   RULES  {Table Rules}
      Ovr16Flg = 0
      FOR I := 1 TO MainDetails.NoPersons DO
          IF (HHGrid.PersonId[I].Person.Age < 16) AND (HHGrid.PersonId[I].Person.Age >65)THEN
              AgeFlg := 0
          ELSEIF (HHGrid.PersonId[I].Person.Age >15) AND (HHGrid.PersonId[I].Person.Age <66) THEN
              AgeFlg := 1
          ENDIF
          Ovr16Flg := Ovr16Flg + AgeFlg
      ENDDO
      SIGNAL
      IF (HHGrid.PersonId[MainDetails.NoPersons].Person.Age <> EMPTY) THEN
          (Ovr16Flg >0) INVOLVING (MainDetails.NoPersons, HHGrid.PersonId[MainDetails.NoPersons].Person.Age)
           "@RWarning@R@/@XThere is no one in this household aged between 16 and 65 years of age.
            @/@/@wPlease amend one or more of the ages,
            @/or add another eligible household member at NoPersons
            @/or choose suppress then proceed to CloseCM Question to close interview.@w@X"
      ENDIF
      IF (Ovr16Flg  >0) THEN
          FOR I := 1 TO MainDetails.NoPersons DO
              ConfPers[I]
          ENDDO
      ENDIF

ENDTABLE

FIELDS
   ConfirmAge :  TConfirmAge
