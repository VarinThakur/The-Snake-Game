#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <vector>
using namespace std;

HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
void Color(int y)
{
    SetConsoleTextAttribute(out, y); 
}

void loadingBar()
{
    Color(2);
    char a = 177, b = 219;

    printf("\n\n\n\n\t\tLoading...\n\n");
    printf("\t");

    for (int i = 0; i < 26; i++)
        printf("%c", a);

    printf("\r"); 
    printf("\t");

    for (int i = 0; i < 26; i++)
    {
        printf("%c", b);

        Sleep(300);
    }
}

class God
{
    bool Game_Over;
    int score;

public:
    God()
    {
        Game_Over = false;
        score = 0;
    }

    void cursorReset();
    void EndGame();
    void ScoreIncrease();
    void display_SCORE();
    bool get_Game_Over();
};

void God ::cursorReset()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
}

void God ::EndGame()
{
    Game_Over = true;
}

void God ::ScoreIncrease()
{
    score += 10;
}

void God ::display_SCORE()
{
    Color(7);
    cout << "Score : " << score << endl;
}

bool God ::get_Game_Over()
{
    return Game_Over;
}

class Map
{
public:
    int width;
    int height;

    Map(int x = 50, int y = 20)
    {
        width = x;
        height = y;
    }
    void Draw_WALL();
    void Draw_EMPTY_SPACE();
};

void Map ::Draw_WALL()
{
    Color(6);
    char b = 219;
    cout << b;
}

void Map ::Draw_EMPTY_SPACE()
{
    Color(10);
    char a = 219;
    cout << a;
}

class Snake : public Map
{

    int head_x_coordinate;
    int head_y_coordinate;

    vector <int> tail_x_coordinate = vector <int> (100);
    vector <int> tail_y_coordinate = vector <int> (100);
    int length_tail;

public:
    enum Direction
    {
        STOP = 0,
        LEFT,
        RIGHT,
        UP,
        DOWN
    } dir;

    Snake()
    {
        head_x_coordinate = width / 2;
        head_y_coordinate = height / 2;
        length_tail = 0;
        dir = STOP;
    }
    void Draw_HEAD();
    void Draw_TAIL();
    void logic_MOVE();
    void logic_TAIL();
    void increment_TAIL();
    int get_head_x_coordinate();
    int get_head_y_coordinate();
    int get_tail_length();
    vector <int>::iterator get_tailX();
    vector <int>::iterator get_tailY();
    void Input(God *&g);
};

void Snake::Draw_HEAD()
{
    Color(1);
    char a = 219;
    cout << a;
}

void Snake::Draw_TAIL()
{
    Color(5);
    char a = 219;
    cout << a;
}

void Snake::logic_MOVE()
{
    switch (dir)
    {
    case LEFT:
        head_x_coordinate--;
        break;
    case RIGHT:
        head_x_coordinate++;
        break;
    case UP:
        head_y_coordinate--;
        break;
    case DOWN:
        head_y_coordinate++;
        break;
    default:
        break;
    }
}

void Snake::logic_TAIL()
{
    int prev_x = tail_x_coordinate[0];
    int prev_y = tail_y_coordinate[0];
    tail_x_coordinate[0] = head_x_coordinate;
    tail_y_coordinate[0] = head_y_coordinate;
    int prev_2x, prev_2y;

    if(length_tail > 100)
    {
        tail_x_coordinate.resize(length_tail);
        tail_y_coordinate.resize(length_tail);
    }

    for (int i = 1; i < length_tail; i++)
    {
        prev_2x = tail_x_coordinate[i];
        prev_2y = tail_y_coordinate[i];
        tail_x_coordinate[i] = prev_x;
        tail_y_coordinate[i] = prev_y;
        prev_x = prev_2x;
        prev_y = prev_2y;
    }
}

void Snake::increment_TAIL()
{
    length_tail++;
}

int Snake::get_head_x_coordinate()
{
    return head_x_coordinate;
}

int Snake::get_head_y_coordinate()
{
    return head_y_coordinate;
}

