using namespace std;

struct tpacijent{
	char s;
	string ime, prezime;
	int ai, bi, ci, di, ei, dan, mjesec, godina;
};

struct el{
	tpacijent e;
	el *s;
};

struct tred{
	el *f,*r;
};

typedef struct tpacijent element;

void InitQ(tred *Q){
	el *novi=new el;
	novi->s=NULL;
	Q->r=novi;
	Q->f=novi;
}

tpacijent FrontQ(tred *Q){
   return Q->f->s->e;
}

void EnQueueQ(element x, tred *Q){
	el *novi=new el;
	novi->e = x;
	novi->s=NULL;
	Q->r->s=novi;
	Q->r=novi; 
}

void DeQueueQ(tred *Q){
	el *brisi = Q->f;
	Q->f = brisi->s;
	delete brisi;
}

bool IsEmptyQ(tred *Q){
	if(Q->r==Q->f)
		return true;
	return false;
}
