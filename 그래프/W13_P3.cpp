#include <iostream>
#include <string>
#include <vector>
using namespace std;

// vertex ������Ʈ
struct vertex {
	int vertexId; // ������ ���� ��ȣ
	int matrixId; // edge matrix ���� ������ �ε��� ��ȣ

	vertex* prev; // vertex ���������� �ڽ��� ������ ���� vertex ������Ʈ�� ���������� ����
	vertex* next;

	vertex() {
		vertexId = matrixId = -1;
		prev = next = NULL;
	}

	vertex(int vertexId) {
		this->vertexId = vertexId;
		matrixId = -1;
		prev = next = NULL;
	}
};

// ������ �����ϴ� ������ 
// ( �̷� ������ ��� �Ͱ� �޸�, ���� ������Ʈ���� ����Ű�� ��������, vertex ������Ʈ���� ��Ű���� �������� ���� �������� �ʴ´�.)
class vertexList {
private:
	vertex* header;
	vertex* trailer;
public:
	vertexList();
	void insertVertex(vertex* newVertex);
	void eraseVertex(vertex* delVertex);
	vertex* findVertex(int vertexId);
};

vertexList::vertexList() {
	header = new vertex();
	trailer = new vertex();
	header->next = trailer;
	header->matrixId = -1;
	trailer->prev = header;
}

// ���� ������Ʈ �������� ���ο� ������ ����
void vertexList::insertVertex(vertex* newVertex) {
	newVertex->prev = trailer->prev;
	newVertex->next = trailer;
	newVertex->matrixId = trailer->prev->matrixId + 1; // ���� ���� ������Ʈ �������� ������ ���� ������Ʈ�� matrixId ���� 3�̶��, ���� ���Խ�ų ������ 4�� ����
	trailer->prev->next = newVertex;
	trailer->prev = newVertex;
}

// ���� ������Ʈ ���������� �ش� ������ ����
// => �׷������� ���� ������ 1
// 1) ���� ������Ʈ ���� 2) ���� ������Ʈ�� ������ ���Ҹ� ����(���� �ǽ� �ڵ�� �� �������� ���ξ���)
// 3) ������ ������(adjacent) ������ ����
// 4) ������ �������� �ε��� ��ȣ ������ (matrixId) �� ū �������� matrixId �� 1�� ����
// ���⼭�� 1���� "���� ������Ʈ ����" ������ �� �Լ��� �����ϸ� �ȴ�.
void vertexList::eraseVertex(vertex* delVertex) {
	for (vertex* cur = delVertex; cur != trailer; cur = cur->next) {    // ������ �������� matrixId�� ū �������� matrixId�� 1�� ����
		cur->matrixId--;
	}

	delVertex->prev->next = delVertex->next;
	delVertex->next->prev = delVertex->prev;
	delete delVertex; // delVertex �� ���� ������Ʈ ���������� ����
}

