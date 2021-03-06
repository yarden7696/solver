#include "solver.hpp"
#include <cmath>
#include <iostream>

using namespace std;

namespace solver {
    
    ////////////////////////////////////////////////// RealVariable ////////////////////////////////////////////////////
    
RealVariable::RealVariable(double a ,double b, double c) { // constructor
    this->a=a;
    this->b=b;
    this->c=c;
}

//+ operator
RealVariable operator+(const RealVariable& x, const RealVariable &y ){return RealVariable(x.getA()+y.getA(), x.getB()+y.getB(), x.getC()+y.getC());}
RealVariable operator+(const RealVariable& x, const double y ){ return RealVariable(x.getA(), x.getB(), x.getC()+y);}
RealVariable operator+(const double y, const RealVariable& x){ return RealVariable(x.getA(), x.getB(), x.getC()+y);}

//- operator
RealVariable operator-(const RealVariable& x, const RealVariable &y ){return RealVariable(x.getA()-y.getA(), x.getB()-y.getB(), x.getC()-y.getC());}
RealVariable operator-(const RealVariable& x, const double y){ return RealVariable(x.getA(), x.getB(), x.getC()-y);}
RealVariable operator-(const double y, const RealVariable& x){ return RealVariable(x.getA(), x.getB(), y-x.getC());}

//* operator
RealVariable operator*(const RealVariable& x, const RealVariable &y ){
    return RealVariable(x.getA() * y.getC() + y.getA() * x.getC() + x.getC() * y.getB() ,
                        x.getB() * y.getC() + y.getB() * x.getC(),
                        x.getC() * y.getC());
}
RealVariable operator*(const RealVariable& x, const double y ){return RealVariable(x.getA()*y, x.getB()*y, x.getC()*y);}
RealVariable operator*(const double y, const RealVariable& x){return RealVariable(x.getA()*y, x.getB()*y, x.getC()*y);}


// operator /
RealVariable operator/(const RealVariable& x, const RealVariable &y ){return RealVariable(x.getA()/y.getA(), x.getB()/y.getB(), x.getC()/y.getC());}
RealVariable operator/(const RealVariable& x, const double y ){return RealVariable(x.getA()/y, x.getB()/y, x.getC()/y);}
RealVariable operator/(const double y, const RealVariable& x){ return RealVariable(x.getA(), x.getB(), y/x.getC());}


// operator ^
    RealVariable operator^(const RealVariable &x, const double power){
    if((power>2 && x.getA()==0 && x.getB()==0)) return RealVariable(0,0,pow(x.c,power)); // threre is just c so ---> c^power
    if ((x.getA()!=0) || (power>2) || (power<0) ) throw std::out_of_range {" the power is not valid"}; 
    if(x.getB()!=0 && x.getC()!=0 && power==2) return RealVariable(pow(x.getB(),power),x.getB()*x.getC()*power,pow(x.getC(),power)); //like:(3x+2)^2=9x^2+12x+4
    if(x.getB()!=0 && x.getC()==0 && power==2) return RealVariable(pow(x.getB(),power),0,0); // like: (3x)^2= 9x^2
    if(power==1) return x;
    if(power==0) return RealVariable(0,0,1);
}

// == operator
 RealVariable operator==(const RealVariable& x, const RealVariable &y) { return x-y; } // if x-y==0 we get 0 that is true
 RealVariable operator==(const RealVariable& x, const double y){ return x-y; }
 RealVariable operator==(const double y, const RealVariable &x){ return y-x; }



 double solve(const RealVariable& x) {
     
    double a = x.getA();
    double b = x.getB();
    double c = x.getC();
     
    if(a==0) { // its mean that we dont have x^2
        if(b==0 && c!=0) throw std::out_of_range {" there is no solution "}; // caz (0,0,c) cannot return Proper solution
        else return c/-b; // for example : 3x+2=0 ------> 3x=-2-------> x= -2/3
    }

     // else: a!=0 , there is x^2
    if ((b * b - 4 * a * c) > 0) return (-b + sqrt(b * b - 4 * a * c)) / (2 * a); // sqrt > 0
    else if ((b * b - 4 * a * c) == 0)  return ((-b + sqrt(b * b - 4 * a * c)) / (2 * a)); // sqrt == 0
    throw std::out_of_range {"There is no a real solution"}; // sqrt < 0

}
    
