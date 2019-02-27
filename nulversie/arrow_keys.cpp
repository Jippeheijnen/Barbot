#include <conio.h>
#include <iostream>
using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


int main() {
    bool running = true;
    bool straight;
    bool left;
    bool right;
    bool back;
    int c = 0;
    while (running) {
        c = _getch();
        switch ((c = _getch())) {
            case KEY_UP:
                if(straight){
                    continue;
                }else{
                    left = false;
                    straight = true;
                    right = false;
                    back = false;
                    std::cout << "straight";

                    //code straight
                }

                break;

            case KEY_DOWN:
                if(back){
                    continue;
                }else {
                    left = false;
                    straight = false;
                    right = false;
                    back = true;
                    std::cout << "back";

                    //code back
                }
                break;

            case KEY_LEFT:
                if(left){
                    continue;
                }else{
                    left = true;
                    straight = false;
                    right = false;
                    back = false;
                    std::cout << "left";

                    //code left
                }
                break;

            case KEY_RIGHT:
                if(right){
                    continue;
                }else{
                    left = false;
                    straight = false;
                    right = true;
                    back = false;
                    std::cout << "right";

                    //code right
                }
                break;

            default:
                if(straight){
                    //code stop bij straight
                    straight = false;
                }else if(left){
                    //code stop bij left
                    left = false;
                }else if(right){
                    //code stop bij right
                    right = false;
                }else if(back){
                    //code stop bij back
                    back = false;

                break;
        }
    }
}
}