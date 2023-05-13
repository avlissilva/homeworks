#include <iostream>
#include <string>
#include <memory>
#include <exception>


class Cell {
	private:
		std::string m_value;

	public:
		void set_value (const int& value) {
			m_value = std::to_string(value);
		}

		void set_value (const double& value) {
			m_value = std::to_string(value);
		}

		void set_value (std::string value) {
			m_value = value;
		}

		int to_int () {
			try {
				return std::stoi(m_value);
			} catch (std::invalid_argument& exp) {
				throw std::runtime_error("Invalid argument");
			} catch (std::out_of_range& exp) {
			       throw std::runtime_error("Out of range");
			}
		}
		

		double to_double () {
			try {
				return std::stod(m_value);
			} catch (std::invalid_argument& exp) {
				throw std::runtime_error ("Invalid argument");
			} catch (std::out_of_range& exp) {
				throw std::runtime_error ("Out of range");
			}
		}

		std::string to_str () {
			return m_value;
		}

		std::string get_value() {
			return m_value;
		}
};




class Spreadsheet {
	private:
		Cell** m_cells;
		size_t m_row;
		size_t m_column;

	protected:

		 bool check_range(const int& row, const int& column) {
                         if (row < 0 || row >= m_row || column < 0 || column >= m_column) {
                                 std::cerr << "Out of Spreadsheet range." << std::endl;
                                 return false;
                         }
                         return true;
                  }
			
		 void copy (Cell** tmp) {
			 for (size_t i = 0; i < m_row; ++i) {
				 for (size_t j = 0; j < m_column; ++j) {
					 tmp[i][j] = m_cells[i][j];
				 }
			 }
		 }

		void free_mem () {
			for (size_t i = 0; i < m_row; ++i) {
				delete [] m_cells[i];
			}
			delete [] m_cells;
			m_cells = nullptr;
		}

  

	public:
		Spreadsheet (const int& row, const int& column) {
			m_row = row;
			m_column = column;
			m_cells = new Cell* [row];
			for (size_t i = 0; i < row; ++i) {
				m_cells[i] = new Cell [column];
			}
		}	


		~Spreadsheet() {
			free_mem ();
		}
		

		void set_cell_at (const int& row, const int& column, std::string str) { 
			if (check_range(row, column)) {
				m_cells[row][column].set_value(str);
			}
		}


		void set_cell_at (const int& row, const int& column, Cell* ptr) {
			if (check_range(row, column)) {
				m_cells[row][column].set_value(ptr->to_str());
			}
		}


		Cell get_cell_at ( const int& row, const int& column) {
			if (check_range(row, column)) {
		       		return m_cells[row][column];
			}
			throw std::out_of_range ("Out of range");
		}	

		
		void add_row (const int& adder) {
			Cell** tmp = new Cell* [m_row + adder];
	       		for(size_t i = 0; i < m_row + adder; ++i) {
		 		tmp[i] = new Cell [m_column];
			}
			copy(tmp);
			free_mem();
			m_cells = tmp;
			tmp = nullptr;
			m_row += adder;
		}

			

		void add_column (const int& adder) {
			Cell** tmp = new Cell* [m_row];
			for (size_t i = 0; i < m_row; ++i) {
				tmp[i] = new Cell [m_column + adder];
			}

			copy(tmp);
			free_mem();
			m_cells = tmp;
			tmp = nullptr;
			m_column += adder;
		}

};

