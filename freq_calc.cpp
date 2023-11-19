#include <iostream>
#include<cmath>
#include<vector>

using namespace std;

double err(double x,double y){
    if(x>y)
    swap(x,y);
    
    return (y/x)-1;
}

double medie(double a,double b){
    return (a+b)/2;
}

struct Config{
    double R1[2],R2[2];
    double C;
    double Rpot;
    double eroare_medie;
    double FM;
    double Fm;
};

int main()
{
    double F_min=250;
    double F_max=10000;
    
    //10,22,33,51,68,82,100,150,220,330,470,510,680,820,910,
    //,330000,390000,510000
    vector<double> Rez={1000,1500,1800,2000,2200,2700,3300,3900,4700,5600,6800,8200,9100,10000,15000,
    22000,47000,68000,100000,150000,180000,220000};
    
    //100,500,2000,
    vector<double> Pot={5000,10000,50000,100000,500000};
    
    //
    vector<double> C_pF={4.7,10,47,100,470,1000,2200,4700,5600,10000,22000,33000,100000,220000,330000,
    470000,1000000,2200000,4700000,10000000};
    
     for(int i=0;i<C_pF.size();i++)
        C_pF[i]=C_pF[i]/1000000000000;
    
    //  for(double C:C_pF)
    //     cout<<C<<' ';
    
    int Solutii=0;
    double eroare=0.1;
    double Ideal_max=F_max*2;
    double Ideal_min=F_min/2;
    Config Ideal;
    Ideal.eroare_medie=1;
    
    double RM11,RM12,RM21,RM22,CM,RMpot;
    double Rm11,Rm12,Rm21,Rm22,Cm,Rmpot;
    
    for(int i=0;i<C_pF.size();i++)
        for(int m=0;m<Rez.size();m++)//pt rez in plus
            for(int j=0;j<Rez.size();j++)
                for(int k=0;k<Rez.size();k++)
                    for(int l=0;l<Pot.size();l++)
                        for(int n=0;n<Rez.size();n++){
                        
                        //C=C/1000000000;//transformare pF->F
                        
                        double C=C_pF[i];
                        double R1=Rez[j]+Rez[m];
                        double R2=Rez[k]+Rez[n];
                        double Rpot=Pot[l];
                        
                        //cout<<log(3)<<endl;
                        
                        double fmin=1/(2*(R1+(R2*Rpot)/(R2+Rpot))*C*log(3));
                        double fmax=1/(2*R1*C*log(3));
                        //(R2*Rpot)/(R2+Rpot)
                        
                        // if(fmin<INFINITY && fmax<INFINITY && fmin>1){
                        //     cout<<":  R1="<<R1<<"  R2="<<R2<<"  C="<<C<<"  Rpot="<<Rpot<<endl;
                        //     cout<<fmin<<" "<<fmax<<endl;
                        // }
                        
                        if(fmax>F_max && fmin<F_min)
                        {
                            if(fmax<F_max*(1+eroare) && fmin>F_min*(1-eroare)){
                                cout<<"Solutie ";
                                cout<<"excelenta ";
                                 cout<<":  R1="<<R1<<"="<<Rez[j]<<"+"<<Rez[m]<<
                                 "  R2="<<R2<<"="<<Rez[k]<<"+"<<Rez[n]<<"  C="<<C<<"  Rpot="<<Rpot<<endl;
                                 cout<<fmin<<" "<<fmax<<endl;
                                 Solutii++;
                                 
                                 if(Ideal_max>fmax)
                                    {
                                        Ideal_max=fmax;
                                        CM=C;
                                        RM11=Rez[j];
                                        RM12=Rez[m];
                                        RM21=Rez[k];
                                        RM22=Rez[n];
                                        RMpot=Rpot;
                                    }
                                    
                                if(Ideal_min<fmin)
                                    {
                                        Ideal_min=fmin;
                                        Cm=C;
                                        Rm11=Rez[j];
                                        Rm12=Rez[m];
                                        Rm21=Rez[k];
                                        Rm22=Rez[n];
                                        Rmpot=Rpot;
                                    }
                                    
                                if((err(F_max,fmax)+err(F_min,fmin))/2<Ideal.eroare_medie)
                                {
                                    Ideal.eroare_medie=(err(F_max,fmax)+err(F_min,fmin))/2;
                                    Ideal.FM=fmax;
                                    Ideal.Fm=fmin;
                                    Ideal.R1[0]=Rez[j];
                                    Ideal.R1[1]=Rez[m];
                                    Ideal.R2[0]=Rez[k];
                                    Ideal.R2[1]=Rez[n];
                                    Ideal.C=C;
                                    Ideal.Rpot=Rpot;
                                }
                                 
                            }
                            
                        }
                    }
    
    
    cout<<endl<<"Solutii: "<<Solutii<<endl;
    
    cout<<"Cea mai buna fmax: "<<Ideal_max<<endl;
    cout<<"Cea mai buna fmin: "<<Ideal_min<<endl<<endl;
    
    cout<<"Solutia ideala: "<<" R1="<<Ideal.R1[0]<<"+"<<Ideal.R1[1]<<
        "   R2="<<Ideal.R2[0]<<"+"<<Ideal.R2[1]<<"  C="<<Ideal.C<<"  Rpot="<<Ideal.Rpot<<endl;
    cout<<"Cu frecventele: fmin="<<Ideal.Fm<<"  si  fmax="<<Ideal.FM<<endl<<endl;
                                
    
    cout<<"Am definit cea mai buna fmax ca fiind frecventa limita superioara cea mai mica, mai mare decat F_max din"<< 
    "cerintele proiectului";
    
    
    return 0;
}
