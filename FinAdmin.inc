{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : Asks a last question in the Piaac survey Admin section.
***************************************************************************************************************************************}
BLOCK BFinAdmin "Finish Admin Section"

   EXTERNALS {Meta data file .bmi}
      Screener   : ScrLookUp  ('C:\CSO\Piaac\Pilot\Piaac2022Scr')

   LOCALS
      I, LastVisNo : INTEGER

   INCLUDE "PostIntAdmin.inc"

   FIELDS
      VMLastQasked   {This field is updated [IT HOLDS THE LAST QUESTION VARIABLE ASKED]
                      once the user exits the VM after updating a case } : STRING[15]
      VMLatestStatus {This field holds the latest status [paused or Finished] updated
                      once the user exits the VM} : STRING[10]
      SampTyp  {Used in PiaacAdmin Manipula for Front End Tables = Screener.MainDetails.Sample} : STRING[13], EMPTY
      LastVis  {Used in PiaacAdmin Manipula for Front End Tables} : STRING[10],EMPTY
      LastDay  {Used in question text of Finalise question, based on Day value keyed at latest visit} : STRING[9],EMPTY
      LastDat  {Used in question text of Finalise question, based on Dat value keyed at latest visit} : TDATE,EMPTY
      LastTim  {Used in question text of Finalise question, based on Tim value keyed at latest visit} : TIMETYPE,EMPTY
      LastScr  {Used in question text of Finalise question, based on Scr value keyed at latest visit} : TScr
      LastInit {Used in question text of Finalise question, based on Init value keyed at latest visit} : TBQInit
      LastBQ   {Used in question text of Finalise question, based on BackgroundQuestionnaire value keyed at latest visit}   : TBQInit,EMPTY
      LastDoor {Used in question text of Finalise question, based on Doorstep value keyed at latest visit}   : TDoorStep,EMPTY
      LastCore {Used in question text of Finalise question, based on Locator value keyed at latest visit} : TCore,EMPTY
      LastExcr {Used in question text of Finalise question, based on Excr value keyed at latest visit} : TExcr,EMPTY
      LastTyp  {Used in PiaacAdmin Manipula for Front End Tables}  : TContact,EMPTY
      CaseStatus  {Used in question text of Finalise question, based on Scr or Intm values keyed at latest visit} : STRING[80], EMPTY
      LastScrTx   {Used in question text of Finalise question, based on LastScr value}  : STRING[75],EMPTY
      LastInitTx  {Used in question text of Finalise question, based on LastInit value} : STRING[150]
      LastBQTx    {Used in question text of Finalise question, based on LastBQ value}   : STRING[150]
      LastDoorTx  {Used in question text of Finalise question, based on LastCore value} : STRING[150]
      LastCoreTx  {Used in question text of Finalise question, based on LastCore value} : STRING[150]
      LastExcrTx  {Used in question text of Finalise question, based on LastExcr value} : STRING[150]
      Finalise   "Summary details for ·@S^MainAdmin.BlockNo ·^MainAdmin.LduNo@S
                  @/@/PersID @S^Screener.HHComponent.PersId@S
                  @/Contact Name @S^Screener.HHComponent.FlNmChos@S
                  @/@/Interview Final outcomes from last visit which took place on @S^LastDay ^LastDat at ^LastTim@S
                  @/@/PIAAC Status @|@| @S^VMLatestStatus@S @S^VMLastQasked@S
                  @/Case Status @|@| @S^CaseStatus@S
                  @/@/Screener @|@| @S^LastScrTx@S
                  @/Case Initialisation @| @S^LastInitTx@S
                  @/DoorStep @|@| @S^LastDoorTx@S
                  @/Background Questionnaire @|@|@| @S^LastBQTx@S
                  @/Locator @|@|@| @S^LastCoreTx@S
                  @/Exercise @|@| @S^LastExcrTx@S
                  @/@/@SDo you wish to finalise this case?@S" : TYesNoFin


   RULES
      IF Screener.SEARCH(MainAdmin.BlockNo, MainAdmin.LduNo) THEN
         Screener.READ
      ENDIF

      SampTyp.KEEP
     { SampTyp := Screener.MainDetails.Sample   }
      FOR I := 1 TO 10 DO
         IF (HHCall.CallGrid.Call[I].NewVisit = NO) THEN
            LastVisNo := I
         ENDIF
      ENDDO
      VMLatestStatus.KEEP
      VMLastQasked.KEEP
      LastVis.KEEP
      LastDat.KEEP
      LastTim.KEEP
      LastDay.KEEP
      LastScr.KEEP
      LastScrTx.KEEP
      LastInit.KEEP
      LastInitTx.KEEP
      LastBQ.KEEP
      LastBQTx.KEEP
      LastDoor.KEEP
      LastDoorTx.KEEP
      LastCore.KEEP
      LastCoreTx.KEEP
      LastExcr.KEEP
      LastExcrTx.KEEP
      LastTyP.KEEP
      IF (HHCall.CallGrid.Call[LastVisNo].NewVisit = NO) THEN
          LastVis  := HHCall.CallGrid.Call[LastVisNo].Visit
          LastDay  := HHCall.CallGrid.Call[LastVisNo].Day
          LastDat  := HHCall.CallGrid.Call[LastVisNo].Date
          LastTim  := HHCall.CallGrid.Call[LastVisNo].Time
          LastScr  := HHCall.CallGrid.Call[LastVisNo].Screener
          LastInit := HHCall.CallGrid.Call[LastVisNo].Initial
          LastBQ   := HHCall.CallGrid.Call[LastVisNo].BackgroundQuestionnaire
          LastDoor := HHCall.CallGrid.Call[LastVisNo].Doorstep
          LastCore := HHCall.CallGrid.Call[LastVisNo].Locator
          LastExcr := HHCall.CallGrid.Call[LastVisNo].Exercise
          LastTyp  := HHCall.CallGrid.Call[LastVisNo].CallType
       ENDIF
       IF (LastScr = C1) THEN
           LastScrTx := 'Complete - 1 sample person selected'  {Answers are long and look odd on question screen so have}
       {ELSEIF (LastScr = C2) THEN                              {included carriage returns in the answer lists in the .lib file.}
           LastScrTx := 'Complete - 2 sample persons selected'} {These won't work in the screen text in the Finalise question so}
       ELSEIF (LastScr = PB) THEN                              {assigning the original text values here for}
           LastScrTx := 'Partial complete / break-off'         {LastScr, LastBQ, LastInit, LastCore and LastExcr}
       ELSEIF (LastScr = RH) THEN
           LastScrTx := 'Refusal by household member'
       ELSEIF (LastScr = RG) THEN
           LastScrTx := 'Refusal by gatekeeper'
       ELSEIF (LastScr = LP) THEN
           LastScrTx := 'Language barrier'
       ELSEIF (LastScr = LM) THEN
           LastScrTx := 'Learning / mental disability'
       ELSEIF (LastScr = HI) THEN
           LastScrTx := 'Hearing impairment'
       ELSEIF (LastScr = BV) THEN
             LastScrTx := 'Blindness / visual impairment'
       ELSEIF (LastScr = SI) THEN
           LastScrTx := 'Speech impairment'
       ELSEIF (LastScr = PD) THEN
           LastScrTx := 'Physical disability'
       ELSEIF (LastScr = OD) THEN
           LastScrTx := 'Other disability'
       ELSEIF (LastScr = OU) THEN
           LastScrTx := 'Other (unspecified) e.g. sickness falsification or unusual circumstances'
       ELSEIF (LastScr = CN) THEN
           LastScrTx := 'Complete - no eligible sample persons'
       ELSEIF (LastScr = UL) THEN
           LastScrTx := 'Unable to locate dwelling unit'
       ELSEIF (LastScr = MX) THEN
           LastScrTx := 'Maximum number of calls i.e. a household member not successfully contacted'
       ELSEIF (LastScr = DC) THEN
           LastScrTx := 'Dwelling unit under construction'
       ELSEIF (LastScr = TA) THEN
           LastScrTx := 'Temporarily absent / unavailable during field period'
       ELSEIF (LastScr = VU) THEN
           LastScrTx := 'Vacant dwelling unit or holiday home'
       ELSEIF (LastScr = DA) THEN
          LastScrTx := 'Duplication - already interviewed'
       ELSEIF (LastScr = AN) THEN
          LastScrTx := 'Address not a dwelling unit'
       ELSEIF (LastScr = IP) THEN
          LastScrTx := 'Interview Pending'
       ELSEIF (LastScr = EMPTY) THEN
          LastScrTx := ''
       ENDIF
       IF (LastInit = CP) THEN
           LastInitTx := 'Complete'
       ELSEIF (LastInit = PB) THEN
           LastInitTx := 'Partial complete / break-off'
       ELSEIF (LastInit = RS) THEN
           LastInitTx := 'Refusal by sample person e.g. refusal to participate due to time constraints or lack of interest'
       ELSEIF (LastInit = RO) THEN
           LastInitTx := 'Refusal by other person'
       ELSEIF (LastInit = LP) THEN
           LastInitTx := 'Language barrier'
       ELSEIF (LastInit = RW) THEN
           LastInitTx := 'Reading and writing difficulty'
       ELSEIF (LastInit = LM) THEN
           LastInitTx := 'Learning / mental disability'
       ELSEIF (LastInit = HI) THEN
          LastInitTx := 'Hearing impairment'
       ELSEIF (LastInit = BV) THEN
          LastInitTx := 'Blindness / visual impairment'
       ELSEIF (LastInit = SI) THEN
          LastInitTx := 'Speech impairment'
       ELSEIF (LastInit = PD) THEN
          LastInitTx := 'Physical disability'
       ELSEIF (LastInit = OD) THEN
          LastInitTx := 'Other disability'
       ELSEIF (LastInit = OU) THEN
          LastInitTx := 'Other (unspecified) e.g. sickness falsification or unusual circumstances'
       ELSEIF (LastInit = DT) THEN
          LastInitTx := 'Death'
       ELSEIF (LastInit = MX) THEN
          LastInitTx := 'Maximum number of calls e.g. sample person not successfully contacted'
       ELSEIF (LastInit = MW) THEN
          LastInitTx := 'Moved within the country but not successfully located by the interviewer'
       ELSEIF (LastInit = TA) THEN
          LastInitTx := 'Temporarily absent / unavailable during field period'
       ELSEIF (LastInit = IL) THEN
          LastInitTx := 'Not in target population i.e. not in age range or moved outside the country or in to an institution'
       ELSEIF (LastInit = DA) THEN
          LastInitTx := 'Duplication - already interviewed'
       ELSEIF (LastInit = TP) THEN
          LastInitTx := 'Technical problem'
       ELSEIF (LastInit = IP) THEN
          LastInitTx := 'Interview Pending'
       ELSEIF (LastInit = EMPTY) THEN
          LastInitTx := ''
       ENDIF
       IF (LastBQ = CP) THEN
           LastBQTx := 'Complete'
       ELSEIF (LastBQ = PB) THEN
           LastBQTx := 'Partial complete / break-off'
       ELSEIF (LastBQ = RS) THEN
           LastBQTx := 'Refusal by sample person'
       ELSEIF (LastBQ = RO) THEN
           LastBQTx := 'Refusal by other person'
       ELSEIF (LastBQ = LP) THEN
           LastBQTx := 'Language barrier'
       ELSEIF (LastBQ = RW) THEN
           LastBQTx := 'Reading and writing difficulty'
       ELSEIF (LastBQ = LM) THEN
           LastBQTx := 'Learning / mental disability'
       ELSEIF (LastBQ = HI) THEN
           LastBQTx := 'Hearing impairment'
       ELSEIF (LastBQ = BV) THEN
           LastBQTx := 'Blindness / visual impairment'
       ELSEIF (LastBQ = SI) THEN
           LastBQTx := 'Speech impairment'
       ELSEIF (LastBQ = PD) THEN
           LastBQTx := 'Physical disability'
       ELSEIF (LastBQ = OD) THEN
           LastBQTx := 'Other disability'
       ELSEIF (LastBQ = OU) THEN
           LastBQTx := 'Other (unspecified) e.g. sickness falsification or unusual circumstances'
       ELSEIF (LastBQ = DT) THEN
           LastBQTx := 'Death'
       ELSEIF (LastBQ = MX) THEN
           LastBQTx := 'Maximum number of calls e.g. sample person not successfully contacted'
       ELSEIF (LastBQ = MW) THEN
          LastBQTx := 'Moved within the country but not successfully located by the interviewer'
       ELSEIF (LastBQ = TA) THEN
           LastBQTx := 'Temporarily absent / unavailable during field period'
       ELSEIF (LastBQ = IL) THEN
           LastBQTx := 'Not in target population i.e. not in age range or moved outside the country or in to an institution'
       ELSEIF (LastBQ = DA) THEN
           LastBQTx := 'Duplication - already interviewed'
       ELSEIF (LastBQ = TP) THEN
           LastBQTx := 'Technical problem'
       ELSEIF (LastBQ = IP) THEN
           LastBQTx := 'Interview Pending'
       ELSEIF (LastBQ = EMPTY) THEN
           LastBQTx := ''
       ENDIF

       IF (LastDoor = CP) THEN
           LastDoorTx := 'Complete'
       ELSEIF (LastDoor = PB) THEN
           LastDoorTx := 'Partial complete / break-off'
       ELSEIF (LastDoor = RS) THEN
           LastDoorTx := 'Refusal by sample person'
       ELSEIF (LastDoor = UL) THEN
           LastDoorTx := 'Unaccommodated language'
       ELSEIF (LastDoor = OU) THEN
           LastDoorTx := 'Other (unspecified)'
       ELSEIF (LastDoor = MX) THEN
           LastDoorTx := 'Maximum number of calls'
       ELSEIF (LastDoor = TP) THEN
           LastDoorTx := 'Technical problem'
       ELSEIF (LastDoor = EMPTY) THEN
           LastDoorTx := ''
       ENDIF

       IF (LastCore = CP) THEN
           LastCoreTx := 'Complete'
       ELSEIF (LastCore = PB) THEN
           LastCoreTx := 'Partial complete / break-off'
       ELSEIF (LastCore = RS) THEN
           LastCoreTx := 'Refusal by sample person e.g. for refusal to participate due to time constraints or lack of interest'
       ELSEIF (LastCore = RO) THEN
           LastCoreTx := 'Refusal by other person'
       ELSEIF (LastCore = LS) THEN
           LastCoreTx := 'Lacks the skills to use the tablet'
       ELSEIF (LastCore = LP) THEN
           LastCoreTx := 'Language barrier'
       ELSEIF (LastCore = RW) THEN
           LastCoreTx := 'Reading and writing difficulty'
       ELSEIF (LastCore = LM) THEN
           LastCoreTx := 'Learning / mental disability'
       ELSEIF (LastCore = HI) THEN
           LastCoreTx := 'Hearing impairment'
       ELSEIF (LastCore = BV) THEN
           LastCoreTx := 'Blindness / visual impairment'
       ELSEIF (LastCore = SI) THEN
           LastCoreTx := 'Speech impairment'
       ELSEIF (LastCore = PD) THEN
           LastCoreTx := 'Physical disability'
       ELSEIF (LastCore = OD) THEN
           LastCoreTx := 'Other disability'
       ELSEIF (LastCore = OU) THEN
           LastCoreTx := 'Other (unspecified) e.g. sickness falsification or unusual circumstances'
       ELSEIF (LastCore = DT) THEN
           LastCoreTx := 'Death'
       ELSEIF (LastCore = MX) THEN
            LastCoreTx := 'Maximum number of calls; e.g. respondent not successfully contacted'
       ELSEIF (LastCore = TA) THEN
            LastCoreTx := 'Temporarily absent / unavailable during field period'
       ELSEIF (LastCore = DA) THEN
            LastCoreTx := 'Duplication - already interviewed'
       ELSEIF (LastCore = TP) THEN
            LastCoreTx := 'Technical problem'
       ELSEIF (LastCore = EMPTY) THEN
            LastCoreTx := ''
       ENDIF
       {Either a doorstep of a Core should be completed}
       IF (LastCore <> EMPTY) AND (LastDoor = EMPTY) THEN
           LastDoorTX := 'Not Applicable'
       ENDIF
       IF (LastExcr = CP) THEN
            LastExcrTx := 'Complete'
       ELSEIF (LastExcr = PB) THEN
            LastExcrTx := 'Partial complete / break-off'
       ELSEIF (LastExcr = RS) THEN
           LastExcrTx := 'Refusal by sample person'
       ELSEIF (LastExcr = RO) THEN
           LastExcrTx := 'Refusal by other person'
       ELSEIF (LastCore = LS) THEN
           LastExcrTx := 'Lacks the skills to use the tablet'
       ELSEIF (LastExcr = LP) THEN
            LastExcrTx := 'Language barrier'
       ELSEIF (LastExcr = RW) THEN
           LastExcrTx := 'Reading and writing difficulty'
       ELSEIF (LastExcr = LM) THEN
           LastExcrTx := 'Learning / mental disability'
       ELSEIF (LastExcr = HI) THEN
           LastExcrTx := 'Hearing impairment'
       ELSEIF (LastExcr = BV) THEN
            LastExcrTx := 'Blindness / visual impairment'
       ELSEIF (LastExcr = SI) THEN
            LastExcrTx := 'Speech impairment'
       ELSEIF (LastExcr = PD) THEN
            LastExcrTx := 'Physical disability'
       ELSEIF (LastExcr = OD) THEN
            LastExcrTx := 'Other disability'
       ELSEIF (LastExcr = OU) THEN
            LastExcrTx := 'Other (unspecified) e.g. sickness or falsification or unusual circumstances'
       ELSEIF (LastExcr = DT) THEN
            LastExcrTx := 'Death'
       ELSEIF (LastExcr = MX) THEN
            LastExcrTx := 'Maximum number of calls e.g. respondent not successfully contacted'
       ELSEIF (LastExcr = TA) THEN
            LastExcrTx := 'Temporarily absent / unavailable during field period'
       ELSEIF (LastExcr = DA) THEN
            LastExcrTx := 'Duplication - already interviewed'
       ELSEIF (LastExcr = TP) THEN
            LastExcrTx := 'Technical problem'
       ELSEIF (LastExcr = EMPTY) THEN
           LastExcrTx := ''
       ENDIF
       CaseStatus.KEEP
       IF (HHCall.CallGrid.Call[LastVisNo].Screener = C1) THEN
          CaseStatus := 'Complete - 1 sample person selected'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = PB) THEN
          CaseStatus := 'Partial complete / break-off'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = RH) THEN
          CaseStatus := 'Refusal by household member'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = RG) THEN
          CaseStatus := 'Refusal by gatekeeper'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = LP) THEN
          CaseStatus := 'Language barrier'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = LM) THEN
          CaseStatus := 'Learning / mental disability'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = HI) THEN
          CaseStatus := 'Hearing impairment'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = BV) THEN
          CaseStatus := 'Blindness / visual impairment'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = SI) THEN
          CaseStatus := 'Speech impairment'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = PD) THEN
          CaseStatus := 'Physical disability'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = OD) THEN
          CaseStatus := 'Other disability'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = OU) THEN
          CaseStatus := 'Other (unspecified) e.g. sickness falsification or unusual circumstances'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = CN) THEN
          CaseStatus := 'Complete - no eligible sample persons'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = UL) THEN
          CaseStatus := 'Unable to locate dwelling unit'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = MX) THEN
          CaseStatus := 'Maximum number of calls i.e. a household member not successfully contacted'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = DC) THEN
          CaseStatus := 'Dwelling unit under construction'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = TA) THEN
          CaseStatus := 'Temporarily absent / unavailable during field period'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = VU) THEN
          CaseStatus := 'Vacant dwelling unit or holiday home or temporary residence'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = DA) THEN
          CaseStatus := 'Duplication - already interviewed'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = AN) THEN
          CaseStatus := 'Address not a dwelling unit'
       ELSEIF (HHCall.CallGrid.Call[LastVisNo].Screener = EMPTY) THEN
          IF (HHCall.CallGrid.Call[LastVisNo].Interim = AP) THEN
              CaseStatus := 'Call back - appointment'
          ELSEIF (HHCall.CallGrid.Call[LastVisNo].Interim = CB) THEN
              CaseStatus := 'Call back - no appointment'
	      ELSEIF (HHCall.CallGrid.Call[LastVisNo].Interim = NH) THEN
              CaseStatus := 'Not at home'
          ELSEIF (HHCall.CallGrid.Call[LastVisNo].Interim = AV) THEN
              CaseStatus := 'Avoidance'
          ELSEIF (HHCall.CallGrid.Call[LastVisNo].Interim = LO) THEN
              CaseStatus := 'Locked / gated dwelling unit'
	      ELSEIF (HHCall.CallGrid.Call[LastVisNo].Interim = RB) THEN
              CaseStatus := 'Initial refusal'
          ELSEIF (HHCall.CallGrid.Call[LastVisNo].Interim = IL) THEN
              CaseStatus := 'Illness / disability'
          ELSEIF (HHCall.CallGrid.Call[LastVisNo].Interim = OT) THEN
              CaseStatus := 'Other - Proceed to code detailed Screener outcome'
          ENDIF
       ENDIF

       Finalise.KEEP
       Finalise
       IF (Finalise = YES) THEN
           IF (HHCall.CallGrid.Call[LastVisNo].Exercise = CP OR HHCall.CallGrid.Call[LastVisNo].Exercise = PB) THEN
               PostIntAdmin
           ENDIF

          CHECK
          (HHCall.CallGrid.Call[LastVisNo].Interim = OT) INVOLVING (HHCall.CallGrid.Call[LastVisNo].Screener, HHCall.CallGrid.Call[LastVisNo].Interim)
          "@RError@R
           @/@/@XIf Finalise is Yes and the Screener field has not yet been completed, you must
           @/change the interim code to 8. 'Other, including moved on to PIAAC interview.'
           @/@/You will then be routed to the Screener outcome codes before finalising the case@X"
       ENDIF
   LAYOUT
      BEFORE Finalise INFOPANE Finalise

ENDBLOCK

FIELDS
   FinAdmin : BFinAdmin
