#include "data_structures.h"
#include "find_max_submatrix_maps.h"

// ������� ��� ���������� ��������� � ������������ ����������
void update_max_submatrix(int& current_mx, Point& upper_left, Point& bottom_right,
		const int candidate_mx, const int x, const int y,
		const int height, const int width){

    if (candidate_mx > current_mx){

        current_mx = candidate_mx;

        upper_left.x = x - width + 1;
        upper_left.y = y - height + 1;

        bottom_right.x = x;
        bottom_right.y = y;
    }
}

Rectangle find_max_submatrix_maps(std::vector<std::vector<bool>>& matrix){
	// ���������� ������ �������� � ������� ������� �����
	Point upper_left{}, bottom_right{};

	// ������ �������
    int height = (int)matrix.size();
    if (height == 0) return Rectangle(upper_left, bottom_right);

    // ������ �������
    int width = (int)matrix[0].size();

    // ������� ��� �������� ������������ ��������� ������ ��������� ������
    // � ���������� ������
    std::vector<std::map<int, int>> prev_line_maps(width);

    // ������� ����� ������ ������ ������ � ������
    int curr_series = 0;

    // ������� ��������� �������� �������
    int mx = 0;

    // ��������� ������ �������� ������ ������
    for (int w = 0; w < width; w++){
        if (matrix[0][w]){
            curr_series++;
            prev_line_maps[w][curr_series] = 1;

            // ������� � ���������� ������������ �������
            update_max_submatrix(mx, upper_left, bottom_right,
                            curr_series, w, 0, 1, curr_series);

         // ���� ������ ����, ����� ������ �����������
        }else{curr_series = 0;}
    }
    // ������� ��� ����� ������
    std::map<int, int> curr_line_maps;
    // ��������������� ����������
    int max_width = 0;

    // �������� ������ ��� � ������ ������
    for (int h = 1; h < height; h++){
        curr_series = 0;
        for (int w = 0; w < width; w++){
        	// ������� �������
            curr_line_maps.clear();

            if (matrix[h][w]){
                curr_series++;
                // ��������� ������� �������� ������� ����� ������
                update_max_submatrix(mx, upper_left, bottom_right,
                            curr_series, w, h, 1, curr_series);

                // � ������ ������ ����� ������ ������������� ������������ ������� 1
                curr_line_maps[curr_series] = 1;

                // ������ �� ������� ������ ������� � ���������� ������
                for (auto it = prev_line_maps[w].begin(); (it != prev_line_maps[w].end()); it++){
                	// ������� ����� ������ ����� ���� �������� �����, �� ������������� �� ����� ����
                    max_width = std::min((it -> first), curr_series);

                    // ���� � ��� �� ����� ������ ������ ������ � ������ ����� �������� ��������������
                    // ���������� ��������� �������; ���������� ������� ����� ��� ����������
                    curr_line_maps[max_width] = std::max((it -> second) + 1, curr_line_maps[max_width]);

                    // ��������� ��������
                    update_max_submatrix(mx, upper_left, bottom_right, max_width * (curr_line_maps[max_width]),
                                         w, h, curr_line_maps[max_width], max_width);
                }
            // ����� ����� ������ �����������
            }else{curr_series = 0;}

            // ��������� � ����� ������
            prev_line_maps[w] = curr_line_maps;
        }
    }
    // ���������� ���� �����, �������� ���������� ���������� �������,
    // ������������ ��� ����� ������ ������� �� ������� �������, � ����� - �� ��������
    return Rectangle(upper_left, bottom_right);
}
