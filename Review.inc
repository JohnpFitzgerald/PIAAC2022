{Author Name    : Johgn FItzgerald

 Date written   : 2022 Pilot
 Version        : 1.0

 Description    : Creates the Case Management Tab part of the PIAAC Pilot Screener survey
                  This is data collected at MainDetails Block which is filled into some admin/case management fields
                  to be shown in a separate tab at any stage throughout the survey

****************************************************************************************************************************************}
BLOCK BReview "Review Case"

   AUXFIELDS
      CloseCM      "@/@S@Zi@Z Do you want to close the case review and continue?
                    @/@/ IF YOU WISH TO AMEND DETAILS CHOOSE NO @S then make the relevant amendments" : TYesNo

   FIELDS
      PiaacFile    "@/@/@S@Zi@Z PIAAC File Status@S": STRING[7], EMPTY {Indicator to determine if Piaac zip file has been created}
      CM_BlockNumber   "@/@/@S@Zi@Z This is the number already entered for this household@S" : STRING[4], EMPTY {key}
      CM_LDUNumber    "@/@/@S@Zi@Z This is the Household number already entered for this household@S"   : STRING[3], EMPTY  {key}
      CM_IntvwrNo  "@/@/@S@Zi@Z This is the interviewer number already entered for this household@S" : STRING[3], EMPTY
      CM_ID         "@/@/@S@Zi@Z Unique ID for the PDS evaluation@S" :STRING[11], EMPTY
      CM_TeamID    "@/@/@S@Zi@Z This is the Team ID number already entered for this household@S" : STRING[2], EMPTY
      CM_Sample    "@/@/@S@Zi@Z This is the Sample type recorded for this household@S" : STRING[13], EMPTY
      CM_Postal    "@/@/@S@Zi@Z This is the address which has been confirmed for this household@S" : STRING[120], EMPTY

   RULES
      CloseCM
      IF (CloseCM <> EMPTY) THEN
          CHECK
         (CloseCM = YES) INVOLVING (MainDetails.IntvwrNo, MainDetails.TeamID, MainDetails.Postal, CloseCM)
         "@RError@R@/@XPlease make the relevant amendment.
          @/@/When making amendments please choose from the list below.
          @/@/ When finished PRESS THE END KEY ON YOUR KEYBOARD to get back to CloseCM field then
          @/Choose YES to close and exit.
          @/or choose NO to continue and make further amendments.@X"
      ENDIF
      CM_BlockNumber.KEEP
      CM_BlockNumber := MainDetails.BlockNo
      CM_BlockNumber.SHOW
      CM_LDUNumber.KEEP
      CM_LDUNumber := MainDetails.LDUNo
      CM_LDUNumber.SHOW
      CM_ID.KEEP
      CM_ID := HHComponent.PiaacID
      CM_ID.SHOW
      CM_IntvwrNo.KEEP
      CM_IntvwrNo := MainDetails.IntvwrNo
      CM_IntvwrNo.SHOW
      CM_TeamID.KEEP
      CM_TeamID := MainDetails.TeamID
      CM_TeamID.SHOW
      CM_Postal.KEEP
      CM_Postal  := Contact.PostalAddr
      CM_Postal.SHOW
      PiaacFile.KEEP

      IF (PiaacFile = 'Created') THEN
          PiaacFile.SHOW
      ENDIF
      IF (PiaacFile = EMPTY) AND (SetElig.Select = Yes) AND (CloseCM = Yes) THEN
         CreatePiaacJSON(MainDetails.BlockNo, MainDetails.LDUNo, HHComponent.PiaacID, PiaacFile)
         PiaacFile := 'Created'
      ENDIF

      LAYOUT
         BEFORE CloseCM GRID Review
         BEFORE CM_Sample FIELDPANE Review
         BEFORE CloseCM INFOPANE Person

ENDBLOCK

FIELDS
   Review : BReview
