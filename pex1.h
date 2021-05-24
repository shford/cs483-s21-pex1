//
// Created by hampton on 2/21/21.
//
#pragma once

#define MAX_COMMAND_LEN (100)
#define INVALID_ARG_ERROR (-3)
#define STD_FUNCTION_ERROR (-4)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "Queue.h"

/*
 * Purpose: Start custom shell
 * @Params: List*
 * @Return: void
 */
void startShell(List* list);