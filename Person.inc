{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : The person block is contained within the PersonID block and looped in the Table HHGrid
****************************************************************************************************************************************}
BLOCK BPerson

    LOCALS
       J, NameLen         : INTEGER   {Using J as a local instead of the usual i, because i is used as a fill for interviewer instruction symbol at Txt_ResNo3}

    AUXFIELDS
       Txt_Age    {Used as fill in select question}      : STRING[13]
       Txt_Name    {Used as fill in select questino}      : STRING[42]
       Txt_Elig    {Used as fill in confirm age section}  : STRING[50]
       Txt_ResNo1  {Used as fill in Name question}        : STRING[120]
       Txt_ResNo2  {Used as fill in Name question}        : STRING[120]
       Txt_ResNo3  {Used as fill in Name question}        : STRING[1]
       NameTest        : ARRAY [1..14] OF STRING[1]
       NameProbFlg     : ARRAY [1..14] OF STRING[1]
       NmProbChar      : ARRAY [1..14] OF STRING[9]

    FIELDS
       Line      {This is the persons line number within the HHGrid Table}      : 01..20
       Name      "@/@/Please identify the person by keying in their first name.
                  @/@/@S@Z^Txt_ResNo3@Z ^Txt_ResNo1
                  @/^Txt_ResNo2@S" : STRING[14], NODK, NORF
       Surname   "@/@/Please enter @S^NAME's@S surname." : STRING[21], EMPTY
       Gender       "@/@/Please enter @S^NAME's@S gender." : TSex, NODK, NORF
       Age      "@/@/Please agree @S^NAME's@S current age and enter it here.
                  @/@/If you are amending / confirming an age then press Page Down to return
                  to the confirmation section."          : 0..110, NODK, NORF
       Hist      "@/@/Is @S^NAME@S providing the information to you for this Screener?" : TYesNo, NODK, NORF

    RULES
       Line := LineCount
       IF (Line = 1) THEN
          Txt_ResNo3 := 'i'
          IF (MainDetails.NoPersons = 1) THEN
             Txt_ResNo1 := 'If there is more than 1 resident in this household please go back to NoPersons and change accordingly.'
          ELSEIF (MainDetails.NoPersons >1) THEN
             Txt_ResNo1 := 'Please complete details for all ' + STR(MainDetails.NoPersons) + ' residents in this household.'
          ENDIF
          IF (MainDetails.NoPersons = 1) THEN
             Txt_ResNo2 := ' '
          ELSEIF (MainDetails.NoPersons >1) THEN
             Txt_ResNo2 := 'If there are more or less than ' + STR(MainDetails.NoPersons) + ' residents please go back to NoPersons and change accordingly.'
          ENDIF
       ENDIF
       Name
       Name := UpperCase(Name)
       NameLen := LEN(Name)
       FOR J := 1 TO 14 DO
          IF J <= NameLen THEN
             NameTest[J] := SUBSTRING(Name,J,1)                 {Problems with certain characters when reading in the }
             IF (NameTest[J] >= 'A' AND NameTest[J] <= 'Z') OR  {name field to the xml file needed to open the vm piaac}
                (NameTest[J] >= 'a' AND NameTest[J] <= 'z') OR  {@ " > < & cause probs also fadas in names}
                (NameTest[J] = '.') OR                          {Can remove the offending chars from the lookup but interviewers}
                (NameTest[J] = ' ') THEN                        {could still accidentally key incorrect chars. To avoid this}
                 NameProbFlg[J] := 'O'                          {There are checks on Name to tie down to a-z, A-Z, . and space}
             ELSE
                 NameProbFlg[J] := 'P'
                 NmProbChar[J]  := NameTest[J]
                 IF NmProbChar[J] = '@' THEN               {The @ character doesn't show in the Check text so added 'character'}
                    NmProbChar[J] := 'character'            {instead of having a blank appear}
                 ENDIF
             ENDIF
             CHECK
             (NameProbFlg[J] = 'O') INVOLVING (Name)
             "@RError@R @XThere is a problem in the Name field.
              @/The @w^NmProbChar[J]@w keyed at position @w^J@w is not allowed.
              @/@/@wPlease edit the name field to remove the ^NmProbChar[J]
              @/Also please make sure the rest of the name only contains Letters or Full Stops@w.
              @/@/Unfortunately no other punctuation e.g. apostrophe or fadas etc. can be accomodated.
              @/These symbols cause problems when loading the Name into the PIAAC vm questionnaire. @X"
          ENDIF
       ENDDO
       Surname.KEEP
       Surname
       Surname := Uppercase(Surname)
       Gender.KEEP
       Gender
       Age
       IF (Age <> EMPTY) THEN
           SIGNAL
          (Age <100)
          "@RWarning.@R
           @/@XInterviewer are you sure this person is @w^Age@w years of age?@X"
       ENDIF
       IF (Age <> EMPTY) THEN               {Used as fill in select question}
           Txt_Age := 'aged ' + STR(Age)   {No coding for DK or RF as these are not allowed for Age}
       ELSEIF (Age = EMPTY) THEN
           Txt_Age := ' '
       ELSEIF (Age >0) THEN
           Txt_Age := 'aged ' + STR(Age)
       ENDIF
       Hist.KEEP
       Hist
       IF (Hist = YES) THEN
           CHECK
           (Age >15) INVOLVING (Hist, Age)
            "@RError.@R
             @/@XInterviewer this person is @w^Age@w years of age.
             @/Hist for this person should be marked as @wHist = No.@w
             @/@wThe person providing the information to you for this Screener should be 16 years of age or over@w@X"
       ENDIF
       IF (Name <> EMPTY) THEN               {Used as fill in select question}
           Txt_Name := STR(Line) + '. ' + Name + ' ' + Surname
       ELSEIF (Name = DK) THEN
           Txt_Name := 'Name not known'
       ELSEIF (Name = RF) THEN
           Txt_Name := 'Name Refused'
       ELSEIF (Name = EMPTY) THEN
           Txt_Name := ' '
       ENDIF
       IF (MainDetails.NoPersons >1) THEN      {Used as fill in confirm age section}
           IF (Age >15 AND Age <66) THEN   {No coding for DK or RF as these are not allowed for Age}
               Txt_Elig := 'is ELIGIBLE for PIAAC interview'
           ELSEIF (Age <16 OR Age >65) THEN
               Txt_Elig := 'is NOT ELIGIBLE for PIAAC interview'
           ENDIF
       ELSEIF (MainDetails.NoPersons = 1) THEN
           IF (Age >15 AND Age <66) THEN
               Txt_Elig := ' is THE ONLY PERSON ELIGIBLE for PIAAC interview'
           ELSEIF (Age <16 OR Age >65) THEN
               Txt_Elig := ' is NOT ELIGIBLE for PIAAC interview'
           ENDIF
       ENDIF
ENDBLOCK

FIELDS
   Person : BPerson
