/*                           SCIENTIFIC COMPUTING
                               MIDSEM ASSIGNMENT
****************************************************************************************

NAME - ANURAAG KHANDAGLE
ROLL NUMBER - 130123007


****************************************************************************************
*/
#include <iostream>
#include<bits/stdc++.h>               // library to reduce the time
#include<cmath>						 //library to use the modf function - to extract the fractional part of a number					
using namespace std;

int main()
{
	int ch;
	char shift; 
	
    ifstream fin;					// to access the .csv file for reading the extracted points
    ofstream fout;                  // to output the points in a .csv file inorder to plot the image
    cout<<"\nEnter the choice : 1) Spiral curve 2) Signature1 (requires less than 20 points) 3) Signature2 (requires more than 20 points)  :";
    cin >>ch;
    int n;                           // number of points taken 
	if(ch==1)
	{
	
	fin.open("q1data.csv");                   //opening the .csv file to read the points 
    fout.open("q1ans.csv");						
	cout<<"\nEnter the total number of points extracted : ";
	cin>>n;
	}
	if(ch==2)
	{
	fin.open("q2data.csv");
	fout.open("q2ans.csv");
	cout<<"\nEnter the total number of points extracted : ";
	cin>>n;
	}
	if(ch==3)
	{
		fin.open("q3data.csv");
	fout.open("q3ans.csv");
	cout<<"\nEnter the total number of points extracted : ";
	cin>>n;
	}
	float betay[n], betax[n];                                   //variables to store intermediate values 
		float check;
	 float xpoint[n+1], ypoint[n+1], par[n+1], h[n+1];        //par is the parameter    
	 float l[n], mu[n], zx[n], zy[n];                           //variables to store intermediate values 
	 float bx[n], by[n], cx[n], cy[n], dx[n], dy[n];        // b,c and d values for X and Y
	 float xout[n*10], yout[n*10];                            // final points to plot the image
	  float s[n*10];                                           
	
  //  int n=19;       
   
    for(int i=0; i<n+1; i++)
    {
      par[i]= 0.0 + i;                          
      h[i]=1.0;                    //  1 since h[i]=par[i+1]-par[i] is always equal to 1
    }
   
    for(int i=0; i<n+1; i++)
    {
        fin>> xpoint[i];           //reading the x coordinates of the image from a .csv file
        fin>> shift;				//to read the commas or space between cooordinates
        fin>> ypoint[i];          //reading the y coordinates 
    }
    
    for(int i=1; i<n; i++)  
    {
        betay[i]= 3*(ypoint[i+1]-2*ypoint[i]+ypoint[i-1]);       //calculating betax and betay for X and Y in the same loop
        betax[i]= 3*(xpoint[i+1]-2*xpoint[i]+xpoint[i-1]);
    }
    
    l[0]= 1.0;                                                  //initialising the internediate variables
    mu[0]= 0.0;                                            
    zy[0]= 0.0;
    zx[0]= 0.0;
    for(int i=1; i<n; i++)                                        //loop to calculate the intermediate values
    {
        l[i]= 2*(par[i+1]-par[i-1]) - (mu[i-1]);
        mu[i]= (1/l[i]);
        zx[i]= (betax[i]-(1*zx[i-1]))/l[i];
        zy[i]= (betay[i]-(1*zy[i-1]))/l[i];
    }
    l[n]=1.0;
    zx[n]=0.0;
    zy[n]=0.0;
    
    cx[n]=0.0;
	cy[n]=0.0;
    for(int i=(n-1); i>=0; i--)                                     //loop to calculate the b,c and d values for X and Y respectively
    {
       cx[i]=  zx[i] - (mu[i]*cx[i+1]);                                 
       bx[i]=  (xpoint[i+1]-xpoint[i]) - (cx[i+1]+2*cx[i])/3;
       dx[i]=  (cx[i+1]-cx[i])/3;
	   cy[i]=  zy[i] - (mu[i]*cy[i+1]);
       by[i]=  (ypoint[i+1]-ypoint[i]) - (cy[i+1]+2*cy[i])/3;
       dy[i]=  (cy[i+1]-cy[i])/3;
    }
   
    s[0]=0.0;
    for(int i=1; i<((n)*10); i++)                      // dividing the par intervals into 10 parts for the final plotting
    {
        s[i]= 0.1*(i-1);
    }
    
    int temp;
   
    for(int i=0; i< (n*10); i++)
    {
        temp= int(s[i]);
       // cout<<temp<<endl;
        check=temp;
        
		float tp=modf(s[i],&check);             //using modf function to find the fractional part (cmath.h)
        //tp= s[i]- temp;
        //cout<<tp<<endl;
        for(int j=0;j<n;j++)
        if(temp==j)
		{
		xout[i]= (dx[temp]*pow(tp,3))+ (cx[temp]*pow(tp,2))+ (bx[temp]*pow(tp,1))+ xpoint[temp]; 
        yout[i]= (dy[temp]*pow(tp,3))+ (cy[temp]*pow(tp,2))+ (by[temp]*pow(tp,1))+ ypoint[temp];
    	 }
	}
    for(int i=0; i<(n-2)*10; i++)
    {
        fout<< xout[i]<<","<< -1*yout[i]<<endl;
    }
    if(ch==1)
    cout<<"\n The coordinates to plot the spiral curve using cubic spline are put in q1ans.csv";
    if (ch==2)
    cout<<"\n The coordinates to plot the signature1 using cubic spline are put in q2ans.csv";
    if (ch==3)
    cout<<"\n The coordinates to plot the signature2 using cubic spline are put in q2ans.csv";
	fin.close();
    fout.close();
    return 0;
}