int Snake::get_tail_length()
{
    return length_tail;
}

vector<int> :: iterator Snake::get_tailX()
{
    return tail_x_coordinate.begin();
}

vector<int> :: iterator Snake::get_tailY()
{
    return tail_y_coordinate.begin();
}

void Snake ::Input(God *&g)
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            g->EndGame();
            break;
        }
    }
}

class Fruit : public Map
{

    int fruit_x_coordinate;
    int fruit_y_coordinate;

public:
    Fruit()
    {
        srand(time(0));
        do
        {
            fruit_x_coordinate = rand() % width + 1;

        } while (fruit_x_coordinate == 0);

        fruit_y_coordinate = rand() % height;
    }

    void Draw_FRUIT();
    void logic_FRUIT();
    int get_fruit_x();
    int get_fruit_y();
};

void Fruit ::Draw_FRUIT()
{
    Color(4);
    char a = 254;
    cout << a;
}

void Fruit ::logic_FRUIT()
{
    do
    {
        fruit_x_coordinate = rand() % width + 1;

    } while (fruit_x_coordinate == 0); 

    fruit_y_coordinate = rand() % height;
}

int Fruit ::get_fruit_x()
{
    return fruit_x_coordinate;
}

int Fruit ::get_fruit_y()
{
    return fruit_y_coordinate;
}

void Setup();
void Draw();
void Logic();

void Setup(God **g, Snake **s, Map **m, Fruit **f)
{
    *g = new God();
    *s = new Snake();
    *m = new Map();
    *f = new Fruit();
}

void Draw(God *g, Snake *s, Map *m, Fruit *f)
{
    g->cursorReset();
    for (int i = 0; i < m->width + 2; i++)
        m->Draw_WALL();
    cout << endl;

    for (int i = 0; i < m->height; i++)
    {
        
        for (int j = 0; j < m->width+2; j++)
        {
            bool wall_print = false ;
            if (j == 0 || j == m->width + 1)
            {
                m->Draw_WALL();
                wall_print = true ;
            }
            if (i == s->get_head_y_coordinate() && j == s->get_head_x_coordinate())
                s->Draw_HEAD();
            else if (i == f->get_fruit_y() && j == f->get_fruit_x())
                f->Draw_FRUIT();
            else
            {
                bool print = false;
                for (int k = 0; k < s->get_tail_length(); k++)
                {

                    if (s->get_tailX()[k] == j && s->get_tailY()[k] == i)
                    {
                        s->Draw_TAIL();
                        print = true;
                    }
                }
                if (print == 0 && wall_print == 0)
                    m->Draw_EMPTY_SPACE();
            }

        }
        cout << endl;
    }

    for (int i = 0; i < m->width + 2; i++)
        m->Draw_WALL();
    cout << endl;
    g->display_SCORE();
}

void Logic(God *g, Snake *s, Map *m, Fruit *f)
{
    if (s->get_head_x_coordinate() == f->get_fruit_x() && s->get_head_y_coordinate() == f->get_fruit_y())
    {
        g->ScoreIncrease();
        f->logic_FRUIT();
        s->increment_TAIL();
    }
    s->logic_TAIL();
    s->logic_MOVE();

    if (s->get_head_x_coordinate() > m->width  || s->get_head_x_coordinate() < 0 || s->get_head_y_coordinate() > m->height - 1 || s->get_head_y_coordinate() < 0)
        g->EndGame();

    for (int i = 0; i < s->get_tail_length(); i++)
        if (s->get_tailX()[i] == s->get_head_x_coordinate() && s->get_tailY()[i] == s->get_head_y_coordinate())
            g->EndGame();

}

int main()
{
    God *g;
    Snake *s;
    Map *m;
    Fruit *f;
    loadingBar();
    Setup(&g, &s, &m, &f);
    while (!g->get_Game_Over())
    {
        Draw(g, s, m, f);
        Logic(g, s, m, f);
        s->Input(g); 
        Sleep(50);
    }
    return 0;
}