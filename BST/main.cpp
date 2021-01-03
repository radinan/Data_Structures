#include <iostream>
#include "AVLTree.h"

int main()
{
	AVL<int> roo;
	roo.insert(50);
	roo.insert(30);
	roo.insert(20);
	roo.insert(40);
	roo.insert(70);
	roo.insert(60);
	roo.insert(80);

	std::cout << "Inorder traversal\n";
	roo.inorder();

	std::cout << "\nremove 20\n";
	roo.remove(20);
	std::cout << "Inorder traversal\n";
	roo.inorder();

	std::cout << "\nremove 80\n";
	roo.remove(80);
	std::cout << "Inorder traversal\n";
	roo.inorder();

	std::cout << "\nremove 50\n";
	roo.remove(50);
	std::cout << "Inorder traversal\n";
	roo.inorder();
  
  std::cout << "\nsearch "40"\n";
	std::cout << std::endl << roo.search(40)->data;

	return 0;
}
