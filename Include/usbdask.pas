{*
 * 2012.10.29 version 0.2
 *}
unit UsbDask;

interface

uses
Classes, SysUtils, Windows;

const
    USB_1902 = 1;
    USB_1903 = 2; { USB_1902A }
    USB_1901 = 3; { USB_1902L }
    USB_2401 = 4;
    USB_7250 = 5;
    USB_7230 = 6;
    USB_2405 = 7;
    USB_1210 = 8;    
	USB_2401_A3 = 9;
	USB_101 = 10;
    NUM_USBDAQ_TYPE = 11;
    NUM_MODULE_TYPE = 11; { NUM_MODULE_TYPE = USB_2405 + 1 }
    MAX_USB_DEVICE = 8;
    { Error Number }
    NoError = 0;
    ErrorUnknownCardType = -1;
    ErrorInvalidCardNumber = -2;
    ErrorTooManyCardRegistered = -3;
    ErrorCardNotRegistered = -4;
    ErrorFuncNotSupport = -5;
    ErrorInvalidIoChannel = -6;
    ErrorInvalidAdRange = -7;
    ErrorContIoNotAllowed = -8;
    ErrorDiffRangeNotSupport = -9;
    ErrorLastChannelNotZero = -10;
    ErrorChannelNotDescending = -11;
    ErrorChannelNotAscending = -12;
    ErrorOpenDriverFailed = -13;
    ErrorOpenEventFailed = -14;
    ErrorTransferCountTooLarge = -15;
    ErrorNotDoubleBufferMode = -16;
    ErrorInvalidSampleRate = -17;
    ErrorInvalidCounterMode = -18;
    ErrorInvalidCounter = -19;
    ErrorInvalidCounterState = -20;
    ErrorInvalidBinBcdParam = -21;
    ErrorBadCardType = -22;
    ErrorInvalidDaRefVoltage = -23;
    ErrorAdTimeOut = -24;
    ErrorNoAsyncAI = -25;
    ErrorNoAsyncAO = -26;
    ErrorNoAsyncDI = -27;
    ErrorNoAsyncDO = -28;
    ErrorNotInputPort = -29;
    ErrorNotOutputPort = -30;
    ErrorInvalidDioPort = -31;
    ErrorInvalidDioLine = -32;
    ErrorContIoActive = -33;
    ErrorDblBufModeNotAllowed = -34;
    ErrorConfigFailed = -35;
    ErrorInvalidPortDirection = -36;
    ErrorBeginThreadError = -37;
    ErrorInvalidPortWidth = -38;
    ErrorInvalidCtrSource = -39;
    ErrorOpenFile = -40;
    ErrorAllocateMemory = -41;
    ErrorDaVoltageOutOfRange = -42;
    ErrorDaExtRefNotAllowed = -43;
    ErrorDIODataWidthError = -44;
    ErrorTaskCodeError = -45;
    ErrorTriggercountError = -46;
    ErrorInvalidTriggerMode = -47;
    ErrorInvalidTriggerType = -48;
    ErrorInvalidCounterValue = -50;
    ErrorInvalidEventHandle = -60;
    ErrorNoMessageAvailable = -61;
    ErrorEventMessgaeNotAdded = -62;
    ErrorCalibrationTimeOut = -63;
    ErrorUndefinedParameter = -64;
    ErrorInvalidBufferID = -65;
    ErrorInvalidSampledClock = -66;
    ErrorInvalidOperationMode = -67;
    { Error number for driver API }
    ErrorConfigIoctl = -201;
    ErrorAsyncSetIoctl = -202;
    ErrorDBSetIoctl = -203;
    ErrorDBHalfReadyIoctl = -204;
    ErrorContOPIoctl = -205;
    ErrorContStatusIoctl = -206;
    ErrorPIOIoctl = -207;
    ErrorDIntSetIoctl = -208;
    ErrorWaitEvtIoctl = -209;
    ErrorOpenEvtIoctl = -210;
    ErrorCOSIntSetIoctl = -211;
    ErrorMemMapIoctl = -212;
    ErrorMemUMapSetIoctl = -213;
    ErrorCTRIoctl = -214;
    ErrorGetResIoctl = -215;
    ErrorCalIoctl = -216;
    ErrorPMIntSetIoctl = -217;
    { Jeff added }
    ErrorAccessViolationDataCopy = -301;
    ErrorNoModuleFound = -302;
    ErrorCardIDDuplicated = -303;
    ErrorCardDisconnected = -304;
    ErrorInvalidScannedIndex = -305;
    ErrorUndefinedException = -306;
    ErrorInvalidDioConfig = -307;
    ErrorInvalidAOCfgCtrl = -308;
    ErrorInvalidAOTrigCtrl = -309;
    ErrorConflictWithSyncMode = -310;
    ErrorConflictWithFifoMode = -311;
    ErrorInvalidAOIteration = -312;
    ErrorZeroChannelNumber = -313;
    ErrorSystemCallFailed = -314;
    ErrorTimeoutFromSyncMode = -315;
    ErrorInvalidPulseCount = -316;
    ErrorInvalidDelayCount = -317;
    ErrorConflictWithDelay2 = -318;
    ErrorAOFifoCountTooLarge = -319;
    ErrorConflictWithWaveRepeat = -320;
    ErrorConflictWithReTrig = -321;
    ErrorInvalidTriggerChannel = -322;
    ErrorInvalidInputSignal = -323;
    ErrorInvalidConversionSrc = -324;
    ErrorInvalidRefVoltage = -325;
    ErrorCalibrateFailed = -326;
    ErrorInvalidCalData = -327;
    ErrorChanGainQueueTooLarge = -328;
    ErrorInvalidCardType = -329;
    ErrorInvlaidSyncMode = -330;
    ErrorIICVersion = -331;
    ErrorFX2UpgradeFailed = -332;
    ErrorInvalidReadCount = -333;
    ErrorTEDSInvalidSensorNo = -334;
    ErroeTEDSAccessTimeout = -335;
    ErrorTEDSChecksumFailed = -336;
    ErrorTEDSNotIEEE1451_4 = -337;
    ErrorTEDSInvalidTemplateID = -338;
    ErrorTEDSInvalidPrecisionValue = -339;
    ErrorTEDSUnsupportedTemplate = -340;
    ErrorTEDSInvalidPropertyID = -341;
    ErrorTEDSNoRawData = -342;   
    ErrorInvalidChannel = -397;
    ErrorNullPoint = -398;
    ErrorInvalidParamSetting = -399;
    { -401 ~ -499 the Kernel error }
    ErrorAIStartFailed = -401;
    ErrorAOStartFailed = -402;
    ErrorConflictWithGPIOConfig =  -403;
    ErrorEepromReadback = -404;
    ErrorConflictWithInfiniteOp = -405;
    ErrorWaitingUSBHostResponse = -406;
    ErrorAOFifoModeTimeout = -407;
    ErrorInvalidModuleFunction = -408;
    ErrorAdFifoFull = -409;
    ErrorInvalidTransferCount = -410;
    ErrorConflictWithAIConfig = -411;
    ErrorDDSConfigFailed = -412;
    ErrorDDSConfigFailed = -413;
    ErrorPLDBusy = -414;
    ErrorPLDTimeout = -415;
    ErrorUndefinedKernelError = -420;
    { the functions supported in the future }
    ErrorSyncModeNotSupport = -501;
    { AD Range }
    AD_B_10_V = 1;
    AD_B_5_V = 2;
    AD_B_2_5_V = 3;
    AD_B_1_25_V = 4;
    AD_B_0_625_V = 5;
    AD_B_0_3125_V = 6;
    AD_B_0_5_V = 7;
    AD_B_0_05_V = 8;
    AD_B_0_005_V = 9;
    AD_B_1_V = 10;
    AD_B_0_1_V = 11;
    AD_B_0_01_V = 12;
    AD_B_0_001_V = 13;
    AD_U_20_V = 14;
    AD_U_10_V = 15;
    AD_U_5_V = 16;
    AD_U_2_5_V = 17;
    AD_U_1_25_V = 18;
    AD_U_1_V = 19;
    AD_U_0_1_V = 20;
    AD_U_0_01_V = 21;
    AD_U_0_001_V = 22;
    AD_B_2_V = 23;
    AD_B_0_25_V = 24;
    AD_B_0_2_V = 25;
    AD_U_4_V = 26;
    AD_U_2_V = 27;
    AD_U_0_5_V = 28;
    AD_U_0_4_V = 29;
    AD_B_1_5_V = 30;
    AD_B_0_2125_V = 31;
    AD_B_40_V = 32;  { PCI-9527 AI }
    AD_B_3_16_V = 33; { PCI-9527 AI }
    AD_B_0_316_V = 34; { PCI-9527 AI }
    AD_B_25_V = 35; { Jeff added for USB-2401 AI }
    AD_B_12_5_V = 36;
    { Common Constants }
    { Synchronous Mode }
    SYNCH_OP = 1;
    ASYNCH_OP = 2;
    
    { wConfigCtrl in UD_AI_Channel_Config() }
    { Input Type }
    UD_AI_NonRef_SingEnded = $01;
    UD_AI_SingEnded = $02;
    UD_AI_Differential = $04;
    UD_AI_PseudoDifferential = $08;
    { Input Coupling }
    UD_AI_EnableIEPE = $10;
    UD_AI_DisableIEPE = $20;
    UD_AI_Coupling_AC = $40;
    UD_AI_Coupling_None = $80;
    
    { Conversion Source in UD_AI_Trigger_Config() }
    UD_AI_CONVSRC_INT = $01;
    UD_AI_CONVSRC_EXT = $02;
    
    { wTrigCtrl in UD_AI_Trigger_Config() }
    { Trigger Source bit 9:0 }
    UD_AI_TRGSRC_AI0 = $0200;
    UD_AI_TRGSRC_AI1 = $0201;
    UD_AI_TRGSRC_AI2 = $0202;
    UD_AI_TRGSRC_AI3 = $0203;
    UD_AI_TRGSRC_AI4 = $0204;
    UD_AI_TRGSRC_AI5 = $0205;
    UD_AI_TRGSRC_AI6 = $0206;
    UD_AI_TRGSRC_AI7 = $0207;
    UD_AI_TRGSRC_AI8 = $0208;
    UD_AI_TRGSRC_AI9 = $0209;
    UD_AI_TRGSRC_AI10 = $020A;
    UD_AI_TRGSRC_AI11 = $020B;
    UD_AI_TRGSRC_AI12 = $020C;
    UD_AI_TRGSRC_AI13 = $020D;
    UD_AI_TRGSRC_AI14 = $020E;
    UD_AI_TRGSRC_AI15 = $020F;
    UD_AI_TRGSRC_SOFT = $0380;
    UD_AI_TRGSRC_DTRIG = $0388;
    { Trigger Edge bit 14 }
    UD_AI_TrigPositive = $4000;
    UD_AI_TrigNegative = $0000;
    { Gated Trigger Level bit 14 }
    UD_AI_Gate_PauseLow = $4000;
    UD_AI_Gate_PauseHigh = $0000;
    { ReTrigger bit 13 }
    UD_AI_EnReTrigger = $2000;
    UD_AI_DisReTrigger = $0000;
        
    { Trigger Mode }
    UD_AI_TRGMOD_POST = $0000;
    UD_AI_TRGMOD_DELAY = $4000;
    UD_AI_TRGMOD_PRE = $8000;
    UD_AI_TRGMOD_MIDDLE = $C000;
    UD_AI_TRGMOD_GATED = $1000;
    
    { UD_DIO_Config }
    UD_DIO_DIGITAL_INPUT = $30;
    UD_DIO_COUNTER_INPUT = $31;
    UD_DIO_DIGITAL_OUTPUT = $32;
    UD_DIO_PULSE_OUTPUT = $33;    

    { TEDS Property IDs }
    UD_TEDS_PROPERTY_TEMPLATE = 1;
    UD_TEDS_PROPERTY_ElecSigType = 2;
    UD_TEDS_PROPERTY_PhysMeasType = 3;
    UD_TEDS_PROPERTY_MinPhysVal = 4;
    UD_TEDS_PROPERTY_MaxPhysVal = 5;
    UD_TEDS_PROPERTY_MinElecVal = 6;
    UD_TEDS_PROPERTY_MaxElecVal = 7;
    UD_TEDS_PROPERTY_MapMeth = 8;
    UD_TEDS_PROPERTY_BridgeType = 9;
    UD_TEDS_PROPERTY_SensorImped = 10;
    UD_TEDS_PROPERTY_RespTime = 11;
    UD_TEDS_PROPERTY_ExciteAmplNom = 12;
    UD_TEDS_PROPERTY_ExciteAmplMin = 13;
    UD_TEDS_PROPERTY_ExciteAmplMax = 14;
    UD_TEDS_PROPERTY_CalDate = 15;
    UD_TEDS_PROPERTY_CalInitials = 16;
    UD_TEDS_PROPERTY_CalPeriod = 17;
    UD_TEDS_PROPERTY_MeasID = 18;
        
    { Constants for USB-1902 }
    { wConfigCtrl in UD_AI_1902_Config() }
    { Input Type
      bit 7:6 in AI_CONFG }
    { 2011April29, Jeff changed }
    P1902_AI_NonRef_SingEnded = $00;
    P1902_AI_SingEnded = $01;
    P1902_AI_PseudoDifferential = $02;
    P1902_AI_Differential = $02;    
    
    { Conversion Source
      bit 9 in AI_ACQMCR }
    P1902_AI_CONVSRC_INT = $00;
    P1902_AI_CONVSRC_EXT = $80;
    { wTrigCtrl in UD_AI_1902_Config() }
    { Trigger Source 
      bit 8:3 in AI_ACQMCR }
    P1902_AI_TRGSRC_AI0 = $020;
    P1902_AI_TRGSRC_AI1 = $021;
    P1902_AI_TRGSRC_AI2 = $022;
    P1902_AI_TRGSRC_AI3 = $023;
    P1902_AI_TRGSRC_AI4 = $024;
    P1902_AI_TRGSRC_AI5 = $025;
    P1902_AI_TRGSRC_AI6 = $026;
    P1902_AI_TRGSRC_AI7 = $027;
    P1902_AI_TRGSRC_AI8 = $028;
    P1902_AI_TRGSRC_AI9 = $029;
    P1902_AI_TRGSRC_AI10 = $02A;
    P1902_AI_TRGSRC_AI11 = $02B;
    P1902_AI_TRGSRC_AI12 = $02C;
    P1902_AI_TRGSRC_AI13 = $02D;
    P1902_AI_TRGSRC_AI14 = $02E;
    P1902_AI_TRGSRC_AI15 = $02F;
    P1902_AI_TRGSRC_SOFT = $030;
    P1902_AI_TRGSRC_DTRIG = $031;
    { Trigger Edge 
      bit 2 in AI_ACQMCR }
    P1902_AI_TrgPositive = $040;
    P1902_AI_TrgNegative = $000;
    { Gated Trigger Level
      bit 2 in AI_ACQMCR }
    P1902_AI_Gate_PauseLow = $000;
    P1902_AI_Gate_PauseHigh = $040;
    { Trigger Mode }
    P1902_AI_TRGMOD_POST = $000;
    P1902_AI_TRGMOD_GATED = $080;
    P1902_AI_TRGMOD_DELAY = $100;
    { ReTrigger 
      bit 25 in AI_ACQMCR }
    P1902_AI_EnReTigger = $200;
    { AO Constants }
    { Conversion Source }
    P1902_AO_CONVSRC_INT = $00;
    P1902_AO_TRIG_CTRL_MASK = (not $00000711);
    { Trigger Mode }
    P1902_AO_TRGMOD_POST = $00;
    P1902_AO_TRGMOD_DELAY = $01;
    { Trigger Source }
    { bit 24 in AO_TCFIGR }
    P1902_AO_TRGSRC_SOFT = $00;
    P1902_AO_TRGSRC_DTRIG = $10;
    { Trigger Edge }
    { bit 25 in AI_ACQMCR }
    P1902_AO_TrgPositive = $100;
    P1902_AO_TrgNegative = $000;
    { Enable Re-Trigger }
    { bit 10 in AO_TCFIGR }
    P1902_AO_EnReTigger = $200;
    { Flag for AO Waveform Seperation Interval COunt Register (AO_WSIC) }
    P1902_AO_EnDelay2 = $400;
    { Constants for USB-2401 }
    { wConfigCtrl in UD_AI_2401_Config() }
    { Input Type }
    { V >=2.5V, V<2.5, 
    Current, 
    RTD (4 wire), RTD (3-wire), RTD (2-wire), 
    Resistor, Thermocouple, Full-Bridge, Half-Bridge }
    P2401_Voltage_2D5V_Above = $00;
    P2401_Voltage_2D5V_Below = $01;
    P2401_Current = $02;
    P2401_RTD_4_Wire = $03;
    P2401_RTD_3_Wire = $04;
    P2401_RTD_2_Wire = $05;
    P2401_Resistor = $06;
    P2401_ThermoCouple = $07;
    P2401_Full_Bridge = $08;
    P2401_Half_Bridge = $09;
    P2401_ThermoCouple_Differential = $0A;
    P2401_350Ohm_Full_Bridge = $0B;
    P2401_350Ohm_Half_Bridge = $0C;
    P2401_120Ohm_Full_Bridge = $0D;
    P2401_120Ohm_Half_Bridge = $0E;    
    { Conversion Source }
    {  bit 9 in AI_ACQMCR }
    P2401_AI_CONVSRC_INT = $00;
    { wTrigCtrl in UD_AI_2401_Config() }
    { Trigger Source }
    { bit 8:3 in AI_ACQMCR } 
    P2401_AI_TRGSRC_SOFT = $030;
    P2401_AI_TRGSRC_DTRIG = $031;
    { Trigger Edge }
    { bit 2 in AI_ACQMCR }
    P2401_AI_TrgPositive = $040;
    P2401_AI_TrgNegative = $000;
    { Trigger Mode }
    P2401_AI_TRGMOD_POST = $000;
    { wMAvgStageCh1 ~ wMAvgStageCh4 in UD_AI_2401_PollConfig() }
    P2401_Polling_MAvg_Disable = $00;
    P2401_Polling_MAvg_2_Sampes = $01;
    P2401_Polling_MAvg_4_Sampes = $02;
    P2401_Polling_MAvg_8_Sampes = $03;
    P2401_Polling_MAvg_16_Sampes = $04;
    { wEnContPolling in UD_AI_2401_PollConfig() }
    P2401_Continue_Polling_Disable = $00;
    P2401_Continue_Polling_Enable = $01;
    { wPollSpeed in UD_AI_2401_PollConfig() }
    P2401_ADC_2000_SPS = $09;
    P2401_ADC_1000_SPS = $08;
    P2401_ADC_640_SPS = $07;
    P2401_ADC_320_SPS = $06;
    P2401_ADC_160_SPS = $05;
    P2401_ADC_80_SPS = $04;
    P2401_ADC_40_SPS = $03;
    P2401_ADC_20_SPS = $02;
    

    { Input Coupling }
    P2405_AI_EnableIEPE = $004;
    P2405_AI_DisableIEPE = $008;
    P2405_AI_Coupling_AC = $010;
    P2405_AI_Coupling_None = $020;

    { Input Type }
    P2405_AI_Differential = $000;
    P2405_AI_PseudoDifferential = $040;

    P2405_AI_CONVSRC_INT = $000;
    P2405_AI_CONVSRC_EXT = $200;
 

    { Trigger Source }
    P2405_AI_TRGSRC_AI0 = $200;
    P2405_AI_TRGSRC_AI1 = $208;
    P2405_AI_TRGSRC_AI2 = $210;
    P2405_AI_TRGSRC_AI3 = $218;
    P2405_AI_TRGSRC_SOFT = $380;
    P2405_AI_TRGSRC_DTRIG = $388; 

    { Trigger Edge }
    P2405_AI_TrgPositive = $004;
    P2405_AI_TrgNegative = $000;
    
    { Gated Trigger Level }
    P2405_AI_Gate_PauseLow = $004;
    P2405_AI_Gate_PauseHigh = $000;

    { ReTrigger }
    P2405_AI_EnReTigger = $2000;

    { AI Trigger Mode }
    P2405_AI_TRGMOD_POST = $0000;
    P2405_AI_TRGMOD_DELAY = $4000;
    P2405_AI_TRGMOD_PRE = $8000;
    P2405_AI_TRGMOD_MIDDLE = $C000;
    P2405_AI_TRGMOD_GATED = $1000;
    
    { GPIO/GPTC Configuration }
    GPIO_IGNORE_CONFIG = $00;
    GPTC0_GPO1 = $01;
    GPI0_3_GPO0_1 = $02;
    { ENC0_GPO0 = $04; }
    GPTC0_TC1 = $08;
    GPTC2_GPO3 = $10;
    GPI4_7_GPO2_3 = $20;
    { ENC1_GPO2 = $40; }
    GPTC2_TC3 = $80;
	{ UD_DIO_Config for USB-101 }
	GPO0 = $1100;
	GPO1 = $1200;
	GPO2 = $1400;
	GPO3 = $1800;
	GPI0_3 = $2000;
    { GPIO Port }
    GPIO_PortA = 0;
    GPIO_PortB = 1;
    {
     General Purpose Timer/Counter for USB-1902
    }
    { Counter Mode }
    SimpleGatedEventCNT = $01;
    SinglePeriodMSR = $02;
    SinglePulseWidthMSR = $03;
    SingleGatedPulseGen = $04;
    SingleTrigPulseGen = $05;
    RetrigSinglePulseGen = $06;
    SingleTrigContPulseGen = $07;
    ContGatedPulseGen = $08;
    EdgeSeparationMSR = $09;
    SingleTrigContPulseGenPWM = $0a;
    ContGatedPulseGenPWM = $0b;
    CW_CCW_Encoder = $0c;
    x1_AB_Phase_Encoder = $0d;
    x2_AB_Phase_Encoder = $0e;
    x4_AB_Phase_Encoder = $0f;
    Phase_Z = $10;
    MultipleGatedPulseGen = $11;
    { GPTC clock source }
    GPTC_CLK_SRC_Ext = $01;
    GPTC_CLK_SRC_Int = $00;
    GPTC_GATE_SRC_Ext = $02;
    GPTC_GATE_SRC_Int = $00;
    GPTC_UPDOWN_Ext = $04;
    GPTC_UPDOWN_Int = $00;
    { GPTC clock polarity }
    GPTC_CLKSRC_LACTIVE = $01;
    GPTC_CLKSRC_HACTIVE = $00;
    GPTC_GATE_LACTIVE = $02;
    GPTC_GATE_HACTIVE = $00;
    GPTC_UPDOWN_LACTIVE = $04;
    GPTC_UPDOWN_HACTIVE = $00;
    GPTC_OUTPUT_LACTIVE = $08;
    GPTC_OUTPUT_HACTIVE = $00;
    { GPTC OP Parameter }
    IntGate = $0; {Internal Gate}
    IntUpDnCTR = $1;  {Internal Up/Down Counter}
    IntENABLE = $2;  {Internal Enable}
    { DAQ Event type for the event message }
    AIEnd = 0;
    AOEnd = 0;
    DIEnd = 0;
    DOEnd = 0;
    DBEvent = 1;
    { Encoder/GPTC Constants }
    P1902_GPTC0 = $00;
    P1902_GPTC1 = $01;
    { Encoder Setting Event Control }
    P1902_EPT_PULWIDTH_200us = $00;
    P1902_EPT_PULWIDTH_2ms = $01;
    P1902_EPT_PULWIDTH_20ms = $02;
    P1902_EPT_PULWIDTH_200ms = $03;
    P1902_EPT_TRGOUT_GPO = $04;
    P1902_EPT_TRGOUT_CALLBACK = $08;
    { Event Type }
    P1902_EVT_TYPE_EPT0 = $00;
    P1902_EVT_TYPE_EPT1 = $01;
    { Constants for I Squared C (I2C) }
    { I2C Port }
    I2C_Port_A = 0;
    { I2C Control Operation }
    I2C_ENABLE = 0;
    I2C_STOP = 1;
    { convert from enum }
    UD_CTR_Filter_Disable = 0;
    UD_CTR_Filter_Enable = 1;
    UD_CTR_Reset_Rising_Edge_Counter = 2;
    UD_CTR_Reset_Frequency_Counter = 4;
    UD_CTR_Polarity_Positive = 0;
    UD_CTR_Polarity_Negative = 8;
	
	{ THERMO }
	THERMO_B_TYPE = 1;
	THERMO_C_TYPE = 2;
	THERMO_E_TYPE = 3;
	THERMO_K_TYPE = 4;
	THERMO_R_TYPE = 5;
	THERMO_S_TYPE = 6;
	THERMO_T_TYPE = 7;
	THERMO_J_TYPE = 8;
	THERMO_N_TYPE = 9;
	RTD_PT100 = 10;
	RTD_PT1000 = RTD_PT100;
	THERMO_MAX_TYPE = RTD_PT100;

