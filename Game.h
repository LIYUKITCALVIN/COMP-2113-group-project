// Game.h
#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();
    void run(); // 主游戏循环

private:
    void mainMenu(); // 主菜单
    void initializeGame(); // 初始化游戏
    void loadGame(); // 加载游戏
};

#endif
