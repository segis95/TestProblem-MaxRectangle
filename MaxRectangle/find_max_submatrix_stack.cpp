#include "find_max_submatrix_stack.h"
#include "data_structures.h"

// <позиция в строке, высота единиц над этой позицией>
struct Pile{
    int index;
    int height;

    explicit Pile(int ind, int h){
        index = ind;
        height = h;
    }
};


Rectangle find_max_submatrix_stack(std::vector<std::vector<bool>>& matrix){
    // Координаты левого верхнего и правого нижнего углов
	Point upper_left{}, bottom_right{};

	// Высота матрицы
    int height = (int)matrix.size();
    if (height == 0) return Rectangle(upper_left, bottom_right);

    // Ширина матрицы
    int width = (int)matrix[0].size();

    // Вектор числа единиц над каждой позицией в строке матрицы;
    // подсчитывается для каждой новой строки матрицы
    std::vector<int> current_height(width, 0);

    // Стек для хранения записей вида
    // <позиция в строке, высота единиц над этой позицией>
    std::stack<Pile> st;

    // Текущий известный максимум площади
    // и предыдущий известный индекс значения, не превосходящего данное
    int mx = 0, last_available_idx = 0;

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
        	// пересчитываем число нулей для позиции w в строке
            current_height[w] = matrix[h][w] ? current_height[w] + 1 : 0;

            // наша цель - найти позицию в стеке, значение единиц над
            // которым не превосходит числа единиц над позицией w
            last_available_idx = w;

            // В цикле удаляем из стека все значения, большие current_height[w]
            // Пример:
            //
            //		|
            //    	|   |
            //	  	|   |	|				  |
            //	| 	|	|	|    ---->    |	  |
            //	|	|	|	|			  |	  |
            // id1 id2 id3	w            id1 id2
            //
            // В данном примере после удаления всех позиций id в стеке, где высота единиц
            // превышает высоту над w, last_available_idx станет равным id2.
            //
            // При удалении очередного столбца подсчитывается площадь, которую он образовал вправо вплоть
            // до позиции w. Поскольку в позиции w высота меньше, дальнейшее продолжение вправо
            // прямоугольника с такой высотой невозможно.

            while((!st.empty()) && (st.top().height > current_height[w])){
                // Индекс удаляемого столбца
            	last_available_idx = st.top().index;

                // Подсчёт и обновление площади для удаленного столбца
            	update_max_submatrix(mx, upper_left, bottom_right,
                    st.top().height * (w - last_available_idx),
                    w - 1, h, st.top().height, w - last_available_idx);

                // Удаление столбца
                st.pop();
            }
            // После удаления столбца создаем новый (в примере - id2 со значением как над w);
            // В случае, когда все значения столбцов в стеке не превосходили значения над w,
            // никакого удаления не было и просто добавляется очередной столбец в стек
            st.push(Pile(last_available_idx, current_height[w]));
        }

        // Если стек непуст, то в нем содержится возрастающая к концу строки
        // последовательность столбцов. Каждый из них задает подматрицу, начинающуюся в нем,
        // оканчивающуюся в конце строки и имеющую высоту этого слобца. Площади таких подматриц
        // также учитываем.
        if (st.empty()) continue;
        while(!st.empty()){
        	// Подсчёт и обновление площади
        	update_max_submatrix(mx, upper_left, bottom_right,
                st.top().height * (width - st.top().index),
                width - 1, h, st.top().height, width - st.top().index);
            // Удаляем значения из стека
            st.pop();
        }
    }
    // Возвращаем пару точек, задающих подматрицу наибольшей площади,
    // начинающуюся как можно раньше сначала по строкам матрицы, а затем - по столбцам
    return Rectangle(upper_left, bottom_right);
}

