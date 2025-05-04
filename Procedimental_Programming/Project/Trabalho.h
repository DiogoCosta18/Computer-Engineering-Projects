#ifndef Estruturas_H
#define Estruturas_H

#define Lavagem 1
#define Manutencao 2

typedef struct Hora Hora;
typedef struct Reserva Reserva;

typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

struct Reserva{
    int id;
    int n_reserva;
    int tipo; //Lavagem=1, Manutenção=2
    int estado; //Pré reserva=1, Reserva=2
    Data data;
    Hora *inicio;
    Hora *fim;
};

typedef struct no{
    Reserva *pre_reserva;
    struct no *proximo;
}no;

typedef struct{
    no *inicio;
    no *fim;
}lista;

struct Hora{
    char hora[20];
    Reserva *reserva;
    lista *pre_reservas;
    struct Hora *proximo;
    struct Hora *anterior;
};

typedef struct Lista_Blocos{
    Hora *inicio;
    Hora *fim;
    Data data;
    struct Lista_Blocos *proximo;
    struct Lista_Blocos *anterior;
}Lista_Blocos;

typedef struct{
    Lista_Blocos *inicio;
    Lista_Blocos *fim;
}Lista_Dias;


typedef struct {
    int id;
    Reserva reservas;
} Cliente;

#endif