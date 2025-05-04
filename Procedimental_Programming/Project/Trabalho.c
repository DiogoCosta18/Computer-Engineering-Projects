#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "Trabalho.h"

int compara_datas(Data d1, Data d2){
    // se a data for menor retorna -1, se for maior retorna 1, se for igual retorna 0
    if (d1.ano<d2.ano) return -1;
    if (d1.ano>d2.ano) return 1;
    if (d1.mes<d2.mes) return -1;
    if (d1.mes>d2.mes) return 1;
    if (d1.dia<d2.dia) return -1;
    if (d1.dia>d2.dia) return 1;
    return 0;
}

Lista_Blocos * cria_fila(char horas[20][20]){
    //A função cria uma lista encadeada de blocos de tempo representados pela Estrutura Lista_Blocos. 
    //Para cada bloco de tempo, representado pela Estrutura Hora, a função aloca memória, inicializa os membros e adiciona-os no início da lista. 
    //Além disso, são alocadas memórias para as Estruturas Reserva e Lista, para armazenar informações sobre reservas e pré-reservas. 
    //No final, a função retorna a lista encadeada de blocos de tempo.
    Lista_Blocos *f = (Lista_Blocos *) malloc(sizeof(Lista_Blocos));
    f->inicio = NULL;
    for(int i=20-1; i>=0; i--){
        Hora* h = (Hora *) malloc(sizeof(Hora));
        if (h==NULL){
            printf ("Memória não disponível\n");
            return f; // Assinala erro
        }
        h->anterior = NULL;
        h->proximo = f->inicio;
        if(f->fim == NULL){
            f->fim = h;
        }
        if(f->inicio != NULL){
            f->inicio->anterior = h;
        }
        f->inicio = h;
        strcpy(h->hora, horas[i]);
        h->reserva = (Reserva *) malloc(sizeof(Reserva));
        h->pre_reservas = (lista*) malloc(sizeof(lista));
        if (h->reserva == NULL || h->pre_reservas == NULL){
            printf ("Memória não disponível\n");
            return f; // Assinala erro
        }
        else{
            h->reserva->n_reserva = 0;
            h->reserva->tipo = 0; 
            h->reserva->estado = 0;
            h->pre_reservas->inicio = (no*) malloc(sizeof(no));
            h->pre_reservas->fim = (no*) malloc(sizeof(no));
            h->pre_reservas->inicio->proximo = h->pre_reservas->fim;
            h->pre_reservas->inicio->pre_reserva = (Reserva *)malloc(sizeof(Reserva));
            h->pre_reservas->fim->pre_reserva = (Reserva *)malloc(sizeof(Reserva));
            
        }
    }
    return f;
}

Lista_Blocos * adiciona_data(Lista_Dias *d, char horas[20][20], Data data){
    //adiciona um novo dia e chama a função que cria os blocos de horas para esse dia
    Lista_Blocos *novo_dia = cria_fila(horas);
    novo_dia->data.dia = data.dia;
    novo_dia->data.mes = data.mes;
    novo_dia->data.ano = data.ano;
    novo_dia->proximo = NULL;

    Lista_Blocos *f = d->inicio;
    while(f->proximo!=NULL && compara_datas(f->proximo->data,data)==-1) f = f->proximo;

    novo_dia->anterior = f;
    novo_dia->proximo = f->proximo;
    if(f == d->fim){
        d->fim = novo_dia;
    }
    else{
        novo_dia->proximo->anterior = novo_dia;
    }
    f->proximo = novo_dia;
    
    return novo_dia;
}

Data *avanca_data(Data *data, Lista_Dias *d, char horas[20][20]){
    // apos o utilizador selecionar a opcao 6, vemos a que mes pertence, se tiver no ultimo dia mudamos de mes, caso contrário aumentamos so o dia. A 31/12/ano mudamos de ano
    int mes_31[7] = { 1, 3, 5, 7, 8, 10, 12};
    int mes_30[4] = {4, 6, 9, 11};
    int mes_28 = 2;
    if (data->mes==12 && data->dia==31){
        data->dia = 1;
        data->mes = 1;
        data->ano ++;
        adiciona_data(d, horas, *data);
        return data;
    }
    if (data->dia<28){
        data->dia++;
        adiciona_data(d, horas, *data);
        return data;
    }
    else{
        if (data->mes==mes_28){
            data->dia = 1;
            data->mes++;
            adiciona_data(d, horas, *data);
            return data;
        }
        else{ 
            for(int i=0; i<4; i++){
                if (data->mes==mes_30[i]){
                    if(data->dia<30){
                        data->dia++;
                        adiciona_data(d, horas, *data);
                        return data;
                    }
                    else{
                        data->dia = 1;
                        data->mes++;
                        adiciona_data(d, horas, *data);
                        return data;
                    }
                }
            }
            for(int i=0; i<7; i++){
                if (data->mes==mes_31[i]){
                    if(data->dia<31){
                        data->dia++;
                        adiciona_data(d, horas, *data);
                        return data;
                    }
                    else{
                        data->dia = 1;
                        data->mes++;
                        adiciona_data(d, horas, *data);
                        return data;
                    }
                }
            }
        }
    }
    return data;
}

Lista_Dias cria_lista_datas(char horas[20][20], Data data){
    //cria o primeiro dia e chama a função que cria os blocos de hora para cada dia
    Lista_Dias d;
    d.inicio = cria_fila(horas);
    d.inicio->data.dia = data.dia;
    d.inicio->data.mes = data.mes;
    d.inicio->data.ano = data.ano;
    d.fim = d.inicio;
    d.fim->proximo = NULL;
    d.inicio->anterior = NULL;
    return d;
}

