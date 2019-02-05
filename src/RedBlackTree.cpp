#include "RedBlackTree.hpp"
#include <math.h>

// treeNode *ROOT = NULL;

RedBlackTree::treeNode * RedBlackTree::CreateLeaf(treeNode *parent)
{
	treeNode *leaf = new treeNode;
	leaf->color = black;
	leaf->is_leaf = true;
	leaf->parent = parent;
	return leaf;
}

void RedBlackTree::CreateRoot(int number)
{
	ROOT = new treeNode;
	ROOT->data = number;
	ROOT->color = black;
	ROOT->left_child = CreateLeaf(ROOT);
	ROOT->right_child = CreateLeaf(ROOT);
	ROOT->parent = NULL;
}

RedBlackTree::treeNode * RedBlackTree::CreateRed(treeNode *parent, uint64_t number)
{
	treeNode *unit = new treeNode;
	unit->data = number;
	unit->color = red;
	unit->parent = parent;
	unit->left_child = CreateLeaf(unit);
	unit->right_child = CreateLeaf(unit);
	return unit;
}

void RedBlackTree::RotateRight(treeNode *node, bool last_rotate)
{
	//шаги I-V указаны и проиллюстрированы в отчёте
	treeNode *point = node->left_child;
	//printf("RIGHT rotate, node:%d point:%d\n", node->data, point->data);
	//I переопределяем правого сына p как левого n
	node->left_child = point->right_child;
	node->left_child->parent = node;
	//II переопределяем предка p, если его нет, то p становится корнем
	point->parent = node->parent;
	if (point->parent == NULL)	ROOT = point;
	//III переопределяем n как правого сына p
	point->right_child = node;
	//IV переопределяем p как предка n
	node->parent = point;
	//V переопределяем потомка предка p, если он есть
	if (point->parent != NULL)
	{
		if (point->parent->left_child == node)point->parent->left_child = point;
		else point->parent->right_child = point;
	}
	if (last_rotate)
	{
		point->color = black;
		if (!point->left_child->is_leaf)point->left_child->color = red;
		if (!point->right_child->is_leaf)point->right_child->color = red;
	}
	//printf("done\n");
}

void RedBlackTree::RotateLeft(treeNode *node, bool last_rotate)
{
	//шаги I-V указаны и проиллюстрированы в отчёте
	treeNode *point = node->right_child;
	//printf("LEFT rotate, node:%d point:%d\n", node->data, point->data);
	//I переопределяем левого сына p как правого n
	node->right_child = point->left_child;
	node->right_child->parent = node;
	//II переопределяем предка p, если его нет, то p становится корнем
	point->parent = node->parent;
	if (point->parent == NULL)	ROOT = point;
	//III переопределяем n как левого сына p
	point->left_child = node;
	//IV переопределяем p как предка n
	node->parent = point;
	//V переопределяем потомка предка p, если он есть
	if (point->parent != NULL)
	{
		if (point->parent->left_child == node)point->parent->left_child = point;
		else point->parent->right_child = point;
	}
	if (last_rotate)
	{
		point->color = black;
		if (!point->left_child->is_leaf)point->left_child->color = red;
		if (!point->right_child->is_leaf)point->right_child->color = red;
	}
	//printf("done\n");
}

void RedBlackTree::PrintBranch(RedBlackTree::Side side)
{
	if (side == right)printf("====R====\n");
	else printf("====L====\n");
	treeNode *pointer = ROOT;
	while (!pointer->is_leaf)
	{
		printf("parent:\n     %ld - ", pointer->data);
		if (pointer->color == red)printf("(RE)\n");
		else printf("(BL)\n");
		if (pointer->left_child->is_leaf)printf("NULL       ");
		else
		{
			printf("L");
			if (pointer->left_child->color == red)printf("(RE)");
			else printf("(BL)");
			printf(":%ld  ", pointer->left_child->data);
		}
		if (pointer->right_child->is_leaf)printf("NULL\n");
		else
		{
			printf("R");// :%d\n", k->right_child->num);
			if (pointer->right_child->color == red)printf("(RE)");
			else printf("(BL)");
			printf(":%ld  \n", pointer->right_child->data);

		}
		if (side == right)pointer = pointer->right_child;
		else pointer = pointer->left_child;
	}
	printf("========\n");
}

void RedBlackTree::Recolor(treeNode* rec_node)
{
	treeNode *pointer = rec_node->parent;
	pointer->color = black;
	pointer = pointer->parent;
	if (pointer == ROOT)pointer->color = black;
	else pointer->color = red;
	if (pointer->left_child == rec_node->parent)pointer = pointer->right_child;
	else pointer = pointer->left_child;
	pointer->color = black;
}

bool RedBlackTree::IsLeftChild(treeNode *node)
{
	treeNode *pointer = node->parent;
	if (pointer->left_child == node)return true;
	return false;
}