type
    BOOL = Boolean;
    PBOOL = ^Boolean;
    U8  = Byte;
    I16 = SmallInt;
    U16 = Word;
    USHORT = Word;
    PUSHORT = ^Word;
    I32 = LongInt;
    U32 = Cardinal;
    I64 = Int64;
    F32 = Single;
    F64 = Double;
    PU8 = ^Byte;
    PI16 = ^SmallInt;
    PU16 = ^Word;
    PI32 = ^LongInt;
    PPI32 = ^PI32;
    PU32 = ^Cardinal;
    PI64 = ^Int64;
    PF64 = ^Double;
    PHANDLE = ^THANDLE;
    PUSBDAQ_DEVICE = ^USBDAQ_DEVICE;
    USBDAQ_DEVICE = packed record
                  wModuleType:U16;
                  wCardID:U16;
    end;
    QCInfo = packed record
                  RefVoltage : array [1..4] of Double;
                  Trimmer : USHORT;
                  Reserved : array [1..3] of USHORT;
    end;
    PQC_INFO_1902 = ^QC_INFO_1902;
    QC_INFO_1902 = packed record
                  case Integer of
                  0: (QCInfo : QCInfo);
                  1: (bValue : array [1..40] of Byte);
    end;
    CALInfo = packed record
                  AI_Offset : array [1..2] of Cardinal;
                  AI_Gain : array [1..2] of Cardinal;
                  AO_Offset : Cardinal;
                  AO_Gain : Cardinal;
    end;
    PCAL_INFO_1902 = ^CAL_INFO_1902;
    CAL_INFO_1902 = packed record
                  case Integer of
                  0: (CalInfo : CalInfo);
                  1: (bValue : array [1..24] of Byte);
    end;

    TUDDaskCallback = procedure; stdcall; 

