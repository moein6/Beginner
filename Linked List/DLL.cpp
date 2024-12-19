#include <iostream>

template <typename Ty>
class Node {

public:

	Ty m_data;
	
	std::shared_ptr<Node<Ty>> next;
	std::shared_ptr<Node<Ty>> prev;


	Node(const Ty newData){
		m_data = newData;
	
		next = nullptr;
		prev = nullptr;

	}
	Node() {
		m_data = 0;

		next = nullptr;
		prev = nullptr;
	}
};	//	end class


template <typename Ty> class DoubbleLinkedList {

private:
	std::shared_ptr<Node<Ty>> first;
	std::shared_ptr<Node<Ty>> last ;
	
	unsigned int List_size;


public:
	DoubbleLinkedList() {
		first = nullptr;
		last = nullptr;
		List_size = 0;
	}

	~DoubbleLinkedList()
	{
		//	do nothing
	}

	void push_back(const Ty newData) {
		auto newnode = std::make_shared<Node<Ty>>(newData);

		if (first == nullptr) 
			first = last = std::move(newnode); // using 'move' function to avoid creating a copy of pointer
		else
		{

			last->next = newnode;
			newnode->prev = last;
			last = newnode;
		}//	end else


		List_size++;

	}//	end fucntion

	void push_front(const Ty newData) {
		auto newnode = std::make_shared<Node<Ty>>(newData);

		if (first == nullptr)
			first = last = newnode;
		else {
			newnode->next = first;
			first = newnode;
		}


		List_size++;

	}//	end function

	void Delete(const Ty date) {

		auto temp = first;
		bool found = false;
		if (List_size) {
			while (temp) {

				if (temp->m_data == date) {
					found = true;
					break;
				}//	end if

				temp = temp->next;
			}//	end while

			if (found) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				List_size--;
			}
		}
		else
			throw std::exception("List is empty");

	}//	end function

	void Print_reverse(){
		auto reverse_Temp = last;

		while (reverse_Temp)
		{
			std::cout << reverse_Temp->m_data << ' ';
			reverse_Temp = reverse_Temp->prev;
		}//	end while

		std::cout << '\n';
	}//	end function

	void Print() {
		auto temp = first;


		while (temp) {

			std::cout << temp->m_data << ' ';
			temp = temp->next;
		}//	end while
		std::cout << '\n';

	}//	end function

	unsigned int Get_Size()const {
		return List_size;
	}

	void InsertAt(unsigned short index, const unsigned short data) {
		auto newnode = std::make_shared<Node<Ty>>(data);

		if (index == List_size) {
			push_back(data);
			return;
		}
		else if (index == 0) {
			push_front(data);
			return;
		}

		if (index > List_size or index < 1) {
			throw std::exception("Out of range");
			return;
		}



		
		auto temp = first;

		for (auto i = 0; i < index; i++)
			temp = temp->next;

		temp->next->prev = newnode;
		newnode->next = temp->next;
		temp->next = newnode;
		newnode->prev = temp;
	}//	end function

};//	end class
