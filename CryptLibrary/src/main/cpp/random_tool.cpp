//
// Created by lulu on 17-10-12.
//

#include "random_tool.h"

string generateAlphaAndDigit(int lenght){

    string result = "";
    if(lenght < 1){
        return result;
    }
    int data = 0;
    for (int i = 0; i < lenght; ++i) {
        int index = rand() % 3;
        char *tmp = NULL;
        tmp = new char[20];
        switch (index){

            case 0:
                data = rand() % 10;
                sprintf(tmp, "%d", data);
                result += tmp;
                break;
            case 1:
                data = rand() % 26 + 65;
                result += data;
                break;
            case 2:
                data = rand() % 26 + 97;
                result += data;
                break;
            default:break;
        }
        delete[] tmp;
    }
    return result;
}