{
    USB-DASK Function prototype 
}
{
    Function
}
function UD_Register_Card(CardType, card_num : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_Release_Card(CardNumber : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_Device_Scan(pModuleNum : PU16; 
pAvailModules : PUSBDAQ_DEVICE) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 AI Function
}
function UD_AI_1902_Config(CardNumber, wConfigCtrl, wTrigCtrl : U16; 
 dwTrgLevel, wReTriggerCnt, dwDelayCount : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_2401_Config(CardNumber, wChanCfg1, wChanCfg2, wChanCfg3, wChanCfg4, wTrigCtrl : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_2401_PollConfig(wCardNumber, wPollSpeed, wMAvgStageCh1, wMAvgStageCh2, wMAvgStageCh3, wMAvgStageCh4 : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_1902_CounterInterval(CardNumber : U16; ScanIntrv, SampIntrv : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncCheck(CardNumber : U16; Stopped : PBool; AccessCnt : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncClear(CardNumber : U16; AccessCnt : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncDblBufferHalfReady(CardNumber : U16; HalfReady, StopFlag : PBool) : I16; 
stdcall; external 'usb-dask.dll'; 
 
function UD_AI_AsyncDblBufferMode(CardNumber : U16; Enable : Boolean) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncDblBufferTransfer(CardNumber : U16; Buffer : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncDblBufferTransfer32(CardNumber : U16; pwBuffer : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncDblBufferOverrun(CardNumber : U16; op : U16; overrunFlag : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncDblBufferHandled(CardNumber : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncDblBufferToFile(CardNumber : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_ContReadChannel(CardNumber : U16; Channel : U16; AdRange : U16; Buffer : PU16; ReadCount : U32; SampleRate : F64; SyncMode : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_ContReadMultiChannels(CardNumber : U16; NumChans : U16; Chans : PU16; AdRanges : PU16; Buffer : PU16; ReadCount : U32; SampleRate : F64; SyncMode : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_ContReadChannelToFile(CardNumber : U16; Channel : U16; AdRange : U16; FileName : PU8; ReadCount : U32; SampleRate : F64; SyncMode : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_ContReadMultiChannelsToFile(CardNumber : U16; NumChans : U16; Chans : PU16; AdRanges : PU16; FileName : PU8; ReadCount : U32; SampleRate : F64; SyncMode : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_ContScanChannelsToFile(CardNumber : U16; Channel : U16; AdRange : U16; FileName : PU8; ReadCount : U32; SampleRate : F64; SyncMode : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_InitialMemoryAllocated(CardNumber : U16; MemSize : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_ReadChannel(CardNumber : U16; Channel : U16; AdRange : U16; Value : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_VReadChannel(CardNumber : U16; Channel : U16; AdRange : U16; voltage : PF64) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_ReadMultiChannels(CardNumber : U16; NumChans : U16; Chans : PU16; AdRanges : PU16; Buffer : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_SetTimeOut(CardNumber : U16; TimeOut : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_VoltScale(CardNumber : U16; AdRange : U16; reading : I16; voltage : PF64) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_ContVScale(CardNumber : U16; adRange : U16; readingArray : Pointer; voltageArray : PF64; count : I32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_2401_Scale32(CardNumber : U16; adRange : U16; inType : U16; reading : U32; voltage : PF64) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_2401_ContVScale32(CardNumber : U16; adRange : U16; inType : U16; readingArray : U32; voltageArray : PF64; count : I32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncReTrigNextReady(CardNumber : U16; Ready : PBOOL; StopFlag : PBOOL; RdyTrigCnt : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_AsyncBufferTransfer(wCardNumber : USHORT; pwBuffer : PUSHORT; offset : U32; count : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_EventCallBack(CardNumber : U16; mode : I16; EventType : I16; callbackAddr : TUDDaskCallback) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_Moving_Average32(CardNumber : U16; SrcBuf : PU32; DesBuf : PU32; dwTgChIdx : U32; dwTotalCh : U32; dwMovAvgWindow : U32; dwSamplCnt : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_2401_Stop_Poll(wCardNumber : U16) : I16; 
stdcall; external 'usb-dask.dll'; 
 
function UD_AI_Channel_Config (CardNumber : U16; wChanCfg1 : U16; wChanCfg2 : U16; wChanCfg3 : U16; wChanCfg4 : U16 ) : I16;
stdcall; external 'usb-dask.dll'; 

function UD_AI_Trigger_Config (CardNumber : U16; wConvSrc : U16; wTrigMode : U16; wTrigCtrl : U16; wReTrigCnt : U32; dwDLY1Cnt : U32; dwDLY2Cnt : U32; dwTrgLevel : U32 ) : I16;
stdcall; external 'usb-dask.dll'; 

function UD_AI_2405_Chan_Config (CardNumber : U16; wChanCfg1 : U16; wChanCfg2 : U16; wChanCfg3 : U16; wChanCfg4 : U16 ) : I16;
stdcall; external 'usb-dask.dll'; 

function UD_AI_2405_Trig_Config (CardNumber : U16; wConvSrc : U16; wTrigMode : U16; wTrigCtrl : U16; wReTrigCnt : U32; dwDLY1Cnt : U32; dwDLY2Cnt : U32; dwTrgLevel : U32 ) : I16;
stdcall; external 'usb-dask.dll'; 
                                                                            
function UD_AI_VoltScale32 ( CardNumber : U16;  adRange : U16; inType : U16; reading : U32; voltage : PF64 ) : I16;
stdcall; external 'usb-dask.dll'; 
                                                                            
function UD_AI_ContVScale32 ( CardNumber : U16; adRange : U16; inType : U16; readingArray : U32; voltageArray : PF64; count : I32) : I16; 
stdcall; external 'usb-dask.dll'; 
                                            
function UD_AI_AsyncBufferTransfer32 ( CardNumber : U16; pdwBuffer : PU32; offset : U32; count : U32 ) : I16; 
stdcall; external 'usb-dask.dll';      

function UD_AI_DDS_ActualRate_Get ( CardNumber : U16; fSampleRate : F64; fActualRate : PF64 ) : I16; 
stdcall; external 'usb-dask.dll';

function UD_AI_Monitor_Config(CardNumber : U16; mode : I16; aiCh : U16; gpoCh : U16; adRange : U16; trgHigh : F64; trgLow : F64; deltaT : F64 ) : I16; 
stdcall; external 'usb-dask.dll';

function UD_AI_Monitor_AlarmClear ( CardNumber : U16; gpoCh : U16 ) : I16; 
stdcall; external 'usb-dask.dll';

function UD_AI_Monitor_AlarmClear ( CardNumber : U16; gpoCh : U16; alarmStatus : PU16 ) : I16; 
stdcall; external 'usb-dask.dll';

function UD_AI_Monitor_Reset ( CardNumber : U16 ) : I16; 
stdcall; external 'usb-dask.dll';

{
 AO Function
}
function UD_AO_1902_Config(CardNumber : U16; ConfigCtrl : U16; TrigCtrl : U16; ReTrgCnt : U32; DLY1Cnt : U32; DLY2Cnt : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_AsyncCheck(CardNumber : U16; Stopped : PBOOL; AccessCnt : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_AsyncClear(CardNumber : U16; AccessCnt : PU32; stop_mode : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_AsyncDblBufferHalfReady(CardNumber : U16; bHalfReady : PBOOL) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_AsyncDblBufferTransfer(wCardNumber : U16; wBufferID : USHORT; pwBuffer : PUSHORT) : I16; stdcall; external 'usb-dask.dll'; 

function UD_AO_AsyncDblBufferMode(CardNumber : U16; Enable : BOOLEAN; bEnFifoMode : BOOLEAN) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_ContBufferCompose(CardNumber : U16; TotalChnCount : U16; ChnNum : U16; UpdateCount : U32; ConBuffer : Pointer; Buffer : Pointer) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_ContWriteChannel(CardNumber : U16; Channel : U16; pAOBuffer : Pointer; WriteCount : U32; Iterations : U32; CHUI : U32; definite : U16; SyncMode : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_ContWriteMultiChannels(CardNumber : U16; NumChans : U16; Chans : PU16; pAOBuffer : Pointer; WriteCount : U32; Iterations : U32; CHUI : U32; definite : U16; SyncMode : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_InitialMemoryAllocated(CardNumber : U16; MemSize : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_SetTimeOut(CardNumber : U16; TimeOut : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_SimuVWriteChannel(CardNumber : U16; Group : U16; VBuffer : PF64) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_SimuWriteChannel(CardNumber : U16; Group : U16; Buffer : PI16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_VWriteChannel(CardNumber : U16; Channel : U16; Voltage : F64) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_WriteChannel(CardNumber : U16; Channel : U16; Value : I16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_WriteChannels(wCardNumber : U16; wNumChans : U16; pwChans : PU16; pwBuffer : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_VoltScale(CardNumber, Channel : U16; Voltage : F64; binValue : PI16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_EventCallBack(CardNumber : U16; mode : I16; EventType : I16; callbackAddr : TUDDaskCallback) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 1902
}
function UD_DIO_1902_Config(wCardNumber : U16; wPart1Cfg : U16; wPart2Cfg : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_DIO_2401_Config(wCardNumber : U16; wPart1Cfg : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_DIO_2405_Config(wCardNumber : U16; wPart1Cfg : U16; wPart2Cfg : U16) : I16; 
stdcall; external 'usb-dask.dll';  

function UD_DIO_Config(wCardNumber : U16; wPart1Cfg : U16; wPart2Cfg : U16) : I16; 
stdcall; external 'usb-dask.dll';  
{
 DI Function
}
function UD_DI_ReadLine(CardNumber : U16; Port : U16; Line : U16; State : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_DI_ReadPort(CardNumber : U16; Port : U16; Value : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 DO Function
}
function UD_DO_ReadLine(CardNumber : U16; Port : U16; Line : U16; Value : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_DO_ReadPort(CardNumber : U16; Port : U16; Value : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_DO_WriteLine(CardNumber : U16; Port : U16; Line : U16; Value : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_DO_WritePort(CardNumber : U16; Port : U16; Value : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 Timer/Counter Function
}
function UD_GPTC_Clear(CardNumber : U16; GCtr : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_GPTC_Control(CardNumber : U16; GCtr : U16; ParamID : U16; Value : U16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_GPTC_Read(CardNumber : U16; GCtr : U16; Value : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_GPTC_Setup(CardNumber : U16; GCtr : U16; Mode : U16; SrcCtrl : U16; PolCtrl : U16; LReg1_Val : U32; LReg2_Val : U32; RulseCount : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_GPTC_Setup_N(CardNumber : U16; GCtr : U16; Mode : U16; SrcCtrl : U16; PolCtrl : U16; LReg1_Val : U32; LReg2_Val : U32; RulseCount : U32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_GPTC_Status(CardNumber : U16; GCtr : U16; Value : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 
{
 Get Event or View Function
}
function UD_AI_GetEvent(CardNumber : U16; Event : PHANDLE) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_GetEvent(CardNumber : U16; Event : PHANDLE) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AI_GetView(CardNumber : U16; View : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_AO_GetView(CardNumber : u16; View : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 
{
 Common Function
}
function UD_GetActualRate(CardNumber : U16; SampleRate : F64; ActualRate : PF64) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_GetCardIndexFromID(CardNumber : U16; cardType : PU16; cardIndex : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_GetCardType(CardNumber : U16; cardType : PU16) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_IdentifyLED_Control(wCardNumber : U16; bEnable : U8) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 Misc. Functions
}
function UD_Read_ColdJunc_Thermo(wCardNumber : U16; pfValue : PF64) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_Read_ColdJunc_Thermo_QC(wCardNumber : USHORT; wSensorNo : USHORT; pfValue : PF64) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 USB-1901/1902 Calibration
}
function UD_1902_AD_Read_Average(wCardNumber : U16; wCalSrc : USHORT; bOffsetGain : U8; pAD_Data : PI32) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 USB-1903 Calibration
}

function UD_1903_AD_Read_Average(wCardNumber : U16; wCalSrc : USHORT; pAD_Data : PI32) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 USB-2401 Calibration
}

function UD_2401_AD_Read_Sum(wCardNumber : U16; wOperation : WORD; wCalSrc : U16; dwSampleRate : U32; pAD_Data : PI64) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_2401_AD_Read_Raw(wCardNumber : U16; wOperation : WORD; wCalSrc : U16; dwSampleRate : U32; pAD_Data : PPI32 ) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 Common
}

function UD_GetFPGAVersion(wCardNumber : U16; pdwFPGAVersion : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_1902_Trimmer_Set(wCardNumber : U16; bValue : U8) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_2401_Trimmer_Set(wCardNumber : U16; bValue : U8) : I16; 
stdcall; external 'usb-dask.dll'; 

{
 UD_CTR functions
}
function UD_CTR_Control(wCardNumber, wCtr : U16; dwCtrl : U32) : I16; 
stdcall; external 'usb-dask.dll'; 
function UD_CTR_ReadFrequency(wCardNumber, wCtr : U16; pfValue : PF64) : I16; 
stdcall; external 'usb-dask.dll'; 
function UD_CTR_ReadRisingEdgeCounter(wCardNumber, wCtr : U16; dwValue : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 

function UD_CTR_SetupMinPulseWidth(wCardNumber, wCtr, wValue : U16) : I16; 
stdcall; external 'usb-dask.dll'; 
{
 UD_DI functions
}
function UD_DI_GetCOSLatchData32(wCardNumber, wPort : U16; pwCosLData : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 
function UD_DI_SetupMinPulseWidth(wCardNumber, wValue : U16) : I16; 
stdcall; external 'usb-dask.dll'; 
function UD_DI_Control(wCardNumber, wPort : U16; dwCtrl : U32) : I16; 
stdcall; external 'usb-dask.dll'; 
function UD_DI_SetCOSInterrupt32(wCardNumber, wPort : U16; dwCtrl : U32; hEvent : PHANDLE; ManualReset : Boolean) : I16; 
stdcall; external 'usb-dask.dll'; 
function UD_DO_GetInitPattern(wCardNumber, wPort : U16; pdwPattern : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 
function UD_DO_SetInitPattern(wCardNumber, wPort : U16; pdwPattern : PU32) : I16; 
stdcall; external 'usb-dask.dll'; 
function UD_DIO_INT_EventMessage(wCardNumber : U16; mode : I16; evt : THANDLE; windowHandle : HWND; message : U32; callbackAddr : TUDDaskCallback) : I16;
stdcall; external 'usb-dask.dll'; 

implementation

end.

