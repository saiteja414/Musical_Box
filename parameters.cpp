  double hx=1 , hy=209.0/256, hz=190.0/256 ; 
  double lbh = 3 , lbl = 20, lbw = 15,lcr = 158.0/255,lcg =20.0/256,lcb =200.0/256,lca =1;
  double ubh = 10 , ubl = 20, ubw = 15,ucr = 158.0/255,ucg = 20.0/256,ucb =200.0/256, uca =1;
  double rt11 = 0.8, rt12 = 1.6, ht1 = 2.5, ct1r = 158.0/255, ct1g = 20.0/256, ct1b = 120.0/256, ct1a = 1.0;
  double rt2  = rt11             , ct2r = 0.4, ct2g = 0.5, ct2b = 0.6, ct2a = 1.0;
  double rt4  = rt12             , ct4r = 0.4, ct4g = 0.5, ct4b = 0.6, ct4a = 1.0;
  double rt31 = rt2 , rt32 = rt2 , ht3 = 2, ct3r = 0.3, ct3g = 0.3, ct3b = 0.3, ct3a = 1.0;
  double nr1  = 0.6 , nr2  = 1 , hn  = 1.5, cnr  = 0.4, cng  = 0.5, cnb  = 0.6, cna  = 1.0;
  double rh1  = nr2  , chr  = 0.4, chg  = 0.5, chb  = 0.6, cha  = 1.0;
  double rsj1 = 0.2 , csjr = 0.4, csjg = 0.5, csjb = 0.6, csja = 1.0;
  double rbj1 = 0.4 , cbjr = 0.3, cbjg = 0.3, cbjb = 0.6, cbja = 1.0;
  double rhn1 = 2 , rhn2 = 2 , hhn = 2, chnr = 0.4, chng = 0.5, chnb = 0.6, chna = 1.0;
  double rua1  = rbj1 , rua2  = rsj1 , hua  = 2, cuar  = 0.4, cuag  = 0.5, cuab  = 0.6, cuaa  = 1.0;
  double rla1  = rsj1 , rla2  = rsj1 * 0.75 , hla  = 2, clar  = 0.4, clag  = 0.5, clab  = 0.6, claa  = 1.0;
  double rul1  = rbj1 , rul2  = rsj1 , hul  = 3.7, culr  = 0.88, culg  = 0.90, culb  = 0.85, cula  = 1.0;
  double rll1  = rsj1 , rll2  = rsj1 , hll  = 3.7 ; 
  double joint_length = .4;
  double lens_radius = .25;

  double bxc[6] =  { 0,  -9.4, 10 ,  0,  0,  0};
  double lbx[6] =  { 0,  15, 0 ,  0,  0,  0};
  double ubx[6] =  { 0,  0, -1 * lbw ,  -90,  180,  180};
  double t1x[6] =  {0, 12.5, 2, 0, 0, 0};
  double t2x[6] =  { 0.0,  -0.2 ,  0, 0, 0,  180};  
  double t3x[6] =  { 0.0,  0.2 ,  0, 0, 0,  0};   
  double t4x[6] =  { 0.0,  2.5 ,  0, 0, 0,  0};   
  double njx[6] =  { 0.0,  0.7 ,  0, 0, 0,  0};   
  double nx[6] =  { 0.0,  0.2 ,  0.3, 0, 0,  0};   
  double hdx[6] =  { 0.0,  hn  , 0, 0, 0,  0};  
  double slx[6] =  { rt12,  ht1 - rbj1/2 ,  0, 0, 0,  -90};  
  double srx[6] =  { -1 * rt12,  ht1 - rbj1/2,  0, 0, 180,  -90};   
  double ualx[6] =  {0,0,0,0,0,-90};
  double uarx[6] =  {0,0,0,0,0,-90};
  double elx[6] =  {0,hua,0,0,180,0};
  double erx[6] =  {0,hua,0,0,180,0};
  double lalx[6] =  {0,0,0,0,0,0};
  double larx[6] =  {0,0,0,0,0,0};
  double ullx[6] =  {0,0,0,0,0,0};
  double ulrx[6] =  {0,0,0,0,0,0};
  double hlx[6] =  {rt32-rbj1,ht3,0,0,0,0  };
  double hrx[6] =  {-1*rt32+rbj1,ht3,0,0,0,0 };
  double klx[6] =  {0,hul,0,0,180,0 };
  double krx[6] =  {0,hul,0,0,180,0};
  double lllx[6] =  {0,0,0,0,0,0};
  double llrx[6] =  {0,0,0,0,0,0};
  double alx[6] =  {0,hll,0,0,0,0};
  double arx[6] =  {0,hll,0,0,0,0};
  double wlx[6] =  {0,hla-rsj1*.5,0,0,0,180};
  double wrx[6] =  {0,hla-rsj1*.5,0,0,0,180};
  double footLx[6] =  {0,0,0.2,0,0,0};
  double footRx[6] =  {0,0,0.2,0,0,0};
  double eyeLx[6] =  {-0.3,0.9,0.7,0,0,0};
  double eyeRx[6] =  {0.3,0.9,0.7,0,0,0};
  double mx[6] =  {0,.5,0.7,0,0,180};
  double tx[6] =  {0,.4,0.8,0,0,0};


  double cx=0.8,cy=0.8,cz=0.8; 

  double el = .5, eh = 0.8 ; 
  double ml = .8, mh = .4 ; 
  double cbj = 0.3, csj = 0.1 ; 
  double cbe[3] = {1,1,3} ;
  double cle[3] = {0.2,0.1,1.3} ;
  double ctail1[3] = {0.2,0.1,1} ;
  double ctail2[3] = {0.1,0.05,1} ;
  double ctail3[3] = {0.05,0.0,1} ;


  double centroid[6] = {5,5,3,0,0,0};
  double cbellyx[6] = {-1.5,0,0,0,0,-90};

  double cl1j1x[6] = {0.7,1,0.7,0,0,270};
  double cl2j1x[6] = {0.7,1,-0.7,0,0,270};
  double cl3j1x[6] = {0.7,2.7 ,0.7,0,0,270};
  double cl4j1x[6] = {0.7,2.7,-0.7,0,0,270};

  double cl1j2x[6] = {0,cle[2],0,90,0,0};
  double cl2j2x[6] = {0,cle[2],0,90,0,0};
  double cl3j2x[6] = {0,cle[2],0,90,0,0};
  double cl4j2x[6] = {0,cle[2],0,90,0,0};

  double cl1x[6] = {0,0,0,0,0,0};
  double cl2x[6] = {0,0,0,0,0,0};
  double cl3x[6] = {0,0,0,0,0,0};
  double cl4x[6] = {0,0,0,0,0,0};

  double cpaw1x[6] = {0.2,0,0,0,0,0};
  double cpaw2x[6] = {0.2,0,0,0,0,0};
  double cpaw3x[6] = {0.2,0,0,0,0,0};
  double cpaw4x[6] = {0.2,0,0,0,0,0};

  double ct1x[6] = {0,0,0,0,0,0};
  double ct2x[6] = {0,0,0,0,0,0};
  double ct3x[6] = {0,0,0,0,0,0};

  double ct1j1x[6] = {-1*cbe[0]+0.2,cbe[2],0,0,180,0};
  double ct1j2x[6] = {0,ctail1[2],0,0,0,-60};
  double ct1j3x[6] = {0,ctail2[2],0,0,180,-60};


  double chdx[6] = {0,-cbe[0],0,180,0,0};

  double cbumx[6] = {0,cbe[2],0,0,0,0};

  double cleyex[6] = {-0.5,-0.6,-0.3,0,0,0};
  double creyex[6] = {-0.5,-0.6, 0.3,0,0,0};


  double clamp[4] = {0.3,0.4,0.3,1} ; // colors
  double dlamp[4] = {3,1,4,10} ; // dimensions
  double plamp[6] = {0,7,0,0,0,0} ; // parameters

  double clamp_base[4] = {0.3,0.4,0.3,0.6} ; // colors
  double dlamp_base[4] = {.5,.5,7,1} ; // dimensions
  double plamp_base[6] = {-8,2,12,0,0,0} ; // parameters
  

  double proom[6] = {-50,-20,60,0,0,0} ; // parameters




  // table
  double angle = 45.0;
  double ctableTop[4] = {0.3,0.4,0.3,1} ; // colors
  double dtableTop[4] = {15,15,1,1} ; // dimensions
  double ctableL[4] = {0.3,0.4,0.3,1} ; // colors 
  double dtableL[4] = {1,1,10,1} ; // dimensions
  double ptableTop[4] = {0,dtableL[2]*sin(angle) - 2,0} ; // parameters

  double ptableL1[6] = {0,0,0,0,45,angle} ; // parameters
  double ptableL2[6] = {0,0,0,0,135,angle} ; // parameters
  double ptableL3[6] = {0,0,0,0,225,angle} ; // parameters
  double ptableL4[6] = {0,0,0,0,315,angle} ; // parameters
  double ptableL5[6] = {0,0,0,0,45,180-angle} ; // parameters
  double ptableL6[6] = {0,0,0,0,135,180-angle} ; // parameters
  double ptableL7[6] = {0,0,0,0,225,180-angle} ; // parameters
  double ptableL8[6] = {0,0,0,0,315,180-angle} ; // parameters

  // double ptableL12[6] = {0,0,0,0,0,0} ; // parameters
  // double ptableL22[6] = {0,0,0,0,0.0} ; // parameters
  // double ptableL32[6] = {0,0,0,0,0.0} ; // parameters
  // double ptableL42[6] = {0,0,0,0,0,0} ; // parameters

  // chair
  double cchair[4] = {0.3,0.2,0.7,1} ; // color of chair base
  double cchairl[4] = {0.1,0.1,0.3,1} ; // color of legs
  double dchair[3] = {1,8,8} ;  // dimensions chair base
  double dchairl[3] = {0.5,0.5,12} ; // dimension of legs
  double dchairr[3] = {2,dchair[1],0.2} ; // dimensions chair rest
  // chair
  double pchairL1[6] = {-dchair[1]/2.0,0,0,0,0,        180} ;
  double pchairL2[6] = { dchair[1]/2.0,0,-dchair[2],0,0,180} ;
  double pchairL3[6] = { dchair[1]/2.0,0,0,0,0,        180} ;
  double pchairL4[6] = {-dchair[1]/2.0,0,-dchair[2],0,0,180} ;
  double pchairA1[6] = {-dchair[1]/2.0,0,0,0,0,0} ;
  double pchairA2[6] = { dchair[1]/2.0,0,0,0,0,0} ;
  double pchairR[6]  = {dchair[1]/2.0,dchairl[2],0,0,0,0} ;

  //cupboard
  double dcb[3]  = {1,20,10} ; // dimensions
  double dcbl[3] = {.1,20,10} ; // dimensions
  double db[3] = {5,40,25} ; // dimensions
  double dbl1[3] = {.4,25,16} ; // dimensions
  double dbl2[3] = {.4,25,18} ; // dimensions
  double ddoor[3] = {.4,35,15} ; // dimensions
  double ddk[3] = {.4} ; // dimensions
  double pd[6]  = {20,17.5,0,0,90,90} ; // initial parameters
  double pdk[6]  = {-3,-ddk[0],-ddoor[2] + ddk[0]*2 ,0,0,0} ; // initial parameters
  double pcb[6]  = {25,25,-20,90,-90,0} ; // initial parameters
  double pcbl[6] = {0,.1,0,60,0,0} ; // initial parameters
  
  double pdoor[6] = {20,17.5,0,60,0,0} ; // initial parameters

  double pb[6]  = {-25,5,20,0,90,0} ; // initial parameters
  double pbl1[6] = {-1* db[1]/2 - dbl2[0]/2,-dbl2[2] * .7,-1*db[2]/2,90,0,90} ; // initial parameters
  double pbl2[6] = {1* db[1]/2 + dbl2[0]/2,-dbl2[2]*.7,-1*db[2]/2,90,0,90} ; // initial parameters

  double ccb[4] = {0.3,0.3,0.5,1} ; 
  double ccbl[4] = {0.3,0.5,0.4,1} ;
  
  double cdoor[4] = {0.3,0.5,0.4,1} ;
  double cdk[4] = {0.3,0.5,0.4,1} ;

  double cb[4] = {0.3,0.3,0.5,1} ; 
  double cbl1[4] = {0.3,0.5,0.4,1} ;
  double cbl2[4] = {0.3,0.5,0.4,1} ;

