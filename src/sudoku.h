#pragma once

#include <stdbool.h>

#define BOARD_SIZE 9

struct Cell_impl
{
    int row_index; // vị trí hàng ô đó thuộc về
    int col_index; // vị trí cột ô đó thuộc về
    int box_index; // thuộc khối ô 3x3 nào
    int num_candidates; // số lượng giá trị có thể đặt vào
    int candidates[BOARD_SIZE];// mang giá trị true/false, giá trị thứ i+1 có thể tồn tại ở ô đó
    int value; // đáp án của ô đó
    bool fixed; // ko thể được sửa trong game
};

typedef struct Cell_impl Cell;

struct SudokuBoard_impl
{
    int solved_counter; // đếm số ô đã hoàn thành.
    Cell **data; // 9x9 cell board

    Cell **p_rows[BOARD_SIZE];  // rows pointers
    Cell **p_cols[BOARD_SIZE];  // cols pointers
    Cell **p_boxes[BOARD_SIZE]; // boxes pointers
    Cell *solved_cells[BOARD_SIZE *
                       BOARD_SIZE]; // solved cell pointers (maximum)
};

typedef struct SudokuBoard_impl SudokuBoard;

void init_sudoku(SudokuBoard *p_board);
void load_sudoku(SudokuBoard *p_board, char *input_text);
bool apply_constraint(Cell **p_cells, int value);
bool is_in_list(Cell **p_array, int size, Cell *p);
void print_candidate_num(SudokuBoard *p_board);
void print_solution(SudokuBoard *p_board);

void set_candidate(Cell *cell, int value);
void unset_candidate(Cell *cell, int value);
void set_candidates(Cell *cell, int *candidates, int size);
int *get_candidates(Cell *cell);

int check_solved_cells(SudokuBoard *p_board, Cell ***p_solved_cells);
bool show_possible(SudokuBoard *p_board, Cell **p_solved_cells, int counter);
void free_sudoku(SudokuBoard *p_board);
extern bool is_candidate(Cell *cell, int value);

void show_sudoku(SudokuBoard *p_board);