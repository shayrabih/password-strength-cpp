#include <iostream>
#include <string.h>
#include <vector>
#define VECTOR_MAX_SIZE  10
#define loop_size   5  //for check possible to input only 5 Msg
using namespace std;


class Msg
{

public:
    Msg (string m ){if(m.length() != 0)
                        setMsg(m);}
    Msg();
    double getSafeFactor(void) const {return this->safeFactor;}
    virtual ~Msg();
    virtual void updateSafeFactor(){}
    virtual string getClassName(){return "Msg";}
    void setMsg(string s);
    string getMsg () const;
    void setSafeFactor(double val){this->safeFactor = val;}
    virtual void show(){cout<<"hi"<<endl;}
    bool operator<(const Msg& m) const;

protected:

    string bodyText;
    double safeFactor;
};

bool Msg::operator<(const Msg& m) const
{
	return (this->safeFactor <  m.safeFactor ? true : false) ;
}

    Msg::Msg(){cout<<"you must input body string"<<endl;}
    Msg::~Msg(){ cout << "MSG destractor called" << endl;}
	void Msg::setMsg (string s){ this->bodyText = s; }
	string Msg::getMsg() const {return this->bodyText;}

/*-------------------------------------------------------------------*/
class PlainMsg: public Msg
{
public:
        PlainMsg& operator=(const PlainMsg& other);
        PlainMsg(const PlainMsg& other);
        enum ownerClass {A,B,C,D,E} ;
        PlainMsg (string  S,unsigned char  o);
        PlainMsg();
        virtual ~PlainMsg(){cout << "plain mesage dtor call"<<endl; }
        void updateSafeFactor();
        void show();
        void setType(char ch);
        ownerClass GetType() const { return type; }
        string getClassName() {return "PlainMsg";}

private:
        ownerClass type;
        unsigned char t;

};
void PlainMsg::setType(char ch)
{
	 switch (ch){
        case 'A': type  = A; break;
        case 'B': type  = B; break;
        case 'c': type  = C; break;
        case 'D': type  = D; break;
        case 'E': type  = E; break;
        default : cout<<"invalid ownerClass parameter"<<endl;
	
}
}
PlainMsg& PlainMsg::operator=(const PlainMsg& other)
{
    if (this != &other)
    {       
     setMsg(other.getMsg());
     setType(other.GetType());  
    }
    return *this;
}

PlainMsg::PlainMsg(const PlainMsg& other) //copy constractor
{
	setMsg(other.getMsg());
	setType(other.GetType());	
		
}


PlainMsg::PlainMsg()
{	cout<<"you must input 1 char or more..." << endl<<"please try again";}


PlainMsg::PlainMsg(string s ,unsigned char ow):Msg(s){

    switch (ow){
        case 'A': type  = A; updateSafeFactor() ;t = ow  ;break;
        case 'B': type  = B; updateSafeFactor() ;t = ow  ;break;
        case 'c': type  = C; updateSafeFactor() ;t = ow  ;break;
        case 'D': type  = D; updateSafeFactor() ;t = ow  ;break;
        case 'E': type  = E; updateSafeFactor() ;t = ow  ;break;
        default : cout<<"invalid ownerClass parameter"<<endl;


    }
}
void PlainMsg::updateSafeFactor()
{
    double va  = 0.7* double(type) + (0.3*(1.0/double(this->getMsg().length()))) ;
     Msg::setSafeFactor(va);
    }


void PlainMsg::show()
{
    cout<<endl<<endl;
    cout<<this->getClassName()<<endl << "message : " << Msg::getMsg() <<endl\
    <<"length  :"<<this->getMsg().length() << endl << "ownerClass  :"<< double(this->getSafeFactor())<< endl;\
     cout << "safeFactor  :   "<< t << endl;
     cout<<"------------------------------------------------------- "<<endl;
}
/* **************************************************************************************************/



