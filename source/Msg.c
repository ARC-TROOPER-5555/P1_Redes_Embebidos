/*
 * Msg.c
 *
 *  Created on: 1 jun. 2025
 *      Author: Frida Hernandez
 */

#include "Msg.h"

static uint8_t counter = 0;

const uint8_t* Msg_SendMessage(uint8_t id)
{
	switch(id)
	{
		case 0:
			return "No todo lo que es oro reluce...";

		case 1:
			return "Aun en la oscuridad...";

		case 2:
			return "¿Que es la vida?";

		case 3:
			return "No temas a la oscuridad...";

		case 4:
			return "Hasta los mas pequeños...";

		case 5:
			return "No digas que el sol se ha puesto...";

		case 6:
			return "El coraje se encuentra...";

		case 7:
			return "No todos los tesoros...";

		case 8:
			return "Es peligroso...";

		case 9:
			return "Un mago nunca llega tarde...";

		case 10:
			return "Aun hay esperanza...";

		case 11:
			return "El mundo esta cambiando...";

		case 12:
			return "Las raices profundas...";

		case 13:
			return "No se puede...";

		case 14:
			return "Y sobre todo...";

		case 15:
			return "De las cenizas, un fuego...";

		default:
			return "Frase invalida";
	}
}


int Msg_ProcessMessage(const uint8_t* recibida)
{
    if (strcmp(recibida, "...Ni todos los que vagan estan perdidos.") == 0)
        return 0;

    else if (strcmp(recibida, "...brilla una luz.") == 0)
        return 1;

    else if (strcmp(recibida, "Nada mas que un breve caminar a la luz del sol.") == 0)
        return 2;

    else if (strcmp(recibida, "...pues en ella se esconden las estrellas.") == 0)
        return 3;

    else if (strcmp(recibida,  "...pueden cambiar el curso del futuro.") == 0)
        return 4;

    else if (strcmp(recibida, "...si aun te queda la luna.") == 0)
        return 5;

    else if (strcmp(recibida, "...en los lugares mas inesperados.") == 0)
        return 6;

    else if (strcmp(recibida, "...son oro y plata.") == 0)
        return 7;

    else if (strcmp(recibida,  "...cruzar tu puerta.") == 0)
        return 8;

    else if (strcmp(recibida, "...ni pronto, Frodo Bolson. Llega precisamente cuando se lo propone.") == 0)
        return 9;

    else if (strcmp(recibida, "...mientras la Compañia permanezca fiel.") == 0)
        return 10;

    else if (strcmp(recibida, "...Siento que algo se avecina.") == 0)
        return 11;

    else if (strcmp(recibida, "...no alcanzan las heladas.") == 0)
        return 12;

    else if (strcmp(recibida, "...pasar.") == 0)
        return 13;

    else if (strcmp(recibida,  "...cuidado con el Anillo.") == 0)
        return 14;

    else if (strcmp(recibida,   "...se despertara.") == 0)
        return 15;
    else
    	return -1; // No reconocida
}

void Msg_ButtonCounter()
{
	counter = (counter > 15) ? 0 : counter + 1;
}

uint8_t Msg_GetCounter()
{
	return counter;
}

