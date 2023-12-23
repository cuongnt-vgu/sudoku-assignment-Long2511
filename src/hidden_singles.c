#include "hidden_singles.h"

int find_hidden_single_values(Cell **p_cells, int *hidden_single_values) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        hidden_single_values[i] = 0;
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        Cell *cell = p_cells[i];
        if (cell->num_candidates > 1) {
            for (int j = 0; j < cell->num_candidates; j++) {
                if (cell->candidates[j] != 0) {
                    hidden_single_values[cell->candidates[j] - 1]++;
                }
            }
        }
    }
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (hidden_single_values[i] == 1) {
            hidden_single_values[counter++] = i + 1;
        }
    }

    return counter;
}

void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter) {
    int hidden_single_values[BOARD_SIZE];
    int num_hidden_single_values = find_hidden_single_values(p_cells, hidden_single_values);

    // Loop through the cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        Cell *cell = p_cells[i];
        if (cell->num_candidates > 1) {
            for (int j = 0; j < cell->num_candidates; j++) {
                for (int k = 0; k < num_hidden_single_values; k++) {
                    if (cell->candidates[j] == hidden_single_values[k]) {
                        p_hidden_singles[*p_counter].p_cell = cell;
                        p_hidden_singles[*p_counter].value = cell->candidates[j];
                        (*p_counter)++;
                    }
                }
            }
        }
    }
}

int hidden_singles(SudokuBoard *p_board) {
    HiddenSingle hidden_singles[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;

    // Find hidden singles in rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &counter);
    }

    // Find hidden singles in columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_single(p_board->p_cols[i], hidden_singles, &counter);
    }

    // Find hidden singles in boxes
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_single(p_board->p_boxes[i], hidden_singles, &counter);
    }

    // Apply the hidden singles to the board
    for (int i = 0; i < counter; i++) {
        Cell *cell = hidden_singles[i].p_cell;
        cell->value = hidden_singles[i].value;
        cell->num_candidates = 0;
    }

    return counter;
}