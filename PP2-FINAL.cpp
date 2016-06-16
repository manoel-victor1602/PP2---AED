#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

#define TAM 787
#define NIL NULL

class Item{
	private:
		int chave;
	public:
		void setChave(int chave){
			this->chave = chave;
		}
		
		int getChave(){
			return chave;
		}
};

class No{
	private:
		Item item;
		string nome;
		int fatorBalance; 
		int alturaEsquerda;
		int alturaDireita;
		No* noEsq;
		No* noDir;
		No* pai;
		No* maisLongo;
		int cont;
		int compara;
		int aux;
		
		void distancia(No* x, No* p){
			cont++;
			aux = 0;
			if(p->ehNoFolha() == true){
				if(x->getItem() == p->getItem()){
					aux = cont;
					cont = 0;
				}
			}
			else if(x->getItem() > p->getItem()){
				distancia(x, p->getNoDir());
			}
			else if(x->getItem() < p->getItem()){
				distancia(x, p->getNoEsq());
			}
		}
		
		void noMaisLongo(No* p, No* raiz){
			cont = 0;
			if(p->ehNoFolha() == true){
				distancia(p, raiz);
				armazenaMaior(aux);
			}
			else{
				if(p->temNoDir() == true){
					noMaisLongo(p->getNoDir(), raiz);
				}				
				if(p->temNoEsq() == true){
					noMaisLongo(p->getNoEsq(), raiz);
				}			
			}
		}
		
		string formatacao(string std){
			while(std.length() < 4){
				std = "0" + std;
			}
			return std;
		}
				
	public:
			
		void criaNo(string it){
			nome = formatacao(it);
			Item aux;
			aux.setChave(atoi(it.c_str()));
			item = aux;
			alturaDireita = 0;
			alturaEsquerda = 0;
			noEsq = NIL;
			noDir = NIL;
			pai = NIL;
			compara = 0;
			cont = 0;
		}
		
		int armazenaMaior(int it){
			if(it > compara){
				compara = it;
			}
			return compara;
		}
		
		void setItem(Item item){
			this->item = item;
		}
		
		void setNoEsq(No* noEsq){
			this->noEsq = noEsq;
		}
		
		void setNoDir(No* noDir){
			this->noDir = noDir;
		}
		
		void setPai(No* pai){
			this->pai = pai;
		}
		
		string getNome(){
			return nome;
		}
		
		No* getPai(){
			return pai;
		}
		
		int getItem(){
			return item.getChave();
		}
		
		No* getNoEsq(){
			return this->noEsq;
		}
		
		No* getNoDir(){
			return this->noDir;
		}
		
		bool ehNoFolha(){
			if((noDir == NIL )&&(noEsq == NIL)){
				return true;
			}
			else{
				return false;
			}
		}
		
		bool temNoPai(){
			if(pai == NIL){
				return false;
			}
			else{
				return true;
			}
		}
		
		bool temNoEsq(){
			if(noEsq != NIL){
				return true;
			}
			else{
				return false;
			}
		}
		
		bool temNoDir(){
			if(noDir != NIL){
				return true;
			}
			else{
				return false;
			}
		}
		
		
		int alturaDir(){
			compara = 0;
			if(temNoDir() == true){
				noMaisLongo(noDir, noDir);
				alturaDireita = compara;
				return alturaDireita;	
			}
			alturaDireita = 0;
			return 0;
		}
		
		int alturaEsq(){
			compara = 0;
			if(temNoEsq() == true){
				noMaisLongo(noEsq, noEsq);
				alturaEsquerda = compara;
				return alturaEsquerda;				
			}
			else{
				alturaEsquerda = 0;
				return 0;
			}
			

		}
		
		int fatBalance(){
			int altE = 0;
			int altD = 0;
			if(temNoEsq() == true){
				compara = 0;
				noMaisLongo(noEsq, noEsq);
				altE = compara;
			}
			if(temNoDir() == true){
				compara = 0;
				noMaisLongo(noDir, noDir);
				altD = compara;
			}
			return altD - altE;
		}
		
		
};

class Pilha{
	private:
		int topo;
		int fundo;
		No* pilha[100];
		
	public:
		void criarPilha(){
			fundo = 0;
			topo = fundo;
		}
		
		void empilha(No* item){
 			if(topo == 100){
				cout << "Lista Cheia";
			}
			else{
				topo = topo +1;
				pilha[topo] = item;
			}
		}
		
		No* desempilha(){
			No* aux = pilha[topo];
			if(topo == fundo){
				cout << "Lista Vazia\n";
			}
			else{
				topo = topo - 1;
			}
			return aux;
		}
		
		void mostraPilha(){
			for(int i =1; i < topo + 1; i++){
				cout<< pilha[i]->getItem() << "\n";
			}
			cout << "-\n";
		}
		
		bool achaElemento(No* it){
			
			for(int i = 1; i < topo + 1; i++){
				if(pilha[i]->getItem() == it->getItem()){
					return true;
				}
			}
			
			return false;
		}
		
