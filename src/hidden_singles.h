#pragma once

#include "sudoku.h"

struct hidden_single_reserved{
    struct hidden_single_reserved *next;
    int candidate;
    int col;
    int row;
};

void insert(struct hidden_single_reserved **HEAD, int row, int col, int candidate);
void transverseLinkedList (struct hidden_single_reserved *HEAD, SudokuBoard *board);
void free_linked_list(struct hidden_single_reserved *HEAD);

int find_hidden_single_values(Cell **p_cells, int *hidden_single_values);
int hidden_singles(SudokuBoard *p_board);

bool check_row(SudokuBoard *board, int idRow, int idCol, int idCandidate);
bool check_col(SudokuBoard *board, int idRow, int idCol, int idCandidate);
bool check_box (SudokuBoard *board, int idRow, int idCol, int idBox, int idCandidate);

void remove_candidates(SudokuBoard *board, int idRow, int idCol, int idBox, int idCandidate);
void self_remove_candidates(Cell *cell, int idCandidate);