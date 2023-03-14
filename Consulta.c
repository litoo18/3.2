#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) 
{
    MYSQL *conn;
    int err;
    // Estructura especial para almacenar resultados de consultas
    MYSQL_RES *resultado;
    MYSQL_ROW row;
    // Creamos una conexión al servidor MYSQL
    conn = mysql_init(NULL);
    if (conn==NULL) {
        printf ("Error al crear la conexión: %u %s\n",
                mysql_errno(conn), mysql_error(conn));
        exit (1);
    }
    // Inicializar la conexión
    conn = mysql_real_connect (conn, "localhost","root", "mysql", "Juego",0, NULL, 0);
    if (conn==NULL) {
        printf ("Error al inicializar la conexión: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit (1);
    }
    int id;
    // Pregunto el nombre del jugador ganador de la partida introducida por texto
    printf ("Dame que partida quieres consultar y te dire el nombre del ganador\n");
    scanf ("%d", &id);
    char consulta [80];
    sprintf(consulta, "SELECT Partida.ganador FROM Partida WHERE Partida.identificador = '%d'", id);
    err = mysql_query(conn, consulta);
    if (err!=0) {
        printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit (1);
    }
    resultado = mysql_store_result (conn);
    row = mysql_fetch_row (resultado);
    if (row == NULL)
        printf ("No se han obtenido datos en la consulta\n");
    else {
        while (row != NULL){
            // La columna 0 contiene el username del jugador
            printf ("%s\n", row[0]);
            // Obtenemos la siguiente fila
            row = mysql_fetch_row (resultado);
        }
    }
    mysql_close (conn);
    exit(0);
}
