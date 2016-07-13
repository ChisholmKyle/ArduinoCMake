
#ifndef ARD_PID_H
#define ARD_PID_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArdPidState {
    double e1;
    double e2;
    double u1;
    double u2;
} ArdPidState;

typedef struct ArdPidParam {
    double kp;
    double ki;
    double kd;
    double umin;
    double umax;
    double tf;
} ArdPidParam;

inline void ard_pid_reset(ArdPidState *state) {

    state->e1 = 0.0;
    state->e2 = 0.0;

    state->u1 = 0.0;
    state->u2 = 0.0;

}

// forwards euler
inline double ard_pid_run_fwd(const double des, const double meas,
                             ArdPidState *state, const double ts,
                             const ArdPidParam *param) {

    /* error */
    double e = des - meas;

    /* calculate output */
    double t2 = 1.0/param->tf;
    double t3 = param->kp*param->tf;
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


// backwards euler
inline double ard_pid_run_back(const double des, const double meas,
                            ArdPidState *state, const double ts,
                            const ArdPidParam *param) {

    /* error */
    double e = des - meas;

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

// trapezoidal
inline double ard_pid_run_trap(const double des, const double meas,
                            ArdPidState *state, const double ts,
                            const ArdPidParam *param) {

    /* error */
    double e = des - meas;

    /* calculate output */
    double t2 = ts*ts;
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


#ifdef __cplusplus
}
#endif

#endif
