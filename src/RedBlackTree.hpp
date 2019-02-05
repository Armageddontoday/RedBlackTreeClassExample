#include <stdio.h> 
#include <stdint.h> //for uint64_t

class RedBlackTree {
//перечисление под цвета
enum Color { black, red };
enum Side { left, right };

struct treeNode
{
	treeNode *parent = NULL;
	uint64_t data = 0;
	int count = 1;
	Color color;
	treeNode *left_child = NULL;
	treeNode *right_child = NULL;
	bool is_leaf = false;
};

treeNode *ROOT = NULL;

//создание чёрного листа-тупика
treeNode *CreateLeaf(treeNode *parent);
//при первом числе идёт создание корня
void CreateRoot(int number);
//создание новой ноды красного цвета
treeNode * CreateRed(treeNode *parent, uint64_t number);
//вращение вправо, node опускается в структуре дерева, в left-тоже самое
void RotateRight(treeNode *node, bool last_rotate);
void RotateLeft(treeNode *node, bool last_rotate);
//показать крайнюю ветку, side- left/right
void PrintBranch(Side side);
//перекрас родителя, дяди  и деда
void Recolor(treeNode* rec_node);
//проверка является ли нода левым потомком
bool IsLeftChild(treeNode *node);
//проверка красный ли брат ноды- предка
bool UncleIsRed(treeNode *node);
//проверка дерева на конфликты red-red
void CheckTree(treeNode* ch_node);

// public:
//поиск и добавление элементов в дерево
void Insert(uint64_t ins_data);
/*
//запись ноды в файл
void WriteNodeToFile(FILE *file, treeNode *curr_node);
//запись дерева в файл
void WriteTreeToFile();
*/
};