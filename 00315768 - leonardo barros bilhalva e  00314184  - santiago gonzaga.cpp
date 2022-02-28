//+------------------------------------------------------------------+
//|                                                   Laboratório 04 |
//|              Alunos: Leonardo Barros Bilhalva  e Santiago Gonzaga|
//|                     Disciplina: Classificação e Pesquisa de Dados|
//|                                    Código da Disciplina: INF01124|
//+------------------------------------------------------------------+

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct estrutura_tabela_hash
{
    string nome;    
    bool ocupado = false;
    bool usado = false;
    estrutura_tabela_hash* next;
};

void make_hash_table(vector<string> vetor_de_nomes, vector<estrutura_tabela_hash *> &tabela_hash, int tamanho_tabela)  // Função que cria uma hash_table em tabela_hash a partir do vetor_de_nomes
{
    int numero = 0;                                     //numero será o caractere lido convertido para a tabela criada por mim onde | 1 == " " (espaço é o que mais aparece, então garanti que ele fosse o menor número pequeno) | 2 até 27 são as minusculas | 28 até 53 são as maiusculas(maiusculas escolhidas para serem as maiores, pois elas aparecem menos nos nomes(multiplicaremos por número menor))
    long long hash = 0;                                 //somatorio para hash de cada nome

    for(int a = 0; a<vetor_de_nomes.size(); a++)        //percorre lista de nomes
    {
        hash = 0;
        for(int b=0; b<vetor_de_nomes[a].size(); b++)   //percorre caracteres do nome atual
        { 
            numero = 0;
            if(vetor_de_nomes[a][b] >= 'A' || vetor_de_nomes[a][b] <= 'Z')
            numero = vetor_de_nomes[a][b] - 40/*diminui para chegar no 1*/+ 26/*pula os primeiros 26 que sao as minusculas*/+ 1;/*espaço é o primeiro*/
            if(vetor_de_nomes[a][b] >= 'a' || vetor_de_nomes[a][b] <= 'z')
            numero = vetor_de_nomes[a][b] - 60/*diminui para chegar no 1*/+ 1;/*espaço é o primeiro*/
            if(vetor_de_nomes[a][b] == ' ')
            numero = 1;/*espaço e o primeiro*/
            if(vetor_de_nomes[a][b] == ',')
            numero = 54;/*virgula*/
            if(vetor_de_nomes[a][b] >= '0' || vetor_de_nomes[a][b] <= '9')
            numero = vetor_de_nomes[a][b] + 55 /*todos caracteres que vieram antes*/;


            hash = (59 * hash + numero) % tamanho_tabela;                // 59 é o número primo escolhido para potência da string, pois é o maior número primo após 53 | o módulo é feito pelo tamanho da tabela hash atual            
        }
        // temos um hash pronto para ser alocado em -> long long hash

        if(tabela_hash[hash] != NULL) // Se tabela hash apontar para diferente de nulo, significa que já foi preenchido
        {
            estrutura_tabela_hash *pointer = tabela_hash[hash];                         //cria um ponteiro para percorrer os proximos

            while(pointer->next != NULL)                                                //percorre até chegar no ponteiro que terá o próximo nulo
            {
                pointer = pointer->next;
            }

            estrutura_tabela_hash* temp1 = new estrutura_tabela_hash;                   // cria um ponteiro temporário e aloca os dados de forma igual a alocação base
            temp1->nome = vetor_de_nomes[a];
            temp1->ocupado = true;
            temp1->usado = true;
            temp1->next = NULL;

            pointer->next = temp1;                                                      // o ponteiro do último elemento da lista obtido no while é utilizado para indicar o novo próximo elemento, que é o alocado a cima em temp1
        }
        else    //caso aponta para nulo -> preencher!
        {   
            tabela_hash[hash] = new estrutura_tabela_hash;          // aloca uma nova estrutura e preenche
            tabela_hash[hash]->nome    = vetor_de_nomes[a];
            tabela_hash[hash]->ocupado = true;
            tabela_hash[hash]->usado   = true;
            tabela_hash[hash]->next    = NULL;
        }
    }
}

