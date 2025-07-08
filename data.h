struct Data{
    int dia, mes, ano;
};

void mostraData(struct Data data);
struct Data criaData();
int comparaData(struct Data d1, struct Data d2);

// (h1 < h2) = -1 | (h1 > h2) = 1 | (h1 = h2) = 0
// ( < ) - Mais cedo que | ( > ) - Mais tarde que
int comparaData(struct Data d1, struct Data d2){
    if(d1.ano < d2.ano)
        return -1;
    if(d1.ano > d2.ano)
        return 1;
    if(d1.mes < d2.mes)
        return -1;
    if(d1.mes > d2.mes)
        return 1;
    if(d1.dia < d2.dia)
        return -1;
    if(d1.dia > d2.dia)
        return 1;
    return 0;
}

struct Data criaData(){
    struct Data data;
    do {
        printf("Dia: ");
        scanf("%d", &data.dia);
    } while ((data.dia < 0) || (data.dia > 31));
    do {
        printf("Mes: ");
        scanf("%d", &data.mes);
    } while (data.mes < 0 || data.mes > 12);
    do {
        printf("Ano: ");
        scanf("%d", &data.ano);
    } while (data.ano < 0 || data.mes > 3000);
    return data;
}

void mostraData(struct Data data){
    if(data.dia < 10) {
        printf("0%d", data.dia);
    } else {
        printf("%d", data.dia);
    }
    printf("/");
    if(data.mes < 10) {
        printf("0%d", data.mes);
    } else {
        printf("%d", data.mes);
    }
    printf("/%d\n", data.ano);
}