bool RedBlackTree::UncleIsRed(treeNode *node)
{
	treeNode *pointer = node->parent->parent;
	if (pointer->left_child == node->parent)pointer = pointer->right_child;
	else pointer = pointer->left_child;
	//printf("uncle:%d ", pointer->data);
	//if (pointer->color == red)printf("RE\n");
	//else printf("BL\n");
	if (pointer->color == red)return true;
	return false;
}

void RedBlackTree::CheckTree(treeNode* ch_node)
{
	//printf("\n=====\n");
	//if(ch_node->is_leaf)printf("enterd check, node:NULL\nROOT:%d\n", ch_node->data, ROOT->data);
	//else printf("enterd check, node:%d\nROOT:%d\n", ch_node->data, ROOT->data);
	//printf("checing NODE parent:%d\n", ch_node->parent->data);
	treeNode *pointer = ch_node;
	while (pointer != ROOT)
	{
		//printf("check step, node:%d, parent:%d ", pointer->data, pointer->parent->data);
		//if (pointer->parent->color == red)printf("RE\n");
		//else printf("BL\n");
		if (pointer->color == red && pointer->parent->color == red)
		{
			//printf("red-red situation: node %d ->parent:%d\n", pointer->data,pointer->parent->data);
			if (UncleIsRed(pointer))
			{

				if (pointer->parent->parent == ROOT)
				{
					//printf("no root Recolor\n");
					Recolor(pointer);
				}
				else
				{
					//printf("Recolor &check\n");
					Recolor(pointer);
				}
			}
			else//если дядя всё таки не красный
			{
				if (IsLeftChild(pointer))//если нода- левый потомок
				{
					if (IsLeftChild(pointer->parent))//если её предок- левый потомок
					{
						//printf("LL:\n");
						RotateRight(pointer->parent->parent, 1);
						//CheckTree(pointer->left_child);
						//if (pointer == ROOT)return;
						pointer = pointer->right_child;
					}
					else//если её предок- правый потомок
					{
						//printf("LR:\n");
						RotateRight(pointer->parent, 0);
						RotateLeft(pointer->parent, 1);
						pointer = pointer->right_child;
					}
				}
				else//если нода- правый потомок
				{
					//printf("RL:\n");
					if (IsLeftChild(pointer->parent))//если её предок- левый потомок
					{

						RotateLeft(pointer->parent, 0);
						RotateRight(pointer->parent, 1);
						//CheckTree(pointer->left_child);
						//if (pointer == ROOT)return;
						//printf("pointer:%d\n", pointer->data);
						pointer = pointer->left_child;
						//printf("ololo\n");
						//printf("pointer:%d\n", pointer->data);
						//printf("RR:\n");
					}
					else//если её предок- правый потомок
					{
						RotateLeft(pointer->parent->parent, 1);
						//CheckTree(pointer->left_child);
						//if (pointer == ROOT)return;
						pointer = pointer->left_child;
					}
				}
			}
		}
		pointer = pointer->parent;
	}
	//printf("=====\n");
}

void RedBlackTree::Insert(uint64_t ins_data)
{
	//printf("inserting %d\n", ins_data);
	treeNode *pointer = ROOT;
	if (pointer == NULL)
	{
		CreateRoot(ins_data);
		return;
	}
	while (pointer != NULL)
	{
		if (pointer->data == ins_data)
		{
			pointer->count++;
			return;
		}
		if (ins_data < pointer->data)
		{
			if (!pointer->left_child->is_leaf)pointer = pointer->left_child;
			else
			{
				pointer->left_child = CreateRed(pointer, ins_data);
				//printf("added as left son of %d\n", pointer->data);
				CheckTree(pointer->left_child);
				return;
			}

		}
		else
		{
			if (!pointer->right_child->is_leaf)pointer = pointer->right_child;
			else
			{
				pointer->right_child = CreateRed(pointer, ins_data);
				//printf("added as right son of %d\n", pointer->data);
				CheckTree(pointer->right_child);
				return;
			}

		}
	}
}
/*
void RedBlackTree::WriteNodeToFile(FILE *file, treeNode *curr_node)
{
	if (!curr_node->left_child->is_leaf)WriteNodeToFile(file, curr_node->left_child);
	if (!curr_node->right_child->is_leaf)WriteNodeToFile(file, curr_node->right_child);
	fputs("0x", file);
	char string[100];
	//ui64toa_s(curr_node->data, string, 100, 16);
	//if(strlen(string))printf("%s\n", string);
	fputs(string, file);
	fputs("|", file);
	//ui64toa_s(curr_node->data, string, 100, 10);
	fputs(string, file);
	fputs("  count:", file);
	//ui64toa_s(curr_node->count, string, 100, 10);
	fputs(string, file);
	fputs("\n", file);
	curr_node->is_leaf = true;
}

void RedBlackTree::WriteTreeToFile()
{
	FILE* result_file;
	result_file = fopen("result.txt", "w");
	if (ROOT == NULL)
	{
		fputs("no nums found", result_file);
	}
	else WriteNodeToFile(result_file, ROOT);
	fclose(result_file);
}
*/