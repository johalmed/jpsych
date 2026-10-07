#pragma once
#include <cmath>
#include <string>
#include <cctype>
#include <cstdlib>
#include <algorithm>
class Formula {
public:
 explicit Formula(std::string s="60 + round(sin(t*0.25)*7)"):text(std::move(s)){}
 bool set(const std::string&s){text=s;return valid();}
 double eval(double t,double x,double n,double r,double b,double p,double v)const{
  Parser q{text,0,false,t,x,n,r,b,p,v}; double y=q.expr(); return(!q.error&&q.pos==q.s.size()&&std::isfinite(y))?y:60.0;
 }
 bool valid()const{Parser q{text,0,false,0,0,0,0,0,0,0};q.expr();return !q.error&&q.pos==q.s.size();}
private:
 std::string text;
 struct Parser{
  const std::string&s;size_t pos;bool error;double t,x,n,r,b,p,v;
  void ws(){while(pos<s.size()&&std::isspace((unsigned char)s[pos]))++pos;}
  bool eat(char c){ws();if(pos<s.size()&&s[pos]==c){++pos;return true;}return false;}
  double expr(){double a=term();for(;;){if(eat('+'))a+=term();else if(eat('-'))a-=term();else return a;}}
  double term(){double a=power();for(;;){if(eat('*'))a*=power();else if(eat('/')){double d=power();a=std::abs(d)<1e-12?0:a/d;}else if(eat('%')){double d=power();a=std::fmod(a,d);}else return a;}}
  double power(){double a=unary();if(eat('^'))a=std::pow(a,power());return a;}
  double unary(){if(eat('+'))return unary();if(eat('-'))return-unary();return atom();}
  double atom(){ws();if(pos>=s.size()){error=true;return 0;}if(eat('(')){double a=expr();if(!eat(')'))error=true;return a;}
   if(std::isdigit((unsigned char)s[pos])||s[pos]=='.'){char*e=nullptr;double a=std::strtod(s.c_str()+pos,&e);pos=(size_t)(e-s.c_str());return a;}
   if(std::isalpha((unsigned char)s[pos])){size_t st=pos;while(pos<s.size()&&(std::isalnum((unsigned char)s[pos])||s[pos]=='_'))++pos;std::string id=s.substr(st,pos-st);ws();
    if(eat('(')){double a=expr();if(!eat(')'))error=true;return fn(id,a);}
    if(id=="t")return t;if(id=="x")return x;if(id=="n")return n;if(id=="r")return r;if(id=="b")return b;if(id=="p")return p;if(id=="v")return v;if(id=="pi")return M_PI;if(id=="e")return M_E;
   }error=true;return 0;}
  double fn(const std::string&i,double a){if(i=="sin")return std::sin(a);if(i=="cos")return std::cos(a);if(i=="tan")return std::tan(a);if(i=="abs")return std::abs(a);if(i=="sqrt")return std::sqrt(std::max(0.0,a));if(i=="floor")return std::floor(a);if(i=="ceil")return std::ceil(a);if(i=="round")return std::round(a);if(i=="log")return std::log(std::max(1e-12,a));if(i=="exp")return std::exp(a);if(i=="asin")return std::asin(std::clamp(a,-1.0,1.0));if(i=="acos")return std::acos(std::clamp(a,-1.0,1.0));if(i=="atan")return std::atan(a);error=true;return 0;}
 };
};