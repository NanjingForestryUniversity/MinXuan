
#ifndef _USBDAQ_THERMO_COUPLE_H
#define _USBDAQ_THERMO_COUPLE_H



#ifdef __cplusplus
extern "C" {
#endif

#define THERMO_B_TYPE      1
#define THERMO_C_TYPE      2
#define THERMO_E_TYPE      3
#define THERMO_K_TYPE      4
#define THERMO_R_TYPE      5
#define THERMO_S_TYPE      6
#define THERMO_T_TYPE      7
#define THERMO_J_TYPE      8
#define THERMO_N_TYPE      9
#define RTD_PT100          10
#define RTD_PT1000         RTD_PT100
#define THERMO_MAX_TYPE    RTD_PT100

#define NoThermoError                  0

#define ErrorInvalidThermoType      -601
#define ErrorOutThermoRange         -602
#define ErrorThermoTable            -603


short __stdcall ADC_to_Thermo( unsigned short wThermoType, double fScaledADC, double fColdJuncTemp, double* pfTemp );


#ifdef __cplusplus
}
#endif

#endif // _USBDAQ_THERMO_COUPLE_H
