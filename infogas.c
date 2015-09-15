#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*Sugiro que afim de primeiro programa deixe a declaração de variáveis a ser livre pelo programa,
 e em suas versões va organizando as variasveis antes, declarando de forma global, e deixar local o que puder.*/
//=========================================GRUPO 3============================================================
//ver:1.0


int main()
{
    printf("Programa referencial para abastecimento:");
    printf("\nObs: o tempo do programa deve entrar em forma de\n HH:MM no formato de 24h");
    char escolha,sair, timeini[6];
    struct lkt{ //registro para poder guardar todos os valores de parciais.
            float litros;
            float consumo;
            float velocidade;
            char tempo[6];
    };
    struct lkt control[50];
    printf("\nDigite o valor inicial do Odometro: ");
    float kmi, disttotal; //quilometro inicial
    scanf("%f", &kmi);

    printf("\nDigite o instante de tempo inicial em HH:MM : ");
    scanf("%s", &timeini);
    char horasref[3], minutosref[3];//variaveis intermediarias, conversão str to int
    int i=0;
    for(i=0;i<2;i++)
    {
        horasref[i]=timeini[i];
    }
    horasref[2]='\0';
    for(i=0;i<2;i++)
    {
        minutosref[i]=timeini[(3+i)];
    }
    minutosref[2]='\0';
    float horas, min, tempoini;//a base do tempo ini será minutos
     horas=atoi(horasref);
    min=atoi(minutosref);
    tempoini=horas*60+min;
    printf("\nTempo em min: %f", tempoini);
    printf("\nDigite a distancia total da viagem em Km: ");
    scanf("%f", &disttotal);
    int cont=0;
    printf("\nNumero de paradas: %d", cont);
    printf("\nPara entrar no programa digite a letra 'p' ");
    
    float litrosf=0, kmf=0, odometro=0, last_odometro=0, last_h=0, last_m=0, consumof=0;
    last_odometro=kmi;
    do
    {   
        fflush(stdin);
        scanf("%s", &escolha);
        if(escolha=='p')
        {
            printf("\nDigite o Odometro atual: ");
            scanf("%f", &odometro);
            kmf+=(odometro-last_odometro);//somatório para calcular distancia total de viagem.
            printf("\nDigite o instante de tempo atual HH:MM : ");
            fflush(stdin);
            scanf("%s", &control[cont].tempo);
            for(i=0;i<2;i++)
            {
                horasref[i]=control[cont].tempo[i];
            }
            horasref[2]='\0';
            for(i=0; i<2; i++)
            {
                minutosref[i]=control[cont].tempo[(3+i)];
            }
            minutosref[2]='\0';
            last_h=horas;
            last_m=min;
            horas=atoi(horasref);
            min=atoi(minutosref);
            control[cont].velocidade=(odometro-last_odometro)/(((horas*60+min)-(last_h*60+last_m))/60);
            printf("Digite o Valor da bomba em litros: ");
            scanf("%f", &control[cont].litros);
            litrosf+= control[cont].litros;//vai fazer o somatório de todos os valores em litros colocados
            control[cont].consumo=control[cont].litros/(odometro-last_odometro);
            consumof=+control[cont].consumo;
            printf("\nA velocidade nesse trecho foi %.2fKm/h", control[cont].velocidade);
            printf("\nO consumo de combustivel consumido foi de %.2fL/Km", control[cont].consumo);
            printf("\nBaseado na velocidade do trecho eh presumido que o tempo final");
            int ref_h;
            float ref_m;
              
            ref_h=(int)(disttotal-kmf)/control[cont].velocidade;
            ref_m=((disttotal-kmf)/control[cont].velocidade-ref_h)*100;
            if(ref_m>59)
            {
                ref_m=ref_m-60;
                ref_h=ref_h+1;
            }
            printf("\nda viagem seja %02d:%02.0f", ref_h,ref_m );
            cont++;
            printf("\nNumero de paradas: %d", cont);
            printf("\nPara entrar no programa novamente digite 'p'");
            fflush(stdin);
            last_odometro=odometro;


        }
        else
            printf("\nComando Invalido!");
        
        if(kmf>=disttotal)
        
        {
            fflush(stdin);
            printf("\nULTIMO ABASTECIMENTO? s/n ");
            scanf("%s", &sair);
        }
    }while(kmf<disttotal||sair!='s');
    printf("\nRelatorio das parciais: ");
    for(i=0; i<cont; i++)
    {
        printf("\nParada %d:", i+1);
        printf("\nVelocidade do trecho: %.2fKm/h", control[i].velocidade);
        printf("\nInstante da parada: %s", control[i].tempo);
        printf("\nAbastecido com %.2fL", control[i].litros);
        printf("\nConsumo de combustivel: %.2fL/Km\n\n", control[i].consumo);


    }
    printf("\nRelatorio final:");
    printf("\nVelocidade Media: %.2fKm/h", disttotal/(((horas*60+min)-tempoini)/60));
    printf("\nConsumo total de %.2fL\n", consumof);
  

return 0;
}
