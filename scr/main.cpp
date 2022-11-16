//
// Created by bulat on 16.11.22.
//
#include <opus/opus.h>
#include <iostream>


int main()
{
    std::cout << opus_get_version_string();
    return 0;
}