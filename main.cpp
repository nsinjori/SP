#include<iostream>
#include<ctime>
#include<cstdlib>
//#include "red_polje.h"
#include "red_pokazivaci.h"
using namespace std;

string imena[]={"Ime1","Ime2","Ime3","Ime4","Ime5","Ime6","Ime7","Ime8","Ime9","Ime10"};
string prezimena[]={"Prezime1","Prezime2","Prezime3","Prezime4","Prezime5","Prezime6","Prezime7","Prezime8","Prezime9","Prezime10","Prezime11"};
void ispisivanje(tpacijent n){
	cout<<endl<<"---------------------"<<endl;
	cout<<"Ime i prezime: "<<n.ime<<" "<<n.prezime<<endl<<"Prioritet: ";
	switch(n.ci){
		case 1: cout<<"Hitni slucajevi"<<endl;break;
		case 2: cout<<"Invalidi"<<endl;break;
		case 3: cout<<"Trudnice"<<endl;break;
		case 4: cout<<"Djeca ispod 6 godina"<<endl;break;
		case 5: cout<<"Drugi pacijenti"<<endl;break;
	}
	cout<<"Vrsta usluge: ";
	switch(n.di){
		case 1: cout<<"Pregled"<<endl;break;
		case 2: cout<<"Previjanje"<<endl;break;
		case 3: cout<<"Recepti"<<endl;break;
		case 4: cout<<"Uputnice"<<endl;break;
	}
	cout<<"Ordinacija: ";
	switch(n.ei){
		case 1: cout<<"Obiteljska medicina"<<endl;break;
		case 2: cout<<"Oftamologija"<<endl;break;
		case 3: cout<<"Dermatovenerologija"<<endl;break;
		case 4: cout<<"Ginekologija"<<endl;break;
		case 5: cout<<"Urologija"<<endl;break;
	}
	if(n.s=='z')cout<<"Spol: zenski"<<endl;
	else cout<<"Spol: muski"<<endl;
	cout<<"Datum rodenja: "<<n.dan<<"."<<n.mjesec<<"."<<n.godina<<".";
}
void ispis(tred *red){
	tred pom;
	InitQ(&pom);
	while(!IsEmptyQ(red)){
		tpacijent n=FrontQ(red);
		EnQueueQ(n,&pom);
		ispisivanje(n);
		DeQueueQ(red);
	}
	while(!IsEmptyQ(&pom)){
		tpacijent n=FrontQ(&pom);
		EnQueueQ(n,red);
		DeQueueQ(&pom);
	}
}
void sortirano(tred *r){
	tred pom1, pom2, pom3, pom4, pom5;
	InitQ(&pom1);InitQ(&pom2);InitQ(&pom3);InitQ(&pom4);InitQ(&pom5);
	while(!IsEmptyQ(r)){
		tpacijent t=FrontQ(r);
		switch(t.ci){
			case 1: EnQueueQ(t,&pom1);break;
			case 2: EnQueueQ(t,&pom2);break;
			case 3: EnQueueQ(t,&pom3);break;
			case 4: EnQueueQ(t,&pom4);break;
			case 5: EnQueueQ(t,&pom5);break;
		}
		DeQueueQ(r);
	}
	while(!IsEmptyQ(&pom1)){
		EnQueueQ(FrontQ(&pom1),r);
		DeQueueQ(&pom1);
	}
	while(!IsEmptyQ(&pom2)){
		EnQueueQ(FrontQ(&pom2),r);
		DeQueueQ(&pom2);
	}
	while(!IsEmptyQ(&pom3)){
		EnQueueQ(FrontQ(&pom3),r);
		DeQueueQ(&pom3);
	}
	while(!IsEmptyQ(&pom4)){
		EnQueueQ(FrontQ(&pom4),r);
		DeQueueQ(&pom4);
	}
	while(!IsEmptyQ(&pom5)){
		EnQueueQ(FrontQ(&pom5),r);
		DeQueueQ(&pom5);
	}
}
bool star(int d, int m, int g, int k){
	if(g<2013-k) return true;
	if(g==2013-k){
		if(m==12&&d<14) return true;
		if(m<12) return true;
	}
	return false;
}
void ispis25(tred *r){
	cout<<endl<<"Pacijentice na pregledu kod oftamologa starije od 25 godina"<<endl;
	cout<<"==========================================================="<<endl;
	tred pom;
	InitQ(&pom);
	while(!IsEmptyQ(r)){
		tpacijent n=FrontQ(r);
		EnQueueQ(n,&pom);
		if(n.di==1&&n.ei==2&&n.s=='z'&&star(n.dan,n.mjesec,n.godina, 25))
		ispisivanje(n);
		DeQueueQ(r);
	}
	while(!IsEmptyQ(&pom)){
		tpacijent n=FrontQ(&pom);
		EnQueueQ(n,r);
		DeQueueQ(&pom);
	}
}
void unos(tred *r){
	srand((unsigned)time(0));
	int a, b, c, d, e, n, j=0;
	cout<<"Unesite broj petorki za generiranje: "; 
	cin>>n;
	cout<<"...pridruzujem 3 pacijenta svakoj petorki..."<<endl;
	for(int i=0; i<n; i++){
		a=50+rand()%250;
		b=50+rand()%250;
		c=1+rand()%5;
		d=1+rand()%4;
		switch(c){
			case 1: e=2+rand()%5;break;
			case 3: e=1+rand()%4;break;
			default: e=1+rand()%5;
		}		
		for (int l=0;l<3;l++){
			j++;
			tpacijent novi;
			novi.ai=a, novi.bi=b, novi.ci=c, novi.di=d, novi.ei=e;
			novi.ime=imena[rand()%10];
			novi.prezime=prezimena[rand()%11];
			if(j%2)novi.s='m';
			else novi.s='z';
			novi.mjesec=1+rand()%12;
			novi.dan=1+rand()%30;
			novi.godina=1913+rand()%100;
			EnQueueQ(novi, r);
		}
	}
	cout<<"Pacijenti se nalaze u cekaonici!"<<endl;
	sortirano(r);
	ispis25(r);
}
void invalid(tred *r){
	bool i=false;
	tred pom;
	InitQ(&pom);
	cout<<"Popis invalida koji su uklonjeni iz reda: "<<endl;
	cout<<"---------------------"<<endl;
	while(!IsEmptyQ(r)){
		tpacijent n=FrontQ(r);
		if(n.di==2&&n.ci==2&&star(n.dan,n.mjesec,n.godina, 50)){
			ispisivanje(n);
			i=true;
		}
		if(!i) EnQueueQ(n,&pom);
		DeQueueQ(r);
	}
	cout<<endl<<"---------------------"<<endl;
	while(!IsEmptyQ(&pom)){
		tpacijent n=FrontQ(&pom);
		EnQueueQ(n,r);
		DeQueueQ(&pom);
	}
}

