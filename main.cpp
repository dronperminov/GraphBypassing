#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

// структура для ребра графа
struct Edge {
	string v1; // начальная вершина
	string v2; // конечная вершина
};

// получение индекса строки в упорядоченном массиве
int indexOf(const vector<string> &vertexes, const string& vertex) {
	if (vertexes.size() == 0) // если массив пуст
		return -1; // то и элемента в нём нет

	// если искомый элемент левее минимального или правее максимального
	if (vertex < vertexes[0] || vertex > vertexes[vertexes.size() - 1])
		return -1; // то элемента нет

	int a = 0;
	int b = vertexes.size();

	// пока границы не сомкнутся
	while (a < b) {
		int mid = a + (b - a) / 2; // находим середину интервала поиска

		// если искомый элемент не правее центра
		if (vertex <= vertexes[mid]) {
			b = mid; // сдвигаем правую границу
		}
		else {
			a = mid + 1; // иначе сдвигаем левую границу
		}
	}

	return vertexes[b] == vertex ? b : -1; // если нашли, то возвращаем индекс, иначе -1
}

// обход в глубину, требует логический вектор посещённых вершин, изначально состоящий только из false
void dfs(vector<bool>& used, int **g, int n, int start, vector<string> &vertexes) {
	used[start] = true; // помещаем текущую вершину как посещённую
	cout << vertexes[start] << endl; // выводим вершину

	// проходим по всем вершинам
	for (int i = 0; i < n; i++) {
		if (g[start][i] != 0 && !used[i]) // если ребро есть и вершина не посещена
			dfs(used, g, n, i, vertexes); // посещаем её
	}
}

// обход в ширину
void bfs(vector<bool>& used, int **g, int n, int start, vector<string> &vertexes) {
	queue<int> q; // очередь непосещённых вершин данного уровня
	q.push(start); // заносим в очередь стартовую вершину

	used[start] = true; // помечаем её как посещённую

	cout << vertexes[start] << endl; // выводим её

	// пока очередь не опустеет
	while (!q.empty()) {
		int v = q.front(); // получаем очередную вершину
		q.pop(); // и удаляем её из очереди

		// проходи по всем вершинам
		for (int i = 0; i < n; i++) {
			if (g[v][i] != 0 && !used[i]) { // если ребро из v в i есть и вершина не была посещена 
				used[i] = true; // отмечаем её как посещённую
				q.push(i); // добавляем её в очередь
				cout << vertexes[i] << endl; // и выводим
			}
		}
	}
}

int main() {
	string type; // тип графа: 'd' - ориентированный, 'u' - неориентированный
	string start; // стартовая вершина
	string search; // тип поиска: 'd' - в глубину, 'b' - в ширину

	Edge edge; // ребро графа

	vector<Edge> edges; // вектор рёбер
	vector<string> vertexes; // вектор вершин
	vector<string> tmp; // вектор вершин

	cin >> type >> start >> search; // считываем тип графа, стартовую вершину и тип прохода

	// считываем рёбра графа
	while (cin >> edge.v1 >> edge.v2) {
		edges.push_back(edge); // добавляем в вектор рёбер очередное ребро

		tmp.push_back(edge.v1); // добавляем во временный вектор первую вершину
		tmp.push_back(edge.v2); // добавляем во временный вектор вторую вершину
	}

	sort(tmp.begin(), tmp.end()); // сортируем вершины

	vertexes.push_back(tmp[0]); // добавляем начальную вершину

	// проходимся по временному вектору и добавляем в вектор вершин толко уникальные
	for (size_t i = 1; i < tmp.size(); i++) 
		if (tmp[i] != tmp[i - 1]) // если не совпадает с предыдущей
			vertexes.push_back(tmp[i]); // то добавляем

	int n = vertexes.size(); // число вершин в графк
	int startIndex = indexOf(vertexes, start);

	// выделяем память под матрицу смежности
	int **matrix = new int*[n];

	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];

		for (int j = 0; j < n; j++)
			matrix[i][j] = 0; // обнуляем все значения в матрице
	}

	// проходи по всем рёбрам
	for (size_t i = 0; i < edges.size(); i++) {
		int v1 = indexOf(vertexes, edges[i].v1); // находим индекс начальной вершины
		int v2 = indexOf(vertexes, edges[i].v2); // находим индекс конечной вершины

		matrix[v1][v2] = 1; // проставляем 1 в матрице смежности для ребра v1-v2

		// если граф неориентированный
		if (type == "u")
			matrix[v2][v1] = 1;	// проставляем 1 в матрице смежности для ребра v2-v1
	}

	vector<bool> used(n, false); // вектор флагов посещённых вершин

	if (search == "d") {
		dfs(used, matrix, n, startIndex, vertexes); // запускам поиск в глубину
	}
	else {
		bfs(used, matrix, n, startIndex, vertexes); // запускаем поиск в ширину
	}

	// очищаем память из-под матрицы смежности
	for (int i = 0; i < n; i++)
		delete[] matrix[i];

	delete[] matrix;
}