int search_hash_table(vector<estrutura_tabela_hash *> tabela_hash, string nome, int tamanho_tabela)  // Função que pesquisa um nome em uma tabela hash e retorna a quantidade de buscas/colisões da pesquisa
{
    int numero = 0;                                     //numero será o caractere lido convertido para a tabela criada por mim onde | 1 == " " (espaço é o que mais aparece, então garanti que ele fosse o menor número pequeno) | 2 até 27 são as minusculas | 28 até 53 são as maiusculas(maiusculas escolhidas para serem as maiores, pois elas aparecem menos nos nomes(multiplicaremos por número menor))
    long long hash = 0;                                 //somatorio para hash de cada nome
    int quantidade_busca = 1;


        hash = 0;
        for(int b=0; b<nome.size(); b++)   //percorre caracteres do nome atual
        { 
            numero = 0;
            if(nome[b] >= 'A' || nome[b] <= 'Z')
            numero = nome[b] - 40/*diminui para chegar no 1*/+ 26/*pula os primeiros 26 que sao as minusculas*/+ 1;/*espaço é o primeiro*/
            if(nome[b] >= 'a' || nome[b] <= 'z')
            numero = nome[b] - 60/*diminui para chegar no 1*/+ 1;/*espaço é o primeiro*/
            if(nome[b] == ' ')
            numero = 1;/*espaço é o primeiro*/
            if(nome[b] == ',')
            numero = 54;/*virgula*/
            if(nome[b] >= '0' || nome[b] <= '9')
            numero = nome[b] + 55 /*todos caracteres que vieram antes*/;

            hash = (59 * hash + numero) % tamanho_tabela;                // 59 é o número primo escolhido para potência da string, pois é o maior número primo após 53 | o módulo é feito pelo tamanho da tabela hash atual            
        }
        // temos um hash pronto para ser alocado em -> long long hash

        if(tabela_hash[hash] != NULL) // Se tabela hash apontar para diferente de nulo, significa que já foi preenchido
        {
            estrutura_tabela_hash *pointer = tabela_hash[hash];                         //cria um ponteiro para percorrer os proximos

            while(pointer->next != NULL && pointer->nome != nome)         //percorre até chegar no ponteiro que terá ou o próximo nulo ou o nome atual
            {
                pointer = pointer->next;
                quantidade_busca ++;
            }

            if(pointer->nome == nome) 
            return quantidade_busca;                            // Se ele achou, significa que a quantidade de colisões até então já foi somada
            else return quantidade_busca + 1;                    // Se não, significa que o nome não está na tabela e próximo nome seria nulo, então precisamos somar +1 pela comparação com o nome nulo e retornar a quantidade de busca até então           

        }
        else    //caso aponta para nulo -> preencher!
        {        
            return quantidade_busca;  // 1 só busca, pois o hash não foi alocado!
        }
}

void write_professor(vector<estrutura_tabela_hash *> tabela_hash, vector<string> vetor_de_consultas, int tamanho_tabela, ofstream &escrita_experimento) // Função que escreve as estatisticas requeridas pelo professor
{
    int valor_atual = -1;  // valor atual da hash consulta | inicializacao: menor valor possível antes de começar
    int valor_maximo = 0; // variavel para máximo de consultas
    float soma_consultas = 0; // variavel para somar as consultas para media

    for(int i = 0; i < vetor_de_consultas.size(); i ++)
    {
        valor_atual = search_hash_table(tabela_hash, vetor_de_consultas[i], tamanho_tabela);
        soma_consultas += valor_atual;
        escrita_experimento << "NOME" << i + 1 << " " << vetor_de_consultas[i] << " #" << valor_atual << endl;
        if(valor_atual > valor_maximo)
        valor_maximo = valor_atual;
    }
    escrita_experimento << "MEDIA #"  << (float)(soma_consultas/vetor_de_consultas.size()) << endl;
    escrita_experimento << "MAXIMO #" << valor_maximo                                      << endl;

}