		int alturaPilha(){
			return topo;
		}
		
		int alturaDe(No* it){
			for(int i = 1; i < topo + 1; i++){
				if(pilha[i]->getItem() == it->getItem()){
					return i;
				}
			}			
		}
		
		No* ultimoElemento(){
			return pilha[topo];
		}
};

class Arvore{
	private:
		No* raiz;
		Pilha pilha;
		No* ultimo;
		No* saida[20];
		int cont;
		
		void inser(No* item, No* raiz){
			if(((raiz->temNoDir() == false) && (item->getItem() > raiz->getItem())) || ((raiz->temNoEsq() == false) && (item->getItem() < raiz->getItem()))){
				if(item->getItem() > raiz->getItem()){
					item->setPai(raiz);
					raiz->setNoDir(item);
				}
				else{
					item->setPai(raiz);
					raiz->setNoEsq(item);
				}
			}
			else if(item->getItem() > raiz->getItem()){
				inser(item, raiz->getNoDir());
			}
			else if(item->getItem() < raiz->getItem()){
				inser(item, raiz->getNoEsq());
			}
		}
		
		void percorre(No* x, No* p){
			if((p->fatBalance() > 1) || (p->fatBalance() < -1)){
				pilha.empilha(p);
			}
			if(p->temNoDir() == true){
				percorre(x, p->getNoDir());
			}				
			if(p->temNoEsq() == true){
				percorre(x, p->getNoEsq());
			}			
		}
		
		No* rotacaoSimplesEsq(No* p){
			No* aux;
			No* saida;
			No* nPai;
			saida = p->getNoDir();
			if(p->temNoPai() == true){
				nPai = p->getPai();
				p->getNoDir()->setPai(nPai);
				if(saida->getItem() > nPai->getItem()){
					nPai->setNoDir(saida);
				}
				else{
					nPai->setNoEsq(saida);
				}
				saida->setPai(nPai);
			}
			else{
				saida->setPai(NIL);
			}
			p->setPai(p->getNoDir());
			aux = p->getNoDir()->getNoEsq();
			p->getNoDir()->setNoEsq(p);
			p->setNoDir(aux);
			return saida;
		}
		
		No* rotacaoSimplesDir(No* p){
			No* aux;
			No* saida;
			No* nPai;
			saida = p->getNoEsq();
			if(p->temNoPai() == true){
				nPai = p->getPai();
				p->getNoEsq()->setPai(nPai);
				if(saida->getItem() > nPai->getItem()){
					nPai->setNoDir(saida);
				}
				else{
					nPai->setNoEsq(saida);
				}
				saida->setPai(nPai);
			}
			else{
				saida->setPai(NIL);
			}
			p->setPai(p->getNoEsq());
			aux = p->getNoEsq()->getNoDir();
			p->getNoEsq()->setNoDir(p);
			p->setNoEsq(aux);
			return saida;
		}
		
		No* rotacaoDuplaEsq(No* p){
			No* aux;
			No* nPai;
			aux = p->getNoDir()->getNoEsq();
			if(p->temNoPai() == true){
				nPai = p->getPai();
				if(aux->getItem() > nPai->getItem()){
					nPai->setNoDir(aux);
				}
				else{
					nPai->setNoEsq(aux);
				}
			}
			rotacaoSimplesDir(p->getNoDir());
			p->setNoDir(aux);
			rotacaoSimplesEsq(p);
			if(aux->temNoEsq() == true){
				if(aux->getNoEsq()->temNoEsq() == true){
					aux->getNoEsq()->getNoEsq()->setPai(aux->getNoEsq());
				}
				if(aux->getNoEsq()->temNoDir() == true){
					aux->getNoEsq()->getNoDir()->setPai(aux->getNoEsq());
				}
			}
			if(aux->temNoDir() == true){
				if(aux->getNoDir()->temNoEsq() == true){
					aux->getNoDir()->getNoEsq()->setPai(aux->getNoDir());
				}
				if(aux->getNoDir()->temNoDir() == true){
					aux->getNoDir()->getNoDir()->setPai(aux->getNoDir());
				}
			}
			return aux;
		}
		
		No* rotacaoDuplaDir(No* p){
			No* aux;
			No* nPai;
			aux = p->getNoEsq()->getNoDir();
			if(p->temNoPai() == true){
				nPai = p->getPai();
				if(aux->getItem() > nPai->getItem()){
					nPai->setNoDir(aux);
				}
				else{
					nPai->setNoEsq(aux);
				}
			}
			rotacaoSimplesEsq(p->getNoEsq());
			p->setNoEsq(aux);
			rotacaoSimplesDir(p);
			if(aux->temNoEsq() == true){
				if(aux->getNoEsq()->temNoEsq() == true){
					aux->getNoEsq()->getNoEsq()->setPai(aux->getNoEsq());
				}
				if(aux->getNoEsq()->temNoDir() == true){
					aux->getNoEsq()->getNoDir()->setPai(aux->getNoEsq());
				}
			}
			if(aux->temNoDir() == true){
				if(aux->getNoDir()->temNoEsq() == true){
					aux->getNoDir()->getNoEsq()->setPai(aux->getNoDir());
				}
				if(aux->getNoDir()->temNoDir() == true){
					aux->getNoDir()->getNoDir()->setPai(aux->getNoDir());
				}
			}
			return aux;
		}
		
