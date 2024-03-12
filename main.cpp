/* программа получает csv-строку от TCP-клиента и
 * выводит данные в табличном виде в терминал
 *
 * csv-строка, параметры, по порядку:
 *  0/ Дистанция до точки, int8_t
 *  1/ Пеленг на точку, float
 *  2/ Иду в точку, широта, double
 *  3/ Иду в точку, долгота, double
 *  4/ Примерные координаты аппарата, широта, double
 *  5/ Примерные координаты аппарата, долгота, double
 *  6/ Желаемый курс, float
 *  7/ Курс аппарата, float
 *  8/ Курсовая разница, float
 *  9/ Выставленный руль, int8_t
 *  10/ Угол погружения глайдера, int8_t
 *  11/ Глубина глайдера по корме, float
 *  12/ Глубина глайдера по носу, float
 *  13/ Дельта перекладки глубины, float
 *  14/ Механизм Изменения Плавучести, uint8_t
 *  15/ Механизм Изменения Дифферента, int8_t
 *  16/ Поведение/Режим глайдера (флаг/код для switch), uint8_t// добавить ENUM
*/

#include "datadisplay.h"


int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    /*socket create and verification*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    memset(&servaddr, 0, sizeof(servaddr));

    /*assign IP, PORT*/
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    /*Binding newly created socket to given IP and verification*/
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    /*Now server is ready to listen and verification*/
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    /*Accept the data packet from client and verification*/
    connfd = accept(sockfd, (SA*)&cli, (socklen_t*)&len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");

    /*Function for chatting between client and server*/
    dataDisplay(connfd);

    /*After chatting close the socket*/
    close(sockfd);

    getchar();
    endwin();
}

