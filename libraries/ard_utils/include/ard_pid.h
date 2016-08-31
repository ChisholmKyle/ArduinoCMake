/**
 * @file       ard_pid.h
 * @author     Kyle Chisholm (dev@kylechisholm.ca)
 * @brief      PID controller
 *
 * @details
 *
 * See group @ref ArdPid
 *
 */

#ifndef ARD_PID_H
#define ARD_PID_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup   ArdPid PID controller
 * @brief      PID controller
 *
 * The PID implementation is based on Matlab's discretized PID controllers as described in
 * [Matlab's PID controller documentation](http://www.mathworks.com/help/control/ref/pid.html)
 *
 * The main PID dicrete-time controller transfer function is
 *
 * \f$C = K_p + K_i IF(z) + \frac{K_d}{T_f + DF(z)}\f$
 *
 * where \f$ IF(z) \f$ and \f$ DF(z) \f$ depend on the type of discretization and the parameters
 * \f$K_p, \; K_i, \; K_d, \; T_f\f$, and the sample time \f$T_f\f$ correspond to the parameters in ArdPidParam \ref
 *
 * @{
 *
 */

/**
 * State container for PID controller
 */
typedef struct ArdPidState {
    double e1;
    double e2;
    double u1;
    double u2;
} ArdPidState;


/**
 * Constant PID parameters
 */
typedef struct ArdPidParam {
    /** proportional gain */
    double kp;
    /** integral gain */
    double ki;
    /** derivative gain */
    double kd;
    /** minimum control variable output (saturation) */
    double umin;
    /** maximum control variable output (saturation) */
    double umax;
    /** time constant for derivative filter (in seconds) */
    double tf;
} ArdPidParam;

/**
 * @brief      Reset PID (zero everything)
 *
 * @param      state  State container for PID
 */
inline void ard_pid_reset(ArdPidState *state) {

    state->e1 = 0.0;
    state->e2 = 0.0;

    state->u1 = 0.0;
    state->u2 = 0.0;

}

/**
 * @brief      forward euler step linearized PID controller
 *
 * This function is equivalent to running a discrete control system generated from Maltab's `pid` function:
 *
 *     sys = pid(kp,ki,kd,tf,ts,'IFormula','ForwardEuler','DFormula','ForwardEuler');
 *
 * @param[in]  des    Desired set value
 * @param[in]  meas   Measured value
 * @param      state  PID state (do not manually edit)
 * @param[in]  ts     Time-step in seconds
 * @param[in]  param  PID parameters (gains, saturation, etc.)
 *
 * @return     controller output
 */
inline double ard_pid_run_fwd(const double des, const double meas,
                             ArdPidState *state, const double ts,
                             const ArdPidParam *param) {

    /* error */
    const double e = des - meas;

    /* calculate output */
    const double t2 = 1.0/param->tf;
    const double t3 = param->kp*param->tf;
    double u = state->e2*t2*(param->kd+t3-param->kp*ts+param->ki*(ts*ts)-param->ki*param->tf*ts)+t2*state->u1*(param->tf*2.0-ts)+e*t2*(param->kd+t3)-state->e1*t2*(param->kd*2.0+param->kp*param->tf*2.0-param->kp*ts-param->ki*param->tf*ts)-t2*state->u2*(param->tf-ts);

    /* saturate output */
    u = (u > param->umax ? param->umax : (u < param->umin ? param->umin : u));

    /* next state */
    state->u2 = state->u1;
    state->u1 = u;

    state->e2 = state->e1;
    state->e1 = e;

    return u;

}


/**
 * @brief      backwards euler step linearized PID controller
 *
 * This function is equivalent to running a discrete control system generated from Maltab's `pid` function:
 *
 *     sys = pid(kp,ki,kd,tf,ts,'IFormula','BackwardEuler','DFormula','BackwardEuler');
 *
 * @param[in]  des    Desired set value
 * @param[in]  meas   Measured value
 * @param      state  PID state (do not manually edit)
 * @param[in]  ts     Time-step in seconds
 * @param[in]  param  PID parameters (gains, saturation, etc.)
 *
 * @return     controller output
 */
inline double ard_pid_run_back(const double des, const double meas,
                            ArdPidState *state, const double ts,
                            const ArdPidParam *param) {

    /* error */
    const double e = des - meas;

    /* calculate output */
    double u = (e*param->kd-state->e1*param->kd*2.0+state->e2*param->kd+param->tf*state->u1*2.0-param->tf*state->u2+ts*state->u1+e*param->ki*(ts*ts)+e*param->kp*param->tf+e*param->kp*ts-state->e1*param->kp*param->tf*2.0+state->e2*param->kp*param->tf-state->e1*param->kp*ts+e*param->ki*param->tf*ts-state->e1*param->ki*param->tf*ts)/(param->tf+ts);

    /* saturate output */
    u = (u > param->umax ? param->umax : (u < param->umin ? param->umin : u));

    /* next state */
    state->u2 = state->u1;
    state->u1 = u;

    state->e2 = state->e1;
    state->e1 = e;

    return u;

}

/**
 * @brief      trapezoidal linearized PID controller
 *
 * This function is equivalent to running a discrete control system generated from Maltab's `pid` function:
 *
 *     sys = pid(kp,ki,kd,tf,ts,'IFormula','Trapezoidal','DFormula','Trapezoidal');
 *
 * @param[in]  des    Desired set value
 * @param[in]  meas   Measured value
 * @param      state  PID state (do not manually edit)
 * @param[in]  ts     Time-step in seconds
 * @param[in]  param  PID parameters (gains, saturation, etc.)
 *
 * @return     controller output
 */
inline double ard_pid_run_trap(const double des, const double meas,
                            ArdPidState *state, const double ts,
                            const ArdPidParam *param) {

    /* error */
    const double e = des - meas;

    /* calculate output */
    const double t2 = ts*ts;
    double u = (e*param->kd*2.0-state->e1*param->kd*4.0+state->e2*param->kd*2.0+param->tf*state->u1*4.0-param->tf*state->u2*2.0+ts*state->u2+e*param->ki*t2*(1.0/2.0)+e*param->kp*param->tf*2.0+state->e1*param->ki*t2+state->e2*param->ki*t2*(1.0/2.0)+e*param->kp*ts-state->e1*param->kp*param->tf*4.0+state->e2*param->kp*param->tf*2.0-state->e2*param->kp*ts+e*param->ki*param->tf*ts-state->e2*param->ki*param->tf*ts)/(param->tf*2.0+ts);

    /* saturate output */
    u = (u > param->umax ? param->umax : (u < param->umin ? param->umin : u));

    /* next state */
    state->u2 = state->u1;
    state->u1 = u;

    state->e2 = state->e1;
    state->e1 = e;

    return u;

}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
