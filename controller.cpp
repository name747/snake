#include <iostream>
#include <time.h>
// #include <conio.h> Remove windows header file
// #include <windows.h>
#include "controller.h"
#include "tools.h"
#include "startinterface.h"
#include "map.h"
#include "snake.h"
#include "food.h"
#include <unistd.h> //linux header file for usleep

void Controller::Start()//Initialize game
{
    SetWindowSize(41, 32);//Set window size
    SetColor(2);//Set initial color
    StartInterface *start = new StartInterface();//Dynamically create a StartInterface object
    start->Action();//Start interface
    delete start;//Release memory space

    /*Set cursor position, show message, wait for user input*/
    SetCursorPosition(13, 26);
    std::cout << "Press any key to start... " ;
    SetCursorPosition(13, 27);
    // system("pause");
    getch(); //Wait for any key
}

void Controller::Select()//Select difficulty
{
    /*Start interface selection*/
    SetColor(3);
    SetCursorPosition(13, 26);
    std::cout << "                          " ;
    SetCursorPosition(13, 27);
    std::cout << "                          " ;
    SetCursorPosition(6, 21);
    std::cout << "Select game difficulty:" ;
    SetCursorPosition(6, 22);
    std::cout << "(Up/Down to select, Enter to confirm)" ;
    SetCursorPosition(27, 22);
    SetBackColor();//Highlight selected option with background color
    std::cout << "Easy" ;
    SetCursorPosition(27, 24);
    SetColor(3);
    std::cout << "Normal" ;
    SetCursorPosition(27, 26);
    std::cout << "Hard" ;
    SetCursorPosition(27, 28);
    std::cout << "Extreme" ;
    SetCursorPosition(0, 31);
    score = 0;

    /*Difficulty selection mode*/
    int ch;//Record key value
    key = 1;//Record selected option, initially select first option
    bool flag = false;//Record whether Enter is pressed, initially false
    while ((ch = getch()))
    {
        switch (ch)//��������
        {
        case 72://UP�Ϸ����
            if (key > 1)//����ʱѡ����Ϊ��һ��ʱ��UP�Ϸ������Ч
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27, 22);//����ѡ�������ñ���ɫ
                    SetBackColor();
                    std::cout << "��ģʽ" ;

                    SetCursorPosition(27, 24);//����ѡ����ȡ���ұ���ɫ
                    SetColor(3);
                    std::cout << "��ͨģʽ" ;

                    --key;
                    break;
                case 3:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "��ͨģʽ" ;

                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "����ģʽ" ;

                    --key;
                    break;
                case 4:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "����ģʽ" ;

                    SetCursorPosition(27, 28);
                    SetColor(3);
                    std::cout << "����ģʽ" ;

                    --key;
                    break;
                }
            }
            break;

        case 80://DOWN�·����
            if (key < 4)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "��ͨģʽ" ;
                    SetCursorPosition(27, 22);
                    SetColor(3);
                    std::cout << "��ģʽ" ;

                    ++key;
                    break;
                case 2:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "����ģʽ" ;
                    SetCursorPosition(27, 24);
                    SetColor(3);
                    std::cout << "��ͨģʽ" ;

                    ++key;
                    break;
                case 3:
                    SetCursorPosition(27, 28);
                    SetBackColor();
                    std::cout << "����ģʽ" ;
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "����ģʽ" ;

                    ++key;
                    break;
                }
            }
            break;

        case 13://Enter�س���
            flag = true;
            break;
        default://��Ч����
            break;
        }
        if (flag) break;//����Enter�س���ȷ�ϣ��˳��������ѭ��

        SetCursorPosition(0, 31);//������������½ǣ�����ر���˸Ӱ����Ϸ����
    }

    switch (key)//Based on selected option, set movement speed, smaller speed value means faster speed
    {
    case 1:
        speed = 135;
        break;
    case 2:
        speed = 100;
        break;
    case 3:
        speed = 60;
        break;
    case 4:
        speed = 30;
        break;
    default:
        break;
    }
}

