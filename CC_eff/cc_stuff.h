int cc_vcrpl_(float *r0, float *dir, float *plane_par,
              float *dist, float *cross_point);
int cc_vcrpl(float *r0, float *dir, float *plane_par,
              float *dist, float *cross_point);
int cceffn(int run_number, int sector_number, float *point,
      float *dir, float *Nphe,float *Nphe_err, float *cc_eff);
int cceffn_(int *run_number, int *sector_number, float *point,
      float *dir, float *Nphe,float *Nphe_err, float *cc_eff);
int cceffn1(int run_number, int sector_number, float *point,
      float *dir, float *Nphe,float *Nphe_err, float *cc_eff,
      float *Theta, float *Phy);
int cceffn1_(int *run_number, int *sector_number, float *point,
      float *dir, float *Nphe,float *Nphe_err, float *cc_eff,
      float *Theta, float *Phy);
int cc_n_ini(int run_number);
int cc_n_ini_(int *run_number);
float cc_eff_nphe(float *nphe);
int cceffn_out(int run_number, int sector_number, float *point,
      float *dir, float *Nphe,float *Nphe_err, float *cc_eff,
      float *Theta, float *Phy);
int cceffn_out_(int *run_number, int *sector_number, float *point,
      float *dir, float *Nphe,float *Nphe_err, float *cc_eff,
      float *Theta, float *Phy);
int cc_n_ini_out(int run_number);
int cc_n_ini_out_(int *run_number);
float cc_eff_out(float *nphe);
