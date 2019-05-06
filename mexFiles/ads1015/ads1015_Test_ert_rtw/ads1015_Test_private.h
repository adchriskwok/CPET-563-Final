/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ads1015_Test_private.h
 *
 * Code generated for Simulink model 'ads1015_Test'.
 *
 * Model version                  : 1.32
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Fri Apr 19 08:29:59 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ads1015_Test_private_h_
#define RTW_HEADER_ads1015_Test_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "ads1015_Test.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

extern void ads1015(SimStruct *rts);
extern void ads1015_Test_step0(void);
extern void ads1015_Test_step1(void);

#endif                                 /* RTW_HEADER_ads1015_Test_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