void imprime_lista(Lista_Dias *d, char horas[20][20], int tipo, Data data){
    //imprime a lista de blocos de horas para o utilizador ver se estão ocupadas ou livres.
    //faz a destinção entre lavagem e manutenção
    //numa lavagem imprime blocos de meia hora
    //numa manutenção imprime blocos de hora
    Lista_Blocos *f = d->inicio;
    Hora *h = f->inicio;
    printf("Horas disponíveis:\n\n");
    while (f!=NULL){
        int i=0;
        h = f->inicio;
        if (f->data.dia==data.dia && f->data.mes==data.mes && f->data.ano==data.ano){
            while (h!=NULL){
                if (tipo==1){
                    if(h->reserva->n_reserva==0){
                        printf("%s - %s  - Livre\n", horas[i], horas[i+1]);
                    }
                    else printf("%s - %s  - Ocupado\n", horas[i], horas[i+1]);
                }
                else if (i<19){
                    if(h->reserva->n_reserva==0&&h->proximo->reserva->n_reserva==0){
                        printf("%s - %s  - Livre\n", horas[i], horas[i+2]);
                    }
                    else printf("%s - %s  - Ocupado\n", horas[i], horas[i+2]);
                }
                h = h->proximo;
                i++;
            }
        }
        f = f->proximo;
    }
}

void listarReservas(Lista_Dias *d){
    //imprime as reservas e as pré-reservas separadamente
    //indica sempre o numero de reserva, o id, o tipo de reserva e a hora de inicio
    //se não existir nada, informa que não há reservas ou pré-reservas feitas
    Lista_Blocos *f = d->fim;
    Hora *h = f->fim;
    printf("\n");
    printf("Reservas marcadas:\n");
    int flag = 0;
    while (f!=NULL){
        h = f->fim;
        while (h!=NULL){
            if (h->reserva->tipo==1){
                if(h->reserva->n_reserva!=0){
                    printf("%d: Cliente %d, Lavagem, Data: %d/%d/%d, Hora Início: %s\n", h->reserva->n_reserva, h->reserva->id, f->data.dia, f->data.mes, f->data.ano, h->reserva->inicio->hora);
                    flag++;
                }
            }
            if (h->reserva->tipo==2){
                if(h->reserva->n_reserva!=0 && h->reserva->n_reserva!=h->proximo->reserva->n_reserva){
                    printf("%d: Cliente %d, Manutenção, Data: %d/%d/%d, Hora Início: %s\n", h->reserva->n_reserva, h->reserva->id, f->data.dia, f->data.mes, f->data.ano, h->reserva->inicio->hora);
                    flag++;
                }
            }
            h = h->anterior;
        }
        f = f->anterior;
    }
    if (flag==0){
        printf("Não existem reservas marcadas.\n");
    }
    flag = 0;
    //Pre-reservas
    f = d->fim;
    printf("\n");
    printf("Pré-Reservas:\n");
    while (f!=NULL){
        h = f->fim;
        while (h != NULL) {
            no *n = h->pre_reservas->inicio;
            while (n != NULL) {
                if (n->pre_reserva != NULL) {
                    if (n->pre_reserva->estado == 1) {
                        if (n->pre_reserva->tipo == Lavagem) {
                            printf("%d: Cliente %d, Pré-Lavagem, Data: %d/%d/%d, Hora Início: %s\n", n->pre_reserva->n_reserva, n->pre_reserva->id, f->data.dia, f->data.mes, f->data.ano, n->pre_reserva->inicio->hora);
                            flag++;
                        } else if (n->pre_reserva->tipo == Manutencao) {
                            if(h->pre_reservas->inicio->pre_reserva->n_reserva != h->proximo->pre_reservas->inicio->pre_reserva->n_reserva){
                                printf("%d: Cliente %d, Pré-Manutenção, Data: %d/%d/%d, Hora Início: %s\n", n->pre_reserva->n_reserva, n->pre_reserva->id, f->data.dia, f->data.mes, f->data.ano, n->pre_reserva->inicio->hora);
                                flag++;
                            }
                        }
                    }
                }
                n = n->proximo;
            }
            h = h->anterior;
        }
        f = f->anterior;
    }
    if (flag==0){
        printf("Não existem pré-reservas marcadas.\n");
    }
}

int listarReservasCliente(Lista_Dias *d, int id){
    //através do id do cliente é feita uma filtragem para apenas apresentar as reservas e pré-reservas do cliente com o id fornecido
    //apresenta as informações da mesma forma que a função listarReservas()
    Lista_Blocos *f = d->inicio;
    Hora *h = f->inicio;
    printf("\n");
    printf("Reservas do cliente com id %d:\n", id);
    int flag = 0;
    while (f!=NULL){
        h = f->inicio;
        while (h!=NULL){
            if (h->reserva->tipo == Lavagem){
                if(h->reserva->n_reserva!=0 && h->reserva->id==id){
                    printf("%d: Cliente %d, Lavagem, Data: %d/%d/%d, Hora Início: %s\n", h->reserva->n_reserva, h->reserva->id, f->data.dia, f->data.mes, f->data.ano, h->reserva->inicio->hora);
                    flag++;
                }
            }
            if (h->reserva->tipo == Manutencao){
                if(h->reserva->n_reserva!=0 && h->reserva->id==id){
                    if(h->reserva->n_reserva!=h->proximo->reserva->n_reserva){
                        printf("%d: Cliente %d, Manutenção, Data: %d/%d/%d, Hora Início: %s\n", h->reserva->n_reserva, h->reserva->id, f->data.dia, f->data.mes, f->data.ano, h->reserva->inicio->hora);
                        flag++;
                    }
                }
            }
            h = h->proximo;
        }
        f = f->proximo;
    }
    int sem_reservas = 2;
    if (flag==0){
        printf("Não existem reservas do cliente com id %d.\n", id);
        sem_reservas--;
    }
    flag = 0;
    //Pre-reservas
    printf("\n");
    printf("Pré-Reservas do cliente com id %d:\n", id);
    f = d->inicio;
    while (f!=NULL){
        h = f->inicio;
        while (h != NULL) {
            no *n = h->pre_reservas->inicio;
            while (n != NULL) {
                if (n->pre_reserva != NULL) {
                    if (n->pre_reserva->estado == 1) {
                        if (n->pre_reserva->tipo == Lavagem) {
                            if(n->pre_reserva->n_reserva!=0 && n->pre_reserva->id==id){
                                printf("%d: Cliente %d, Pré-Lavagem, Data: %d/%d/%d, Hora Início: %s\n", n->pre_reserva->n_reserva, n->pre_reserva->id, f->data.dia, f->data.mes, f->data.ano, n->pre_reserva->inicio->hora);
                                flag++;
                            }
                        } else if (n->pre_reserva->tipo == Manutencao) {
                            if(n->pre_reserva->n_reserva!=0 && n->pre_reserva->id==id){
                                if(h->pre_reservas->inicio->pre_reserva->n_reserva != h->proximo->pre_reservas->inicio->pre_reserva->n_reserva){
                                    printf("%d: Cliente %d, Pré-Manutenção, Data: %d/%d/%d, Hora Início: %s\n", n->pre_reserva->n_reserva, n->pre_reserva->id, f->data.dia, f->data.mes, f->data.ano, n->pre_reserva->inicio->hora);
                                    flag++;
                                }
                            }
                        }
                    }
                }
                n = n->proximo;
            }
            h = h->proximo;
        }
        f = f->proximo;
    }
    if (flag==0){
        printf("Não existem pré-reservas do cliente com id %d.\n", id);
        sem_reservas--;
    }
    return sem_reservas;
}

