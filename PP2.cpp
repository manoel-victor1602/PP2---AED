#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

#define TAM 787
#define NIL NULL
#define numChaves 20000
#define ESQUERDA 0
#define DIREITA 1
#define tamPilha 100


class Util {
public:	
	string addzeros(string key){
		
		while(key.length() < 4){
			key = "0" + key;
		}
		return key;
	}

};
class No{
	private:
		int chave;
		string nome;
		int fatorBalance;
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
			if(p->ehNoFolha() == true && x->getChave() == p->getChave()){
				aux = cont;
				cont = 0;
			}
			else if(x->getChave() > p->getChave()){
				distancia(x, p->getNoDir());
			}
			else{
				distancia(x, p->getNoEsq());
			}
		}

		void noMaisLongo(No* p, No* raiz){
			cont = 0;
			if(p->ehNoFolha()){
				distancia(p, raiz);
				armazenaMaior(aux);
			}
			else{
				if(p->temNoDir()){
					noMaisLongo(p->getNoDir(), raiz);
				}
				if(p->temNoEsq()){
					noMaisLongo(p->getNoEsq(), raiz);
				}
			}
		}

	public:

		void setChave(int chave){
			this->chave = chave;
		}

		int getChave(){
			return chave;
		}

		void criaNo(string it){
			Util util;
			nome = util.addzeros(it);
			int aux;
			aux = atoi(it.c_str());
			chave = aux;
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

		No* getNoEsq(){
			return this->noEsq;
		}

		No* getNoDir(){
			return this->noDir;
		}

		bool ehNoFolha(){
			return ((noDir == NIL )&&(noEsq == NIL));
			
		}

		bool temNoPai(){
			return (pai != NIL);
		}

		bool temNoEsq(){
			return (noEsq != NIL);
		}

		bool temNoDir(){
			return (noDir != NIL);
		}

		int alturaEsquerda(){

			int altE = 0;		

			if(temNoEsq()){
				compara = 0;
				noMaisLongo(noEsq, noEsq);
				altE = compara;
			}

			return altE;
		}
		
		int alturaDireita(){
		
			int altD = 0;

			if(temNoDir()){
				compara = 0;
				noMaisLongo(noDir, noDir);
				altD = compara;
			}

			return altD;
		
		}

		int fatBalance(){
			
			return alturaDireita() - alturaEsquerda();
		}


};


class Pilha{
	private:
		int tam;
		No* pilha[tamPilha];

	public:
		void criarPilha(){
			tam = 0;
		}

		void empilha(No* item){
 			if(tam != tamPilha){
				tam++;
				pilha[tam] = item;
			}
		}

		No* desempilha(){
			No* aux = pilha[tam];
			if(tam != 0){
				tam--;
			}
			return aux;
		}


		bool achaElemento(No* it){

			for(int i = 0; i < tam; i++){
				if(pilha[i]->getChave() == it->getChave()){
					return true;
				}
			}

			return false;
		}

		int alturaPilha(){
			return tam;
		}

		int alturaDe(No* it){
			for(int i = 0; i < tam; i++){
				if(pilha[i]->getChave() == it->getChave()){
					return i;
				}
			}
		}

		No* ultimoElemento(){
			return pilha[tam];
		}
};


class Arvore{
	private:
		No* raiz;
		Pilha pilha;
		No* ultimo;
		No* saida[tamPilha];
		int cont;

		void inser(No* item, No* raiz){
			if(((raiz->temNoDir() == false) && (item->getChave() > raiz->getChave())) ||
			   ((raiz->temNoEsq() == false) && (item->getChave() < raiz->getChave()))) {

				if(item->getChave() > raiz->getChave()){
					item->setPai(raiz);
					raiz->setNoDir(item);
				}
				else{
					item->setPai(raiz);
					raiz->setNoEsq(item);
				}
			}
			else if(item->getChave() > raiz->getChave()){
				inser(item, raiz->getNoDir());
			}
			else if(item->getChave() < raiz->getChave()){
				inser(item, raiz->getNoEsq());
			}
		}

		void percorre(No* x, No* p){
			if((p->fatBalance() > 1) || (p->fatBalance() < -1)){
				pilha.empilha(p);
			}
			else if(p->temNoDir()){
				percorre(x, p->getNoDir());
			}
			else if(p->temNoEsq()){
				percorre(x, p->getNoEsq());
			}
		}

