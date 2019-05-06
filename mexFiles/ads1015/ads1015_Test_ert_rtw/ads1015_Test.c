/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ads1015_Test.c
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

#include "ads1015_Test.h"
#include "ads1015_Test_private.h"
#include "ads1015_Test_dt.h"

/* Block signals (default storage) */
B_ads1015_Test_T ads1015_Test_B;

/* Block states (default storage) */
DW_ads1015_Test_T ads1015_Test_DW;

/* Real-time model */
RT_MODEL_ads1015_Test_T ads1015_Test_M_;
RT_MODEL_ads1015_Test_T *const ads1015_Test_M = &ads1015_Test_M_;
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to "remember" which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void ads1015_Test_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(ads1015_Test_M, 1));
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (ads1015_Test_M->Timing.TaskCounters.TID[1])++;
  if ((ads1015_Test_M->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.01s, 0.0s] */
    ads1015_Test_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function for TID0 */
void ads1015_Test_step0(void)          /* Sample time: [0.001s, 0.0s] */
{
  {                                    /* Sample time: [0.001s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* External mode */
  rtExtModeUploadCheckTrigger(2);
  rtExtModeUpload(0, (real_T)ads1015_Test_M->Timing.t[0]);

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(ads1015_Test_M)!=-1) &&
        !((rtmGetTFinal(ads1015_Test_M)-ads1015_Test_M->Timing.t[0]) >
          ads1015_Test_M->Timing.t[0] * (DBL_EPSILON))) {
      rtmSetErrorStatus(ads1015_Test_M, "Simulation finished");
    }

    if (rtmGetStopRequested(ads1015_Test_M)) {
      rtmSetErrorStatus(ads1015_Test_M, "Simulation finished");
    }
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  ads1015_Test_M->Timing.t[0] =
    (++ads1015_Test_M->Timing.clockTick0) * ads1015_Test_M->Timing.stepSize0;
}

/* Model step function for TID1 */
void ads1015_Test_step1(void)          /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (ads1015): '<Root>/adc' */

  /* Level2 S-Function Block: '<Root>/adc' (ads1015) */
  {
    SimStruct *rts = ads1015_Test_M->childSfunctions[0];
    sfcnOutputs(rts,1);
  }

  rtExtModeUpload(1, (real_T)ads1015_Test_M->Timing.t[1]);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   */
  ads1015_Test_M->Timing.t[1] =
    (++ads1015_Test_M->Timing.clockTick1) * ads1015_Test_M->Timing.stepSize1;
}