class SecureMsg:public Msg
{
public:

enum securityType { PWD ,AES ,PKI , SSL } ;
enum keyStrength  {LOW , NORM , MID ,HIGH};
SecureMsg();
SecureMsg (string  body ,string se ,string key);
SecureMsg(const SecureMsg& other); //copy constractor
~SecureMsg(){cout << "plain mesage dtor call"<<endl; }
void updateSafeFactor();
void show();
void set_secureType(securityType s) {secureType = s;}
void set_keystrengthType(keyStrength g){keystrengthType = g;}
securityType Get_secureType() const { return secureType; }
keyStrength Get_keystrengthType() const {return keystrengthType ;}
string getClassName() const  {return "SecureMsg";}
void setSecureString(string str){sec = str;}
void setKeyString(string str){ke = str;}
string getSecureString() const {return sec ;}
string getKeyString() const{return ke;}
SecureMsg& operator=(const SecureMsg& other);



private :

securityType secureType;
keyStrength  keystrengthType;
string sec , ke ;
};


SecureMsg& SecureMsg::operator =(const SecureMsg& other) //operator = implementation
{
	
  if (this != &other)
    {       
     this->setMsg(other.getMsg());
     this->set_secureType(other.Get_secureType());	
     this->set_keystrengthType(other.Get_keystrengthType()); 
    }
    return *this;	
	
}


 SecureMsg::SecureMsg(const SecureMsg& other) //copy constractor
{
this->set_secureType(other.Get_secureType());	
this->set_keystrengthType(other.Get_keystrengthType());	
this->setMsg(other.getMsg());	
	
	
}


void SecureMsg::updateSafeFactor(){
    double v = (0.4*secureType + 0.3*keystrengthType + 0.3*(1.0/this->getMsg().length()));
    this->setSafeFactor(v);

}

void SecureMsg::show(){
    cout<<endl<<endl;
    cout << "secure message:"<< Msg::getMsg() << endl ;
    cout << "safeFactor  :  " << this->getSafeFactor() << endl ;
    cout << "message length  :  " << this->getMsg().length() << endl;
    cout <<"security type : " <<  sec  << "     keystrength :  " << ke   << endl;
    cout<<"------------------------------------------------------- "<<endl;




    }
SecureMsg::SecureMsg(){

    cout<<"you must input values ...."<<endl<<" please try again"<<endl;
}

//init securetype & keystrength and save them as string for easy work 
SecureMsg::SecureMsg(string b , string se ,string key):	Msg(b)
{
if     (se.compare("PWD")==0)  {secureType=PWD; sec = se ;}
else if(se.compare("AES")==0)  {secureType=AES; sec = se ;}
else if(se.compare("PKI")==0)  {secureType=PKI; sec = se ;}
else if(se.compare("SSL")==0)  {secureType=SSL; sec = se ;}

if(key.compare("LOW")==0){keystrengthType=LOW; ke = key ;}
else if(key.compare("NORM")==0){keystrengthType=NORM; ke = key;}
else if(key.compare("MID")==0){keystrengthType=MID; ke = key;}
else if(key.compare("HIGH")==0){keystrengthType=HIGH; ke = key;}

}

/*-------------------------------------------------------------------------*/

class MsgAdmin
{
public:
    MsgAdmin();
    ~MsgAdmin();
    MsgAdmin(int);
    int getCounter(){return counter;}
    void addToCounter(void);
    void addToVector(Msg* m){vec.push_back(m);}
    void show();
    int getVectorSize() const {return vec.size();}
    void findSafest();
    void findSafest(string MsgType);
    Msg* getFromVector(int index);

private:
    vector<Msg*> vec;
    static int counter;

};
int MsgAdmin::counter = 0;



