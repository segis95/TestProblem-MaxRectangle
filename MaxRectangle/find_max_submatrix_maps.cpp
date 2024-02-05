#include "data_structures.h"
#include "find_max_submatrix_maps.h"

// updating max and maximal submatrix
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
	// Coords of max rectangle
	Point upper_left{}, bottom_right{};

	// Matrix height
    int height = (int)matrix.size();
    if (height == 0) return Rectangle(upper_left, bottom_right);

    // Matrix width
    int width = (int)matrix[0].size();

    // Maps storing max submatrix for each position
    // for each available width in previous line
    std::vector<std::map<int, int>> prev_line_maps(width);

    // Current series of sequential ones
    int curr_series = 0;

    // Currently known max area
    int mx = 0;

    // Filling Map array of the first string
    for (int w = 0; w < width; w++){
        if (matrix[0][w]){
            curr_series++;
            prev_line_maps[w][curr_series] = 1;

            // Updating the max area
            update_max_submatrix(mx, upper_left, bottom_right,
                            curr_series, w, 0, 1, curr_series);

         // if a zero found the current ones series is interrupted
        }else{curr_series = 0;}
    }
    // a new line map: length of ones series ending in a given position -> it's height
    std::map<int, int> curr_line_maps;
    // auxiliary variable
    int max_width = 0;

    // starting with line number one
    for (int h = 1; h < height; h++){
        curr_series = 0;
        for (int w = 0; w < width; w++){
        	// cleaning the map
            curr_line_maps.clear();

            if (matrix[h][w]){
                curr_series++;
                // updating area with current ones series
                update_max_submatrix(mx, upper_left, bottom_right,
                            curr_series, w, h, 1, curr_series);

                // at the moment the current series has depth of one
                curr_line_maps[curr_series] = 1;

                // checking different ones submatrices ending in the previous line
                // in current position and having different heights
                for (auto it = prev_line_maps[w].begin(); (it != prev_line_maps[w].end()); it++){
                	// current ones series may only extend a shorted or equal series 
                    max_width = std::min((it -> first), curr_series);

                    // the same series of consequent ones can extend preceding matrices of different 
                    // height; we select the one with max height
                    curr_line_maps[max_width] = std::max((it -> second) + 1, curr_line_maps[max_width]);

                    // updating max submatrix
                    update_max_submatrix(mx, upper_left, bottom_right, max_width * (curr_line_maps[max_width]),
                                         w, h, curr_line_maps[max_width], max_width);
                }
            // otherwise the current series is interrupted
            }else{curr_series = 0;}

            // passing to the new line
            prev_line_maps[w] = curr_line_maps;
        }
    }
    // Returning a submatrix of max area with smalles line number
    // and after that with smalles column number 
    return Rectangle(upper_left, bottom_right);
}