int search_hash_table_alunos(vector<estrutura_tabela_hash *> tabela_hash, string nome, int tamanho_tabela, bool &nao_achou)  // Função que pesquisa um nome em uma tabela hash e retorna a quantidade de buscas/colisões da pesquisa
{
    int numero = 0;                                     //numero será o caractere lido convertido para a tabela criada por mim onde | 1 == " " (espaço é o que mais aparece, então garanti que ele fosse o menor número pequeno) | 2 até 27 são as minusculas | 28 até 53 são as maiusculas(maiusculas escolhidas para serem as maiores, pois elas aparecem menos nos nomes(multiplicaremos por número menor))
    long long hash = 0;                                 //somatorio para hash de cada nome
    int quantidade_busca = 1;


        hash = 0;
        for(int b=0; b<nome.size(); b++)   //percorre caracteres do nome atual
        { 
            numero = 0;
            if(nome[b] >= 'A' || nome[b] <= 'Z')
            numero = nome[b] - 40/*diminui para chegar no 1*/+ 26/*pula os primeiros 26 que sao as minusculas*/+ 1;/*espaço é o primeiro*/
            if(nome[b] >= 'a' || nome[b] <= 'z')
            numero = nome[b] - 60/*diminui para chegar no 1*/+ 1;/*espaço é o primeiro*/
            if(nome[b] == ' ')
            numero = 1;/*espaço é o primeiro*/

            hash = (59 * hash + numero) % tamanho_tabela;                // 59 é o número primo escolhido para potência da string, pois é o maior número primo após 53 | o módulo é feito pelo tamanho da tabela hash atual            
        }
        // temos um hash pronto para ser alocado em -> long long hash

        if(tabela_hash[hash] != NULL) // Se tabela hash apontar para diferente de nulo, significa que já foi preenchido
        {
            estrutura_tabela_hash *pointer = tabela_hash[hash];                         //cria um ponteiro para percorrer os proximos

            while(pointer->next != NULL && pointer->nome != nome)         //percorre até chegar no ponteiro que terá ou o próximo nulo ou o nome atual
            {
                pointer = pointer->next;
                quantidade_busca ++;
            }

            if(pointer->nome == nome) 
            return quantidade_busca;                            // Se ele achou, significa que a quantidade de colisões até então já foi somada
            else 
            {   
                nao_achou = true;                               // Significa que o nome não foi encontrado             
                return quantidade_busca + 1;                    // Se não, significa que o nome não está na tabela e próximo nome seria nulo, então precisamos somar +1 pela comparação com o nome nulo e retornar a quantidade de busca até então
            }           

        }
        else    //caso aponta para nulo -> preencher!
        {        
            return quantidade_busca;  // 1 só busca, pois o hash não foi alocado!
        }
}

void write_alunos(vector<estrutura_tabela_hash *> tabela_hash, vector<string> vetor_de_consultas, int tamanho_tabela, ofstream &escrita_experimento) // Função que escreve as estatistiscas requeridas pelo professor na otica dos alunos
{
    int valor_atual = -1;  // valor atual da hash consulta | inicializacao: menor valor possível antes de começar
    int valor_maximo = 0; // variavel para máximo de consultas
    float soma_consultas = 0; // variavel para somar as consultas para media

    bool nao_achou = false;             //booleano para saber se não achou
    vector<int> vetor_de_perdidos;  //vetor com os números não encontrados

    escrita_experimento << "Nomes encontrados:" << endl;

    for(int i = 0; i < vetor_de_consultas.size(); i ++)
    {
        nao_achou = false;
        valor_atual = search_hash_table_alunos(tabela_hash, vetor_de_consultas[i], tamanho_tabela, nao_achou);
        
        if(nao_achou)                           //Se o nome não foi encontrado, adiciona o indice dele a vetor_de_perdidos e pula para o proximo laço do for(pula a escrita dele na secao dos encontrados)
        {
            vetor_de_perdidos.push_back(i);
            continue;
        }

        soma_consultas += valor_atual;
        escrita_experimento << "NOME" << i + 1 << " " << vetor_de_consultas[i] << " #" << valor_atual << endl;

        if(valor_atual > valor_maximo)
        valor_maximo = valor_atual;
    }

    escrita_experimento << "-------------------------------------------------------------------------" << endl;
    escrita_experimento << "Nomes nao encontrados:" << endl;

    for(int i = 0; i < vetor_de_perdidos.size(); i ++)  // percorre o vetor de perdidos para escrever todos nomes não encontrados
    {
        valor_atual = search_hash_table_alunos(tabela_hash, vetor_de_consultas[vetor_de_perdidos[i]], tamanho_tabela, nao_achou);
        
        soma_consultas += valor_atual;
        escrita_experimento << "NOME" << i + 1 << " " << vetor_de_consultas[vetor_de_perdidos[i]] << " #" << valor_atual << endl;

        if(valor_atual > valor_maximo)
        valor_maximo = valor_atual;
    }
    
    escrita_experimento << "Estatisticas sobre o total de nomes:" << endl;
    escrita_experimento << "MEDIA #"  << (float)(soma_consultas/vetor_de_consultas.size()) << endl;
    escrita_experimento << "MAXIMO #" << valor_maximo                                      << endl;
}