int cancelarReserva(Lista_Dias *d,int id){
    //depois de escolhida a opcao para cancelar e depois de fornecido o id é chamada a funcao listarReservasCliente() para o cliente poder ver todas as suas reservas
    //o cliente tem de introduzir o numero da reserva que pretende cancelar
    /* 1.Se quiser cancelar Manutencao:
        1.1.Se o que estiver em lista de espera for lavagem passamos para reserva. Se o bloco seguinte estiver livre com:
            1.1.1.lavagem em pré-reserva passamos para reserva
            1.1.2.manutencao em pré-reserva vemos se o bloco seguinte esta livre e marcamos reserva
        1.2. Se o que estiver em lista de espera for uma manutencao
            1.2.1. Se a hora de inicio (da que esta em espera) for a mesma e o bloco seguinte estiver livre passamos para reserva
            1.2.2. Se a hora de inicio (da que esta em espera) for igual a hora anterior e a hora anterior estiver livre passamos para reserva
            
    2.Se quiser cancelar Lavagem:
        2.1.Se o que estiver em lista de espera for lavagem passamos para reserva.
        2.2.Se o que estiver em lista de espera for manutencao:
            2.2.1.Se a hora de inicio for igual a hora da que queremos cancelar e o bloco seguinte estiver livre, passar para reserva
            2.2.2.Se a hora de inicio for igual a hora anterior e o bloco anterior estiver livre, passar para reserva
    3.Cancelar pré-reservas:
        3.1.Cancelar pré-lavagem: removemos a pré-reserva e a pré-reserva seguinte (na lista de espera) passa para a frente, fica em primeiro da lista
        3.2.Cancelar pré-manutencao:
            3.2.1.Hora de inicio igual a hora anterior: a pre-reserva seguinte da hora de inicio e a pre-reserva seguinte da hora anterior passam para primeiro  
            3.2.2.Hora de inicio igual a hora seguinte: a pre-reserva seguinte da hora de inicio e a pre-reserva seguinte da hora seguinte passam para primeiro  
    */  
    Lista_Blocos *f = d->inicio;
    Hora *h = f->inicio;
    int numero_reserva;
    if (listarReservasCliente(d,id) == 0) return 0;
    printf("Para cancelar uma reserva ou pré-reserva insira o numero da reserva/pré-reserva: ");
    scanf("%d", &numero_reserva);
    while (f!=NULL){
        h = f->inicio;
        while(h != NULL) {
            if(h->reserva->n_reserva == numero_reserva){
                if (h->reserva->tipo == Manutencao){ //1.
                    h->reserva->id = 0;
                    h->reserva->tipo = 0;
                    h->reserva->n_reserva = 0;
                    h->reserva->estado = 0;
                    h->reserva->inicio = NULL;
                    h->reserva->fim = NULL;

                    h->proximo->reserva->id = 0;
                    h->proximo->reserva->tipo = 0;
                    h->proximo->reserva->n_reserva = 0;
                    h->proximo->reserva->estado = 0;
                    h->proximo->reserva->inicio = NULL;
                    h->proximo->reserva->fim = NULL;

                        if(h->pre_reservas->inicio->pre_reserva->tipo==Lavagem){ //1.1.
                            h->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                            h->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                            h->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                            h->reserva->estado = 2;
                            h->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                            h->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim; 
                            h->pre_reservas->inicio=h->pre_reservas->inicio->proximo;
                            h->proximo->reserva->n_reserva = 0;
                            printf("A sua reserva foi cancelada ");
                            if(h->proximo->pre_reservas->inicio->pre_reserva->tipo==Lavagem){ //1.1.1.
                                h->proximo->reserva->id = h->proximo->pre_reservas->inicio->pre_reserva->id;
                                h->proximo->reserva->tipo = h->proximo->pre_reservas->inicio->pre_reserva->tipo;
                                h->proximo->reserva->n_reserva = h->proximo->pre_reservas->inicio->pre_reserva->n_reserva;
                                h->proximo->reserva->estado = 2;
                                h->proximo->reserva->inicio = h->proximo->pre_reservas->inicio->pre_reserva->inicio;
                                h->proximo->reserva->fim = h->proximo->pre_reservas->inicio->pre_reserva->fim; 
                                h->proximo->pre_reservas->inicio = h->proximo->pre_reservas->inicio->proximo;
                                printf("A sua reserva foi cancelada ");
                            }else{
                                if(h->proximo->proximo->reserva->n_reserva == 0){ //1.1.2.
                                    h->proximo->reserva->id = h->proximo->pre_reservas->inicio->pre_reserva->id;
                                    h->proximo->reserva->tipo = h->proximo->pre_reservas->inicio->pre_reserva->tipo;
                                    h->proximo->reserva->n_reserva = h->proximo->pre_reservas->inicio->pre_reserva->n_reserva;
                                    h->proximo->reserva->estado = 2;
                                    h->proximo->reserva->inicio = h->proximo->pre_reservas->inicio->pre_reserva->inicio;
                                    h->proximo->reserva->fim = h->proximo->pre_reservas->inicio->pre_reserva->fim;
                                    h->proximo->pre_reservas->inicio = h->proximo->proximo->pre_reservas->inicio->proximo; 

                                    h->proximo->proximo->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                                    h->proximo->proximo->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                                    h->proximo->proximo->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                                    h->proximo->proximo->reserva->estado = 2;
                                    h->proximo->proximo->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                                    h->proximo->proximo->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim; 
                                    h->proximo->proximo->pre_reservas->inicio = h->proximo->proximo->pre_reservas->inicio->proximo;
                                    printf("A sua reserva foi cancelada ");
                                }
                            }
                            
                        }else{ //1.2.
                            if(h->pre_reservas->inicio->pre_reserva->inicio == h->reserva->inicio && h->proximo->reserva->n_reserva == 0){ //1.2.1.
                                h->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                                h->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                                h->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                                h->reserva->estado = 2;
                                h->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                                h->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim; 
                                h->pre_reservas->inicio = h->pre_reservas->inicio->proximo;

                                h->proximo->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                                h->proximo->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                                h->proximo->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                                h->proximo->reserva->estado = 2;
                                h->proximo->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                                h->proximo->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim;
                                if(h->proximo->pre_reservas->inicio->pre_reserva->n_reserva!=0){
                                    h->proximo->pre_reservas->inicio = h->proximo->pre_reservas->inicio->proximo;
                                }
                                printf("A sua reserva foi cancelada ");
                            }
                            if(h != f->inicio){
                                if(h->pre_reservas->inicio->pre_reserva->inicio == h->anterior->reserva->inicio && h->anterior->reserva->n_reserva == 0){ //1.2.2.
                                    h->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                                    h->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                                    h->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                                    h->reserva->estado = 2;
                                    h->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                                    h->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim; 
                                    h->pre_reservas->inicio = h->pre_reservas->inicio->proximo;

                                    h->anterior->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                                    h->anterior->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                                    h->anterior->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                                    h->anterior->reserva->estado = 2;
                                    h->anterior->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                                    h->anterior->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim; 
                                    h->anterior->pre_reservas->inicio = h->anterior->pre_reservas->inicio->proximo;
                                    printf("A sua reserva foi cancelada ");
                                }
                            }
                        }
                }else{ //2.

                    h->reserva->id = 0;
                    h->reserva->tipo = 0;
                    h->reserva->n_reserva = 0;
                    h->reserva->estado = 0;
                    h->reserva->inicio = NULL;
                    h->reserva->fim = NULL;

                    if(h->pre_reservas->inicio->pre_reserva->tipo==Lavagem){ //2.1.
                        h->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                        h->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                        h->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                        h->reserva->estado = 2;
                        h->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                        h->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim; 
                        h->pre_reservas->inicio = h->pre_reservas->inicio->proximo;
                        h->proximo->reserva->n_reserva = 0;
                        printf("A sua reserva foi cancelada ");
                    }if(h->pre_reservas->inicio->pre_reserva->tipo==Manutencao){ //2.2.
                        if(h->pre_reservas->inicio->pre_reserva->inicio == h->reserva->inicio && h->proximo->reserva->n_reserva == 0){ //2.2.1.
                            h->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                            h->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                            h->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                            h->reserva->estado = 2;
                            h->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                            h->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim;                                 h->pre_reservas->inicio = h->pre_reservas->inicio->proximo;
                                
                            h->proximo->reserva->id = h->proximo->pre_reservas->inicio->pre_reserva->id;
                            h->proximo->reserva->tipo = h->proximo->pre_reservas->inicio->pre_reserva->tipo;
                            h->proximo->reserva->n_reserva = h->proximo->pre_reservas->inicio->pre_reserva->n_reserva;
                            h->proximo->reserva->estado = 2;
                            h->proximo->reserva->inicio = h->proximo->pre_reservas->inicio->pre_reserva->inicio;
                            h->proximo->reserva->fim = h->proximo->pre_reservas->inicio->pre_reserva->fim; 
                            h->proximo->pre_reservas->inicio = h->proximo->pre_reservas->inicio->proximo;
                            printf("A sua reserva foi cancelada ");
                        }
                        if(h != f->inicio){
                            if(h->pre_reservas->inicio->pre_reserva->inicio == h->anterior->reserva->inicio && h->anterior->reserva->n_reserva == 0){ //2.2.2.
                                h->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                                h->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                                h->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                                h->reserva->estado = 2;
                                h->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                                h->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim; 
                                h->pre_reservas->inicio=h->pre_reservas->inicio->proximo;

                                h->anterior->reserva->id = h->pre_reservas->inicio->pre_reserva->id;
                                h->anterior->reserva->tipo = h->pre_reservas->inicio->pre_reserva->tipo;
                                h->anterior->reserva->n_reserva = h->pre_reservas->inicio->pre_reserva->n_reserva;
                                h->anterior->reserva->estado = 2;
                                h->anterior->reserva->inicio = h->pre_reservas->inicio->pre_reserva->inicio;
                                h->anterior->reserva->fim = h->pre_reservas->inicio->pre_reserva->fim; 
                                h->anterior->pre_reservas->inicio = h->anterior->pre_reservas->inicio->proximo;
                                printf("A sua reserva foi cancelada ");
                            }
                        }
                    }
                }  
            }
            //Pre-reservas

            no *z = h->pre_reservas->inicio;
            while(z != NULL) {
                if(z->pre_reserva->n_reserva == numero_reserva){ //3.
                    if(z->pre_reserva->tipo == Lavagem){ //3.1.
                        h->pre_reservas->inicio = z->proximo;
                        printf("A sua pré-reserva foi cancelada ");
                    }else{ //3.2.
                        h->pre_reservas->inicio = z->proximo;
                        if(z->pre_reserva->inicio == h->proximo->reserva->inicio){ //3.2.2.
                            h->proximo->pre_reservas->inicio = h->proximo->pre_reservas->inicio->proximo;
                        }
                        printf("A sua pré-reserva foi cancelada ");
                    }
                }
                z = z->proximo;
            }
            
            
            h = h->proximo;
        }
        f = f->proximo;
    }
    return 0;
}

