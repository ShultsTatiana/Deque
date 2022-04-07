class DequeSized {
	size_t _capacity, _size;
	size_t _head, _tail;
	vector<int16_t> _data;

	//сложность - О(1)
	void turnRight(size_t& index) { //двигаем по часовой
		//% _capacity - следим, чтоб индекс не вылетал за пределы вектора с конца
		index = (index + 1) % _capacity;
	}
	//сложность - О(1)
	void turnLeft(size_t& index) { //двигаем против часовой
		index = (index + _capacity - 1) % _capacity;
	}
public:
	//инициализация дека имеет вычислительную сложность O(n) за счет 
	//тяжеловесной операции инициализации вектора _data под размер дека
	DequeSized(size_t max_size) :
		_capacity(max_size), _size(0), _head(0), _tail(0), _data(max_size, 0) {
	}
	ostream& push_back(int16_t x, ostream& out = std::cout) {
		if (_size == _capacity) { //проверка на преполнение дека
			out << "error" << endl;
			return out;
		}
		//хвост и головоа на одном индексе? Есть ли куда двигать голову?
		if (_tail == _head && _size + 1 < _capacity) {
			turnLeft(_head); //двигаем голову против часовой стрелки
		}
		_data[_tail] = x; //сложность - О(1) - запись данных в хвост дека
		turnRight(_tail);//сложность - О(1) - двигаем хвост
		++_size;	//увеличиваем размер дека
		return out;
	}
	ostream& push_front(int16_t x, ostream& out = std::cout) {
		if (_size == _capacity) { //проверка на преполнение дека
			out << "error" << endl;
			return out;
		}
		//хвост и головоа на одном индексе? Есть ли куда двигать хвост?
		if (_tail == _head && _size + 1 < _capacity) {
			turnRight(_tail); //двигаем хвост по часовой стрелке
		}
		_data[_head] = x; //сложность - О(1) - запись данных в голову дека
		turnLeft(_head); //сложность - О(1) - двигаем голову
		++_size;	//увеличиваем размер дека
		return out;
	}
	ostream& pop_front(ostream& out = std::cout) {
		if (_size == 0) { //дек пуст?
			out << "error" << endl;
			return out;
		}
		turnRight(_head); //сложность - О(1) - передвигаем голову
		//удалять данные нет смысла - они просто перезапишутся при вставке
		out << _data[_head] << endl; //сложность - О(1)
		--_size;	//уменьшаем размер дека
		return out;
	}
	ostream& pop_back(ostream& out = std::cout) {
		if (_size == 0) { //дек пуст?
			out << "error" << endl;
			return out;
		}
		turnLeft(_tail); //сложность - О(1) - передвигаем хвост
		//удалять данные нет смысла - они просто перезапишутся при вставке
		out << _data[_tail] << endl;
		--_size;	//уменьшаем размер дека
		return out;
	}
};

ostream& processingData(istream& input = std::cin, ostream& out = std::cout) {
	size_t comandCount(0);
	input >> comandCount; //считываем кол-во команд
	size_t dequeSize(0);
	input >> dequeSize; //считываем размер дека

	DequeSized Deque(dequeSize); //инициализируем дек
	string comand; //эта строка для команды

	for (size_t i(0); i < comandCount; ++i) {
		input >> comand; //считываем команду
		if (comand == "push_back") {
			int16_t element;
			input >> element; //считываем элемент для вставки
			Deque.push_back(element, out);
		}
		else if (comand == "push_front") {
			int16_t element;
			input >> element; //считываем элемент для вставки
			Deque.push_front(element, out);
		}
		else if (comand == "pop_front") {
			Deque.pop_front(out);
		}
		else if (comand == "pop_back") {
			Deque.pop_back(out);
		}
	}

	return out;
}

struct Test {
	string input;
	string expect;
};

void tests() {
	vector<Test> tests{
		{"4\n" "4\n"
		"push_front 861\npush_front -819\n"
			"pop_back\n" "pop_back\n",
			"861\n" 	 "-819\n"		},			//0
		{"7\n" "10\n"
		"push_front -855\npush_front 0\n"
			"pop_back\n" "pop_back\n" "push_back 844\n" "pop_back\n" "push_back 823\n",
			"-855\n"	 "0\n"							"844\n"	},			//1
		{"6\n" "6\n"
		"push_front -201\npush_back 959\npush_back 102\npush_front 20\n"
			"pop_front\n" "pop_back\n",
			"20\n"		  "102\n"	},	//2
		{"2\n" "6\n"
		"pop_back\n" "pop_front\n",
		"error\n"	 "error\n"	},	//3
		{"4\n" "2\n"
		"push_front 20\n""push_back 102\n""push_front 20\n""push_back 102\n",
										  "error\n" 	   "error\n"	},	//4
		{"8\n" "10\n"
		"push_front 1\npush_front 2\npush_front 3\npush_front 4\n"
			"pop_back\n" "pop_back\n" "pop_back\n" "pop_back\n",
			"1\n"	     "2\n"		  "3\n"		   "4\n"	},	//5
		{"8\n" "10\n"
		"push_back 1\npush_back 2\npush_back 3\npush_back 4\n"
			"pop_front\n" "pop_front\n" "pop_front\n" "pop_front\n",
			"1\n" 		  "2\n" 		"3\n" 		  "4\n"	},	//6
		{"8\n" "10\n"
		"push_back 1\npush_back 2\npush_back 3\npush_back 4\n"
			"pop_back\n" "pop_back\n" "pop_back\n" "pop_back\n",
			"4\n" 		 "3\n" 		  "2\n" 	   "1\n"	},	//7
		{"8\n" "10\n" 
		"push_front 1\npush_front 2\npush_front 3\npush_front 4\n"
			"pop_front\n" "pop_front\n" "pop_front\n" "pop_front\n",
			"4\n" 		  "3\n" 		"2\n" 		  "1\n"	},	//8
		{"8\n" "10\n" 
		"push_front 1\npush_front 2\npush_back 3\npush_back 4\n" 
			"pop_front\n" "pop_front\n" "pop_front\n" "pop_front\n",
			"2\n" 		  "1\n" 		"3\n" 		  "4\n"	},	//9
		{"8\n" "10\n" 
		"push_back 1\npush_back 2\npush_front 3\npush_front 4\n" 
			"pop_back\n" "pop_back\n" "pop_back\n" "pop_back\n",
			"2\n" 		 "1\n" 		  "3\n" 	   "4\n"	},	//10
		{"8\n" "3\n" 
		"push_back 1\npush_back 2\npush_back 3\n" 
			"pop_front\n" "push_back 4\n" "pop_front\n" "pop_front\n" "pop_front\n",
			"1\n" 						  "2\n" 		"3\n" 		  "4\n"	},	//11
	};

	size_t failCounter(0), line(0);
	for (Test test : tests) {
		stringstream input(move(test.input));
		stringstream out;

		processingData(input, out);
		string strOutput = out.str();

		if (strOutput != test.expect) {
			++failCounter;
			std::cout << "Test in " << line << "\tis\t" <<
				strOutput << "!= " << test.expect << endl;
		}
		++line;
	}
	std::cout << (failCounter == 0 ? "All tests is Ok\n" : "FAIL\n");
}

int main()
{
	tests();

	processingData();

	return 0;
}
