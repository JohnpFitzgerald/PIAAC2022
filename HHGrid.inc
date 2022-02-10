{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : Creates the Table to gather info on each person
****************************************************************************************************************************************}
   TABLE THHGrid {Table to gather info on each person}

      LOCALS
         LineCount, I : INTEGER


      BLOCK BPersonID
         INCLUDE "Person.inc"

        {FIELDS for Block PersonID declared within the Person.inc file}

         RULES {For BLock PersonID}
            Person

         LAYOUT {For BLock PersonID}
            BEFORE Person INFOPANE Person

      ENDBLOCK


      AUXFIELDS {For Table THHGrid}
         HistFlg                   {Used in the check to make sure only one person marked as hist = yes}  : 0..10

      FIELDS  {For Table THHGrid}
         PersonID : ARRAY [1 .. 20] OF BPersonID

      RULES  {Rules for Table THHGrid}
         FOR LineCount := 1 TO MainDetails.NoPersons DO
             PersonID[LineCount]
         ENDDO
         HistFlg.KEEP
         HistFlg := 0
         FOR I := 1 TO MainDetails.NoPersons DO
            IF (HHGrid.PersonID[I].Person.Hist = YES) THEN
                HistFlg := HistFlg + 1
            ENDIF
         ENDDO
         CHECK                  {Only one person can be marked as Hist = Yes}
        (HistFlg <=1) INVOLVING (HHGrid.PersonID[1].Person.Hist, HHGrid.PersonID[2].Person.Hist,
                                 HHGrid.PersonId[3].Person.Hist, HHGrid.PersonId[4].Person.Hist,
                                 HHGrid.PersonId[5].Person.Hist, HHGrid.PersonId[6].Person.HIst,
                                 HHGrid.PersonId[7].Person.Hist, HHGrid.PersonId[8].Person.HIst,
                                 HHGrid.PersonId[9].Person.HIst, HHGrid.PersonId[10].Person.Hist,
                                 HHGrid.PersonId[11].Person.HIst, HHGrid.PersonId[12].Person.Hist,
                                 HHGrid.PersonId[13].Person.HIst, HHGrid.PersonId[14].Person.Hist,
                                 HHGrid.PersonId[15].Person.HIst, HHGrid.PersonId[16].Person.Hist,
                                 HHGrid.PersonId[17].Person.HIst, HHGrid.PersonId[18].Person.Hist,
                                 HHGrid.PersonId[19].Person.HIst, HHGrid.PersonId[20].Person.Hist)
        "@RError@R@/@X@wOnly one person should be marked as Hist = Yes@w
         @/@/i.e. The person providing the information for the screener is Hist = Yes.
         @/·······All other houehold members should be marked as Hist = No@X"
         IF (MainDetails.NoPersons = 1) THEN
             CHECK
             (HHGrid.PersonId[1].Person.Hist = YES) INVOLVING (MainDetails.CanInterview, HHGrid.PersonId[1].Person.Hist, MainDetails.NoPersons)
             "@RError@R@/@XThere is only one person in this household.
              @/@wThe answer to Hist for ^HHGrid.PersonId[1].Person.Name must be yes.@w
              @/If this is not the case then @wplease return to CanInterview field and answer No to this question.@w
              @/Alternatively you can choose to @wadd another person at the NoPersons question.@w @X"
         ENDIF
         IF (HHGrid.PersonId[MainDetails.NoPersons].Person.Hist <> EMPTY) THEN
             CHECK        {There must be at least one person marked as Hist = Yes}
             (HistFlg >= 1) INVOLVING (MainDetails.CanInterview, HHGrid.PersonId[I].Person.Hist)  {Must be >=1 or incorrect signal shown}
             "@RError@R@/@XThere must be @wat least one person over 16@w in the household providing the
              information to you for this Screener.
              @/If this is not the case then @wplease return to CanInterview field and answer No@w to this question.
              @/Alternatively you can @wchoose yes to Hist for one person in the household.@w@X"
         ENDIF

      LAYOUT {For Table THHGrid}
         BEFORE PersonID GRID Person

   ENDTABLE

FIELDS
   HHGrid : THHGrid
