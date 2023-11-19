#include <iostream>
#include<cmath>
#include<vector>

using namespace std;

double err(double x,double y){
    if(x>y)
    swap(x,y);
    
    return (y/x)-1;
}

int main()
{
    //
    vector<double> Rez={10,22,33,51,68,82,100,150,220,330,470,510,680,820,910,1000,1500,1800,
    2000,2200,2700,3300,3900,4700,5600,6800,8200,9100,10000,15000,
    22000,47000,68000,100000,150000,180000,220000,330000,390000,510000};
    
    //
    vector<double> Pot={100,500,2000,5000,10000,50000,100000,500000};
    
    double Vmin=10*pow(10,-3);
    double Vmax=5;
    double Vin=12.66;
    double Rload=1000;
    
    double VMax_ideal=2*Vmax;
    double Vmin_ideal=Vmin/2;
    double erm=(err(VMax_ideal,Vmax)+err(Vmin_ideal,Vmin))/2;//eroare medie
    
    
    double Tensiune_finala_min=0;
    double Tensiune_finala_max=0;
        double R1i[2];
        double Rpi;
        double R2i[2];
        
        int pl=0;
       
    
    
    for(int i=0;i<Rez.size();i++)
        for(int j=0;j<Rez.size();j++)
            for(int k=0;k<Rez.size();k++)
                for(int l=0;l<Rez.size();l++)
                    for(int m=0;m<Pot.size();m++){
                        
                        
                        //cu j si sub cu l adunate
                        double R1=Rez[i];
                        double R2=Rez[k];
                        double Rp=Pot[m];
                        
                        if(R1<1000 || R2>500)
                            break;
                        
                        double Rlp2=((Rp+R2)*Rload)/(Rp+R2+Rload);
                        double Rl2=(R2*Rload)/(R2+Rload);
                        
                        double vm=Vin*(Rl2)/(R1+Rp+Rl2);
                        double vM=Vin*Rlp2/(R1+Rlp2);
                        
                        // cout<<vm<<" "<<vM<<endl;
                        // pl++;
                        // cout<<":  R1="<<R1<<"="<<Rez[i]<<"+"<<Rez[j]<<
                        //          "  R2="<<R2<<"="<<Rez[k]<<"+"<<Rez[l]<<"  Rp="<<Rp<<endl;
                        //          if(pl==100)
                        //          return 0;
                        
                        if(vm<Vmin && vM>Vmax){
                            
                            if(erm>(err(vM,Vmax)+err(vm,Vmin))/2){
                                
                                // cout<<":  R1="<<R1<<"="<<Rez[i]<<"+"<<Rez[j]<<
                                //  "  R2="<<R2<<"="<<Rez[k]<<"+"<<Rez[l]<<"  Rp="<<Rp<<endl;
                                
                                erm=(err(vM,Vmax)+err(vm,Vmin))/2;
                                
                                    R1i[0]=Rez[i];
                                    //cu j si sub cu l
                                    R1i[1]=0;
                                    R2i[0]=Rez[k];
                                    R2i[1]=0;
                                    Rpi=Rp;
                                    Tensiune_finala_min=vm;
                                    Tensiune_finala_max=vM;
                            }
                            
                        }
                        
                    }


    cout<<"eroare ideal "<<erm<<endl;
    
    cout<<"Solutia ideala: "<<" R1="<<R1i[0]<<"+"<<R1i[1]<<
        "   R2="<<R2i[0]<<"+"<<R2i[1]<<"  Rp="<<Rpi<<endl;
        
    cout<<"Tesniunile vor fi: "<<Tensiune_finala_min<<"  si  "<<Tensiune_finala_max<<endl;
    
    return 0;
}