 ////////////////////////////////////////////////// ComplexVariable ////////////////////////////////////////////////////

//  operator +
ComplexVariable operator+(const ComplexVariable& x,const ComplexVariable &y ){return ComplexVariable(x.getA()+y.getA(),x.getB()+y.getB(),x.getC()+y.getC());}
ComplexVariable operator+(const ComplexVariable& x, const complex<double> y ) { return ComplexVariable(x.getA(),x.getB(),x.getC()+y);}
ComplexVariable operator+(const complex<double> y,const ComplexVariable& x){return ComplexVariable(x.getA(),x.getB(),x.getC()+y);}

//  operator -
ComplexVariable operator-(const ComplexVariable& x,const ComplexVariable &y ) {return ComplexVariable(x.getA()-y.getA(),x.getB()-y.getB(),x.getC()-y.getC());}
ComplexVariable operator-(const ComplexVariable& x,const complex<double> y){return ComplexVariable(x.getA(),x.getB(),x.getC()-y);}
ComplexVariable operator-(const complex<double> y,const ComplexVariable& x) { return ComplexVariable(x.getA(),x.getB(),y-x.getC());}

// operator *
ComplexVariable operator*(const ComplexVariable& x, const ComplexVariable &y) {
    return ComplexVariable(x.getA() * y.getC() + y.getA() * x.getC() + x.getC() * y.getB(),
                           x.getB() * y.getC() + y.getB() * x.getC(),
                           x.getC() * y.getC());
}
ComplexVariable operator*(const ComplexVariable& x, const complex<double> y) {return ComplexVariable(x.getA()*y, x.getB()*y, x.getC()*y);}
ComplexVariable operator*(const complex<double> y,const ComplexVariable& x) { return ComplexVariable(x.getA()*y,x.getB()*y,x.getC()*y);}


// operator /
ComplexVariable operator/(const ComplexVariable& x, const ComplexVariable &y) {
    if (y.getA() == complex<double >(0.0,0.0) && y.getB() == complex<double >(0.0,0.0) && y.getC() == complex<double>(0.0,0.0))//(y.a)=(y.b)=(y.c)==0
        throw invalid_argument("division by zero is not possible !"); // caz we divided by y that equals to 0
    else {
        if (y.getA() == complex<double>(0.0,0.0) && y.getB() == complex<double>(0.0,0.0) && y.getC() != complex<double>(0.0,0.0))//(y.a)=(y.b)==0 and (y.c)!=0
            return ComplexVariable(x.getA() / y.getC(), x.getB() / y.getC(), x.getC() / y.getC()); //like:x/y=(z^2+3z+2)/(5+i)=z^2/(5+i)+3z/(5+i)+2/(5+i)
//         if (y.getA() == complex<double>(0.0,0.0) && y.getB() == complex<double>(0.0,0.0) && y.getC() != complex<double>(0.0,0.0))
//             return ComplexVariable(x.getA() / y.getC(), x.getB() / y.getC(), x.getC() / y.getC());
        if (y.getA() != complex<double>(0.0,0.0) && y.getB() != complex<double>(0.0,0.0) && y.getC() == complex<double>(0.0,0.0)) return ComplexVariable(x.getA() / y.getA(), x.getB() / y.getB(), 0); //?
        if (y.getA() == complex<double>(0.0,0.0) && y.getB() != complex<double>(0.0,0.0) && y.getC() == complex<double>(0.0,0.0)) return ComplexVariable(0, x.getB() / y.getB(), 0); //?
    }
}

ComplexVariable operator/(const ComplexVariable& x, const complex<double> y) {
    if (y != complex<double>(0.0,0.0)) { // y!=0
        return ComplexVariable(x.getA() / y, x.getB() / y, x.getC() / y);
    } 
    else throw invalid_argument("division by zero is not possible !");
}


//  operator ^
ComplexVariable operator^(const ComplexVariable &x, const complex<double> power) {
    
        if(power.imag() != 0) throw invalid_argument("complex power is not valid"); // caz power cannot be with i
    
        if((power.real()>2 && x.getA()==complex<double>(0.0,0.0) && x.getB()==complex<double>(0.0,0.0)))//power> 2 if and only if a and b are equal to 0 
            return ComplexVariable(0,0,pow(x.c,power));
    
        if ((x.getA()!=complex<double>(0.0,0.0)) || (power.real()>2) || (power.real()<0) // if the power>2 and a!=0 throw an error
            throw std::out_of_range {" the power is not valid"};
            
        if(x.getB()!=complex<double>(0.0,0.0) && x.getC()!=complex<double>(0.0,0.0) && power.real()==2)// a==0 and b!=0, c!=0
            return ComplexVariable(pow(x.getB(),power),x.getB()*x.getC()*power,pow(x.getC(),power)); //like:(3z+4)^2=(9z^2,24z,16)
            
        if(x.getB()!=complex<double>(0.0,0.0) && x.getC()==complex<double>(0.0,0.0) && power.real()==2) // a==c==0, b!=0
            return ComplexVariable(pow(x.getB(),power),0,0);
            
        if(power==complex<double>(0.0,1.0)) return x; //?
        if(power==complex<double>(0.0,0.0)) return ComplexVariable(0,0,1);
}


// operator ==
ComplexVariable operator==(const ComplexVariable &x, const ComplexVariable &y) {return x-y;} // if x-y==0 we get 0 that is true, else- 1 is false
ComplexVariable operator==(const ComplexVariable &x, const complex<double> y) { return x-y;}
ComplexVariable operator==(const complex<double> y, const ComplexVariable &x) {return y-x;}


complex<double> solve (const ComplexVariable & x) {
    
    complex<double> a = x.getA();
    complex<double> b = x.getB();
    complex<double> c = x.getC();
   
    if(a==complex<double>(0.0,0.0)) { // there is no z^2
        if(b==complex<double>(0.0,0.0) && c!=complex<double>(0.0,0.0)) // there is no z (b) and there is c
            throw std::out_of_range {" there is no result "};  // caz (0,0,c) cannot return Proper solution
        else return c/-b; //  a==0 and c!=0, b!=0
    }
    return (-b + sqrt(b * b - (a.real()*4+a.imag()*4) * c)) / ((2 * a.real() + 2 * a.imag())); // there is no else- caz in complex sqrt<0 is ok
}
            
}