void Controller::DrawGame()//Draw game interface
{
    system("cls");//����

    /*Draw game map*/
    SetColor(3);
    Map *init_map = new Map();
    init_map->PrintInitmap();
    delete init_map;

    /*Draw title and info*/
    SetColor(3);
    SetCursorPosition(33, 1);
    std::cout << "Greedy Snake" ;
    SetCursorPosition(34, 2);
    std::cout << "Snake Game" ;
    SetCursorPosition(31, 4);
    std::cout << "Difficulty:" ;
    SetCursorPosition(36, 5);
    switch (key)
    {
    case 1:
        std::cout << "Easy" ;
        break;
    case 2:
        std::cout << "Normal" ;
        break;
    case 3:
        std::cout << "Hard" ;
        break;
    case 4:
        std::cout << "Extreme" ;
        break;
    default:
        break;
    }
    SetCursorPosition(31, 7);
    std::cout << "Score:" ;
    SetCursorPosition(37, 8);
    std::cout << "     0" ;
    SetCursorPosition(33, 13);
    std::cout << " Arrow keys to move" ;
    SetCursorPosition(33, 15);
    std::cout << " ESC to pause" ;
}

int Controller::PlayGame()//Game main loop
{
    /*Initialize snake and food*/
    Snake *csnake = new Snake();
    Food *cfood = new Food();
    SetColor(6);
    csnake->InitSnake();
    srand((unsigned)time(NULL)); // Initialize random seed, otherwise food position will be fixed
    cfood->DrawFood(*csnake);

    /*Game main loop*/
    while (csnake->OverEdge() && csnake->HitItself()) //Check if hitting wall or itself
    {
        /*Display menu options*/
        if (!csnake->ChangeDirection()) //When ESC is pressed
        {
            int tmp = Menu();//Display menu and get return value
            switch (tmp)
            {
            case 1://Continue game
                break;

            case 2://Restart game
                delete csnake;
                delete cfood;
                return 1;//Return 1 as PlayGame return value, back to Game function, indicates restart

            case 3://Exit game
                delete csnake;
                delete cfood;
                return 2;//Return 2 as PlayGame return value, back to Game function, indicates exit

            default:
                break;
            }
        }

        if (csnake->GetFood(*cfood)) //Get food
        {
            csnake->Move();//Move snake
            UpdateScore(1); // Update score 1 as food value
            RewriteScore();//Redraw score
            cfood->DrawFood(*csnake);//Draw new food
        }
        else
        {
            csnake->NormalMove();//Normal snake movement
        }

        if (csnake->GetBigFood(*cfood)) //Get big food
        {
            csnake->Move();
            UpdateScore(cfood->GetProgressBar()/5);//Update score based on big food progress
            RewriteScore();
        }

        if (cfood->GetBigFlag()) //When big food appears, flash
        {
            cfood->FlashBigFood();
        }

        usleep(speed * 1000);//�����ߵ��ƶ�Ч������λ��΢��
    }

    /*������*/
    delete csnake;//�ͷŷ�����ڴ�ռ�
    delete cfood;
    int tmp = GameOver();//������Ϸ�������棬��������ѡ��
    switch (tmp)
    {
    case 1:
        return 1;//���¿�ʼ
    case 2:
        return 2;//�˳���Ϸ
    default:
        return 2;
    }
}

void Controller::UpdateScore(const int& tmp)//���·���
{
    score += key * 10 * tmp;//���÷���������Ϸ�Ѷȼ����˵Ĳ���tmpȷ��
}

void Controller::RewriteScore()//�ػ����
{
    /*Ϊ���ַ���β�����룬������������Ϊ6λ�����㵱ǰ����λ������ʣ��λ���ÿո�ȫ�����������*/
    SetCursorPosition(37, 8);
    SetColor(11);
    int bit = 0;
    int tmp = score;
    while (tmp != 0)
    {
        ++bit;
        tmp /= 10;
    }
    for (int i = 0; i < (6 - bit); ++i)
    {
        std::cout << " " ;
    }
    std::cout << score ;
}

