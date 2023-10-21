#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <Windows.h>

using namespace std;

// Структура данных для хранения ребра Graph
struct Node {
    int src, dest, weight;
    Node(int src, int dest, int weight) :src(src), dest(dest), weight(weight) {}
};

struct compare
{
    bool operator() (Node const& a, Node const& b) const {
        return a.weight > b.weight;
    }
};

typedef pair<int, int> Pair;

// Класс для представления graphического объекта
class Graph
{
public:
    // вектор векторов Pair для представления списка смежности
    vector<vector<Pair>> nodeArray;
    unordered_map<int, int> parent;
    vector<Node> nodes;

    Graph(){}

    // Конструктор Graphа
    Graph(vector<Node> const& nod, int n)
    {
        // изменить размер вектора, чтобы он содержал `n` элементов типа vector<Edge>
        nodeArray.resize(n);

        // добавляем ребра в ориентированный graph
        for (auto& node : nod)
        {
            int src = node.src;
            int dest = node.dest;
            int weight = node.weight;

            // вставляем в конце
            nodeArray[src].push_back(make_pair(dest, weight));

            // раскомментируйте следующий код для неориентированного Graph
            // adjList[dest].push_back(make_pair(src, weight));
        }

        nodes = nod;
    }

    void makeSet(int n)
    {
        // создаем `n` непересекающихся наборов (по одному на каждую вершину)
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Находим корень множества, которому принадлежит элемент `k`
    int Find(int k)
    {
        // если `k` это корень
        if (parent[k] == k) {
            return k;
        }

        // повторяем для родителя, пока не найдем корень
        return Find(parent[k]);
    }

    // Выполняем объединение двух подмножеств
    void Union(int a, int b)
    {
        // найти корень множеств, в которых элементы
        // `x` и `y` принадлежат
        int x = Find(a);
        int y = Find(b);

        parent[x] = y;
    }

    // Функция для печати представления списка смежности Graph
    void printGraph()
    {
        for (int i = 0; i < nodeArray.size(); i++)
        {
            // Функция для печати всех соседних вершин данной вершины
            for (Pair v : nodeArray[i]) {
                cout << "(" << i << ", " << v.first << ", " << v.second << ") ";
            }
            cout << endl;
        }
    }

    // Функция построения MST с использованием алгоритма Крускала
    void runKruskalAlgorithm()        // без ссылки, без константы
    {
        // сохраняет ребра, присутствующие в MST
        vector<Node> MST;

        // инициализируем класс `DisjointSet`
        Graph ds;

        // создаем одноэлементный набор для каждого элемента вселенной
        ds.makeSet(nodes.size());

        // сортируем ребра по возрастанию веса
        sort(nodes.begin(), nodes.end(), compare());

        // MST содержит ровно `V-1` ребер
        while (MST.size() != nodes.size() - 1)
        {
            // рассмотрим следующее ребро с минимальным весом из Graph
            Node next_edge = nodes.back();
            nodes.pop_back();

            // находим корень множеств, к которым две конечные точки
            // вершины следующего ребра принадлежат
            int x = ds.Find(next_edge.src);
            int y = ds.Find(next_edge.dest);

            // если обе конечные точки имеют разных родителей, они принадлежат
            // различные связанные компоненты и могут быть включены в MST
            if (x != y)
            {
                MST.push_back(next_edge);
                ds.Union(x, y);
            }
        }
        nodes = MST;
    }

    void printostGraph() {
        for (Node& node : nodes)
        {
            cout << "(" << node.src << ", " << node.dest << ", "
                << node.weight << ")" << endl;
        }
    }
};

Graph constGraph;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Создать граф по варианту или самостоятельно? (1-по варианту/2-самостоятельно) ";
    int n, x, y, w;
    cin >> n;
    switch (n){
    case 1: {
        // vector ребер Graph согласно схеме варианта.
        vector<Node> nodes =
        {
            // (x, y, w) —> ребро от `x` до `y` с весом `w`
            {1, 2, 1}, {1, 3, 2}, {1, 5, 10},
            {2, 4, 3}, {2, 5, 6},
            {3, 4, 4}, {3, 5, 7},
            {4, 5, 11}
        };

        // общее количество узлов в Graph (от 0 до 5)
        n = nodes.size();

        // построить Graph
        Graph graph(nodes, n);

        constGraph = graph;
        break;
    }
    case 2: {
        vector<Node> edges;
        cout << "Введите узел в формате: (x, y, w) —> ребро от `x` до `y` с весом `w`" << endl;
        cout << "Если хотите остановить постройку графа введите три отрицательных числа." << endl;
        cin >> x >> y >> w;
        while (x < 0 || y < 0 || w < 0) {
            Node node(x, y, w);
            edges.push_back(node);
            system("cls");
            cout << "Введите узел в формате: (x, y, w) —> ребро от `x` до `y` с весом `w`" << endl;
            cout << "Если хотите остановить постройку графа введите три отрицательных числа." << endl;
            cin >> x >> y >> w;
        }

        // общее количество узлов в Graph (от 0 до 5)
        n = edges.size();

        // построить Graph
        Graph graph(edges, n);

        constGraph = graph;
        break;
    }
    default:
        break;
    }

    cout << "Выберете команду: 1-Вывести граф, 2-создать оставной граф, 3-вывести оставный граф, 4-закончить выполнение программы " << endl;
    cin >> n;

    while (true) {
        switch (n){
        case 1:
            // вывести представление списка смежности Graph
            constGraph.printGraph();
            break;
        case 2:
            constGraph.runKruskalAlgorithm();
            break;
        case 3:
            constGraph.printostGraph();
            break;
        case 4:
            exit(0);
        default:
            break;
        }
        cout << "Хотите очистить консоль? (1-Да/2-Нет)" << endl;
        cin >> n;
        if (n == 1)
            system("cls");
        cout << "Выберете команду: 1-Вывести граф, 2-создать оставной граф, 3-вывести оставный граф, 4-закончить выполнение программы" << endl;
        cin >> n;
    }
    return 0;
}