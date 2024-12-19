#include <iostream>
#include <memory>


template <typename Ty> class Node
{
public:

	Ty data;


	std::shared_ptr<Node<Ty>> Next ;


	Node(const Ty New_Data) {
		data = New_Data;
		Next = nullptr;
	}

	Node(const Ty new_Data, const Node<Ty> NextNode ) {
		data = new_Data;
		Next = NextNode;
	}

};


template <typename Ty> 
class SingleyLinkedList {
public:
	SingleyLinkedList() {
		First = nullptr;
		List_size = 0;
	}

	void InsertAt(const unsigned short index, const Ty& Data) {

		if(index < 0 or index > List_size)
			throw std::exception("Out of rang index");

		List_size++;
		
		if (index == List_size) {
			Push_Back(Data);
			return;
		}else if (index == 0)
			push_Front(Data);
		else{
			
			auto temp = First;
			auto newnode = std::make_shared<Node<Ty>>(Data);
	
	
			for (; index > -1; index--)
				temp = temp->Next;
	
			newnode->Next = temp->Next->Next;
			temp->Next = newnode;
		}

	}//	end function
	
	void Delete(const Ty& data) {

		if (isEmpty())
			return;


		auto temp = First;
		auto prev = temp;


		while (temp) {

			prev = temp;


			if (temp->data == data)
				break;

			temp = temp->Next;
		}//	end while

		if (temp->Next)
			prev->Next = temp->Next;
		else
			prev->Next = nullptr;

		List_size--;
	}
	
	void Push_Back(const Ty& data) {
		auto newnode = std::make_shared<Node<Ty>>(data);

		if (First == nullptr)
			First = newnode;
		else
		{
			auto temp = First;

			while (temp->Next)
				temp = temp->Next;

			temp->Next = newnode;
		}//	end else

		List_size++;

	}//	end function
	
	void Push_Front(const Ty& data) {
		auto newnode= std::make_shared<Node<Ty>>(data);

		if (First == nullptr)
			First = newnode;
		else {
		
			newnode->Next = First;
			First = newnode;
		
		}//	end else

		List_size++;
	}//	end function

	void Print() {
		auto temp = First;

		while (temp) {
			std::cout << temp->data << ' ';
			temp = temp->Next;
		}//	end while

		std::cout << '\n';

	}//	end function

private:
	bool isEmpty()const {
		return (List_size == 0) ? true : false;
	}


private:
	std::shared_ptr<Node<Ty>> First;

	unsigned short List_size;

};

