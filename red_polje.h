using namespace std;

struct tpacijent{
	char s;
	string ime, prezime;
	int ai, bi, ci, di, ei, dan, mjesec, godina;
};
typedef int pok;

typedef struct tpacijent element;

int AddOne(int n){
	return((n+1)%1000);
}
struct tred{
	tpacijent e[1000];
	pok f, r;
};

void InitQ(tred *Q){
	Q->f = 0;
	Q->r = 9999;
}

element FrontQ(tred *Q){
    return Q->e[Q->f];    
}

void EnQueueQ(element x, tred *Q){
	Q->r=AddOne(Q->r);
	Q->e[Q->r]=x;
}

void DeQueueQ(tred *Q){
	  Q->f=AddOne(Q->f);
}

bool IsEmptyQ(tred *Q){
	if(AddOne(Q->r)==Q->f) return true;
	return false;
}