Msg* MsgAdmin::getFromVector(int index)
{
    if (index <= this->getVectorSize() && index >= 0 )
       {return vec[index];}
    else
    { 
     cout<<"error : invalid index "<<endl; 	 
     return NULL;   	 
}
}
void MsgAdmin::findSafest(){
	
    int counter = 0;
    int Max_index = 0;
    double Max_Factor = 0;
    for(Msg* p : vec )
    {
        if(p->getSafeFactor() > Max_Factor)
        {Max_index = counter; Max_Factor = p->getSafeFactor();}
     ++counter;
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"the string with the biggest safefactor is :  "<< endl;
    vec[Max_index]->show();
}


void MsgAdmin::findSafest(string type)
{
    string temp = "";
    int counter = 0;
    int Max_index = 0 ;
    double Max_Factor = 0;

    for(Msg* p : vec )
    {
        temp = p->getClassName();
        if(temp.compare(type) == 0){
        if(p->getSafeFactor() > Max_Factor)
        {Max_index = counter; Max_Factor = p->getSafeFactor();}
    }
       ++counter;
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"the string with the biggest safefactor is of type  "<< type <<":" << endl;
    vec[Max_index]->show();

}

void MsgAdmin::show() //print all vector objects
{
for (Msg* p : vec)
{
       cout<<"************************"<<endl;
       p->show();
       cout<<"************************"<<endl;
}
}

//for singelton useg
void MsgAdmin::addToCounter(void)
	{this->counter += 1 ;}

MsgAdmin::~MsgAdmin(){

    for (Msg* p : vec)
       delete[] p;
        
}

MsgAdmin::MsgAdmin() //default constractor 
{
    if (this->getCounter() == 0)
    {
        vector<Msg*> vec(VECTOR_MAX_SIZE);     //create vector 
        addToCounter();
    }
    
    else{cout<<"Singelton validation"<<endl;}
}

//constractor for vector with init size
MsgAdmin::MsgAdmin(int n){
    
    if (this->getCounter() == 0){
    if (n > 0 &&  n<=VECTOR_MAX_SIZE)
      {vector<Msg*> vec(n);
          addToCounter();
        }
}
else{cout<<"Singelton validation   "<<endl;}
}



int main()
{
unsigned char ownerClassVal , choice;
string securType , keystrength , str ;
int j = 0;
Msg* m  ;
MsgAdmin v;

for(j=0;j<loop_size;j++) // loop size set in define# global...
{

do{
cin.clear();	
cout << "for PlainMsg input 1 , for secureMessage input 2"<<endl;
cin>>choice ;
}while ((choice!='1' && choice!='2') || choice == '\n');

if (v.getVectorSize() < VECTOR_MAX_SIZE)//check  vector overflow
{
if (choice == '1') // PlainMsg Type
{
do{	
cout << "please enter your string  :" << endl;
cin>>str;
}while (str.size() < 1 );
do{
cin.clear();	
cout << "please enter plaineMessage type : [A ,B ,C , D ,E] "<<endl;
cin >> ownerClassVal;
}while (ownerClassVal != 'A' && ownerClassVal != 'B' && ownerClassVal != 'C' && ownerClassVal !='D' && ownerClassVal !='E');
m = new PlainMsg(str ,ownerClassVal );
}

else // secureMsg type 
{
do{
cout << "please enter your string  :" << endl;
cin>>str;
}while (str.size() < 1);
do{
cin.clear();	
cout << "please enter securityType type :[ PWD ,AES ,PKI , SSL ] "<<endl;
cin >> securType;
}while (securType.compare("PWD")!= 0 && securType.compare("AES")!= 0 && securType.compare("PKI")!= 0 && securType.compare("SSL")!= 0);

do{
cin.clear();	
cout << "please enter your keyStrength : [LOW , NORM , MID ,HIGH] "<< endl;
cin >> 	keystrength ;
}while(keystrength.compare("LOW")!=0 && keystrength.compare("NORM")!= 0 && keystrength.compare("MID")!= 0 && keystrength.compare("HIGH")!= 0)	;
m = new SecureMsg(str , securType , keystrength);
m->updateSafeFactor();

}
v.addToVector(m);

}
else{cout<<"ERROR : vector max size failure"<<endl;}
}

cout<<endl<<endl;
cout<<"--------- vector prints-------------"<<endl;
v.show();
v.findSafest();

//v.findSafest("SecureMsg");
//v.findSafest("PlainMsg");

return 0;
}







