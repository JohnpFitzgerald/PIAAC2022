{Author Name    : John Fitzgerald
 Date written   : MaY 2022
 Version        : 0.11

 Description    : Creates library for Pilot PIAAC 2022 Survey Survey manipula to create lookup file
****************************************************************************************************************************************}
TYPE
       TOtherPersPres = (NP "No one else was present",
                 BQ "Someone else was present during the background questionnaire",
                 TS "Someone else was present during the tablet skills and/or during the tablet tutorial sections when the respondent was working independently",
                 RS "Someone else was present  during  the remaining sections of the Exercise - locator, components and/or assessment")

       TOthAssist = (NA "No one assisted the respondent",
                 BQ "Someone assisted the respondent during the background questionnaire",
                 TS "Someone assisted the respondent during the tablet skills and/or during the tablet tutorial section when the respondent was working independently ",
                 RS "Someone assisted the respondent during the remaining sections of the Exercise - locator, components and/or assessment")

       TRespUnder = (NR "Never",
                 AN "Almost never",
                 NT "Now and then",
                 ON "Often",
                 VO "Very often")



       TBkgNoise = (TC "Air traffic, rail traffic, road traffic including emergency vehicles",
                    OL "Loud noises outside the house, e.g. construction in the area, lawn mowers",
                 HA "Household appliances in use e.g., vacuum cleaner, washing machine/dryer, power tools",
                 TV "A television, radio, game console or music player in use",
                 PT "People talking loudly, crying babies or children, pets",
                 OT "Other")

       TRespStop = (YM "Yes, more than once",
                 YO "Yes, once",
                 N "No")


       TWhereInt = (IH "In the home ",
                 WO "Place of work or office",
                 NT "Now and then",
                 OH "Outside the home e.g., public library, coffee shop")

   TBQInit    = (CP (1)  "Complete",
                 PB (3)  "Partial complete / break-off ",
                 RS (4)  "Refusal by sample person ",
                 RO (5)  "Refusal by other person",
                 LP (7)  "Language barrier",
                 RW (8)  "Reading and writing difficulty",
                 LM (9)  "Learning / mental disability",
                 HI (12) "Hearing impairment",
                 BV (13) "Blindness / visual impairment",
                 SI (14) "Speech impairment",
                 PD (15) "Physical disability",
                 OD (16) "Other disability",
                 OU (17) "Other (unspecified) e.g.
                          @/Sickness falsification or
                          @/unusual circumstances",
                 DT (18) "Death",
                 MX (21) "Maximum number of calls",
                 MW (23) "Moved within the country but
                          @/not successfully located by the interviewers",
                 TA (24) "Temporarily absent /
                          @/Unavailable during field period",
                 IL (25) "Not in target population ",
                 DA (27) "Duplication - already interviewed",
                 TP (90) "Technical problem",
                 IP (92) "Interview pending")

   TContact   = (FF "Face to face contact",
                 PH "Phone contact",
                 NC "No contact with household member yet")

   TCore      = (CP (1)  "Complete",
                 PB (3)  "Partial complete / break-off ",
                 RS (4)  "Refusal by sample person ",
                 RO (5)  "Refusal by other person",
                 LS (6)  "Lacks the skills to use the tablet",
                 LP (7)  "Language barrier",
                 RW (8)  "Reading and writing difficulty",
                 LM (9)  "Learning / mental disability",
                 HI (12) "Hearing impairment",
                 BV (13) "Blindness / visual impairment ",
                 SI (14) "Speech impairment",
                 PD (15) "Physical disability",
                 OD (16) "Other disability",
                 OU (17) "Other (unspecified) e.g.
                          @/Sickness falsification
                          @/or unusual circumstances ",
                 DT (18) "Death",
                 MX (21) "Maximum number of calls; i.e.
                          @/Respondent not successfully contacted",
                 TA (24) "Temporarily absent /
                          @/Unavailable during field period",
                 DA (27) "Duplication - already interviewed",
                 TP (90) "Technical problem")

   TDate      =  DATETYPE

   TDoorstep  = (CP (1)  "Complete",
                 PB (3)  "Partial complete / break-off",
                 RS (4)  "Refusal by sample person",
                 UL (7)  "Unaccommodated language",
                 OU (17) "Other (unspecified) e.g.
                          @/Sickness falsification
                          @/or unusual circumstances ",
                 MX (21) "Maximum number of calls; i.e.
                          @/Respondent not successfully contacted",
                 TP (90) "Technical problem")

  { TEducat    = (NF "No formal education / training",
                 PE "Primary education",
                 LS "Lower Secondary (e.g. Junior / Inter / Group Cert)",
                 US "Upper Secondary (e.g. Leaving Cert)",
                 TV "Technical or Vocational",
                 AC "Advanced Certificate / completed apprenticeships",
                 HC "Higher Certificate (e.g. National cert or equivalent)",
                 OB "Ordinary Bachelor Degree or National Diploma",
                 HB "Honours Bachelor Degree / Professional qualification",
                 PG "Post-grad Diploma or Degree",
                 DH "Doctorate or higher")     }


   TEducat    =  (PE (1) "Up to and including the Junior/Inter/Group Certificate",
                  US (2) "Leaving Certificate or post-Leaving Certificate certificates (including apprenticeships and advanced certificates - below degree level)",
                  DH (3) "Diploma or degree level, or higher (including Higher Certificate, Graduate Diploma, Masters, Doctorate)")



   TExcr      = (CP (1) "Complete",
                 PB (3) "Partial complete / break-off",
                 RS (4) "Refusal by sample person",
                 RO (5) "Refusal by other person",
                 LS (6) "Lacks the skills to use the tablet",
                 LP (7) "Language barrier",
                 RW (8) "Reading and writing difficulty",
                 LM (9) "Learning / mental disability",
                 HI (12) "Hearing impairment",
                 BV (13) "Blindness / visual impairment",
                 SI (14) "Speech impairment",
                 PD (15) "Physical disability",
                 OD (16) "Other disability",
                 OU (17) "Other (unspecified) e.g.
                          @/sickness or falsification
                          @/or unusual circumstances",
                 DT (18) "Death",
                 MX (21) "Maximum number of calls e.g.
                          @/respondent not successfully contacted",
                 TA (24) "Temporarily absent /
                          @/Unavailable during field period",
                 DA (27) "Duplication - already interviewed",
                 TP (90) "Technical problem")

   TExit      = (E "Exit")

   TExType    = (C "PIAAC Interview",
                 P "Doorstep Interview ")

   THistPiaac = (P "Present",
                 T "Temporarily absent from the household")

   TIntm      = (AP "Call back - appointment",
		         CB "Call back - no appointment",
		         NH "Not at home",
                 AV "Avoidance",
                 LO "Locked / gated dwelling unit",
                 RB "Initial refusal",
          	     IL "Illness / disability",
        	     OT "Other - Proceed to code detailed Screener outcome")

   TMonth     = (JAN "January",
                 FEB "February",
                 MAR "March",
                 APR "April",
                 MAY "May",
                 JUN "June",
                 JUL "July",
                 AUG "August",
                 SEP "September",
                 OCT "October",
                 NOV "November",
                 DEC "December")

   TScr       = (C1 (1)  "Complete - 1 sample person selected",
		         PB (3)  "Partial complete / break-off",
           		 RH (4)  "Refusal by household member",
       		     RG (5)  "Refusal by gatekeeper",
	    	     LP (7)  "Language barrier",
		         LM (9)  "Learning / mental disability",
		         HI (12) "Hearing impairment",
		         BV (13) "Blindness / visual impairment",
		         SI (14) "Speech impairment",
		         PD (15) "Physical disability",
		         OD (16) "Other disability",
		         OU (17) "Other (unspecified) e.g.
                          @/Sickness falsification
                          @/or unusual circumstances",
		         CN (19) "Complete - no eligible sample persons",
	 	         UL (20) "Unable to locate dwelling unit",
	        	 MX (21) "Maximum number of calls i.e.
                          @/A household member not successfully contacted",
		         DC (22) "Dwelling unit under construction",
		         TA (24) "Temporarily absent /
                          @/Unavailable during field period",
		         VU (26) "Vacant dwelling unit or holiday home or temporary residence",
	        	 DA (27) "Duplication - already interviewed",
		         AN (28) "Address not a dwelling unit",
                 IP (92) "Interview Pending")

   TScrStatus = (RP "Ready to start PIAAC Respondent available",
                 MA "Make appointment details Respondent available",
                 NS "Can interview but person not selected yet",
                 AN "Ages not confirmed, no one eligible",
                 AC "No one in the house is eligible",
                 NO "Refusal, Can_Int is no",
                 RC "Refusal, contact details collected",
                 RN "Refusal, contact details not collected")

   TSelect    = (S "Select person now",
                 N "Select person later")

   TSex       = (M "Male",
                 F "Female")

   TStart     = (S "Start")

   TSurvey    = (SL "Person Selected",
                 NY "Person not Selected Yet",
                 UN "No one eligible")

   TWrongKey  = (INC "That the information you have entered in @BBlockNumber@B is incorrect",
                 BLK "That the @BBlock Number@B does not appear on the lookup files",
                 NWH "That this is a @BNew Block@B and you want to @BContinue@B")

   TYes       = (YES "Yes")

   TYesApt    = (YES "Yes, make appointment",
                 No  "Conduct interview now",
                 DS  "Conduct Doorstep interview now",
                 NA  "Person not available")

   TYesNoFin  = (Yes "Yes, administration completed, finalise this case",
                 No  "Case not yet complete")

   TYesNo     = (Yes,
                 No)

   TDSLang      = (fraZZZ  "French",
                 deuZZZ  "German",
                 itaZZZ  "Italian",
                 lavZZZ  "Latvian",
                 litZZZ  "Lithuanian",
                 polZZZ  "Polish",
                 porZZZ  "Portuguese",
                 panZZZ  "Punjabi",
                 ronZZZ  "Romanian",
                 espZZZ  "Spanish")
