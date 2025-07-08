#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evento.h"

void descarregaAgenda(FILE *arquivo, struct Evento *agenda);
void mostraAgenda(struct Evento *agenda, int numEventos);
void mostraEvento(struct Evento evento);
void mostraAgendaPorData(struct Evento *agenda, int numEventos, struct Data data);
void mostraAgendaPorDescricao(struct Evento *agenda, int numEventos, char descricao[100]);
int validaEventoAgenda(struct Evento *agenda, int numEventos, struct Evento novoEvento);
int indiceParaIserir(struct Evento *agenda, int numEventos, struct Evento novoEvento);
void insereNaAgendaPorIndice(struct Evento *agenda, int numEventos, struct Evento novoEvento, int indice);
void carregaAgenda(FILE *arquivo, struct Evento *agenda, int numEventos);
int confereData(struct Evento *agenda, int numEventos, struct Data eData);
int confereHorario(struct Evento *agenda, int numEventos, struct Horario eHorario);
void removeEvento(struct Evento *agenda, int numEventos, struct Data eData, struct Horario eHorario);

int main(){
    int numEventos;
    FILE *arquivo = fopen("agenda.txt", "r");
    if(arquivo == NULL){
        FILE *arquivo = fopen("agenda.txt", "wt");
        numEventos = 0;
        fprintf(arquivo, "%d\n", numEventos);
    } else {
        FILE *arquivo = fopen("agenda.txt", "r");
        fscanf(arquivo, "%d", &numEventos);
    }
    
    struct Evento *agenda = malloc(sizeof(struct Evento) * numEventos);
    descarregaAgenda(arquivo, agenda);
    fclose(arquivo);

    struct Data eData;
    struct Horario eHorario;
    int escolha = 0;
    while(escolha != 6){
        arquivo = fopen("agenda.txt", "wt");
        carregaAgenda(arquivo, agenda, numEventos);
        fclose(arquivo);
        
        puts("---------------------");
        printf("[ 1 ] CADASTRAR NOVO evento na agenda.\n[ 2 ] MOSTRAR TODOS eventos da agenda.\n");
        printf("[ 3 ] MOSTRAR eventos da DATA.\n[ 4 ] MOSTRAR eventos com a DESCRICAO.\n");
        printf("[ 5 ] REMOVER evento da agenda.\n[ 6 ] SAIR do programa.\n> ");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            printf(""); // sem isso estava dando o erro: "a label can only be part of a statement and a declaration is not a statement"
            struct Evento novoEvento = criaEvento();
            if(validaEventoAgenda(agenda, numEventos, novoEvento) == 1) {
                printf("* ERRO: O NOVO evento tem conflito com evento JA EXISTENTE.\n");
                break;
            }
            int indice = indiceParaIserir(agenda, numEventos, novoEvento);
            numEventos++;
            agenda = realloc(agenda, sizeof(struct Evento) * numEventos);
            insereNaAgendaPorIndice(agenda, numEventos, novoEvento, indice);
            printf("* NOVO EVENTO ADICIONADO.\n");
            break;
        case 2:
            mostraAgenda(agenda, numEventos);
            break;
        case 3:
            printf("Insira a data para buscar: \n");
            eData = criaData();
            mostraAgendaPorData(agenda, numEventos, eData);
            break;
        case 4:
            printf("Insira a descricao para buscar: \n");
            char eDescricao[100];
            scanf(" %[^\n]", eDescricao);
            mostraAgendaPorDescricao(agenda, numEventos, eDescricao);
            break;
        case 5:
            printf("Informacoes do Evento que quer remover:\n");
            printf("Data:\n");
            eData = criaData();
            if(confereData(agenda, numEventos, eData) == 1){
                printf("* ERRO: Data nao encontrada.\n");
                break;
            }
            printf("Horario Inicial:\n");
            eHorario = criaHorario();
            if(confereHorario(agenda, numEventos, eHorario) == 1){
                printf("* ERRO: Horario nao encontrado.\n");
                break;
            }
            removeEvento(agenda, numEventos, eData, eHorario);
            numEventos--;
            agenda = realloc(agenda, sizeof(struct Evento) * numEventos);
            break;
        }
    }

    free(agenda);
}


void removeEvento(struct Evento *agenda, int numEventos, struct Data eData, struct Horario eHorario){
    int indice;
    for(int i = 0; i < numEventos; i++){
        if(comparaData(agenda[i].data, eData) == 0) {
            if(comparaHorario(agenda[i].horarioInicio, eHorario) == 0);
            indice = i;
            break;
        }
    }
    for(int i = 0; i < (numEventos-1); i++){
        if(i < indice)
            continue;
        agenda[i] = agenda[i+1];
    }
}

// 0 - Horario existe na agenda. | 1 - Horario não existe na agenda.
int confereHorario(struct Evento *agenda, int numEventos, struct Horario eHorario){
    for(int i = 0; i < numEventos; i++){
        if(comparaHorario(agenda[i].horarioInicio, eHorario) == 0)
            return 0;
    }
    return 1;
}

