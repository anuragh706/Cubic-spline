#include <iostream>
#include<bits/stdc++.h>
#include<cmath>
using namespace std;

int main()
{
    //file handling part
    ifstream fin;
    ofstream fout;
    fin.open("signdata.csv");
    fout.open("signans.csv");

    //Taking inputs for spiral curve
    //Inputs of form x(t) and y(t) where t is a parameter
    cout<< "This is a solution for cubic spline interpolation problem for a spiral curve."<<"\n"<< "(20 points)"<<endl;
    int n=12;       //Number of points
    double x[n+1], y[n+1];
     // defining parameter array t
    double t[n+1];
    for(int i=0; i<n+1; i++)
    {
      t[i]= 0.0 + i;
    }
    char buff; // a buffer character just to shift to next column
    for(int i=0; i<n+1; i++)
    {
        fin>> x[i];
        fin>> buff;
        fin>> y[i];
    }
    /* //demo case for y
     for(int i=0; i<n+1; i++)
     {
         y[i]= t[i]*t[i];
         //cout<<y[i]<<endl;
     }
     // demo case for x
       for(int i=0; i<n+1; i++)
     {
         x[i]= t[i]*t[i]*t[i];
         //cout<<y[i]<<endl;
     } */
    //Applying cubic spline algorithm on y
    double hy[n];
    for(int i=0; i<(n); i++)
    {
        hy[i]= t[i+1]-t[i];
        //cout<< hy[i]<< endl;
    }
    double alphay[n];
    for(int i=1; i<n; i++)  //alphay[0] is not required
    {
        alphay[i]= (3/hy[i])*(y[i+1]-y[i]) - (3/hy[i-1])*(y[i]-y[i-1]);
        //cout<< alphay[i]<< endl;
    }
    double ly[n], muy[n], zy[n];
    ly[0]= 1.0;
    muy[0]= 0.0;
    zy[0]= 0.0;
    for(int i=1; i<n; i++)
    {
        ly[i]= 2*(t[i+1]-t[i-1]) - (hy[i-1]*muy[i-1]);
        //cout<<ly[i]<<endl;
        muy[i]= (hy[i]/ly[i]);
        //cout<< muy[i]<< endl;
        zy[i]= (alphay[i]-(hy[i-1]*zy[i-1]))/ly[i];
        //cout<< zy[i]<<endl;
    }
    ly[n]=1.0;
    zy[n]=0.0;
    double by[n], cy[n], dy[n];
    cy[n]=0.0;
    for(int i=(n-1); i>=0; i--)
    {
       cy[i]=  zy[i] - (muy[i]*cy[i+1]);
       //cout<< cy[i] << endl;
       by[i]=  ((y[i+1]-y[i])/(hy[i])) - (hy[i]*(cy[i+1]+2*cy[i]))/3;
       //cout<< by[i]<<endl;
       dy[i]=  (cy[i+1]-cy[i])/(3*hy[i]);
       //cout<< dy[i]<< endl;
    }
    double ay[n];
    for(int i=0; i<n; i++)
    {
        ay[i]= y[i];
        //cout<<ay[i]<<endl;
    }
    // Testing
    for(int i=0; i<n; i++)
    {
        //cout<< ay[i] <<" "<< by[i]<< " "<< cy[i]<< " "<< dy[i]<<" "<< hy[i]<< endl;
    }
    //Applying cubic spline algorithm on x
    double hx[n];
    for(int i=0; i<(n); i++)
    {
        hx[i]= t[i+1]-t[i];
        //cout<< hx[i]<< endl;
    }
    double alphax[n];
    for(int i=1; i<n; i++)  //alphax[0] is not required
    {
        alphax[i]= (3/hx[i])*(x[i+1]-x[i]) - (3/hx[i-1])*(x[i]-x[i-1]);
        //cout<< alphax[i]<< endl;
    }
    double lx[n], mux[n], zx[n];
    lx[0]= 1.0;
    mux[0]= 0.0;
    zx[0]= 0.0;
    for(int i=1; i<n; i++)
    {
        lx[i]= 2*(t[i+1]-t[i-1]) - (hx[i-1]*mux[i-1]);
        //cout<<lx[i]<<endl;
        mux[i]= (hx[i]/lx[i]);
        //cout<< mux[i]<< endl;
        zx[i]= (alphax[i]-(hx[i-1]*zx[i-1]))/lx[i];
        //cout<< zx[i]<<endl;
    }
    lx[n]=1.0;
    zx[n]=0.0;
    double bx[n], cx[n], dx[n];
    cx[n]=0.0;
    for(int i=(n-1); i>=0; i--)
    {
       cx[i]=  zx[i] - (mux[i]*cx[i+1]);
       //cout<< cx[i] << endl;
       bx[i]=  ((x[i+1]-x[i])/(hx[i])) - (hx[i]*(cx[i+1]+2*cx[i]))/3;
       //cout<< bx[i]<<endl;
       dx[i]=  (cx[i+1]-cx[i])/(3*hx[i]);
       //cout<< dx[i]<< endl;
    }
    double ax[n];
    for(int i=0; i<n; i++)
    {
        ax[i]= x[i];
        //cout<<ax[i]<<endl;
    }
    // Testing
    for(int i=0; i<n; i++)
    {
        //cout<< ax[i] <<" "<< bx[i]<< " "<< cx[i]<< " "<< dx[i]<<" "<< hx[i]<< endl;
    }
    //writing in spiralans.csv
    float s[n*100]; // helping variable
    s[0]=0.0;
    for(int i=1; i<((n)*100); i++)
    {
        s[i]= s[i-1]+ 0.01;
        //cout<<s[i]<<endl;
    }
    double xans[n*100], yans[n*100];
    int intermediate;
    for(int i=0; i< (n*100); i++)
    {
        intermediate= int(s[i]);
        float tp; // a temporary variable for computation
        tp= s[i]- intermediate;
        //cout<< tp<< endl;
        //cout<< intermediate<<endl;
        xans[i]= (dx[intermediate]*(tp*tp*tp))+ (cx[intermediate]*(tp*tp))+ (bx[intermediate]*tp)+ ax[intermediate];
        yans[i]= (dy[intermediate]*(tp*tp*tp))+ (cy[intermediate]*(tp*tp))+ (by[intermediate]*tp)+ ay[intermediate];
    }
    for(int i=0; i<(n-2)*100; i++)
    {
        fout<< xans[i]<<","<< yans[i]<<endl;
    }
    fin.close();
    fout.close();
    return 0;
}

