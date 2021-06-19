//RBT.h
enum Color{ RED, BLACK };

struct RBTNode
{
	struct RBTNode* parent;
	struct RBTNode* left;
	struct RBTNode* right;

	int data;
	enum Color color;

};

static RBTNode* NIL;

void RBT_SET();

void RBT_RotateRight(RBTNode** root, RBTNode* parent);
void RBT_RotateLeft(RBTNode** root, RBTNode* parent);