// 0 - Data existe na agenda. | 1 - Data não existe na agenda.
int confereData(struct Evento *agenda, int numEventos, struct Data eData) {
    for(int i = 0; i < numEventos; i++){
        if(comparaData(agenda[i].data, eData) == 0)
            return 0;
    }
    return 1;
}

void carregaAgenda(FILE *arquivo, struct Evento *agenda, int numEventos){
    fprintf(arquivo, "%d\n", numEventos);
    for(int i = 0; i < numEventos; i++){
        fprintf(arquivo, "%d %d %d\n", agenda[i].data.dia, agenda[i].data.mes, agenda[i].data.ano);
        fprintf(arquivo, "%d %d\n", agenda[i].horarioInicio.hora, agenda[i].horarioInicio.minuto);
        fprintf(arquivo, "%d %d\n", agenda[i].horarioFim.hora, agenda[i].horarioFim.minuto);
        fprintf(arquivo, "%s\n", agenda[i].descricao);
        fprintf(arquivo, "%s\n", agenda[i].local);
    }
}

void insereNaAgendaPorIndice(struct Evento *agenda, int numEventos, struct Evento novoEvento, int indice){
    struct Evento eventoTemp;
    for(int i = 0; i < numEventos; i++){
        if(i < indice)
            continue;
            eventoTemp = agenda[i];
            agenda[i] = novoEvento;
            novoEvento = eventoTemp;
    }
}

int indiceParaIserir(struct Evento *agenda, int numEventos, struct Evento novoEvento){
    int i = 0;
    for(i ; i < numEventos; i++){
        if(comparaData(agenda[i].data, novoEvento.data) == 1)
            return i;
        if(comparaData(agenda[i].data, novoEvento.data) == 0) {
            if(comparaHorario(agenda[i].horarioInicio, novoEvento.horarioInicio) == 1)
                return i;
        }
    }
    return i;
}


// 0 - Sem Conflito na agenda | 1 - Com conflito na agenda
int validaEventoAgenda(struct Evento *agenda, int numEventos, struct Evento novoEvento){
    for(int i = 0; i < numEventos; i++){
        if(conflitoEvento(agenda[i], novoEvento) == 1)
            return 1;
    }
    return 0;
}

void mostraAgendaPorDescricao(struct Evento *agenda, int numEventos, char descricao[100]){
    int encontrados = 0;
    printf("Mostrando eventos de: %s\n", descricao);
    for(int i = 0; i < numEventos; i++){ 
        if(strstr(agenda[i].descricao, descricao) != NULL) {
            mostraEvento(agenda[i]);
            encontrados++;
        }
    }
    if(encontrados == 0)
        printf("* ERRO: Lista de eventos vazia.\n");
}

void mostraAgendaPorData(struct Evento *agenda, int numEventos, struct Data data){
    int encontrados = 0;
    printf("Mostrando eventos de: ");
    mostraData(data);
    for(int i = 0; i < numEventos; i++){ 
        if(agenda[i].data.dia == data.dia && agenda[i].data.mes == data.mes && agenda[i].data.ano == data.ano) {
            mostraEvento(agenda[i]);
            encontrados++;
        }
    }
    if(encontrados == 0)
        printf("* Lista de eventos vazia.\n");
}

void mostraEvento(struct Evento evento) {
    puts("---------------------");
    printf("Data: ");
    mostraData(evento.data);
        
    printf("Inicio: ");
    mostraHorario(evento.horarioInicio);
        
    printf("Fim:    ");
    mostraHorario(evento.horarioFim);
        
    printf("Descricao: %s\n", evento.descricao);
        
    printf("Local: %s\n", evento.local);
}

void mostraAgenda(struct Evento *agenda, int numEventos){
    for(int i = 0; i < numEventos; i++){
        mostraEvento(agenda[i]);
    }
}

void descarregaAgenda(FILE *arquivo, struct Evento *agenda){
    int numEventos = 0;
    fscanf(arquivo, "%d", &numEventos);

    for(int i = 0; i < numEventos; i++) {

        fscanf(arquivo, "%d", &agenda[i].data.dia);
        fscanf(arquivo, "%d", &agenda[i].data.mes);
        fscanf(arquivo, "%d", &agenda[i].data.ano);
        
        fscanf(arquivo, "%d", &agenda[i].horarioInicio.hora);
        fscanf(arquivo, "%d", &agenda[i].horarioInicio.minuto);
        
        fscanf(arquivo, "%d", &agenda[i].horarioFim.hora);
        fscanf(arquivo, "%d", &agenda[i].horarioFim.minuto);
        
        fscanf(arquivo, " %[^\n]", agenda[i].descricao);
        
        fscanf(arquivo, " %[^\n]", agenda[i].local);

    }
}

