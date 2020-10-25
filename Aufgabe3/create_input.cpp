#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include "dialog.h"
#include "ui_dialog.h"

using namespace std;

int GetLogBin( float* logscale, int nBins, float n )
{
  for( int i = 1; i < nBins; i++ ) {
    if( n < logscale[i] ) return i-1;
  }
  return nBins-1;
}

int GetPartNum( int* pl, int n_p, int p_id )
{
  for( int i = 0; i < n_p; i++ ) {
    if( pl[i] == p_id ) return i;
  }
  std::cout<<"Error! Wrong particle id!\n";
  return -1;
}

int main( int argc, const char* argv[] )
{
  //
  float p_max_inc(3.14), p_step_inc(3.14 / 20), Ninc(20), Nazm(20), p_max_azm(3.14), p_step_azm(6.28 / 20);
  int particle_list[28] = { -211, 111, 211, 2112, 2212, 311, 321, 221, 3122, -321,
			-311, 3212, 3222, 3112, 3322, 3312, 22, -2112, -2212, -3122,
			-3212, -3112, -3222, 3334, -3322, -3312, 333, -3334 };
  int particle_list1[28] = { -211, 111, 211, 2112, 2212, 311, 321, 221, 3122, -321,
  			-311, 3212, 3222, 3112, 3322, 3312, 22, -2112, -2212, -3122,
  			-3212, -3112, -3222, 3334, -3322, -3312, 333, -3334 };
  sort(&particle_list1[0], &particle_list1[28]);
  float p_logbin[20] = { 0.13229363,  0.28208885,  0.45170104,  0.64375183,  0.86120972,  1.1074359,
      1.38623623,  1.70192008,  2.05936688,  2.46410162,  2.92238018,  3.44128607,
      4.02883991,  4.69412337,  5.44741959,  6.3003721,   7.26616479,  8.3597257,
      9.59795775, 11. };
  //
  const int ii(28), jj(20), kk(20), ll(20);
  int matrix[ii][jj][kk][ll];
  //
  // ---
  int a_phi_s[20];
  int a_teta_s[20];
  int mom_s[20];
  for( int i = 0; i < 20; i++ ) {
      a_phi_s[i] = 0;
      a_teta_s[i] = 0;
      mom_s[i] = 0;
  }

  int n_part_by_type[ii][2];
  for( int i = 0; i < 2; i++ ) {
    for( int j = 0; j < ii; j++ ) {
      n_part_by_type[j][i] = 0;
    }
  }
  // ---
  for( int iqgp = 0; iqgp < 2; iqgp++ ) {
    int n_event = 0;
    for( int ifl = 1; ifl < 6; ifl++ ) {
      string prefix_qgp = "nqgp/";
      if( iqgp ) prefix_qgp = "qgp/";
      string prefix_infile = "phsd50csr.auau.31.2gev.centr.0000";
      string prefix_outfile = "phsd50csr.auau.31.2gev.centr.";
      if( ifl > 9 ) prefix_infile = "phsd50csr.auau.31.2gev.centr.000";
      std::string prefix_nfile = std::to_string(ifl);
      ifstream ifile((prefix_qgp+prefix_infile+prefix_nfile+".dat").data());
      if(!ifile) return 1;
      for( int iev = 0; iev < 1000; iev++ ) {
        int nOfParticles, int_tmp;
        float float_tmp;
        string prefix_outdir = "dataset_new/";
        std::string prefix_nev = std::to_string(n_event);
        ifile >> nOfParticles >> int_tmp >> int_tmp >> float_tmp >> int_tmp;
        ifile >> int_tmp >> float_tmp >> float_tmp >> float_tmp >> float_tmp >> float_tmp >> float_tmp >> float_tmp >> float_tmp;
        for( int i = 0; i < ii; i++ )
          for( int j = 0; j < jj; j++ )
            for( int k = 0; k < kk; k++ )
              for( int l = 0; l < ll; l++ )
        	matrix[i][j][k][l] = 0;
        //
        const int max_len = 10;
        float line[max_len];
        const char ch = '\n';
        char l1[1000];
        ifile.getline(l1, 0, ch);
        for( int iP = 0; iP < nOfParticles; iP++ ) {
          ifile.getline(l1, 999,ch);
          string l1s1(l1);
          stringstream stream(l1s1);
          int real_len = max_len;
          for( int i = 0; i < real_len; i++ ) {
            stream >> line[i];
            if(!stream) {real_len = i; break;}
          }
          bool get_particle = binary_search(&particle_list1[0], &particle_list1[28], int(line[0]));
          if(!get_particle) continue;
          if( real_len < 8 ) { std::cout<<"Error! Array size is wrong! real_len = "<<real_len<<"\n"; continue; }
          float p_abs_val = sqrt(line[2]*line[2] + line[3]*line[3]  + line[4]*line[4]);
          float p_azm = atan2(line[3], line[2]);
          float p_inc = acos(line[4] / p_abs_val);

          int p_id = GetPartNum( particle_list, 28, int(line[0]) );	// Particle Id
          int p_ind = GetLogBin( p_logbin, 20, p_abs_val ) + 1;		// Momentum
          int p_azm_ind = int((p_azm + 3.14) / p_step_azm);		// Azimuth angle
          int p_inc_ind = int(p_inc / p_step_inc);			// Inclination angle
          matrix[p_id][p_ind][p_azm_ind][p_inc_ind]++;
          // ---
          n_part_by_type[p_id][iqgp]++;

          a_phi_s[p_inc_ind]++;
          a_teta_s[p_azm_ind]++;
          mom_s[p_ind]++;
          // ---
        }
        //
        ofstream jfile((prefix_outdir+prefix_qgp+prefix_infile+prefix_outfile+prefix_nev+"_event.dat").data(),std::ios::out|std::ios::app);
        for( int i = 0; i < ii; i++ ) {
          for( int j = 0; j < jj; j++ )
            for( int k = 0; k < kk; k++ )
              for( int l = 0; l < ll; l++ )
        	jfile << matrix[i][j][k][l] << " ";
          jfile << "\n";
        }
        jfile.close();
        n_event++;
      }
      ifile.close();
    }
  }
  // ---
#ifdef STAT
  for( int i = 0; i < 2; i++ ) {
    std::cout<<">>> QGP: "<<i<<"\n";
    for( int j = 0; j < ii; j++ ) {
      std::cout<<" ---> j: "<<j<<";   PDG: "<<particle_list[j]<<";   nParticles: "<<n_part_by_type[j][i]<<"\n";
    }
  }
  std::cout<<"\n";
  for( int i = 0; i < 20; i++ ) {
      std::cout<<"> i: "<<i<<";   a_phi_s: "<<a_phi_s[i]<<";   a_teta_s: "<<a_teta_s[i]<<";   mom_s: "<<mom_s[i]<<"\n";
  }
#endif
  // ---
}
