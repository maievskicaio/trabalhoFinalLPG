#include "data.h"
#include "horario.h"

struct Evento{
    struct Data data;
    struct Horario horarioInicio, horarioFim;
    char descricao[100];
    char local[100];
};

struct Evento criaEvento();
int conflitoEvento(struct Evento e1, struct Evento e2);

// 0 - Sem Conflito | 1 - Com conflito
int conflitoEvento(struct Evento e1, struct Evento e2){
    if(comparaData(e1.data, e2.data) != 0)
        return 0;
    if((comparaHorario(e1.horarioFim, e2.horarioInicio) == -1))
        return 0;
    if((comparaHorario(e2.horarioFim, e1.horarioInicio) == -1))
        return 0;
    return 1;
}

struct Evento criaEvento(){
    struct Evento evento;
    evento.data = criaData();
    printf("Inicio: \n");
    evento.horarioInicio = criaHorario();
    do { // Garante que o horário de fim será após o de inicio.
        printf("Fim: \n");
        evento.horarioFim = criaHorario();
        if(comparaHorario(evento.horarioInicio, evento.horarioFim) != (-1))
            printf("* ERRO: Horario de fim deve ser apos o horario de inicio.\n");
    } while (comparaHorario(evento.horarioInicio, evento.horarioFim) != (-1));

    printf("Descricao: ");
    scanf(" %[^\n]", evento.descricao);
    printf("Local: ");
    scanf(" %[^\n]", evento.local);
    return evento;
}