int compara_strings(char pedido[20],char horas[20][20]){
    //verifica se a hora introduzida pelo utilizador é igual a alguma dos blocos criados
    for(int i=0; i<=20-1; i++){
        if(strcmp(pedido, horas[i])==0) return 0;
    }
    return 1;
}

Lista_Blocos * procura_data(Lista_Dias *d, Data data, char horas[20][20]){
    //procura uma data e devolve-a. se não existir devolve uma nova que adiciona
    Lista_Blocos *f = d->inicio;
    while(f != NULL) {
        if(f->data.dia == data.dia && f->data.mes == data.mes && f->data.ano == data.ano){
            return f;
        }
        f = f->proximo;
    }
    return adiciona_data(d, horas, data);
}

int marcar_reserva(Lista_Dias *d, char pedido[20], Reserva reserva, int tipo, int *n_reserva, int id, char horas[20][20], Data data) {
    //cria uma reserva se o horario estiver livre ou entao cria uma pre-reserva para esse horario
    Lista_Blocos *f = procura_data(d, data, horas);
    Hora *h = f->inicio;
    while (h != NULL) {
        if (strcmp(h->hora, pedido) == 0) {
            if (tipo == Manutencao) {
                if(h->reserva->n_reserva==0 && h->proximo->reserva->n_reserva==0){
                    h->reserva->id = id;
                    h->reserva->tipo = reserva.tipo;
                    h->reserva->n_reserva = *(n_reserva);
                    h->reserva->estado = 2;
                    h->reserva->inicio = h;
                    h->reserva->fim = h->proximo;
                    h->proximo->reserva->id = id;
                    h->proximo->reserva->tipo = reserva.tipo;
                    h->proximo->reserva->n_reserva = *(n_reserva);
                    h->proximo->reserva->estado = 2;
                    h->proximo->reserva->inicio = h;
                    h->proximo->reserva->fim = h->proximo;
                    printf("A sua reserva foi feita com sucesso \n");
                    *(n_reserva) += 1;
                } else {
                    if (h->pre_reservas->inicio->pre_reserva->n_reserva == 0) {
                        h->pre_reservas->fim->pre_reserva = h->pre_reservas->inicio->pre_reserva;
                        h->pre_reservas->inicio->proximo = h->pre_reservas->fim;
                        h->pre_reservas->fim->proximo = NULL;
                        h->pre_reservas->inicio->pre_reserva->tipo = reserva.tipo;
                        h->pre_reservas->inicio->pre_reserva->n_reserva = *(n_reserva);
                        h->pre_reservas->inicio->pre_reserva->estado = 1;
                        h->pre_reservas->inicio->pre_reserva->id = id;
                        h->pre_reservas->inicio->pre_reserva->inicio = h;
                        h->pre_reservas->inicio->pre_reserva->fim = h->proximo;
                        h->proximo->pre_reservas->inicio->pre_reserva->tipo = reserva.tipo;
                        h->proximo->pre_reservas->inicio->pre_reserva->n_reserva = *(n_reserva);
                        h->proximo->pre_reservas->inicio->pre_reserva->estado = 1;
                        h->proximo->pre_reservas->inicio->pre_reserva->id = id;
                        h->proximo->pre_reservas->inicio->pre_reserva->inicio = h;
                        h->proximo->pre_reservas->inicio->pre_reserva->fim = h->proximo;
                        *(n_reserva) += 1;
                    } else {
                        no *novo = (no *)malloc(sizeof(no));
                        novo->pre_reserva = (Reserva *)malloc(sizeof(Reserva));
                        novo->proximo = (no *)malloc(sizeof(no));
                        novo->proximo->pre_reserva = (Reserva *)malloc(sizeof(Reserva));
                        novo->pre_reserva->tipo = reserva.tipo;
                        novo->pre_reserva->n_reserva = *(n_reserva);
                        novo->pre_reserva->estado = 1;
                        novo->pre_reserva->id = id;
                        novo->pre_reserva->inicio = h;
                        novo->pre_reserva->fim = h->proximo;
                        novo->proximo->pre_reserva->tipo = reserva.tipo;
                        novo->proximo->pre_reserva->n_reserva = *(n_reserva);
                        novo->proximo->pre_reserva->estado = 1;
                        novo->proximo->pre_reserva->id = id;
                        novo->proximo->pre_reserva->inicio = h;
                        novo->proximo->pre_reserva->fim = h->proximo;
                        h->pre_reservas->fim->proximo = novo;
                        h->pre_reservas->fim = novo->proximo;
                        *(n_reserva) += 1;
                    }
                    printf("A sua reserva foi colocada em lista de espera \n");
                }
            } else {
                if (h->reserva->n_reserva == 0) {
                    h->reserva->id = id;
                    h->reserva->tipo = reserva.tipo;
                    h->reserva->n_reserva = *(n_reserva);
                    h->reserva->estado = 2;
                    h->reserva->inicio = h;
                    h->reserva->fim = h->reserva->inicio;
                    printf("A sua reserva foi feita com sucesso \n");
                    *(n_reserva) += 1;
                }else{
                    if (h->pre_reservas->inicio->pre_reserva->n_reserva == 0) {
                        h->pre_reservas->fim->pre_reserva = h->pre_reservas->inicio->pre_reserva;
                        h->pre_reservas->inicio->proximo = h->pre_reservas->fim;
                        h->pre_reservas->fim->proximo = NULL;
                        h->pre_reservas->inicio->pre_reserva->tipo = reserva.tipo;
                        h->pre_reservas->inicio->pre_reserva->n_reserva = *(n_reserva);
                        h->pre_reservas->inicio->pre_reserva->estado = 1;
                        h->pre_reservas->inicio->pre_reserva->id = id;
                        h->pre_reservas->inicio->pre_reserva->inicio = h;
                        h->pre_reservas->inicio->pre_reserva->inicio = h;
                        *(n_reserva) += 1;
                    } else {
                        no *novo = (no *)malloc(sizeof(no));
                        novo->pre_reserva = (Reserva *)malloc(sizeof(Reserva));
                        novo->proximo = NULL;
                        novo->pre_reserva->tipo = reserva.tipo;
                        novo->pre_reserva->n_reserva = *(n_reserva);
                        novo->pre_reserva->estado = 1;
                        novo->pre_reserva->id = id;
                        novo->pre_reserva->inicio = h;
                        novo->pre_reserva->fim = novo->pre_reserva->inicio;
                        h->pre_reservas->fim->proximo = novo;
                        h->pre_reservas->fim = novo;
                        *(n_reserva) += 1;
                    }
                    printf("A sua reserva foi colocada em lista de espera \n");
                }
            }
            return 1;
        }
        h = h->proximo;
    }
    printf("Hora não encontrada \n");
    return 0;
}

