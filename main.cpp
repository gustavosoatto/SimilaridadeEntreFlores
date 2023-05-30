#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

struct petala
{
    double comprimento = 0.0;
    double largura = 0.0;
    string especie = " ";
    double v_grupo = -1;
    int grupo = -1;
};

int QuantidadePetalas();
void CriarPetalas(petala *petal, int T);
int Receber_k();
int Receber_x();
void CriarArquivo(petala *petal, int T);

int main()
{
    // Declarações
    srand((unsigned int)time(0));
    int k = 0, x = 1;
    int *p_tamanho, *p_grupo, T;

    // Recebendo quantidade total de linhas pulando o cabeçalho e inicializando o Vetor que armazenará as petalas
    T = QuantidadePetalas();
    p_tamanho = &T;
    petala petal[*p_tamanho];

    // Preenchendo o Vetor com os devidos dados da struct 'petala'
    CriarPetalas(petal, *p_tamanho);

    // Recebendo o valor de 'k', quantidade de grupos que as 'Struct' do 'Vetor' serão classificadas
    k = Receber_k();
    p_grupo = &k;
    petala grupo[*p_grupo];

    // Recebendo o valor de 'x', quantidade de vezes que os grupos serão re-classificados
    x = Receber_x();
    for (int i_1 = 0; i_1 < x; i_1++)
    {

        // Elege um representante 'k' vezes
        for (int i_2 = 0; i_2 < *p_grupo; i_2++)
        {
            int repre = rand() % *p_tamanho;
            grupo[i_2] = petal[repre];
        }

        // Para cada um dos termos do Vetor, classifica e reclassifica 'k' vezes nos grupos
        for (int i_2 = 0; i_2 < *p_tamanho; i_2++)
        {
            for (int i_3 = 0; i_3 < *p_grupo; i_3++)
            {
                // Calcula a distância euclidiana e classifica em grupos
                double z = hypot(petal[i_2].comprimento - grupo[i_3].comprimento, petal[i_2].largura - grupo[i_3].largura);
                if (petal[i_2].v_grupo >= z || petal[i_2].v_grupo < 0)
                {
                    petal[i_2].v_grupo = z;
                    petal[i_2].grupo = i_3;
                    grupo[i_3].comprimento = petal[i_2].comprimento;
                    grupo[i_3].largura = petal[i_2].largura;
                    grupo[i_3].especie = petal[i_2].especie;
                    grupo[i_3].v_grupo = petal[i_2].v_grupo;
                    grupo[i_3].grupo = petal[i_2].grupo;
                }
            }
        }
    }
    CriarArquivo(petal, *p_tamanho);
    return 0;
}

int QuantidadePetalas()
{
    string s_temp;
    int T = 0;

    ifstream ReceberPetalas("./iris_petalas.csv", ios::in);
    getline(ReceberPetalas, s_temp);
    while (getline(ReceberPetalas, s_temp))
        T++;
    ReceberPetalas.close();
    return T;
}

void CriarPetalas(petala *petal, int T)
{
    int length, first, last, i = 0;
    string s_temp, temp;

    ifstream ReceberPetalas("./iris_petalas.csv", ios::in);
    getline(ReceberPetalas, s_temp);
    while (getline(ReceberPetalas, s_temp))
    {
        length = s_temp.length();
        first = s_temp.find(',');
        last = s_temp.find(',', first + 1);

        temp = s_temp.substr(0, first);
        petal[i].comprimento = stod(temp);
        temp = s_temp.substr(first + 1, last - first - 1);
        petal[i].largura = stod(temp);
        temp = s_temp.substr(last + 1, length - last - 1);
        petal[i].especie = temp;
        i++;
    }
    ReceberPetalas.close();
}

int Receber_k()
{
    int k = 0;
    while (k < 1)
    {
        cout << "\n====================================================================\n"
             << "Digite quantos grupos deseja classificar as flores: " << endl;
        cin >> k;
        if (k < 1)
            cout << "Voce precisa classificar em pelo menos 1 grupo, use um valor de (k > 0)" << endl;
    }
    return k;
}

int Receber_x()
{
    int x = 0;
    while (x < 1)
    {
        cout << "\n====================================================================\n"
             << "Digite quantas vezes deseja re-classificar os grupos: " << endl;
        cin >> x;
        if (x < 1)
            cout << "Voce precisa classificar pelo menos 1 vez, use um valor de (x > 0)" << endl;
    }
    return x;
}

void CriarArquivo(petala *petal, int T)
{
    string s_temp;
    ofstream EscreverPetalas;
    ifstream ReceberPetalas;

    EscreverPetalas.open("./SimilaridadeFlores.csv", ios::out);
    ReceberPetalas.open("./iris_petalas.csv", ios::in);
    getline(ReceberPetalas, s_temp);
    EscreverPetalas << s_temp << ",\"Grupo\"\n";
    for (int i = 0; i < T; i++)
    {
        EscreverPetalas << petal[i].comprimento << "," << petal[i].largura << "," << petal[i].especie << "," << petal[i].grupo << "\n";
    }
    ReceberPetalas.close();
    EscreverPetalas.close();
}