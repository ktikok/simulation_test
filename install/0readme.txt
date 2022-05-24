# type the below lines in install directory
source setenv-cc7-gcc8.sh

# for visualization : 
./bin/DRsim

# for details, look up the 0run_all.sh

phi : 1.5 angle, z axis, 0.026179939 rad
eta : 1 angle, y axis, 0.0174533 rad
tower : 2.5m
energy : 1eV
material : cupper
mac file : cm unit
visualize : red, x, green, y, blue, z

0 >> x : 3050.15 y : 0 z : 33.8885 center_distance : 3050.33


// 51>> x : 2542.6 y : 0 z : 3561.32 center_distance : 4375.83

******************************************* for barrel 51
/DRsim/generator/randx 0
/DRsim/generator/randy 0
/DRsim/generator/theta -0.97694993
/DRsim/generator/phi 0.017453293
/DRsim/generator/y0 -3.170329668
/DRsim/generator/z0 -14.62319386
/gun/particle e-
/gun/energy 1 eV
/run/beamOn 1
******************************************* for barrel 51

-------------------------------------endcap----------------------------------------- 52
0>> x : 2496.81, y : 0, z : 3593.58 center_distance : 4375.83
/DRsim/generator/randx 0
/DRsim/generator/randy 0
/DRsim/generator/theta -0.98975053
/DRsim/generator/phi 0.017453293
/DRsim/generator/y0 -3.1132348
/DRsim/generator/z0 -14.907069
/gun/particle e-
/gun/energy 1 eV
/run/beamOn 1
-------------------------------------endcap----------------------------------------- 52






