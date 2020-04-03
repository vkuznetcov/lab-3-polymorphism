#include "libutils/image.h"
#include "libutils/io.h"
#include "shared_ptr.h"
#include "unique_ptr.h"
#include "list.h"
#include "vector.h"
#include <iostream>
#include <list>
#include <vector>
#include <memory>
using namespace std;
template <class T> using UniquePtrType = UniquePtr<T>;
template <class T> using SharedPtrType = SharedPtr<T>;
template <class T> using CollectionType = List<T>;

void mainMenu() {
	cout << "Choose function:" << endl;
	cout << "1. Add element in collection;" << endl;
	cout << "2. Remove element from collection;" << endl;
	cout << "3. Clear collection;" << endl;
	cout << "4. Get size of collection;" << endl;
	cout << "5. Edit collection;" << endl;
	cout << "6. Print elements of collection;" << endl;
	cout << "7. Add node in collection of SharedPtrTypes (on one object);" << endl;
	cout << "0. Exit program;" << endl;
}

template <typename T>
void addElement(CollectionType<T>& c, const int& index, const T& value) {
	auto iterator = c.begin();

	if (c.empty()) {
		c.insert(iterator, value);
		return;
	}
	else {
		for (int i = 0; i < index; ++i)
			++iterator;
		c.insert(iterator, value);
		return;
	}
}

void removeElement(CollectionType<double>& c, const double& index) {
	auto iterator = c.begin();
	for (auto i = 0; i < index; ++i) {
		++iterator;
	}
	c.erase(iterator);
}

void printCollection(const CollectionType<double>& c) {
	auto counter = 0;
	cout << "Your collection includes:";
	auto iterator = c.begin();
	for (auto i : c) {
		cout << "[" << counter << "]" << " " << i << " ";
		++iterator;
		++counter;
	}
	cout << endl << endl;
}

template <typename T>
void print(T colelction) {
	auto beg=
}

int main() {
	//creating any collection
	CollectionType<double> collection;

	CollectionType<SharedPtrType<Image>> collectionShPtr;
	Image* img = new Image(4, 3);
	SharedPtrType<Image> shPtr(img);

	auto choise = -1;

	auto dMin = -10000.0;

	auto dMax = 10000.0;

	while (choise != 0) {
		try {
			mainMenu();
			choise = utils::read_int("Your choise: ", 0, 7);

			system("cls");

			switch (choise) {
				//add element
			case 1:
				addElement<double>(collection, utils::read_int("Input index to paste element in collection: ", 0, collection.sizer()), utils::read_double("Input num to paste it in collection: ", dMin, dMax));
				break;
				//remove element
			case 2: {
				if (!collection.empty())
					removeElement(collection, utils::read_int("Input index to erase element from collection: ", 0, collection.sizer() - 1));
				else throw "ERROR: colelction is empty";
				break;
			}
				//clear list
			case 3: {
				collection.clear();
				cout << "collection cleared" << endl;
				break;
			}
				//get size
			case 4: {
				cout << "size of the collection: " << collection.sizer() << endl;
				break;
			}
				//edit collection
			case 5: {
				if (!(collection.empty())) {
					int index = utils::read_int("Enter index of element for change: ", 0, collection.sizer() - 1);

					auto iterator = collection.begin();
					for (auto i = 0; i < index; ++i)
						++iterator;

					*iterator = utils::read_double("Element is found. Enter new value of this node: ", dMin, dMax);

				}
				else
					throw "ERROR: Collection is empty";
				break;
			}
				//print collection
			case 6: {
				system("cls");
				printCollection(collection);
				break;
			}
				//work with own class
			case 7: {
				system("cls");
				SharedPtrType<Image> shPtrTmp(shPtr);

				collectionShPtr.insert(collectionShPtr.end(), shPtrTmp);
				collectionShPtr.front();
				break;
			}
				//exit program
			case 0: {
				return 0;
			}
			}
		}
		catch (const char* s) {
			cout << s << endl;
		}
	}
	return 0;
}