int cceffn(int run_number, int sector_number, float *point, float *dir, float *Nphe, float *Nphe_err, float *cc_eff);

int test_vlas(){
float Nphe ;
float Nphe_err ;
float cc_eff ;
//gSystem->Load("cc_stuff_c.so");
float point[4];
float dir[4];

point[0]=3;
point[1]=2;
point[2]=4;
dir[0]=0.4;
dir[1]=0.5;
dir[2]=0.3;

int value;
cceffn(42146,2,point,dir,&Nphe,&Nphe_err,&cc_eff) ;
cout << "Nphe_err= " << Nphe_err << endl;
return 0;
}
//int cceffn(int run_number, int sector_number, float *point, float *dir, float *Nphe, float *Nphe_err, float *cc_eff)

  
