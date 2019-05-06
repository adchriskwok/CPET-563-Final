% Command Inputs
fs        = 1000  ;% [Hz]     Update rate
fdc_trim  = 0.1  ;% Trim throttle setting
Ka    = [ 4  4   2 ];% Angle gain vector
Kw    = [ .01   .01    .2  ];% Gyro gain vector
Kwi       = [  0     0    0  ];% Gyro integral gain
          
% Angle Estimator
Kcfw      = 0.99;% [-] Complementary filter gyro gain
Kcfa      = 0.01;% [-] Complementary filter accel gain

Kh    = .6;% [1/s]        Altitude gain
Khd   = .3;% [1/s]        Altitude rate gain
Khdi  = 1;% [1/s]        Altitude rate integral gain

% Mixing Matrix
Kmixing = [  1   1   1  -1    % hdot (lift)           
             1  -1   1   1    % Mx 
             1  -1  -1  -1    % My
             1   1  -1   1  ];% Mz

% Limiters
vel_cmd_lim  = 0.5        ;% [m/s]    Veloctiy command limiter
hdot_cmd_lim = 0.5        ;% [m/s]    Altitude rate command limiter
tilt_cmd_lim = 50*pi/180  ;% [rad]    Tilt command limiter
w_cmd_lim    = 200        ;% [rad/s]  Rate command limiter

%nv_filt = 3;
fdc_ic = 0;
TestAxisSelect = 0;
UsePosDiffVelocity = 1;
RunOnHardware = 1;

UseSmallAngleApprox = 0;
UseTrueThetaPhi = 0;