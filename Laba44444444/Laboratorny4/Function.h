#pragma once
#include "Operator.h"
#include <iostream>
#include <stdio.h>
#include "sqlite3.h"
#include "MainForm.h"

void replace(List<Household^>^& vect, int first_index, int second_index);
void bubbleSort(List<Household^>^& line);

static int selectData(const char* s);
