#include "PID.h"
#include <vector>
#include <iostream>
#include <numeric>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;

  p_error=0.0;
  i_error=0.0;
  d_error=0.0;
  
  iterator=0;
  dp={0.01,0.1,0.00025};
  best_err = 1;
  total_error = 0;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  d_error = cte - p_error;
  p_error = cte;
  i_error+= cte;

}

double PID::TotalError(vector<double> p,double cte) {
  /**
   * TODO: Calculate and return the total error
   */
  double steer_value = 0;
  total_error = 0;

  if(iterator<200)
  {
    UpdateError();
    steer_value = -(p_error*p[0])-(d_error*p[1])-(i_error*p[2]);
    if(i>99)
    {
      total_error+= pow(cte,2);
    }
  }
  return steer_value;  // TODO: Add your total error calc here!
}

double PID::Twiddle(double cte)
{
  
  UpdateError(cte);
  iterator+=1;
  double err=cte;
  cout<<"Average error"<<err<<"CTE"<<cte<<endl;
  cout<<"accumulation"<<accumulate(dp.begin(),dp.end(),0.0);

  if(accumulate(dp.begin(),dp.end(),0.0)>0.00001)
  {
    int i = (iterator%9);
    if(i==1)
    {
      Kp+=dp[0];
    }
    else if(i==2)
    {
      if(err<best_err)
      {
        best_err = err;
        dp[0]=dp[0]*1.1;
      }
      else
      {
        Kp-=2*dp[0];
      }
    }
    else if(i==3)
    {
      if(err<best_err)
      {
        best_err = err;
        dp[0]=dp[0]*1.1;
      }
      else if(err>best_err)
      {
        Kp+=dp[0];
        dp[0]=dp[0]*0.9;
      }
    }
    else if(i==4)
    {
      Kd+=dp[1];
    }
    else if(i==5)
    {
      if(err<best_err)
      {
        best_err = err;
        dp[1]=dp[1]*1.1;
      }
      else
      {
        Kd-=2*dp[1];
      }
    }
    else if(i==6)
    {
      if(err<best_err)
      {
        best_err = err;
        dp[1]=dp[1]*1.1;
      }
      else if(err>best_err)
      {
        Kd+=dp[1];
        dp[1]=dp[1]*0.9;
      }
    }
    else if(i==7)
    {
      Ki+=dp[2];
    }
    else if(i==8)
    {
      if(err<best_err)
      {
        best_err = err;
        dp[2]=dp[2]*1.1;
      }
      else
      {
        Ki-=2*dp[2];
      }
    }
    else if(i==0)
    {
      if(err<best_err)
      {
        best_err = err;
        dp[2]=dp[2]*1.1;
      }
      else if(err>best_err)
      {
        Ki+=dp[2];
        dp[2]=dp[2]*0.9;
      }
    }
    
  }
  cout<<"Best error = "<<best_err<<endl;
  cout<<"Kp Kd and Ki = "<<Kp<<" "<<Kd<<" "<<Ki<<endl;
  return TotalError({Kp,Kd,Ki});
}