int guarda_no_ficheiro_reservas(Lista_Dias *d){
    //escreve as informacoes das reservas num ficheiro, em vez de ser tudo referente a uma reserva numa linha, escreve cada informacao numa linha formando um bloco
    // reescrevemos o ficheiro todo quando se fecha o programa
    FILE *ficheiro_reservas = fopen("reservas.txt", "w");

    Lista_Blocos *f = d->inicio;
    Hora *h = f->inicio;
    while (f!=NULL){
        h = f->inicio;
        while (h!=NULL){
            if (h->reserva->tipo==1){
                if(h->reserva->n_reserva!=0){
                    fprintf(ficheiro_reservas, "\n");
                    fprintf(ficheiro_reservas, "%4d\n", h->reserva->n_reserva);
                    fprintf(ficheiro_reservas, "%4d\n", h->reserva->id);
                    fprintf(ficheiro_reservas, "%2d\n", h->reserva->tipo);
                    fprintf(ficheiro_reservas, "%2d\n", f->data.dia);
                    fprintf(ficheiro_reservas, "%2d\n", f->data.mes);
                    fprintf(ficheiro_reservas, "%4d\n", f->data.ano);
                    fprintf(ficheiro_reservas, "%5s" , h->reserva->inicio->hora);
                }
            }
            if (h->reserva->tipo==2){
                if(h->reserva->n_reserva!=0 && h->reserva->n_reserva!=h->proximo->reserva->n_reserva){
                    fprintf(ficheiro_reservas, "\n");
                    fprintf(ficheiro_reservas, "%4d\n", h->reserva->n_reserva);
                    fprintf(ficheiro_reservas, "%4d\n", h->reserva->id);
                    fprintf(ficheiro_reservas, "%2d\n", h->reserva->tipo);
                    fprintf(ficheiro_reservas, "%2d\n", f->data.dia);
                    fprintf(ficheiro_reservas, "%2d\n", f->data.mes);
                    fprintf(ficheiro_reservas, "%4d\n", f->data.ano);
                    fprintf(ficheiro_reservas, "%5s" , h->reserva->inicio->hora);
                }
            }
            h = h->proximo;
        }
        f = f->proximo;
    }
    fclose(ficheiro_reservas);
    return 0;
}