// ���� ������Ʈ ���������� ���� vertexId �� ã�� ���� 
vertex* vertexList::findVertex(int vertexId) {
	for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
		if (cur->vertexId == vertexId) {
			return cur;
		}
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// edge ������Ʈ
struct edge {
	vertex* src;  // �� edge �� �糡�� � �� ���� ���� (source, destination) �� �����ϰ� �ִ����� ������ ����
	vertex* dst; 

	edge* prev; // ���� ���������� �ڽ��� ������ ���� ������ ���������� ����
	edge* next;
	
	edge() {
		src = dst = NULL;
		prev = next = NULL;
	}

	edge(vertex* src, vertex* dst) {
		this->src = src;
		this->dst = dst;
		prev = next = NULL;
	}
};

// ���� ������Ʈ���� �����ϴ� ������
class edgeList {
private:
	edge* header;
	edge* trailer;
public:
	edgeList();
	void insertEdge(edge* newEdge);
	void eraseEdge(edge* delEdge);
};

edgeList::edgeList() {
	header = new edge();
	trailer = new edge();
	header->next = trailer;
	trailer->prev = header;
}

// ���ο� ���� ������Ʈ�� ���� ������Ʈ �������� ����
void edgeList::insertEdge(edge* newEdge) {
	newEdge->prev = trailer->prev;
	newEdge->next = trailer;
	trailer->prev->next = newEdge;
	trailer->prev = newEdge;
}

// ���� ������Ʈ�� ���� ������Ʈ ���������� ����
// �� �Լ��� ���� ������Ʈ�� �� �����ϰ� ������ Ȱ��� ���� �ց�����, vertex ������Ʈ�� �����ϴ� ���꿡�� Ȱ��ȴ�!
// ( vertex �� �����Ҷ� vertex �� ����, vertex �� ����� edge �鵵 �Բ� �����ؾ� �ϱ⶧��)
void edgeList::eraseEdge(edge* delEdge) {
	delEdge->prev->next = delEdge->next;
	delEdge->next->prev = delEdge->prev;
	delete delEdge;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class graph {
private:
	vector<vector<edge*>> edgeMatrix; // ���� ��� => �� ���� edge �� �ּҸ� �����ؼ�, edge�� �ּҰ� ����� ���� �ش� edge ������Ʈ�� ����Ŵ
	vertexList vList;  // ������ �����ϴ� ����Ʈ
	edgeList eList;    // edge�� �����ϴ� ����Ʈ
public:
	void insertVertex(int vertexId);
	void eraseVertex(int vertexId);
	void insertEdge(int srcVertexId, int dstVertexId);
	void eraseEdge(int srcVertexId, int dstVertexId);
	void SumAdjacentNode(int vertexId);
};

// vertex �������� vertex ������Ʈ�� ����. �̶� ����� ��� ���� ũ�⸦ 1�� �÷��ش�.
// (�̷нð��� ������ ���� ũ�⸦ Ű�� ���ο� ����� ����� ���� ����� ��� ���Ҹ� ī������, ���ο� vertex ������Ʈ�� �����ϴ� ���̿�����,
// ���⼭�� ���� ��Ŀ��� �׳� ũ�⸦ Ű���. )
void graph::insertVertex(int vertexId) {
	if (vList.findVertex(vertexId) != NULL) {  // ���� vertexId �� �̹� �׷����� �����ϴ� ���
		return;
	}

	vertex* newVertex = new vertex(vertexId);

	// ������Ŀ� ���ο� ������ ����� edge �� ������ ������ ������ ����

	for (int i = 0; i < edgeMatrix.size(); i++) {     // ��������� �� �࿡�� NULL ���� �߰��������ν�, ����� ���� 1������Ŵ. 
		edgeMatrix[i].push_back(NULL);                // ex. 3x3 ����� ���, 3x4 �� �ȴ�.  ������� 2�࿡ {NULL, NULL, NULL} �� ������ִ� ���, 
		                                              // NULL �� �ϳ� �߰������ν� �ش� ���� {NULL, NULL. NULL, NULL} �� �ȴ�.
	}

	edgeMatrix.push_back(vector<edge*>(edgeMatrix.size() + 1, NULL)); // ��������� ���� 1 �ø�. 
	// �ռ��� 1���� �÷����Ƿ�, �� �۾��� ���ؼ� �൵ 1�� �ø���. ex) 3x3 ����� �ռ� ������ �۾����� 3x4 �� �Ǿ��ٸ�, �̹� �۾��� ���� 4x4 �� �ȴ�.

	vList.insertVertex(newVertex);   // ���� ������Ʈ �������� ���ο� ���� ������Ʈ�� ���� 
}



// ���� ������Ʈ ���������� �ش� ������ ����
// => �׷������� ���� ������ 
// 1) ���� ������Ʈ ���� 2) ���� ������Ʈ�� ������ ���Ҹ� ����(���� �ǽ� �ڵ�� �� �������� ���ξ���)
// 3) ������ ������(adjacent) ������ ����
// 4) ������ �������� �ε��� ��ȣ ������ (matrixId) �� ū �������� matrixId �� 1�� ����

// ���� vertexId �� ����. �̶� ������ edge �鵵 �Բ� �������ش�.
void graph::eraseVertex(int vertexId) {
	vertex* delVertex = vList.findVertex(vertexId);  // ���� ���������� ���� vertexId �� ã�Ƴ�

	if (delVertex == NULL) { // ������ ������ �������� �ʴ� ���
		return;
	}

	int matrixId = delVertex->matrixId; // ������ ����� �ε��� ��ȣ
	
	// matrixId ���� 2�� vertex, �� ������ �ʵ忡 �ε��� ��ȣ�� 2�� ������ �ִ� vertex ������Ʈ�� 
	// ������ edge ������Ʈ���� �ּҰ��� ������Ŀ��� 2���� �����, 2���� ������ ��� �����ϰ� �ִ�.
	// ���� ������Ŀ��� 2���� �����, 2���� ������ ��� �������ָ�, �ش� vertex�� ������ edge���� ��� �����ϸ鼭 
	// ���ÿ� ����� ��� ���� ũ�⸦ 1 ���� �� �ִ�! (ex. 4x4 ��� => 3x3 ���)

	// ���� ��Ŀ��� ������ ������ ����� edge ��, edge �� ������ �����ϴ� ������ ����
	// i�� matrixId ���� ����ִ� �ּҰ��� �����Ѵ�!
	for (int i = 0; i < edgeMatrix.size(); i++) {  // * ���� : 2���� ������ size() �Լ� ������� ���� ũ�Ⱑ ���´�!!
		if (i != matrixId) {  
			if (edgeMatrix[i][matrixId] != NULL) {  // i�� matrixId �� ����ִ� �ּҰ��� NULL �� �ƴ϶��. ��, i�� matrixLd �� ���� � ���� ������Ʈ�� ����Ű�� �ִ� �����̶��
				eList.eraseEdge(edgeMatrix[i][matrixId]);  // ������ edge ������Ʈ�鵵 �Բ� ����
			}
			edgeMatrix[i].erase(edgeMatrix[i].begin() + matrixId); // i���� �ִ� ������ ��� (�̶�, i�� i���� ����) ����. 
			                                                       // => �̶� ��� �� ��ü�� ������ ������ ���̴�!
		}
	}

	edgeMatrix.erase(edgeMatrix.begin() + matrixId);  // ��������� matrixId ���� ��� ������ ����
	vList.eraseVertex(delVertex); // vertex ���������� vertex ������Ʈ ����
}

void graph::insertEdge(int srcVertexId, int dstVertexId) {
	vertex* src = vList.findVertex(srcVertexId);  // ������ ������ �糡�� vertex ������Ʈ�� vertex ���������� ã�Ƴ�
	vertex* dst = vList.findVertex(dstVertexId);
	if (src == NULL || dst == NULL)
		return;

	int srcMatrixId = src->matrixId;
	int dstMatrixId = dst->matrixId;

	// �� ������ �մ� ������ �̹� �����ϴ� ���
	if (edgeMatrix[srcMatrixId][dstMatrixId] != NULL || edgeMatrix[dstMatrixId][srcMatrixId] != NULL) {
		cout << "Exist" << endl;
		return;
	}

	edge* newEdge = new edge(src, dst);
	eList.insertEdge(newEdge); // ���� �������� ���ο� ���� ������Ʈ�� ����
	edgeMatrix[srcMatrixId][dstMatrixId] = edgeMatrix[dstMatrixId][srcMatrixId] = newEdge; // ��Ŀ� ���ο� edge ������Ʈ�� �ּҸ� ����
}

// ���ڷ� �־��� �� ���� ���̸� �������ְ� �ִ� edge �� ����
void graph::eraseEdge(int srcVertexId, int dstVertexId) {
	vertex* src = vList.findVertex(srcVertexId);
	vertex* dst = vList.findVertex(dstVertexId);

	if (src == NULL || dst == NULL) // ������ �׷����� �������� �ʴ� ���
		return;

	int srcMatrixId = src->matrixId;
	int dstMatrixId = dst->matrixId;

	// �� ������ �մ� ������ �������� �ʴ� ���
	if (edgeMatrix[srcMatrixId][dstMatrixId] == NULL || edgeMatrix[dstMatrixId][srcMatrixId] == NULL)
	{
		cout << "None" << endl;
		return;
	}

	eList.eraseEdge(edgeMatrix[srcMatrixId][dstMatrixId]); // edge ������Ʈ ���������� �����Ϸ��� edge �� ����
	edgeMatrix[srcMatrixId][dstMatrixId] = NULL;  // ��������� �ش� ���� NULL ó��
	edgeMatrix[dstMatrixId][srcMatrixId] = NULL;
}

void graph::SumAdjacentNode(int vertexId)
{
	vertex* vertex = vList.findVertex(vertexId);

	int matrixId = vertex->matrixId;
	int sum = 0; 

	// ����� ��� ���� ���� Ž��
	for (int i = 0; i < edgeMatrix.size(); i++)
	{
		for (int j = 0; j < edgeMatrix.size(); j++) 
		{
			if (edgeMatrix[i][j] != NULL && edgeMatrix[j][i] != NULL) // �ش� ���� � ���� ������Ʈ�� ����Ű�� �ִ� ��� 
			{
				// if (edgeMatrix[i][j] == edgeMatrix[j][i])
				if (edgeMatrix[i][j]->src == vertex || edgeMatrix[i][j]->dst == vertex) // �ش� ���� ���� ������Ʈ�� ����Ű�� �� ���� vertex ������Ʈ�� �ϳ��� ���� vertex �� ���. ��, ���� vertex �� ������ ������ ã�� ���
				{
					// ���� ���� ������Ʈ�� ����Ű�� �� ���� ������Ʈ src, dst �߿��� vertex �� �ƴ� ������ ���ؼ� ���ϱ� ������ �����ϸ� �ȴ�.
					// => vertex�� �ƴ� ������ �ٷ� ���� vertex�� ������ �����̴�.
					if (edgeMatrix[i][j]->src != vertex) // src �� ������ �����̰�, dst �� ���� vertex �� ���
					{
						sum += edgeMatrix[i][j]->src->vertexId;
 					}
					else if (edgeMatrix[i][j]->dst != vertex) // dst �� ������ �����̰�, src �� ���� vertex �� ���
					{
						sum += edgeMatrix[i][j]->dst->vertexId;
					}
				}
			}
		}
	}

	// ����!!!!! => ������ ���ϱ� ������ �����Ҷ� i�� j���� ���ؼ� ���ϱ⸦ �����ߴٸ�, j�� i���� ���ؼ��� ���ϱ⸦ �� �ٽ� �����Ѵ�.
	// ���� sum ����� ������ 2 �� ���ش�!

	if (sum == 0) // ���� vertexId �� ����� ������ �������� �ʴ� ���
	{  //  => ����� ������ �������� �ʾҴٸ�, ���ϱ� ������ �� �ѹ��� �������� �ʾƼ� max ���� �ʱ⿡ �������� ���� 0 �� ���̴�.
		cout << "None" << endl;
		return;
	}

	cout << sum/2 << endl;
}


int main(void)
{
	graph g;
	int t, n;
	cin >> t >>  n;

	while (n--)
	{
		int data;
		cin >> data;
		g.insertVertex(data);
	}

	while (t--)
	{
		string a;
		cin >> a;
		if (a == "insertEdge")
		{
			int data1, data2;
			cin >> data1 >> data2;
			g.insertEdge(data1, data2);
		}
		else if (a == "eraseEdge")
		{
			int data1, data2;
			cin >> data1 >> data2;
			g.eraseEdge(data1, data2);
		}
		else if (a == "SumAdjacentNode")
		{
			int data;
			cin >> data;
			g.SumAdjacentNode(data);
		}
	}
}