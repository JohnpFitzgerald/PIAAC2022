{Author Name    : John Fitzgerald
 Date written   : PIAAC 2022
   Version        : 1.0

Description    : CreatePiaacJSON - Create a JSON file from Screener data which is passed into the PDS by powershell command line scripts
                                  embedded in the PiaacMenu Manipula

***************************************************************************************************************************************}

PROCEDURE CreatePiaacJSON
  PARAMETERS
     TRANSIT BlockNo, LDU, PiaacID, PiaacFile: STRING
ALIEN('c:\cso\piaac\pilot\CreatePDSInput.Msu', 'MakeJSON')
ENDPROCEDURE