		No* rotacaoSimples(No *p, int direcao){
			No *aux;
			No *saida;
			No *nPai;

			if(direcao == ESQUERDA){
				saida = p->getNoDir();
				if(p->getNoDir()->temNoEsq()){
					p->getNoDir()->getNoEsq()->setPai(p);
				}
				if(p->temNoPai() == true){
					nPai = p->getPai();
					p->getNoDir()->setPai(nPai);
					if(saida->getChave() > nPai->getChave()){
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

			}else if(direcao == DIREITA){

				saida = p->getNoEsq();
				
				if(p->getNoEsq()->temNoDir() == true){
					p->getNoEsq()->getNoDir()->setPai(p);
				}

				if(p->temNoPai()){
					nPai = p->getPai();
					p->getNoEsq()->setPai(nPai);
					if(saida->getChave() > nPai->getChave()){
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

			}

			return saida;

		}
		No* rotacaoDupla(No* p, int direcao){

			
			No* aux;
			No* nPai;

			if(direcao == ESQUERDA)			
				aux = p->getNoDir()->getNoEsq();
			else if(direcao == DIREITA)
				aux = p->getNoEsq()->getNoDir();

			if(p->temNoPai() == true){
				nPai = p->getPai();
				if(aux->getChave() > nPai->getChave()){
					nPai->setNoDir(aux);
				}
				else{
					nPai->setNoEsq(aux);
				}
			}

			if(direcao == ESQUERDA){
				rotacaoSimples(p->getNoDir(), DIREITA);
				p->setNoDir(aux);
				rotacaoSimples(p,ESQUERDA);
			}else if(direcao == DIREITA){
				rotacaoSimples(p->getNoEsq(), ESQUERDA);
				p->setNoEsq(aux);
				rotacaoSimples(p, DIREITA);
			}

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
					aux = rotacaoSimples(raiz, ESQUERDA);
					if(!aux->temNoPai()){
						setRaiz(aux);
					}
				}
				else{
					aux = rotacaoDupla(raiz, ESQUERDA);
					if(!aux->temNoPai()){
						setRaiz(aux);
					}
				}
			}
			else if(raiz->fatBalance() < -1){
				if(raiz->getNoEsq()->fatBalance() <= 0){
					aux = rotacaoSimples(raiz, DIREITA);
					if(!aux->temNoPai()){
						setRaiz(aux);
					}
				}
				else{
					aux = rotacaoDupla(raiz, DIREITA);
					if(!aux->temNoPai()){
						setRaiz(aux);
					}
				}
			}
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
			if(!p->ehNoFolha()){
				if(p->temNoDir()){
					busca(x, p->getNoDir());
				}
				if(p->temNoEsq()){
					busca(x, p->getNoEsq());
				}
			}
		}

		void final(string str){
			Util util;
			bool encontrado = false;
			for(int l = 0; l < cont; l++){
				if(util.addzeros(str) == saida[l]->getNome()){
					int menor = 99999;
					int posicao;
					int it;
					No* aux;
					for(int i = 0; i < cont; i++){
						for(int j = 0; j < cont; j++){
							if(saida[j]->getChave() < menor){
								aux = saida[j];
								posicao = j;
								menor = saida[j]->getChave();
							}
						}
						it = 99999;
						saida[posicao]->setChave(it);
						cout << aux->getNome() + " ";
						menor = 99999;
					}

					cout << endl;

					encontrado = true;
				}
			}
			if(encontrado == false){
				cout << "Chave nÃ£o encontrada.";
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

		void inicia(){
			for(int i = 0; i < TAM; i++){
				lista[i].cria();
			}
		}

		void inserirTabela(No* p){
			lista[funcaoHash(p->getNome())].inserir(p);
		}

		void buscaHash(string it){
			Util util;
			int aux = funcaoHash(util.addzeros(it));
			lista[aux].busca(atoi(it.c_str()), lista[aux].getRaiz());
			lista[aux].final(it);
		}
};

void distancia(No* x, No* p);
void noMaisLongo(No* p, No* raiz);
string addzeros(string key);
void criaNo(string it);
int armazenaMaior(int it);
void setChave(int item);
void setNoEsq(No* noEsq);
void setNoDir(No* noDir);
void setPai(No* pai);
string getNome();
No* getPai();
int getChave();
No* getNoEsq();
No* getNoDir();
bool ehNoFolha();
bool temNoPai();
bool temNoEsq();
bool temNoDir();
int alturaEsquerda();
int alturaDireita();
int fatBalance();
void criarPilha();
void empilha(No* item);
No* desempilha();
void mostraPilha();
bool achaElemento(No* it);
int alturaPilha();
int alturaDe(No* it);
No* ultimoElemento();
void inser(No* item, No* raiz);
void percorre(No* x, No* p);
No* rotacaoSimples(No* p, int direcao);
No* rotacaoDupla(No* p, int direcao);
void balanceamento(No* raiz);
void setRaiz(No* raiz);
No* getRaiz();
void cria();
void busca(int x, No* p);
void final(string str);
void inserir(No* num);
int funcaoHash(string s);
int eleva(int n1, int n2);
int mod(int num);
void inicia();
void inserirTabela(No* p);
void buscaHash(string it);

int main(){

	Hash hash;
	ifstream arquivo;
	string entrada;
	string palavra;
	No aux[numChaves];
	No* chaves[numChaves];
	
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

