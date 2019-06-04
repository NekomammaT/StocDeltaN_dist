// stochastic-delta N solver

#ifndef INCLUDED_StocDeltaN_hpp_
#define INCLUDED_StocDeltaN_hpp_

#include "JacobiPDE.hpp"
#include "SRK32.hpp"

class StocDeltaN: virtual public JacobiPDE, virtual public SRKintegrater
{
protected:
  string model; // model name
  double timestep,Nmax,deltaN;
  int recursion,xpdim,Idim; 
  vector<double> x1traj,p1traj,x2traj,Ntraj,Ndata,calPdata;
  
public:
  StocDeltaN(){}
  StocDeltaN(string Model, vector< vector< vector<double> > > &Site,
	     vector< vector<double> > &XPi, double T0, vector<double> &Params);
  // Model : model name, Site : lattice site, XPi : i.c. for inflaton path, T0 : initial time
  // Params[0] = maxstep, Params[1] = tol, Params[2] = funcNo, Params[3] = rhoc,
  // Params[4] = NoiseDim, Params[5] = timestep, Params[6] = Nmax, Params[7] = deltaN,
  // Params[8] = recursion
  void init_txp(); // initialize time and phase-space value of sample path
  void solve(); // do stochastic-delta N
  void sample(); // obtain 1 sample path
  
  // ---------- plot sample path ----------
  void sample_plot(); 
  void sample_logplot();
  void sample_loglinearplot();
  void sample_loglogplot();
  // --------------------------------------

  // ---------- plot Mn or Cn -------------
  void f_plot(int func);
  void f_logplot(int func);
  void f_loglinearplot(int func);
  void f_loglogplot(int func);
  // --------------------------------------

  void calP_plot(); // plot power spectrum of zeta
  double return_intf(int func); // return interpolated Mn or Cn for current point of sample path
  
  virtual double V(vector<double> &X);
  virtual double VI(vector<double> &X, int I);
  virtual double metric(vector<double> &X, int I, int J);
  virtual double inversemetric(vector<double> &X, int I, int J);
  virtual double affine(vector<double> &X, int I, int J, int K);
  virtual double derGamma(vector<double> &X, int I, int J, int K, int L);

  // ---------- validate to modify them if want -------------------
  //virtual double H(vector<double> &X, vector<double> &P);
  //virtual double DI(int xp, int I, vector< vector<double> > &psv);
  //virtual double DIJ(int xpI, int I, int xpJ, int J, vector< vector<double> > &psv);
  //virtual double gIa(int xp, int I, int alpha, vector< vector<double> > &psv);
  //virtual double CC(int num, vector< vector<double> > &psv, int func);
  //virtual void BoundaryCondition();
  //virtual bool EndSurface(vector< vector<double> > &psv);
  // --------------------------------------------------------------
};

#endif
