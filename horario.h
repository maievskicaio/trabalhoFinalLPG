struct Horario{
    int hora, minuto;
};

void mostraHorario(struct Horario horario);
struct Horario criaHorario();
int comparaHorario(struct Horario h1, struct Horario h2);


// (h1 < h2) = -1 | (h1 > h2) = 1 | (h1 = h2) = 0
// ( < ) - Mais cedo que. | ( > ) - Mais tarde que.
int comparaHorario(struct Horario h1, struct Horario h2){
    if (h1.hora < h2.hora)
        return -1;
    if(h1.hora > h2.hora)
        return 1;
    if(h1.minuto < h2.minuto)
        return -1;
    if(h1.minuto > h2.minuto)
        return 1;
    return 0;
}

struct Horario criaHorario(){
    struct Horario horario;
    do {
        printf("Hora: ");
        scanf("%d", &horario.hora);
    } while ((horario.hora < 0) || (horario.hora > 23));
    do {
        printf("Minutos: ");
        scanf("%d", &horario.minuto);
    } while (horario.minuto < 0 || horario.minuto > 59);
    return horario;
}

void mostraHorario(struct Horario horario){
    if(horario.hora < 10) {
        printf("0%d", horario.hora);
    } else {
        printf("%d", horario.hora);
    }
    printf(":");
    if(horario.minuto < 10) {
        printf("0%d", horario.minuto);
    } else {
        printf("%d", horario.minuto);
    }
    printf("\n");
}