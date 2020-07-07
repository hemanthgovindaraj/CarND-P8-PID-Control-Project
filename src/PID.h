#ifndef PID_H
#define PID_H
#include <vector>

using std::vector;

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  void Twiddle(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError(vector<double>,double);

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;
  
  //other variables
  int iterator;
  vector<double> dp;
  double best_err;
  double total_error;
  bool Kp_incremented;
  bool Kd_incremented;
  bool Ki_incremented;
  bool Kp_decremented;
  bool Kd_decremented;
  bool Ki_decremented;
  bool kp_updated;
  bool kd_updated;
  bool ki_updated;
};

#endif  // PID_H