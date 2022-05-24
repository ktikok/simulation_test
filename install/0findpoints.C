//50>> x : 2555.53 y : 0 z : 3483.4 center_distance : 4320.28
//51>> x : 2542.6 y : 0 z : 3561.32 center_distance : 4375.83
// 0;
// cx = 3050.15 ;
// cy = 0 ;
// cz = 33.8885 ;
// cd = 3050.33;
// 
// 51;
// cx = 2542.6;
// cy = 0 ;
// cz = 3561.32 ;
// cd = 4375.83;
// 
// 50;
// cx = 2555.53;
// cy = 0 
// cz = 3483.4
// cd = 4320.28

// -------------------------------------endcap-----------------------------------------
// 0>> x : 2496.81, y : 0, z : 3593.58 center_distance : 4375.83
cx = 2496.81;
cy = 0 
cz = 3593.58
cd = 4375.83


pi = TMath::Pi();

cphi = atan(cy/cx);
ctheta = atan(cz/cx);

ophi = cphi+1*pi/180;
otheta = ctheta+1.5*pi/180;

oy = -(tan(ophi)*cx-cy)*(cd-1250)/cd;
oz = -(tan(otheta)*cx-cz)*(cd-1250)/cd;


// xpy=tan(pi/2-ophi);
// xpz=tan(pi/2-otheta);

// yb = xpy*(cx/xpy-cy);

// zb = xpz*(cx/xpz-cz);
// zc = (-cz+xpz*(-cz+zb)/(xpz*xpz+1));
// zd = (cz*cz+(cz-zb)*(cz-zb))/(xpz*xpz+1);
// // oy = cy - cx*tan(ophi)*1800/sqrt(cx*cx+(cx*tan(ophi))*(cx*tan(ophi)));
// // oz = cz - cx*tan(otheta)*1800/sqrt(cx*cx+(cx*tan(otheta))*(cx*tan(otheta)));
// oy = cy - cx*tan(ophi)*1800/sqrt(cx*cx+(cx*tan(ophi))*(cx*tan(ophi)));
// // oz = sqrt(cos(pi/2-otheta)*cos(pi/2-otheta)*(1800*1800-(cx/(2*cx/tan(pi/2-otheta)-cz)*(cx/tan(pi/2-otheta)-cz))*(cx/(2*cx/tan(pi/2-otheta)-cz)*(cx/tan(pi/2-otheta)-cz))));
// // oz = cos(pi/2-otheta)*sqrt(1800*1800+cz*cz*(sin(pi/2-otheta)*sin(pi/2-otheta)+1))-cz*cz*sin(pi/2-otheta)*sin(pi/2-otheta);
// oz = sqrt(1800*1800/(1+xpz+xpz)-zd+zc*zc)-zc;

otheta = -otheta;
oy = oy/10;
oz = oz/10;

// cout << '---------------------------' << endl;
// cout << otheta << '\n' << -0.0372899 << endl;
// cout << ophi << '\n' << 0.0174533 << endl;
// cout << oy << '\n' << -3.142 << endl;
// cout << oz << '\n' << -4.7135 << endl;
// cout << '---------------------------' << endl;

cout << '---------------------------' << endl;
cout << otheta << endl;
cout << ophi << endl;
cout << oy << endl;
cout << oz << endl;
cout << '---------------------------' << endl;

// /DRsim/generator/theta -0.0372899;
// /DRsim/generator/phi 0.0174533;
// /DRsim/generator/y0 -3.142;
// /DRsim/generator/z0 -4.7135;
// /gun/particle e-;
// /gun/energy 1 eV;
// /run/beamOn 1;