/* Model step wrapper function for compatibility with a static main program */
void ads1015_Test_step(int_T tid)
{
  switch (tid) {
   case 0 :
    ads1015_Test_step0();
    break;

   case 1 :
    ads1015_Test_step1();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void ads1015_Test_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ads1015_Test_M, 0,
                sizeof(RT_MODEL_ads1015_Test_T));
  rtsiSetSolverName(&ads1015_Test_M->solverInfo,"FixedStepDiscrete");
  ads1015_Test_M->solverInfoPtr = (&ads1015_Test_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ads1015_Test_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    ads1015_Test_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ads1015_Test_M->Timing.sampleTimes =
      (&ads1015_Test_M->Timing.sampleTimesArray[0]);
    ads1015_Test_M->Timing.offsetTimes =
      (&ads1015_Test_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ads1015_Test_M->Timing.sampleTimes[0] = (0.001);
    ads1015_Test_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    ads1015_Test_M->Timing.offsetTimes[0] = (0.0);
    ads1015_Test_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(ads1015_Test_M, &ads1015_Test_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ads1015_Test_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = ads1015_Test_M->Timing.perTaskSampleHitsArray;
    ads1015_Test_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    ads1015_Test_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ads1015_Test_M, -1);
  ads1015_Test_M->Timing.stepSize0 = 0.001;
  ads1015_Test_M->Timing.stepSize1 = 0.01;

  /* External mode info */
  ads1015_Test_M->Sizes.checksums[0] = (4065556350U);
  ads1015_Test_M->Sizes.checksums[1] = (137000975U);
  ads1015_Test_M->Sizes.checksums[2] = (1620595324U);
  ads1015_Test_M->Sizes.checksums[3] = (419513399U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    ads1015_Test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(ads1015_Test_M->extModeInfo,
      &ads1015_Test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(ads1015_Test_M->extModeInfo,
                        ads1015_Test_M->Sizes.checksums);
    rteiSetTPtr(ads1015_Test_M->extModeInfo, rtmGetTPtr(ads1015_Test_M));
  }

  ads1015_Test_M->solverInfoPtr = (&ads1015_Test_M->solverInfo);
  ads1015_Test_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&ads1015_Test_M->solverInfo, 0.001);
  rtsiSetSolverMode(&ads1015_Test_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  (void) memset(((void *) &ads1015_Test_B), 0,
                sizeof(B_ads1015_Test_T));

  /* states (dwork) */
  (void) memset((void *)&ads1015_Test_DW, 0,
                sizeof(DW_ads1015_Test_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    ads1015_Test_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;
  }

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &ads1015_Test_M->NonInlinedSFcns.sfcnInfo;
    ads1015_Test_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(ads1015_Test_M)));
    rtssSetNumRootSampTimesPtr(sfcnInfo, &ads1015_Test_M->Sizes.numSampTimes);
    ads1015_Test_M->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr
      (ads1015_Test_M)[0]);
    ads1015_Test_M->NonInlinedSFcns.taskTimePtrs[1] = &(rtmGetTPtr
      (ads1015_Test_M)[1]);
    rtssSetTPtrPtr(sfcnInfo,ads1015_Test_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(ads1015_Test_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(ads1015_Test_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(ads1015_Test_M));
    rtssSetStepSizePtr(sfcnInfo, &ads1015_Test_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(ads1015_Test_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &ads1015_Test_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &ads1015_Test_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &ads1015_Test_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &ads1015_Test_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &ads1015_Test_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &ads1015_Test_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &ads1015_Test_M->solverInfoPtr);
  }

  ads1015_Test_M->Sizes.numSFcns = (1);

  /* register each child */
  {
    (void) memset((void *)&ads1015_Test_M->NonInlinedSFcns.childSFunctions[0], 0,
                  1*sizeof(SimStruct));
    ads1015_Test_M->childSfunctions =
      (&ads1015_Test_M->NonInlinedSFcns.childSFunctionPtrs[0]);
    ads1015_Test_M->childSfunctions[0] =
      (&ads1015_Test_M->NonInlinedSFcns.childSFunctions[0]);

    /* Level2 S-Function Block: ads1015_Test/<Root>/adc (ads1015) */
    {
      SimStruct *rts = ads1015_Test_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = ads1015_Test_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = ads1015_Test_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = ads1015_Test_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &ads1015_Test_M->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &ads1015_Test_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, ads1015_Test_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &ads1015_Test_M->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &ads1015_Test_M->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &ads1015_Test_M->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &ads1015_Test_M->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &ads1015_Test_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &ads1015_Test_M->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &ads1015_Test_M->NonInlinedSFcns.Sfcn0.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &ads1015_Test_M->NonInlinedSFcns.Sfcn0.outputPortCoSimAttribute[0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *) &ads1015_Test_B.adc));
        }
      }

      /* path info */
      ssSetModelName(rts, "adc");
      ssSetPath(rts, "ads1015_Test/adc");
      ssSetRTModel(rts,ads1015_Test_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* work vectors */
      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &ads1015_Test_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &ads1015_Test_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 2);

        /* DWORK1 */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &ads1015_Test_DW.adc_DWORK1);

        /* DWORK2 */
        ssSetDWorkWidth(rts, 1, 1);
        ssSetDWorkDataType(rts, 1,SS_INT32);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &ads1015_Test_DW.adc_DWORK2);
      }

      /* registration */
      ads1015(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.01);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetOutputPortWidth(rts, 0, 1);
      ssSetOutputPortDataType(rts, 0, SS_DOUBLE);
      ssSetOutputPortComplexSignal(rts, 0, 0);
      ssSetOutputPortFrameData(rts, 0, 0);
      ssSetOutputPortUnit(rts, 0, 0);
      ssSetOutputPortIsContinuousQuantity(rts, 0, 0);
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
    }
  }

  /* InitializeConditions for S-Function (ads1015): '<Root>/adc' */
  /* Level2 S-Function Block: '<Root>/adc' (ads1015) */
  {
    SimStruct *rts = ads1015_Test_M->childSfunctions[0];
    sfcnInitializeConditions(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }
}

/* Model terminate function */
void ads1015_Test_terminate(void)
{
  /* Terminate for S-Function (ads1015): '<Root>/adc' */
  /* Level2 S-Function Block: '<Root>/adc' (ads1015) */
  {
    SimStruct *rts = ads1015_Test_M->childSfunctions[0];
    sfcnTerminate(rts);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
