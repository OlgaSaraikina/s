#include <iostream>

using namespace std;

int field[100][100];
// -1 мина
// 0-8 счетчик мин
int field_p[100][100];
// -2 не открыта клетка
// -1 это флаг
// 0-8 счетчик мин

const int N = 5, M = 5, K = 5;

void print_f() {
	system("cls");
	//вывод координат на доске
	cout << "  ";
	for (int i = 0; i < M; i++) {
		cout << " " << i + 1;
		if (i + 1 < 10) cout << ' ';
	}
	cout << endl;
	for (int i = 0; i < N; i++) {
		cout << i + 1 << " ";
		if (i + 1 < 10) cout << ' ';
	//поле игрока
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] == -2) cout << "_  ";
			else if (field_p[i][j] == -1) cout << "f  ";
			else if (field_p[i][j] == -3) cout << "*  ";
			else cout << field_p[i][j] << "  ";
		}
		cout << endl;
	}
}

void dfs(int x, int y) {
	if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] > -2) return;
	field_p[x][y] = field[x][y];
	if (field[x][y] > 0) return;
	for (int i2 = x - 1; i2 <= x + 1; ++i2) {
		for (int j2 = y - 1; j2 <= y + 1; ++j2) {
			if (i2 != x || j2 != y) dfs(i2, j2);
		}
	}
}

// true - ne vsriv
bool open_cell(int x, int y) {
	if (field[x][y] == -1) return false;
	if (field[x][y] > 0) {
		field_p[x][y] = field[x][y];
		return true;
	}
	dfs(x, y);
}

bool is_win() {
	int opened = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] >= 0) opened++;
		}
	}
	return (N * M - K == opened);
}

void end_g(bool is_win = false) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] == -1) field_p[i][j] == -2;
			if (field[i][j] == -1) field_p[i][j] = -3;
		}
	}
	print_f();
	cout << (is_win ? "Win" : "Game over!") << "\nRestsrt lubay stroka:\n";
	string s;
	cin >> s;
}

int main()
{
	while (true) {
		srand(time(0));
		//создание оновного поля
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				field[i][j] = 0;
				field_p[i][j] = -2;
			}
		}
		//генерация мин
		for (int i = 0; i < K; ++i) {
			while (true) {
				int x = rand() % N;
				int y = rand() % M;
				if (field[x][y] != -1) {
					field[x][y] = -1;
					break;
				}
			}
		}
		//счетчик мин
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (field[i][j] != -1) {
					field[i][j] = 0;
					for (int i2 = i - 1; i2 <= i + 1; ++i2) {
						for (int j2 = j - 1; j2 <= j + 1; ++j2) {
							if (i2 >= 0 && i2 < N && j2 >= 0 && j2 < M &&
								field[i2][j2] == -1) ++field[i][j];
						}
					}
				}
			}
		}
		//реализация ходов
		while (true) {
			print_f();
			cout << "vidite comand";
			/*
			\o x y открыть клетку open
			\f x y поставить флаг flag
			\n начало новой игрв restart
			\g завершение игры end
			*/
			string comand;
			cin >> comand;
			if (comand == "\\o") {
				//vvod koordinat
				int x, y;
				cin >> x >> y;
				--x; --y;
				//otkroem kletki
				if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) continue;
				if (!open_cell(x, y)) {
					end_g();
						break;
				}
				//проверка на выиграш 
				if (is_win()) {
					end_g(true);
					break;
				}
			}
			else if (comand == "\\f") {
				//vvod koordinat
				int x, y;
				cin >> x >> y;
				--x; --y;
				if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) continue;
				if (field_p[x][y] == -1) field_p[x][y] = -2;
				else field_p[x][y] = -1;
			}
			else if (comand == "\\n") {
				break;
			}
			else if (comand == "\\g") {
				return 0;
			}
		}
	}
}