int guarda_no_ficheiro_pre_reservas(Lista_Dias *d){
    //escreve as informacoes das pré-reservas num ficheiro, em vez de ser tudo referente a uma pré-reserva numa linha, escreve cada informacao numa linha formando um bloco
    // reescrevemos o ficheiro todo quando se fecha o programa
    FILE *ficheiro_pre_reservas = fopen("pre_reservas.txt", "w");

    Lista_Blocos *f = d->inicio;
    Hora *h = f->inicio;
    while (f!=NULL){
        h = f->inicio;
        while (h != NULL) {
            no *n = h->pre_reservas->inicio;
            while (n != NULL) {
                if (n->pre_reserva != NULL) {
                    if (n->pre_reserva->estado == 1) {
                        if (n->pre_reserva->tipo == Lavagem) {
                            fprintf(ficheiro_pre_reservas, "\n");
                            fprintf(ficheiro_pre_reservas, "%4d\n", n->pre_reserva->n_reserva);
                            fprintf(ficheiro_pre_reservas, "%4d\n", n->pre_reserva->id);
                            fprintf(ficheiro_pre_reservas, "%2d\n", n->pre_reserva->tipo);
                            fprintf(ficheiro_pre_reservas, "%2d\n", f->data.dia);
                            fprintf(ficheiro_pre_reservas, "%2d\n", f->data.mes);
                            fprintf(ficheiro_pre_reservas, "%4d\n", f->data.ano);
                            fprintf(ficheiro_pre_reservas, "%5s" , n->pre_reserva->inicio->hora);
                        } else if (n->pre_reserva->tipo == Manutencao) {
                            if(n->pre_reserva->n_reserva != h->proximo->pre_reservas->inicio->pre_reserva->n_reserva){
                                fprintf(ficheiro_pre_reservas, "\n");
                                fprintf(ficheiro_pre_reservas, "%4d\n", n->pre_reserva->n_reserva);
                                fprintf(ficheiro_pre_reservas, "%4d\n", n->pre_reserva->id);
                                fprintf(ficheiro_pre_reservas, "%2d\n", n->pre_reserva->tipo);
                                fprintf(ficheiro_pre_reservas, "%2d\n", f->data.dia);
                                fprintf(ficheiro_pre_reservas, "%2d\n", f->data.mes);
                                fprintf(ficheiro_pre_reservas, "%4d\n", f->data.ano);
                                fprintf(ficheiro_pre_reservas, "%5s" , n->pre_reserva->inicio->hora);
                            }
                        }
                    }
                }
                n = n->proximo;
            }
            h = h->proximo;
        }
        f = f->proximo;
    }

    fclose(ficheiro_pre_reservas);
    return 0;
}

