#include <iostream>
#include <vector>

using namespace std;

vector<int> convo1d(vector<int>& input, vector<int>& response) {
	size_t input_size = input.size();
	size_t response_size = response.size();
	vector<int> result;
	for (size_t i = 0; i <= input_size; ++i) {
		int y = 0;
		for (size_t j = 0; j <= i; ++j) {
			size_t response_index = i - j;
			if (response_index < 0 or response_index >= response_size or j >= input_size) { continue; }

			y += input[j] * response[response_index];
		}
		result.push_back(y);

	}
	return result;
}

vector<vector<int>> convo2d(vector<vector<int>>& input, vector<vector<int>>& kernel, int input_row, int input_col, int kernel_row, int kernel_col) {

	vector<vector<int>> result;
	int counter = 0;
	for (int i = kernel_row / 2; i <= input_row - kernel_row / 2 - 1; ++i) {
		vector<int> temp;
		for (int j = kernel_col / 2; j <= input_row - kernel_col / 2 - 1; ++j) {
			int sum = 0;


			for (int k = 0; k < kernel_row; ++k) {
				size_t kernel_row_iterator = kernel_row - 1 - k;

				for (int l = 0; l < kernel_col; ++l) {
					size_t kernel_col_iterator = kernel_col - 1 - l;

					size_t ii = i + (kernel_row / 2 - kernel_row_iterator);
					size_t jj = i + (kernel_col / 2 - kernel_col_iterator);

					if (ii >= 0 and ii < input_row and jj >= 0 and jj < input_col) {
						int multiply = input[ii][jj] * kernel[kernel_row_iterator][kernel_col_iterator];
						cout << input[ii][jj] << " * " << kernel[kernel_row_iterator][kernel_col_iterator] << " = " << multiply << endl;
						sum += multiply;
					}
				}
			}
			temp.push_back(sum);
		}
		result.push_back(temp);
	}
	return result;
}

int main() {
	vector<int> input{ 3, 4, 5 };
	vector<int> response{ 2, 1, 1, 0 };

	vector<int> output = convo1d(input, response);

	for (auto& i : output) {
		cout << i << endl;
	}

	vector < vector<int>> input2d{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	vector < vector<int>> kernel2d{
		{-1, -2, -1},
		{0, 0, 0},
		{1, 2, 1}
	};

	vector<vector<int>> res = convo2d(input2d, kernel2d, 3, 3, 3, 3);


	for (int i = 0; i < res.size(); ++i) {
		for (int j = 0; j < res[i].size(); ++j) {
			cout << res[i][j] << " ";
		}
		cout << endl;
	}

	return 0;

}


