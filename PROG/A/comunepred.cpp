#include<iostream>
#include<fstream>
#define N 250

using namespace std;

template<class T> class Nodo{
private:
	Nodo<T>* padre, *left, *right;
	T key;
	
public:
	Nodo(T val){
		padre=left=right=NULL;
		key=val;
	}
	void setPadre(Nodo<T>* p){ padre=p; }
	void setLeft(Nodo<T>* l){ left=l; }
	void setRight(Nodo<T>* r){ right=r; }
	void setKey(T val){ key=val; }
	Nodo<T>* getPadre(){ return padre; }
	Nodo<T>* getLeft(){ return left; }
	Nodo<T>* getRight(){ return right; }
	T getKey(){ return key; }
};

template<class T> class Albero{
private:
	Nodo<T>* root;
	Nodo<T>* search(T val){
		Nodo<T>* tmp=root;
		while(tmp && tmp->getKey()!=val){
			if(val>tmp->getKey())
				tmp=tmp->getRight();
			else
				tmp=tmp->getLeft();	
		}
		return tmp;
	}
	Nodo<T>* min(Nodo<T>* r){
		while(r->getLeft())
			r=r->getLeft();
		return r;	
	}
	void trapianta(Nodo<T>* u, Nodo<T>* v){
		Nodo<T>* p=u->getPadre();
		if(!p) root=v;
		else if(u==p->getRight()) p->setRight(v);
		else  p->setLeft(v);
		if(v) v->setPadre(p);
	}
public:
	Albero(){ root=NULL; }
	void inserimento(T val){
		Nodo<T>* newn=new Nodo<T>(val);
		if(!root) root=newn;
		else{
			Nodo<T>* tmp=root;
			Nodo<T>* p;
			while(tmp){
				p=tmp;
				if(val>tmp->getKey())
					tmp=tmp->getRight();
				else
					tmp=tmp->getLeft();	
			}
			newn->setPadre(p);
			if(val>p->getKey())
				p->setRight(newn);
			else
				p->setLeft(newn);	
		}
	}
	void cancella(T val){
		Nodo<T>* x=search(val);
		if(!x->getLeft()) trapianta(x,x->getRight());
		else if(!x->getRight()) trapianta(x,x->getLeft());
		else{
			Nodo<T>* y=min(x->getRight());
			if(y->getPadre()!=x){
				trapianta(y,y->getRight());
				y->setRight(x->getRight());
				(y->getRight())->setPadre(y);
			}
			trapianta(x,y);
			y->setLeft(x->getLeft());
			(y->getLeft())->setPadre(y);
		}
		delete x;
	}
	T antman(T x1, T x2){
		Nodo<T>* p1=search(x1);
		Nodo<T>* p2=search(x2);
		T vett1[N];
		T vett2[N];
		Nodo<T>* tmp=p1;
		int i=0;
		while(tmp){
			vett1[i]=tmp->getKey();
			tmp=tmp->getPadre();
			i++;
		}
		int n=i;
		tmp=p2;
		i=0;
		while(tmp){
			vett2[i]=tmp->getKey();
			tmp=tmp->getPadre();
			i++;
		}
		int M=i;
		i=0;
		for(i=0; i<n;i++)
			for(int j=0; j<M;j++){
				if(vett1[i]==vett2[j])
					return vett1[i];
			}	
	}
};

void soluzione(ifstream& in, ofstream& out){
	string tipo; in>>tipo;
	int n; in>>n;
	char c;
	if(tipo=="int"){
		Albero<int>* a=new Albero<int>();
		int val;
		int key1;
		int key2;
		for(int i=0; i<n; i++){
			in>>c;
			if(c=='i'){
				in>>c>>c>>c;
				in>>val;
				a->inserimento(val);
			}
			else{
				in>>c>>c>>c>>c;
				in>>val;
				a->cancella(val);
			}
		}
		in>>key1;
		in>>key2;
		out << a->antman(key1,key2) << endl;
	}
	if(tipo=="double"){
		Albero<double>* a=new Albero<double>();
		double val;
		double key1;
		double key2;
		for(int i=0; i<n; i++){
			in>>c;
			if(c=='i'){
				in>>c>>c>>c;
				in>>val;
				a->inserimento(val);
			}
			else{
				in>>c>>c>>c>>c;
				in>>val;
				a->cancella(val);
			}
		}
		in>>key1;
		in>>key2;
		out << a->antman(key1,key2) << endl;
	}
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
}