bool e2=false;
void okretanje(tred *r){
	tpacijent t;
	if(IsEmptyQ(r)) e2=true;
	if(!e2) t=FrontQ(r);
	if(!e2) DeQueueQ(r);
	if(!e2) okretanje(r);
	EnQueueQ(t, r);
}
bool e=false, p=true;
int broj=0;
void brzi_salter(tred *r, tred *b){
	tpacijent t;
	if(IsEmptyQ(r)) e=true;
	if(!e) t=FrontQ(r);
	if(!e) DeQueueQ(r);
	if(!e) broj++;
	if(!e) brzi_salter(r, b);
	if(p){
		broj=broj*0.3;
		p=false;
	}
	if(broj>0&&(t.di==3||t.di==4)) {
	 	EnQueueQ(t, b);
	 	broj--;
	 }
	else EnQueueQ(t,r);
	sortirano(b);
}

int main(){
	tred red, brzi;
	InitQ(&red);
	InitQ(&brzi);
	int i;
	while(1){
		cout<<endl<<"---------------------"<<endl;
		cout<<"Izbornik"<<endl;
		cout<<"---------------------"<<endl;
		cout<<"1. Generiranje pacijenata"<<endl;
		cout<<"2. Izbacivanje invalida starijih od 50 godina"<<endl;
		cout<<"3. Salter za uputnice i recepte"<<endl;
		cout<<"4. Popis ljudi u cekaonici"<<endl;
		cout<<"0. Izlaz iz programa"<<endl;
		cout<<endl<<"Vas odabir: ";
		cin>>i;
		if(i==0) {
			cout<<"Kraj programa";
			break;
		}
		if(i==1) unos(&red);
		if(i==2) invalid(&red);
		if(i==3) {
			e=false; p=true;e2=false;
			broj=0;
			brzi_salter(&red,&brzi);
			cout<<"Brzi red: "<<endl;
			DeQueueQ(&red);
			okretanje(&red);
			DeQueueQ(&red);
			ispis(&brzi);
		}
		if(i==4) ispis(&red);
	}
	return 0;
}