int guarda_no_ficheiro_variaveis(Data data,int *variavel_id, int *n_reserva){
    //escreve as informacoes de variaveis de controlo num ficheiro, escreve cada variavel numa linha 
    // reescrevemos o ficheiro todo quando se fecha o programa
    FILE *ficheiro_variaveis = fopen("variaveis.txt", "w");
    if (ficheiro_variaveis==NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DAS RESERVAS\n");
        return 1;
    }

    fprintf(ficheiro_variaveis, "%d\n", *(variavel_id));
    fprintf(ficheiro_variaveis, "%d\n", *(n_reserva));
    fprintf(ficheiro_variaveis, "%02d\n", data.dia);
    fprintf(ficheiro_variaveis, "%02d\n", data.mes);
    fprintf(ficheiro_variaveis, "%04d\n", data.ano);

    
    fclose(ficheiro_variaveis);
    return 0;
}

Data *le_ficheiro_variaveis(Data *data, int *variavel_id, int *n_reserva){
    //lê o ficheiro das variaveis (ultimo_id gerado, ultimo numero de reserva gerado, data do dia atual)
    FILE *ficheiro_variaveis = fopen("variaveis.txt", "r");
    if (ficheiro_variaveis==NULL) {
        ficheiro_variaveis = fopen("variaveis.txt", "w");
        return data;
    }
    fscanf(ficheiro_variaveis, "%02d", variavel_id);
    fscanf(ficheiro_variaveis, "%02d", n_reserva);
    fscanf(ficheiro_variaveis, "%02d", &data->dia);
    fscanf(ficheiro_variaveis, "%02d", &data->mes);
    fscanf(ficheiro_variaveis, "%04d", &data->ano);
    
    (*variavel_id)++;
    (*n_reserva)++;

    fclose(ficheiro_variaveis);
    return data;
}

int le_ficheiro_reservas(Lista_Dias *d, char horas[20][20]){
    //lê as informações sobre as reservas contidas no ficheiro
    FILE *ficheiro_reservas = fopen("reservas.txt", "r");
    if (ficheiro_reservas==NULL) {
        ficheiro_reservas = fopen("reservas.txt", "w");
        return 1;
    }
    char LINHA[100];
    while (fgets(LINHA, sizeof(LINHA), ficheiro_reservas) != NULL){ 
        Reserva reserva;
        int numero_reserva, ID;
        Data data;
        char hora_inicio[20];
        fscanf(ficheiro_reservas, "%04d", &numero_reserva);
        fscanf(ficheiro_reservas, "%04d", &ID);
        fscanf(ficheiro_reservas, "%02d", &reserva.tipo);
        fscanf(ficheiro_reservas, "%2d", &data.dia);
        fscanf(ficheiro_reservas, "%2d", &data.mes);
        fscanf(ficheiro_reservas, "%4d", &data.ano);
        fscanf(ficheiro_reservas, "%19s" , hora_inicio);
        procura_data(d, data, horas);

        marcar_reserva(d, hora_inicio, reserva, reserva.tipo, &numero_reserva, ID, horas, data);
    }
    fclose(ficheiro_reservas);
    return 0;
}

int le_ficheiro_pre_reservas(Lista_Dias *d, char horas[20][20]){
    //lê as informacoes sobre as pré-reservas contidas no ficheiro
    FILE *ficheiro_pre_reservas = fopen("pre_reservas.txt", "r");
    if (ficheiro_pre_reservas==NULL) {
        ficheiro_pre_reservas = fopen("pre_reservas.txt", "w");
        return 1;
    }
    char LINHA[100];
    while (fgets(LINHA, sizeof(LINHA), ficheiro_pre_reservas) != NULL){ 
        Reserva reserva;
        int numero_reserva, ID;
        char hora_inicio[20];
        Data data;
        fscanf(ficheiro_pre_reservas, "%04d", &numero_reserva);
        fscanf(ficheiro_pre_reservas, "%04d", &ID);
        fscanf(ficheiro_pre_reservas, "%02d", &reserva.tipo);
        fscanf(ficheiro_pre_reservas, "%2d", &data.dia);
        fscanf(ficheiro_pre_reservas, "%2d", &data.mes);
        fscanf(ficheiro_pre_reservas, "%4d", &data.ano);
        fscanf(ficheiro_pre_reservas, "%19s" , hora_inicio);
        procura_data(d, data, horas);
        marcar_reserva(d, hora_inicio, reserva, reserva.tipo, &numero_reserva, ID, horas, data);
    } 

    fclose(ficheiro_pre_reservas);
    return 0;
}

void libertar_memoria(Lista_Dias *d){
    //liberta a memoria alocada
    Lista_Blocos *f = d->inicio;
    Hora *h = f->inicio;
    while (f->proximo != NULL){
        Lista_Blocos *aux = f->proximo;
        h = f->inicio;
        while(h != NULL) {

            Hora *prox = h->proximo;
            free(h->reserva);
            free(h->pre_reservas->inicio->pre_reserva);
            free(h->pre_reservas->inicio->proximo);
            free(h->pre_reservas->inicio);
            free(h->pre_reservas);
            free(h);
            h = prox; 
        }
        
        free(f);
        f = aux;
    }
    
}

