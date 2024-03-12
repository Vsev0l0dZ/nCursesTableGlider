#include "datadisplay.h"


void colorON(WINDOW* win1, WINDOW* win2){
    wattron(win1, COLOR_PAIR(1));
    wattron(win2, COLOR_PAIR(1));
}

void colorOFF(WINDOW* win1, WINDOW* win2){
    wattroff(win1, COLOR_PAIR(1));
    wattroff(win2, COLOR_PAIR(1));
}

void dataDisplay(int connfd){

    setlocale(0, "");
    initscr();

    system("resize -s 32 80");

    if (has_colors()){
        start_color();
    }
    else{
        printw("Your terminal does not support colors\n");
    }

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_RED);

    refresh();

    /*ncurses WINDOWS creation*/
    int8_t nlines = 28;
    int8_t ncolsWinTitle = 42;
    int8_t ncolsWinValues = 16;

    int8_t yWinTitles = 1;
    int8_t xWinTitles = 1;

    refresh();

    WINDOW* winTitles = newwin(nlines, ncolsWinTitle, yWinTitles, xWinTitles);

    int8_t yWinValues = yWinTitles;
    int8_t xWinValues = xWinTitles + ncolsWinTitle + 1;

    WINDOW* winValues = newwin(nlines, ncolsWinValues, yWinValues, xWinValues);
    refresh();

    /*int8_t yInsideWin = 1;*/
    int8_t xInsideWin = 2;

    char buff[MAX];
    /*infinite loop for chat*/
    for (;;) {
        memset(buff, 0, MAX);
        /*read the message from client and copy it in buffer*/
        read(connfd, buff, sizeof(buff));

        int distance2point = atoi(strtok(buff, ","));
        int8_t i = yWinTitles;
        colorON(winTitles, winValues);
        mvwprintw(winTitles, i, xWinTitles, "Дистанция до точки:");
        mvwprintw(winValues, i, xInsideWin, "%d", distance2point);
        colorOFF(winTitles, winValues);

        float bearing2point = atof(strtok(NULL, ","));
        mvwprintw(winTitles, ++i, xWinTitles, "Пеленг на точку:");
        mvwprintw(winValues, i, xInsideWin, "%f", bearing2point);

        double go2lat = atof(strtok(NULL, ","));
        colorON(winTitles, winValues);
        mvwprintw(winTitles, ++i, xWinTitles, "Иду в точку, широта:");
        mvwprintw(winValues, i, xInsideWin, "%lf", go2lat);
        colorOFF(winTitles, winValues);

        double go2lon = atof(strtok(NULL, ","));
        mvwprintw(winTitles, ++i, xWinTitles, "Иду в точку, долгота:");
        mvwprintw(winValues, i, xInsideWin, "%lf", go2lon);

        double currentLat = atof(strtok(NULL, ","));
        colorON(winTitles, winValues);
        mvwprintw(winTitles, ++i, xWinTitles, "Примерные координаты аппарата, широта:");
        mvwprintw(winValues, i, xInsideWin, "%lf", currentLat);
        colorOFF(winTitles, winValues);

        double currentLon = atof(strtok(NULL, ","));
        mvwprintw(winTitles, ++i, xWinTitles, "Примерные координаты аппарата, долгота:");
        mvwprintw(winValues, i, xInsideWin, "%lf", currentLon);

        float desiredCourse = atof(strtok(NULL, ","));
        colorON(winTitles, winValues);
        mvwprintw(winTitles, ++i, xWinTitles, "Желаемый курс:");
        mvwprintw(winValues, i, xInsideWin, "%f", desiredCourse);
        colorOFF(winTitles, winValues);

        float currentCourse = atof(strtok(NULL, ","));
        mvwprintw(winTitles, ++i, xWinTitles, "Курс аппарата:");
        mvwprintw(winValues, i, xInsideWin, "%f", currentCourse);

        float differenceCourse = atof(strtok(NULL, ","));
        colorON(winTitles, winValues);
        mvwprintw(winTitles, ++i, xWinTitles, "Курсовая разница:");
        mvwprintw(winValues, i, xInsideWin, "%f", differenceCourse);
        colorOFF(winTitles, winValues);

        int8_t currentRudder = atoi(strtok(NULL, ","));
        mvwprintw(winTitles, ++i, xWinTitles, "Выставленный руль:");
        mvwprintw(winValues, i, xInsideWin, "%d", currentRudder);

        int8_t gliderAngle = atoi(strtok(NULL, ","));
        colorON(winTitles, winValues);
        mvwprintw(winTitles, ++i, xWinTitles, "Угол погружения глайдера:");
        mvwprintw(winValues, i, xInsideWin, "%d", gliderAngle);
        colorOFF(winTitles, winValues);

        float gliderAssDepth = atoi(strtok(NULL, ","));
        mvwprintw(winTitles, ++i, xWinTitles, "Глубина глайдера по корме:");
        mvwprintw(winValues, i, xInsideWin, "%f", gliderAssDepth);

        float gliderNoseDepth = atof(strtok(NULL, ","));
        colorON(winTitles, winValues);
        mvwprintw(winTitles, ++i, xWinTitles, "Глубина глайдера по носу:");
        mvwprintw(winValues, i, xInsideWin, "%f", gliderNoseDepth);
        colorOFF(winTitles, winValues);

        float depthDelay = atof(strtok(NULL, ","));
        mvwprintw(winTitles, ++i, xWinTitles, "Дельта перекладки глубины:");
        mvwprintw(winValues, i, xInsideWin, "%f", depthDelay);

        uint8_t MIP = atoi(strtok(NULL, ","));
        colorON(winTitles, winValues);
        mvwprintw(winTitles, ++i, xWinTitles, "Механизм Изменения Плавучести:");
        mvwprintw(winValues, i, xInsideWin, "%d", MIP);
        colorOFF(winTitles, winValues);

        int8_t MID = atoi(strtok(NULL, ","));
        mvwprintw(winTitles, ++i, xWinTitles, "Механизм Изменения Дифферента:");
        mvwprintw(winValues, i, xInsideWin, "%d", MID);

        /*mvwprintw(winTitle, ++i, xWinTitle, "Поведение/Режим глайдера:");*/
        mvwprintw(winTitles, ++i, xInsideWin, "\n");

        uint8_t modeCode = atoi(strtok(NULL, ","));
        const char* glideModes[] = {"dive", "gpsFix", "neutral", "obstacle detection", "stabilization", "surface", "waypoints"};
        for (size_t j = 0; j < sizeof (glideModes)/sizeof(glideModes[0]); j++) {
            mvwprintw(winTitles, ++i, xWinTitles, "%39s", glideModes[j]);
            wmove(winValues, i, xInsideWin);
            wclrtoeol(winValues);
            if(j == modeCode){
                wattron(winValues, COLOR_PAIR(2));
                mvwprintw(winValues, i, xInsideWin, "РАБОТАЮ!");
                wattroff(winValues, COLOR_PAIR(2));
            }
        }

        wrefresh(winTitles);
        wrefresh(winValues);
        refresh();

        /*if msg contains "Exit" then server exit and chat ended.*/
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    } /*end of for (;;)*/
}