int Controller::Menu()//Menu selection
{
    /*Display menu*/
    SetColor(11);
    SetCursorPosition(32, 19);
    std::cout << "Menu" ;
    usleep(10000);
    SetCursorPosition(34, 21);
    SetBackColor();
    std::cout << "Continue Game" ;
    usleep(10000);
    SetCursorPosition(34, 23);
    SetColor(11);
    std::cout << "Restart" ;
    usleep(10000);
    SetCursorPosition(34, 25);
    std::cout << "Exit" ;
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 72://UP
            if (tmp_key > 1)
            {
                switch (tmp_key)
                {
                case 2:
                    SetCursorPosition(34, 21);
                    SetBackColor();
                    std::cout << "������Ϸ" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "���¿�ʼ" ;

                    --tmp_key;
                    break;
                case 3:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "���¿�ʼ" ;
                    SetCursorPosition(34, 25);
                    SetColor(11);
                    std::cout << "�˳���Ϸ" ;

                    --tmp_key;
                    break;
                }
            }
            break;

        case 80://DOWN
            if (tmp_key < 3)
            {
                switch (tmp_key)
                {
                case 1:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "���¿�ʼ" ;
                    SetCursorPosition(34, 21);
                    SetColor(11);
                    std::cout << "������Ϸ" ;

                    ++tmp_key;
                    break;
                case 2:
                    SetCursorPosition(34, 25);
                    SetBackColor();
                    std::cout << "�˳���Ϸ" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "���¿�ʼ" ;

                    ++tmp_key;
                    break;
                }
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        if (flag)
        {
            break;
        }
        SetCursorPosition(0, 31);
    }

    if (tmp_key == 1) //Select continue game then hide menu
    {
        SetCursorPosition(32, 19);
        std::cout << "      " ;
        SetCursorPosition(34, 21);
        std::cout << "        ";
        SetCursorPosition(34, 23);
        std::cout << "        ";
        SetCursorPosition(34, 25);
        std::cout << "        ";
    }
    return tmp_key;
}

void Controller::Game()//Game main loop
{
    Start();//Initialize
    while (true)//Game runs as a loop until exit game
    {
        Select();//Select difficulty
        DrawGame();//Draw game interface
        int tmp = PlayGame();//Run game loop, when restart or exit, return value to tmp
        if (tmp == 1) //When return value is 1, restart game
        {
            system("cls");
            continue;
        }
        else if (tmp == 2) //When return value is 2, exit game
        {
            break;
        }
        else
        {
            break;
        }
    }
}

int Controller::GameOver()//Game over screen
{
    /*Display game over screen*/
    usleep(5000);
    SetColor(11);
    SetCursorPosition(10, 8);
    std::cout << "========================================" ;
    usleep(3000);
    SetCursorPosition(9, 9);
    std::cout << "||              Game Over !!!            ||" ;
    usleep(30000);
    SetCursorPosition(9, 10);
    std::cout << "||                                      ||" ;
    usleep(30000);
    SetCursorPosition(9, 11);
    std::cout << "||           Better luck next time!      ||" ;
    usleep(30000);
    SetCursorPosition(9, 12);
    std::cout << "||                                      ||" ;
    usleep(30000);
    SetCursorPosition(9, 13);
    std::cout << "||            Your score:                ||" ;
    SetCursorPosition(24, 13);
    std::cout << score ;
    usleep(30000);
    SetCursorPosition(9, 14);
    std::cout << "||                                      ||" ;
    usleep(30000);
    SetCursorPosition(9, 15);
    std::cout << "||   Would you like to play again?     ||" ;
    usleep(30000);
    SetCursorPosition(9, 16);
    std::cout << "||                                      ||" ;
    usleep(30);
    SetCursorPosition(9, 17);
    std::cout << "||                                      ||" ;
    usleep(30);
    SetCursorPosition(9, 18);
    std::cout << "||    Yes (Left)        No (Right)     ||" ;
    usleep(30);
    SetCursorPosition(9, 19);
    std::cout << "||                                      ||" ;
    usleep(30);
    SetCursorPosition(9, 20);
    std::cout << "||                                      ||" ;
    usleep(30);
    SetCursorPosition(10, 21);
    std::cout << "========================================" ;

    usleep(100);
    SetCursorPosition(12, 18);
    SetBackColor();
    std::cout << "Yes" ;
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 75://LEFT
            if (tmp_key > 1)
            {
                SetCursorPosition(12, 18);
                SetBackColor();
                std::cout << "Yes" ;
                SetCursorPosition(20, 18);
                SetColor(11);
                std::cout << "No, thanks for playing!" ;
                --tmp_key;
            }
            break;

        case 77://RIGHT
            if (tmp_key < 2)
            {
                SetCursorPosition(20, 18);
                SetBackColor();
                std::cout << "No, thanks for playing!" ;
                SetCursorPosition(12, 18);
                SetColor(11);
                std::cout << "Yes" ;
                ++tmp_key;
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        SetCursorPosition(0, 31);
        if (flag) {
            break;
        }
    }

    SetColor(11);
    switch (tmp_key)
    {
    case 1:
        return 1;//Restart
    case 2:
        return 2;//Exit
    default:
        return 1;
    }
}
