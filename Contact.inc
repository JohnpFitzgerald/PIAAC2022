{Author Name    : Caroline Donegan

 Date written   : June Pilot
 Version        : 1.0

 Description    : Collecting contact details for piaac survey
****************************************************************************************************************************************}
BLOCK BContact

   LOCALS
      I, PhonLen : INTEGER

   AUXFIELDS
      ContName   "Displays name of the contact who has been selected for this household." : STRING[25], EMPTY
      Age        "Displays age of the person who has been selected for this household" : STRING[3]
      PhonTest     : ARRAY [1..20] OF STRING[1]
      PhonProbFlg  : ARRAY [1..20] OF STRING[1]
      PhProbChar   : ARRAY [1..20] OF STRING[9]
      Confirm     {Confirm is an Auxfield to ensure signal works. e.g if you leave interview & return}
                 "Are the following details correct?
                  @/@/@SIf you answer no to this question you will be given the option of amending these details.@S
                  @/@/Contact:@|@| @S^HHComponent.FlNmChos@S, aged @S^HHComponent.AgeChos@S
                  @/@/Phone number@| @S^ConPh@S
                  @/@/Address:@|@|@S^PostalAddr@S" : TYesNo

   FIELDS
      StrtCont   "@S^HHComponent.FlNmChos@S has been selected for the PIAAC interview.
                  @/@/@S@Zi@ZPlease press 1 to enter contact / review details for ^HHComponent.FlNmChos.@S" : TYes, NODK, NORF
      ConPh      "@/@/Could you give me a phone number for @S^HHComponent.FlNmChos@S so that I
                      can arrange an appointment?
                  @/@/@S@Zi@ZThis number may be used by a CSO field supervisor to carry out a quality control call. @S
                  @/@/@S@Zi@Z Try to get a mobile number if possible. @S" : STRING[15],EMPTY, NODK, NORF
      ConfPAddr  "@/@/Is the address above correct for this household?
                  @/@/@S@Zi@Z Choose no to make amendments to the address field. @S " : TYesNo
      PostalAddr  {Read from postal and displayed on screen for confirmation by the interviewer} : STRING[120],EMPTY
      Educat     "@/Please enter @B^HHComponent.NameChos's@B highest level of education.
                  @/@/@S@Zi@ZThis question is very important if the person providing the Screener
                  information is not the person selelcted for interview.@S " : TEducat

   RULES
      StrtCont
      IF (StrtCont = YES) THEN
          ContName.KEEP
          ContName := HHComponent.FlNmChos
          ContName.SHOW
          Age.KEEP
          Age := HHComponent.AgeChos
          Age.Show
          ConPh
          PhonLen := LEN(ConPh)
          IF (PhonLen < 10 ) THEN
             SIGNAL
              (PhonLen > 10) INVOLVING (ConPh)
              "@RError.@R
               @/@XInterviewer Phone number should be 10 digits..please check@X"              
          ENDIF
          PostalAddr.KEEP
          PostalAddr := MainDetails.Postal
          PostalAddr.SHOW
          ConfPAddr
          CHECK
          (ConfPAddr = YES) INVOLVING (ConfPAddr,MainDetails.Postal)
          "@RError.@R
           @/@XInterviewer please press return to amend the address details as required.

           @w@/@/After amendments Press Enter
           @/Then Press End

           @/@/If you are happy with amendments
           @/Scroll to ConfPAddr
           @/Press Enter
           @/If details are correct choose Yes to confirm address details and continue.@W@X"
          IF (HHComponent.EligFlg >0) THEN
              Confirm
          ENDIF
      ENDIF
      IF (Confirm <> EMPTY) THEN
          CHECK
          (Confirm = YES) INVOLVING (ConPh, MainDetails.Postal, HHGrid.PersonID[HHComponent.PersChosen].Person.Age,
                                     HHGrid.PersonID[HHComponent.PersChosen].Person.Surname,
                                     HHGrid.PersonID[HHComponent.PersChosen].Person.Name, Confirm)
         "@RError.@R
          @/@XInterviewer please amend the relevant details for @W^HHComponent.FlNmChos@W@X"
      ENDIF
      Educat

   LAYOUT
      BEFORE StrtCont INFOPANE Contact
                      FIELDPANE Contact
                      GRID Contact
      AFTER ConfPAddr INFOPANE Confirm
                      GRID DefaultGrid
      AFTER Confirm NEWPAGE

      BEFORE Educat INFOPANE Education
      AFTER Educat NEWPAGE

ENDBLOCK

FIELDS
   Contact : BContact
