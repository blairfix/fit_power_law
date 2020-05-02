#include <RcppArmadillo.h>
#include <math.h>

/*
This function uses the maximum likelihood method to find
the best fit power law exponent for the tail of vector 'pay'
where the tail is defined by the cutoff percentiles in 'percentile_cutoff'.
*/

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]


double fit_power_law(  arma::vec pay, double percentile_cutoff)
{

    int n_total = pay.size();
    int n_top = percentile_cutoff*pay.size();
    int top_begin = n_total - n_top;

    std::nth_element(pay.begin(), pay.end() - n_top, pay.end());

    double xmin = arma::min( pay.subvec(top_begin, n_total-1) );
    double sum_log = 0;

    for(int i = top_begin; i < n_total ; ++i){
        sum_log = sum_log + std::log( pay[i] / xmin );
    }

    double alpha = 1 + n_top/sum_log;

    return alpha;

}
