#!/bin/env python3

import sys

if __name__ == '__main__':
    output_path = sys.argv[1]
    with open(output_path + "/gameboard_init.hpp", 'w+') as f:
        for i in range(0, 6):
            for j in range(0, 7):
                str_ = f"m_board_array[{i}][{j}] = std::shared_ptr<QLabel>(ui->_{i}_{j});\n"
                f.write(str_)
