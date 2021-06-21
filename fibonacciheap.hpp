//  Calcula tamanho do vetor a baseado no teto do log na base 2
int getASize(int n)
{
    int res = 1;
    int counter = 0;
    while (res < n)
    {
        res *= 2;
        counter++;
    }

    return counter;
}

template<typename tipo>
class No
{
public:
    tipo valor;
    No *pai;
    No *filho;
    No *dir;
    No *esq;
    int grau;
    bool marca;
};

template<typename tipo>
void imprimeArray(No<tipo>* a[], int size)
{

    std::cout << "=== Iprimindo array graus: [ ";
    for (int i = 0; i< size; i++) {
        if (a[i] == nullptr) {
            std::cout << "NULL ";
        }
        else {
            std::cout << a[i]->valor << " " ;
        }
    }
    std::cout << "]" << std::endl;

}

template<typename tipo>
class ListaDeRaizes
{
public:
    No<tipo> *inicio;
    int size;

    void insert(No<tipo> *n)
    {

        if (this->size == 0) {
            this->inicio = n;
            this->inicio->dir = n;
            this->inicio->esq = n;
        } else if (this->size == 1) {
            this->inicio->dir = n;
            this->inicio->esq = n;
            n->dir = this->inicio;
            n->esq = this->inicio;
        } else {
            n->dir = this->inicio;
            n->esq = this->inicio->esq;
            this->inicio->esq->dir = n;
            this->inicio->esq = n;
        }
        this->size++;
    }

    No<tipo>* remove(No<tipo> *n)
    {
        auto *removido = new No<tipo>;
        No<tipo> *ponteiro = this->inicio;
        int condicaoParada = this->size;
        for (int i = 0; i < condicaoParada; i++)
        {
            if (ponteiro == n) {
                if (size == 1) {
                    this->inicio = NULL;
                } else {
                    if (ponteiro == this->inicio)
                        this->inicio = this->inicio->dir;
                    ponteiro->dir->esq = ponteiro->esq;
                    ponteiro->esq->dir = ponteiro->dir;
                }
                size--;
                return n;
            }
            ponteiro = ponteiro->dir;
        }
        removido = NULL;
        return removido;
    }

    void clear()
    {
        int condicaoParada = this->size;
        No<tipo> *indice = this->inicio;
        for (int i = 0; i < condicaoParada; i++) {
            this->remove(indice);
            indice = indice->dir;
        }
    }

    void imprimeLista()
    {
        std::cout << "Imprimindo ListaDeRaizes: [ ";
        No<tipo> *indice = this->inicio;
        for (int i = 0; i < this->size; i++) {
            std::cout << indice->valor << " ";
            indice = indice->dir;
        }
        std::cout << "]" << std::endl;
    }

};

template<typename tipo>
class FibonacciHeap
{
public:
    int n;
    No<tipo> *min;  // menor raiz dos min-heaps
    ListaDeRaizes<tipo> listaDeRaizes;

    FibonacciHeap()
    {
        this->n = 0;
        min = NULL;
        this->listaDeRaizes = ListaDeRaizes<tipo>();
    }

    // cria e retorna um heap sem nenhum elemento
    FibonacciHeap makeHeap()
    {
        FibonacciHeap f = FibonacciHeap<tipo>();

        return f;
    }

    // Insere, no heap H, o elemento x cujo valor já foi preenchido
    void insert(No<tipo> *x)
    {
        x->grau = 0;
        x->marca = false;
        x->pai = NULL;
        x->filho = NULL;

        if (this->min == NULL) {
            this->listaDeRaizes = ListaDeRaizes<tipo>();
            this->listaDeRaizes.insert(x);
            this->min = x;
        } else {
            this->listaDeRaizes.insert(x);
            if (x->valor < this->min->valor) {
                this->min = x;
                this->listaDeRaizes.inicio = x;
            }
        }

        this->n++;
    }

    // Retorna um ponteiro para o elemento do heap H cuja chave é mínima.
    No<tipo>* minimum()
    {
        return this->min;
    }

    // Cria e retorna um novo heap que contém todos os elementos dos heaps H1 e H2.
    //  Os heaps H1 e H2 são “destruídos” por essa operação.
    FibonacciHeap unionHeap(FibonacciHeap h1, FibonacciHeap h2)
    {
        FibonacciHeap<tipo> unionH = makeHeap();

        unionH.min = h1.min;

        unionH.listaDeRaizes.imprimeLista();

        // Adicionando a lista de raizes de h1 em unionH
        unionH.listaDeRaizes.size = h1.listaDeRaizes.size;
        unionH.listaDeRaizes.inicio = h1.listaDeRaizes.inicio;

        std::cout<<"Uniao: listad e raizes: ";
        unionH.listaDeRaizes.imprimeLista();

        std::cout << "concatenando h2.listaDeRaizes em uniao:" << std::endl;

        std::cout<<"Uniao: listad e raizes antes: ";
        unionH.listaDeRaizes.imprimeLista();

        // Concatenando listaDeRaizes.h2 em unionH
        No<tipo> *ponteiroInsercao = h2.listaDeRaizes.inicio;

        int condicaoParada = h2.listaDeRaizes.size;
        for (int i = 0; i < condicaoParada; i++) {
            std::cout << "[FOR INSERÇÃO]" << std::endl;
            std::cout << "i: " << i << " | valor do ponteiro: " << ponteiroInsercao->valor << std::endl;

            No<tipo> *prox = ponteiroInsercao->dir;

            unionH.insert(ponteiroInsercao);

            ponteiroInsercao = prox;
        }
        unionH.listaDeRaizes.imprimeLista();

        if (h1.min == NULL || (h1.min != NULL && h2.min < h1.min))
            unionH.min = h2.min;
        unionH.n = h1.n + h2.n;

        return unionH;
    }

