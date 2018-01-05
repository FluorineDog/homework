using T = int;
class List {
public:
  struct Node {
    T data;
    Node *next;
		Node(T data, Node* next): data(data), next(next){}
  };
  void push(T data) { 
		root = new Node(data, root);
	}
	
private:
  Node *root;
};