#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <ctime>
#include <vector>
#include "rand.h"

int kalman_filter(double duration,double dt){
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::normal_distribution<double> distribution(0,1.0);


    double measnoise=10;
    double accelnoise=0.2;
    Eigen::Matrix<double,2,2> matrix_a;
    matrix_a<<1,dt,0,1;

    Eigen::Matrix<double,2,1> matrix_b;
    matrix_b<<dt*dt/2,dt;

    Eigen::Matrix<double,1,2> matrix_c;
    matrix_c<<1,0;

    Eigen::Matrix<double,2,1> matrix_x;
    matrix_x<<0,0;

    Eigen::Matrix<double,2,1> matrix_xhat=matrix_x;
    std::cout<<matrix_xhat<<std::endl;

    Eigen::Matrix<double,1,1> matrix_Sz;
    matrix_Sz<<measnoise*measnoise;
    Eigen::Matrix<double,2,2> matrix_Sw;
    matrix_Sw<<accelnoise*accelnoise*dt*dt*dt*dt/4,accelnoise*accelnoise*dt*dt*dt/2,
                accelnoise*accelnoise*dt*dt*dt/2,accelnoise*accelnoise*dt*dt;

    Eigen::Matrix<double,2,2> matrix_P=matrix_Sw;

    std::vector<double> x_al;
    std::vector<double> x_measured;
    std::vector<double> x_filtered;

    int abc=(int)(duration/dt);
    for(int i=0;i<abc;i++){
        double u=1;
        Eigen::Matrix<double,2,1> matrix_ProcessNoise;
        matrix_ProcessNoise<<accelnoise*dt*dt*distribution(rd)/2,accelnoise*dt*distribution(rd);

        matrix_x=matrix_a*matrix_x+matrix_b*u+matrix_ProcessNoise;

        Eigen::Matrix<double,1,1> matrix_MeasNoise;
        matrix_MeasNoise<<measnoise*distribution(rd);


        Eigen::Matrix<double,1,1> matrix_y;
        matrix_y=matrix_c*matrix_x+matrix_MeasNoise;
        std::cout<<matrix_y<<std::endl;
        matrix_xhat=matrix_a*matrix_xhat+matrix_b*u;

        Eigen::Matrix<double,1,1> matrix_Inn;
        matrix_Inn=matrix_y-matrix_c*matrix_xhat;

        Eigen::Matrix<double,1,1> matrix_s;
        matrix_s=matrix_c*matrix_P*matrix_c.transpose()+matrix_Sz;

        Eigen::Matrix<double,2,1> matrix_K;
        matrix_K=matrix_a*matrix_P*matrix_c.transpose()*matrix_s.inverse();

        matrix_xhat=matrix_xhat+matrix_K*matrix_Inn;

        matrix_P=matrix_a*matrix_P*matrix_a.transpose()-matrix_a*matrix_P*matrix_c.transpose()*
                matrix_s.inverse()*matrix_c*matrix_P*matrix_a.transpose()+matrix_Sw;

        x_measured.push_back(matrix_y(0,0));
        x_filtered.push_back(matrix_xhat(1,0));
    }
    for(int i=0;i<x_measured.size();i++)//size()容器中实际数据个数
    {
        std::cout<<x_measured[i]<<",";
    }
    std::cout<<std::endl;
    for(int i=0;i<x_filtered.size();i++)//size()容器中实际数据个数
    {
        std::cout<<x_filtered[i]<<",";
    }


}

int main() {

    kalman_filter(10,0.1);
//    double GaussianNoise;
//    GaussianNoise=generateGaussianNoise(0, 1);

    //std::default_random_engine generatoraa;



    return 0;
}