		void balanceamento(No* raiz){
			No* aux;
			if(raiz->fatBalance() > 1){
				if(raiz->getNoDir()->fatBalance() >= 0){
					aux = rotacaoSimplesEsq(raiz);
					if(aux->temNoPai() == false){
						setRaiz(aux);
					}
				}
				else if(raiz->getNoDir()->fatBalance() < 0){
					aux = rotacaoDuplaEsq(raiz);
					if(aux->temNoPai() == false){
						setRaiz(aux);
					}
				}
			}
			else if(raiz->fatBalance() < -1){
				if(raiz->getNoEsq()->fatBalance() <= 0){
					aux = rotacaoSimplesDir(raiz);
					if(aux->temNoPai() == false){
						setRaiz(aux);
					}
				}
				else if(raiz->getNoEsq()->fatBalance() > 0){
					aux = rotacaoDuplaDir(raiz);
					if(aux->temNoPai() == false){
						setRaiz(aux);
					}
				}
			}		
		}
		
		string formatacao(string std){
			while(std.length() < 4){
				std = "0" + std;
			}
			return std;
		}
		
	public:
		
		void setRaiz(No* raiz){
			this->raiz = raiz;
		}
		
		No* getRaiz(){
			return raiz;
		}
		
		void cria(){
			cont = 0;
			raiz = NIL;
		}
		
		void busca(int x, No* p){
			saida[cont] = p;
			cont++;
			if(p->ehNoFolha() == true){
			}
			else{
				if(p->temNoDir() == true){
					busca(x, p->getNoDir());
				}
				if(p->temNoEsq() == true){
					busca(x, p->getNoEsq());
				}
			}
		}
		
		void final(string str){
			bool encontrado = false;
			for(int l = 0; l < cont; l++){
				if(formatacao(str) == saida[l]->getNome()){
					int menor = 99999;
					int posicao;
					Item it;
					No* aux;
					for(int i = 0; i < cont; i++){
						for(int j = 0; j < cont; j++){
							if(saida[j]->getItem() < menor){
								aux = saida[j];
								posicao = j;
								menor = saida[j]->getItem();
							}
						}
						it.setChave(99999);
						saida[posicao]->setItem(it);
						cout << aux->getNome() + " ";
						menor = 99999;
					}
					encontrado = true;
				}
			}
			if(encontrado == false){
				cout << "Chave não encontrada.";
			}
		}
		
		void inserir(No* num){	
			if(raiz == NIL){
				setRaiz(num);
			}
			else{
				ultimo = NIL;			
				inser(num, raiz);
				pilha.criarPilha();
				percorre(raiz, raiz);
				for(int i = 0; i < pilha.alturaPilha(); i++){
					balanceamento(pilha.desempilha());	
				}
				ultimo = NIL;
			}
		}
		
};

class Hash{
	private:
		Arvore lista[TAM];
		
		int funcaoHash(string s){
			int aux = 0;
			int cont = s.length();
			for(int i = 0; i < 4; i++){
				cont--;
				aux += ((int)s[i])*eleva(128, cont);
				
			}
			return mod(aux);
		}
		
		int eleva(int n1, int n2){
			int aux =1;
			for(int i =0; i < n2; i++){
				aux *=n1;
			}
			return aux;
		}
		
		int mod(int num){
			return num%TAM;
		}
		
	public:

		string formatacao(string std){
			while(std.length() < 4){
				std = "0" + std;
			}
			return std;
		}
				
		void inicia(){
			for(int i = 0; i < TAM; i++){
				lista[i].cria();
			}
		}
		
		void inserirTabela(No* p){
			lista[funcaoHash(p->getNome())].inserir(p);
		}
		
		void buscaHash(string it){
			int aux = funcaoHash(formatacao(it));
			lista[aux].busca(atoi(it.c_str()), lista[aux].getRaiz());
			lista[aux].final(it);
		}
};

int main(){
	Hash hash;
	ifstream arquivo;
	string entrada;
	string palavra;
	No aux[20000];
	No* chaves[20000];
	
	hash.inicia();
	arquivo.open("chaves.txt");
	int cont = 0;
	while(arquivo >> palavra){
		aux[cont].criaNo(palavra);
		chaves[cont] = &aux[cont];
		hash.inserirTabela(chaves[cont]);
		cont++;
	}
	arquivo.close();
	
	cin >> entrada;
	hash.buscaHash(entrada);
}