int main(){
    cout << "Laboratorio 4 comecou" << endl;
	ifstream leitura_nomes;
    ifstream leitura_consulta;                 

	ofstream escrita_experimento503;
    ofstream escrita_experimento2503; 
    ofstream escrita_experimento5003; 
    ofstream escrita_experimento7507;

    ofstream escrita_experimento503_alunos;
    ofstream escrita_experimento2503_alunos; 
    ofstream escrita_experimento5003_alunos; 
    ofstream escrita_experimento7507_alunos; 

    string line;
    vector<string> vetor_de_nomes;
    vector<string> vetor_de_consultas;

    leitura_nomes.open("nomes_10000.txt");      
    leitura_consulta.open("consultas.txt");  
    escrita_experimento503.open("escrita_experimento503.txt");  
    escrita_experimento2503.open("escrita_experimento2503.txt");
    escrita_experimento5003.open("escrita_experimento5003.txt");
    escrita_experimento7507.open("escrita_experimento7507.txt");   
     
    escrita_experimento503_alunos.open("escrita_experimento503_alunos.txt");  
    escrita_experimento2503_alunos.open("escrita_experimento2503_alunos.txt");
    escrita_experimento5003_alunos.open("escrita_experimento5003_alunos.txt");
    escrita_experimento7507_alunos.open("escrita_experimento7507_alunos.txt");      

    while(getline(leitura_nomes, line))
    {        
      vetor_de_nomes.push_back(line);
    }

     while(getline(leitura_consulta, line))
    {        
      vetor_de_consultas.push_back(line);
    }		

    //for (int i = 0; i < vetor_de_nomes.size(); i++) {                           //Deixei aqui essa funcao para conferir a leitura
    //    for (int j = 0; j < vetor_de_nomes[i].size(); j++)
    //        cout << vetor_de_nomes[i][j] << " ";
    //    cout << endl;
    //}

    vector<estrutura_tabela_hash *> tabela_503(503);
    make_hash_table(vetor_de_nomes, tabela_503, 503);

    vector<estrutura_tabela_hash *> tabela_2503(2503);
    make_hash_table(vetor_de_nomes, tabela_2503, 2503);

    vector<estrutura_tabela_hash *> tabela_5003(5003);
    make_hash_table(vetor_de_nomes, tabela_5003, 5003);

    vector<estrutura_tabela_hash *> tabela_7507(7507);
    make_hash_table(vetor_de_nomes, tabela_7507, 7507);

    /*for(int i = 0; i<tabela_503.size(); i++)                                  // Aqui deixei para consultar visualmente como ficou organizada a tabela
    {
            estrutura_tabela_hash *pointer = tabela_503[i]->next;
        cout << tabela_503[i]->nome << " | ";
            while(pointer != NULL)
            {            
                cout << pointer->nome << " - ";
                pointer = pointer->next;     
            }
        cout << endl;
    }*/ 

    write_professor(tabela_503,  vetor_de_consultas, 503 , escrita_experimento503);  // Escreve as esatisticas do experimento com tamanho de tabela 503
    write_professor(tabela_2503, vetor_de_consultas, 2503, escrita_experimento2503); // Escreve as esatisticas do experimento com tamanho de tabela 2503
    write_professor(tabela_5003, vetor_de_consultas, 5003, escrita_experimento5003); // Escreve as esatisticas do experimento com tamanho de tabela 5003
    write_professor(tabela_7507, vetor_de_consultas, 7507, escrita_experimento7507); // Escreve as esatisticas do experimento com tamanho de tabela 7503
    
    cout << "Acabou o que professor pediu. A partir desse momento, iremos gerar as saidas opcionais dos alunos." << endl;

    write_alunos(tabela_503,  vetor_de_consultas, 503 , escrita_experimento503_alunos);  // Escreve as esatisticas do experimento com tamanho de tabela 503  | alunos
    write_alunos(tabela_2503, vetor_de_consultas, 2503, escrita_experimento2503_alunos); // Escreve as esatisticas do experimento com tamanho de tabela 2503 | alunos
    write_alunos(tabela_5003, vetor_de_consultas, 5003, escrita_experimento5003_alunos); // Escreve as esatisticas do experimento com tamanho de tabela 5003 | alunos
    write_alunos(tabela_7507, vetor_de_consultas, 7507, escrita_experimento7507_alunos); // Escreve as esatisticas do experimento com tamanho de tabela 7503 | alunos
    
    leitura_nomes.close();
    leitura_consulta.close();
    escrita_experimento503.close();
    escrita_experimento2503.close();
    escrita_experimento5003.close();
    escrita_experimento7507.close();
    escrita_experimento503_alunos.close();
    escrita_experimento2503_alunos.close();
    escrita_experimento5003_alunos.close();
    escrita_experimento7507_alunos.close();
    cout << "Laboratorio 4 terminou :)";
    return 0;
}