int menu(Lista_Dias *d,char horas[20][20],int *variavel_id, int *n_reserva, Data *data1){
    //cria o menu e recolhe os inputs do utilizador, chamando diferentes funcoes consoante o input
    Reserva reserva;
    int escolha;
    int id;
    char res;
    printf("\n\nMenu:\n");
    printf("1. Listar reservas\n");
    printf("2. Listar reservas de um cliente\n");
    printf("3. Cancelar uma reserva\n");
    printf("4. Fazer uma reserva\n");
    printf("5. Avançar um dia\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);
    switch (escolha) {
        case 1:
            listarReservas(d);
            break;
        case 2:
            printf("Digite o ID do cliente: ");
            char buffer[100];
            int count=0;
            while (fgets(buffer, sizeof(buffer), stdin)) {
                if (sscanf(buffer, "%d", &id) == 1 && id > 0 && id <= *variavel_id) {
                    break;
                }
                
                if(count>0){
                    printf("Erro: o valor inserido não é um número inteiro válido ou não existe.\n");
                    printf("Digite o ID do cliente: ");
                }
                count++;
            }
            listarReservasCliente(d,id);
            break;
        case 3:
            printf("Digite o ID do cliente: ");
            count=0;
            while (fgets(buffer, sizeof(buffer), stdin)) {
                if (sscanf(buffer, "%d", &id) == 1 && id > 0 && id <= *variavel_id) {
                    break;
                }
                
                if(count>0){
                    printf("Erro: o valor inserido não é um número inteiro válido ou não existe.\n");
                    printf("Digite o ID do cliente: ");
                }
                count++;
            }
            cancelarReserva(d,id);
            break;
        case 4:
            printf("Tem id (S/N): ");
            scanf(" %c", &res);
            while (res != 'S' && res != 's' && res != 'N' && res != 'n') {
                printf("Operação indisponível. Tem id (S/N): ");
                scanf(" %c", &res);
            }
            printf("\n");            
            if(res=='S' || res=='s' ){
                printf("Digite o seu id: ");
                count=0;
                while (fgets(buffer, sizeof(buffer), stdin)) {
                    if (sscanf(buffer, "%d", &id) == 1 && id > 0 && id <= *variavel_id) {
                        break;
                    }
                    
                    if(count>0){
                        printf("Erro: o valor inserido não é um número inteiro válido ou não existe.\n");
                        printf("Digite o ID do cliente: ");
                    }
                    count++;
                }
            }
            else if(res=='N' || res=='n'){
                id = *(variavel_id);
                *(variavel_id) += 1;
                printf("O seu id é : %d\n", id);
            }
            printf("Digite o tipo de serviço (1 para lavagem, 2 para manutenção): ");
            scanf("%d", &reserva.tipo);
            while((reserva.tipo!=1&&reserva.tipo!=2)||reserva.tipo==0){
                if(reserva.tipo==0){
                    return 0;
                }
                printf("Operação indisponível, se quiser cancelar insira 0. Insira 1 para Lavagem e 2 para Manutenção: ");
                scanf("%d",&reserva.tipo);
            }
            Data data;
            printf("Digite a data da reserva (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
            while(compara_datas(*data1,data)==1){
                printf("Insira uma data válida, posterior à atual (%d/%d/%d): ", data1->dia, data1->mes, data1->ano);
                scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
            }
            procura_data(d, data, horas);
            imprime_lista(d, horas, reserva.tipo, data);
            int existe = 1;
            char pedido[20];
            while(existe == 1 || existe == -1){
                printf("Escolha um dos horários de início que estão livres. Escreva só o horário de início na forma apresentada: ");
                scanf("%19s",pedido);
                existe = compara_strings(pedido,horas);
            }
            marcar_reserva(d, pedido, reserva, reserva.tipo, n_reserva, id, horas, data);
            break;
        case 5:
            //avancamos um dia eliminado as reservas e pre-reservas anteriores ao novo dia
            avanca_data(data1, d, horas);
            data1 = &(d->inicio->proximo->data);
            d->inicio = d->inicio->proximo;

            Lista_Blocos *f = d->inicio->anterior;
            Hora *h = f->inicio;
            while(h != NULL) {
                Hora *prox = h->proximo;
                free(h->reserva);
                free(h->pre_reservas->inicio->pre_reserva);
                free(h->pre_reservas->inicio->proximo);
                free(h->pre_reservas->inicio);
                free(h->pre_reservas);
                free(h);
                h = prox; 
            }
            free(f);
            d->inicio->anterior = NULL;
            break;
        case 6:
            //sempre que se guarda o programa reescrevemos os ficheiros com as novas informacoes
            printf("Encerrando programa.\n");
            guarda_no_ficheiro_reservas(d);
            guarda_no_ficheiro_pre_reservas(d);
            guarda_no_ficheiro_variaveis(*data1,variavel_id,n_reserva);
            libertar_memoria(d);
            free(variavel_id);
            free(n_reserva);
            exit(0);
        default:
            printf("Opção inválida.\n");
            break;
    }
    return 1;
}

int main(){
    /*define os blocos de horas
    define a primeira data do programa
    le os ficheiros
    cria variaveis de controlo
    aloca memoria
    */
    char horas[21][20] = {
        "08:00",
        "08:30",
        "09:00",
        "09:30",
        "10:00",
        "10:30",
        "11:00",
        "11:30",
        "12:00",
        "12:30",
        "13:00",
        "13:30",
        "14:00",
        "14:30",
        "15:00",
        "15:30",
        "16:00",
        "16:30",
        "17:00",
        "17:30",
        "18:00"
    };
    int resposta=1;
    int *variavel_id = malloc(sizeof(int));
    *variavel_id = 1;
    int *n_reserva = malloc(sizeof(int));
    *n_reserva = 1;
    Data *data = (Data * ) malloc(sizeof(Data));
    data->dia = 01;
    data->mes = 06;
    data->ano = 2023;
    data = le_ficheiro_variaveis(data,variavel_id,n_reserva);
    Lista_Dias d = cria_lista_datas(horas, *data);
    printf("\n");
    printf("Bem vindo à oficina do Carlos. \n");
    le_ficheiro_reservas(&d,horas);
    le_ficheiro_pre_reservas(&d,horas);
    while(resposta==1){
        resposta = menu(&d, horas, variavel_id, n_reserva, data);
    }
    
    return 0;
}