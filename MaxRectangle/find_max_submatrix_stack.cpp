#include "find_max_submatrix_stack.h"
#include "data_structures.h"

// <������� � ������, ������ ������ ��� ���� ��������>
struct Pile{
    int index;
    int height;

    explicit Pile(int ind, int h){
        index = ind;
        height = h;
    }
};


Rectangle find_max_submatrix_stack(std::vector<std::vector<bool>>& matrix){
    // ���������� ������ �������� � ������� ������� �����
	Point upper_left{}, bottom_right{};

	// ������ �������
    int height = (int)matrix.size();
    if (height == 0) return Rectangle(upper_left, bottom_right);

    // ������ �������
    int width = (int)matrix[0].size();

    // ������ ����� ������ ��� ������ �������� � ������ �������;
    // �������������� ��� ������ ����� ������ �������
    std::vector<int> current_height(width, 0);

    // ���� ��� �������� ������� ����
    // <������� � ������, ������ ������ ��� ���� ��������>
    std::stack<Pile> st;

    // ������� ��������� �������� �������
    // � ���������� ��������� ������ ��������, �� �������������� ������
    int mx = 0, last_available_idx = 0;

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
        	// ������������� ����� ����� ��� ������� w � ������
            current_height[w] = matrix[h][w] ? current_height[w] + 1 : 0;

            // ���� ���� - ����� ������� � �����, �������� ������ ���
            // ������� �� ����������� ����� ������ ��� �������� w
            last_available_idx = w;

            // � ����� ������� �� ����� ��� ��������, ������� current_height[w]
            // ������:
            //
            //		|
            //    	|   |
            //	  	|   |	|				  |
            //	| 	|	|	|    ---->    |	  |
            //	|	|	|	|			  |	  |
            // id1 id2 id3	w            id1 id2
            //
            // � ������ ������� ����� �������� ���� ������� id � �����, ��� ������ ������
            // ��������� ������ ��� w, last_available_idx ������ ������ id2.
            //
            // ��� �������� ���������� ������� �������������� �������, ������� �� ��������� ������ ������
            // �� ������� w. ��������� � ������� w ������ ������, ���������� ����������� ������
            // �������������� � ����� ������� ����������.

            while((!st.empty()) && (st.top().height > current_height[w])){
                // ������ ���������� �������
            	last_available_idx = st.top().index;

                // ������� � ���������� ������� ��� ���������� �������
            	update_max_submatrix(mx, upper_left, bottom_right,
                    st.top().height * (w - last_available_idx),
                    w - 1, h, st.top().height, w - last_available_idx);

                // �������� �������
                st.pop();
            }
            // ����� �������� ������� ������� ����� (� ������� - id2 �� ��������� ��� ��� w);
            // � ������, ����� ��� �������� �������� � ����� �� ������������ �������� ��� w,
            // �������� �������� �� ���� � ������ ����������� ��������� ������� � ����
            st.push(Pile(last_available_idx, current_height[w]));
        }

        // ���� ���� ������, �� � ��� ���������� ������������ � ����� ������
        // ������������������ ��������. ������ �� ��� ������ ����������, ������������ � ���,
        // �������������� � ����� ������ � ������� ������ ����� ������. ������� ����� ���������
        // ����� ���������.
        if (st.empty()) continue;
        while(!st.empty()){
        	// ������� � ���������� �������
        	update_max_submatrix(mx, upper_left, bottom_right,
                st.top().height * (width - st.top().index),
                width - 1, h, st.top().height, width - st.top().index);
            // ������� �������� �� �����
            st.pop();
        }
    }
    // ���������� ���� �����, �������� ���������� ���������� �������,
    // ������������ ��� ����� ������ ������� �� ������� �������, � ����� - �� ��������
    return Rectangle(upper_left, bottom_right);
}

