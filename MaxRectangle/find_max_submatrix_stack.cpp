#include "find_max_submatrix_stack.h"
#include "data_structures.h"

// <line position, ones column height above this position>
struct Pile{
    int index;
    int height;

    explicit Pile(int ind, int h){
        index = ind;
        height = h;
    }
};


Rectangle find_max_submatrix_stack(std::vector<std::vector<bool>>& matrix){
    // Coords of max rectangle
	Point upper_left{}, bottom_right{};

	// Matrix height
    int height = (int)matrix.size();
    if (height == 0) return Rectangle(upper_left, bottom_right);

    // Matrix width
    int width = (int)matrix[0].size();

    // The count of ones over each position in a line;
    // calculated for each new line
    std::vector<int> current_height(width, 0);

    // Stack storing records of type:
    // <line position, ones heights over this position>
    std::stack<Pile> st;

    // Currently known max area and column id of previous Pile not superior to
    // the actual one
    int mx = 0, last_available_idx = 0;

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
        	// we recalculate the Pile for position w based on it's value in previous line
            current_height[w] = matrix[h][w] ? current_height[w] + 1 : 0;

            // we aim to find a stack position having no more ones above it 
            // than the current position
            last_available_idx = w;

            // We remove from the stack all Piles greater than current_height[w]
            // Example:
            //
            //		|
            //    	|   |
            //	  	|   |	|				  |
            //	| 	|	|	|    ---->    |	  |
            //	|	|	|	|			  |	  |
            // id1 id2 id3	w            id1 id2
            //
            // In this example the earliest available position having at max current_height[w]
            // ones above it is id2.
            //
            // When removing a Pile from stack we account for the area of ones to the right until w-1;
            // because current_height[w] is inferior to the the Pile's height, the submatrix
            // started in last_available_idx of the Pile's height cannot be continued after w

            while((!st.empty()) && (st.top().height > current_height[w])){
                // position of Pile to pop from stack
            	last_available_idx = st.top().index;

                // updating max area for removed Pile
            	update_max_submatrix(mx, upper_left, bottom_right,
                    st.top().height * (w - last_available_idx),
                    w - 1, h, st.top().height, w - last_available_idx);

                // removing a pile
                st.pop();
            }
            // After piles removal we create a new pile for position last_available_idx 
            // and height of current_height[w];
            // In case there was no Pile left to w higher than w we simply add to stack a new Pile
            // for the position w
            st.push(Pile(last_available_idx, current_height[w]));
        }

        // If at the end stack is not empty and contains a monotonous sequence of piles
        // each of those pile start a submatrix lasting until the end of line;
        // we update the max area with these submatrices
        if (st.empty()) continue;
        while(!st.empty()){
        	// updating max area
        	update_max_submatrix(mx, upper_left, bottom_right,
                st.top().height * (width - st.top().index),
                width - 1, h, st.top().height, width - st.top().index);
            // removing from stack
            st.pop();
        }
    }
    // Returning a submatrix of max area with smalles line number
    // and after that with smalles column number 
    return Rectangle(upper_left, bottom_right);
}

