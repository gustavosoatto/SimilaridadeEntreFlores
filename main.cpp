#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

struct dimensao
{
    double comprimento = 0.0;
    double largura = 0.0;
};

struct classificação
{
    double g_valor = -1.0;
    int g_grupo = -1;
};

struct petala
{
    dimensao dimensao;
    string especie = " ";
    classificação grupo;
};

int QuantidadePetalas(string s_temp);
void InicializarPetal(petala *petal, string s_temp);
int Receber_k();
int Receber_x();
void CriarArquivo(petala *petal, int T, string s_temp);

int main()
{
    // Declarações
    srand((unsigned int)time(0));
    int k = 0, x = 0, T = 0;
    double d_euclidiana = 0.0;
    string s_temp;

    // Recebendo quantidade total de linhas pulando o cabeçalho e inicializando o Vetor que armazenará as petalas
    T = QuantidadePetalas(s_temp);
    petala petal[T];

    // Preenchendo o Vetor com os devidos dados da struct 'petala'
    InicializarPetal(petal, s_temp);

    // Recebendo o valor de 'k', quantidade de grupos que as 'Struct' do 'Vetor' serão classificadas
    k = Receber_k();
    dimensao grupo[k];

    // Elege um representante 'k' vezes
    for (int i_2 = 0; i_2 < k; i_2++)
    {
        int repre = rand() % T;
        grupo[i_2].comprimento = petal[repre].dimensao.comprimento;
        grupo[i_2].largura = petal[repre].dimensao.largura;
    }

    // Recebendo o valor de 'x', quantidade de vezes que os grupos serão re-classificados
    x = Receber_x();
    for (int i_1 = 0; i_1 < x; i_1++)
    {
        // Para cada um dos termos do Vetor, classifica e reclassifica 'k' vezes nos grupos
        for (int i_2 = 0; i_2 < T; i_2++)
        {
            for (int i_3 = 0; i_3 < k; i_3++)
            {
                // Calcula a distância euclidiana e classifica em grupos
                d_euclidiana = hypot(petal[i_2].dimensao.comprimento - grupo[i_3].comprimento, petal[i_2].dimensao.largura - grupo[i_3].largura);
                if (petal[i_2].grupo.g_valor >= d_euclidiana || petal[i_2].grupo.g_valor < 0.0)
                {
                    petal[i_2].grupo.g_valor = d_euclidiana;
                    petal[i_2].grupo.g_grupo = i_3;
                    // grupo[i_3].comprimento = petal[i_2].dimensao.comprimento;
                    // grupo[i_3].largura = petal[i_2].dimensao.largura;
                }
            }
        }
    }

    // Cria o arquivo './SimilaridadePetalas.csv'
    CriarArquivo(petal, T, s_temp);
    return 0;
}

int QuantidadePetalas(string s_temp)
{
    int T = 0;

    ifstream ReceberPetalas("./iris_petalas.csv", ios::in);
    getline(ReceberPetalas, s_temp);
    while (getline(ReceberPetalas, s_temp))
        T++;
    ReceberPetalas.close();
    return T;
}

void InicializarPetal(petala *petal, string s_temp)
{
    int length, first, last, i = 0;
    string temp;

    ifstream ReceberPetalas("./iris_petalas.csv", ios::in);
    getline(ReceberPetalas, s_temp);
    while (getline(ReceberPetalas, s_temp))
    {
        length = s_temp.length();
        first = s_temp.find(',');
        last = s_temp.find(',', first + 1);

        temp = s_temp.substr(0, first);
        petal[i].dimensao.comprimento = stod(temp);
        temp = s_temp.substr(first + 1, last - first - 1);
        petal[i].dimensao.largura = stod(temp);
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

void CriarArquivo(petala *petal, int T, string s_temp)
{
    ofstream EscreverPetalas;
    ifstream ReceberPetalas;

    EscreverPetalas.open("./SimilaridadePetalas.csv", ios::out);
    ReceberPetalas.open("./iris_petalas.csv", ios::in);
    getline(ReceberPetalas, s_temp);
    EscreverPetalas << s_temp << ",\"group\"\n";
    for (int i = 0; i < T; i++)
        EscreverPetalas << petal[i].dimensao.comprimento << "," << petal[i].dimensao.largura << "," << petal[i].especie << "," << petal[i].grupo.g_grupo << "\n";
    ReceberPetalas.close();
    EscreverPetalas.close();
}