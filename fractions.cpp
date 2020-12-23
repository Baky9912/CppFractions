#include<exception>

template<class T>
class Fraction{
private:
    static T gcd(T a, T b){
        if(b==0)return a;
        return gcd(b, a%b);
    }

    static T lcm(T a, T b){
        return a * b / gcd(a,b);
    } 
    
    static T binexp(T x, T n) {
        if (n == 0) return 1;
        T u = binexp(x,n/2);
        u *= u;
        if (n%2 == 1) u = (u*x);
        return u;
    }

public:
    T num, den;

    Fraction(T a, T b){
        if(b<=0)throw new std::exception();
        T ngcd = gcd(a,b);
        num=a/ngcd, den=b/ngcd;
    }
    
    void operator=(Fraction other){
        num = other.num;
        den = other.den;
    }

    Fraction operator+(Fraction other){
        T nden = lcm(den, other.den); 
        T nnum = (nden / den) * num + (nden / other.den) * other.num;
        T ngcd = gcd(nden, nnum);
        return Fraction(nnum/ngcd, nden/ngcd); 
    }

    Fraction operator-(Fraction other){
        T nden = lcm(den, other.den); 
        T nnum = (nden / den) * num - (nden / other.den) * other.num;
        T ngcd = gcd(nden, nnum);
        return Fraction(nnum/ngcd, nden/ngcd);
    }

    Fraction operator*(Fraction other){
        T nnum = num * other.num;
        T nden = den * other.den;
        T ngcd = gcd(nden,nnum);
        return Fraction(nnum/ngcd, nden/ngcd);
    }
    
    Fraction operator/(Fraction other){
        T nnum = num * other.den;
        T nden = den * other.num;
        T ngcd = gcd(nden,nnum);
        return Fraction(nnum/ngcd, nden/ngcd);
    }

    static Fraction pow(Fraction f, T n){
        T expnum = binexp(f.num, n);
        T expden = binexp(f.den, n);
        if(n<0){
            return Fraction(expden, expnum);  
        }
        return Fraction(expnum, expden);

    }
    
    Fraction pow(T n){
        return pow(*this, n);    
    }

};
