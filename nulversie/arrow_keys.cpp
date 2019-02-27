#include <iostream>
#include <winuser.h>
#include <signal.h>


int main() {
    bool running = true;
    bool straight;
    bool left;
    bool right;
    bool back;
    while (running){
        if (GetAsyncKeyState(0x26)){
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
        }

        else if (GetAsyncKeyState(0x25)){

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
        }

        else if (GetAsyncKeyState(0x27)){
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
        }

        else if (GetAsyncKeyState(0x28)){
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

        }

    }

}