    // Remove o nó y da lista de raizes e o adiciona como filho de x
    void fibHeapLink(No<tipo> *y, No<tipo> *x)
    {
        // Removendo y da lista de raizes de h
        this->listaDeRaizes.remove(y);

        // Adicionando y como filho de x
        y->pai = x;
        if (x->grau == 0) {
            x->filho = y;
            y->esq = y;
            y->dir = y;
        } else {
            // Adicionando a esquerda o 1º filho (representado pelo atributo ponteiro filho)
            y->dir = x->filho;
            y->esq = x->filho->esq;
            x->filho->esq->dir = y;
            x->filho->esq = y;
        }
        x->grau++;

        // Marcando y como false
        y->marca = false;
    }

    void consolidate()
    {
        int aSize = getASize(this->n);
        No<tipo>* a[aSize];

        for (int i = 0; i < aSize; i++)
            a[i] = NULL;

        No<tipo> *ponteiroIteracao = this->min;
        int condicao = this->listaDeRaizes.size;
        for (int i = 0; i < condicao; i++) {
            No<tipo> *prox = ponteiroIteracao->dir;

            No<tipo> *x = ponteiroIteracao;
            int d = x->grau;

            while (a[d] != NULL) {
                No<tipo> *y = a[d];
                if (x->valor > y->valor) {
                    No<tipo> *temp = y;
                    y = x;
                    x = temp;
                }
                fibHeapLink(y, x);
                a[d] = NULL;
                d++;
            }

            a[d] = x;

            ponteiroIteracao = prox;
        }

        this->min = NULL;
        for (int i = 0; i < aSize; i++) {
            if (a[i] != NULL) {
                if (this->min == NULL) {
                    // limpa a lista de raizes
                    this->listaDeRaizes.clear();
                    this->listaDeRaizes.insert(a[i]);

                    this->min = a[i];
                } else {
                    this->listaDeRaizes.insert(a[i]);

                    if (a[i]->valor < this->min->valor) {
                        this->min = a[i];
                    }
                }
            }
        }
    }

    // Elimina o elemento do heap H cuja chave é mínima, retornando um ponteiro para o elemento.
    No<tipo>* extractMin()
    {
        No<tipo> *z = this->min;
        if (z != NULL) {

            No<tipo> *ponteiroIteracao = z->filho;
            for (int i = 0; i < z->grau; i++) {

                this->listaDeRaizes.insert(ponteiroIteracao);
                ponteiroIteracao->pai = NULL;

                ponteiroIteracao = ponteiroIteracao->dir;
            }

            this->listaDeRaizes.remove(z);

            if (z == z->dir) {
                this->min = NULL;
            }else {
                this->min = z->dir;
                this->consolidate();
            }
            this->n--;
        }

        return z;
    }

    void cut(No<tipo> *x, No<tipo> *y)
    {
        // Remove x da lista de filhos de y
        if (y->grau == 1) {
            y->filho = NULL;
        } else {
            if (y->filho == x)
                y->filho = y->filho->dir;

            x->dir->esq = x->esq;
            x->esq->dir = x->dir;
        }

        y->grau--;

        // Adiciona x a listaDeRaizes de h
        this->listaDeRaizes.insert(x);

        x->pai = NULL;
        x->marca = false;
    }

    void cascadingCut(No<tipo> *y)
    {
        No<tipo> *z = y->pai;
        if (z != NULL) {
            if (!y->marca) {
                y->marca = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    // Atribui ao elemento x dentro do heap H o novo valor de chave k
    void fibDecreaseKey(No<tipo> *x, tipo k) {
        if (k > x->valor) {
            std::cout << "Erro: a nova chave é maior que a chave atual" << std::endl;
            return;
        }

        x->valor = k;

        No<tipo> *y = x->pai;
        if (y != NULL && x->valor < y->valor) {
            cut(x, y);
            cascadingCut(y);
        }

        // atualiza o ponteiro min caso o novo valor seja menor que o minimo
        if (x->valor < this->min->valor)
            this->min = x;
    }

    // Elimina o elemento x do heap H.
    void deleteNode(No<tipo> *x)
    {
        tipo menorValor = this->min->valor;
        menorValor--;
        fibDecreaseKey(x, menorValor);
        extractMin();
    }

};
