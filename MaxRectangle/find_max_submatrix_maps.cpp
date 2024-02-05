#include "data_structures.h"
#include "find_max_submatrix_maps.h"

// функци€ дл€ обновлени€ максимума и максимальной подматрицы
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
	//  оординаты левого верхнего и правого нижнего углов
	Point upper_left{}, bottom_right{};

	// ¬ысота матрицы
    int height = (int)matrix.size();
    if (height == 0) return Rectangle(upper_left, bottom_right);

    // Ўирина матрицы
    int width = (int)matrix[0].size();

    // —ловари дл€ хранени€ максимальных подматриц каждой доступной ширины
    // в предыдущей строке
    std::vector<std::map<int, int>> prev_line_maps(width);

    // “екуща€ сери€ порд€д идущих единиц в строке
    int curr_series = 0;

    // “екущий известный максимум площади
    int mx = 0;

    // «аполн€ем массив словарей первой строки
    for (int w = 0; w < width; w++){
        if (matrix[0][w]){
            curr_series++;
            prev_line_maps[w][curr_series] = 1;

            // ѕодсчЄт и обновление максимальной площади
            update_max_submatrix(mx, upper_left, bottom_right,
                            curr_series, w, 0, 1, curr_series);

         // если найден нуль, сери€ единиц прерываетс€
        }else{curr_series = 0;}
    }
    // словарь дл€ новой строки
    std::map<int, int> curr_line_maps;
    // вспомогательна€ переменна€
    int max_width = 0;

    // начинаем проход уже с первой строки
    for (int h = 1; h < height; h++){
        curr_series = 0;
        for (int w = 0; w < width; w++){
        	// очищаем словарь
            curr_line_maps.clear();

            if (matrix[h][w]){
                curr_series++;
                // обновл€ем площадь площадью текущей серии единиц
                update_max_submatrix(mx, upper_left, bottom_right,
                            curr_series, w, h, 1, curr_series);

                // в данный момент серии единиц соответствует максимальна€ глубина 1
                curr_line_maps[curr_series] = 1;

                // проход по словарю данной позиции в предыдущей строке
                for (auto it = prev_line_maps[w].begin(); (it != prev_line_maps[w].end()); it++){
                	// текуща€ сери€ единиц может лишь продлить серию, не превосход€щую по длине себ€
                    max_width = std::min((it -> first), curr_series);

                    // одна и той же сери€ подр€д идущих единиц в строке может продлить предшествующие
                    // подматрицы различной глубины; необходимо выбрать среди них наибольшую
                    curr_line_maps[max_width] = std::max((it -> second) + 1, curr_line_maps[max_width]);

                    // обновл€ем максимум
                    update_max_submatrix(mx, upper_left, bottom_right, max_width * (curr_line_maps[max_width]),
                                         w, h, curr_line_maps[max_width], max_width);
                }
            // иначе сери€ единиц прерываетс€
            }else{curr_series = 0;}

            // переходим к новой строке
            prev_line_maps[w] = curr_line_maps;
        }
    }
    // ¬озвращаем пару точек, задающих подматрицу наибольшей площади,
    // начинающуюс€ как можно раньше сначала по строкам матрицы, а затем - по столбцам
    return Rectangle(upper_left, bottom_right);
}
