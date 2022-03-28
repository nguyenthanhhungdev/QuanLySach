#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
using namespace std;

struct sach
{
	char tenSach[50];
	char tenTacGia[50];
	int namXuatBan;
};

struct node
{
	sach* data;
	node* next;
	node* prev;
};

struct list
{
	node* head, * tail;
};

void createList(list& l)
{
	l.head = l.tail = NULL;
}

node* getNode(sach *data)
{
	node* p = new node;
	if (p == NULL)
	{
		cout << "Khong du bo nho" << endl;
		exit(1);
	}

	p->data = data;

	p->next = NULL;
	p->prev = NULL;

	return p;
}

void chenCuoi(list& l, node *p)
{
	if (l.head == NULL)
	{
		l.head = l.tail = p;
	}
	else {
		l.tail->next = p;
		p->prev = l.tail;
		l.tail = p;
	}
}

void chenDau(list& l, node* p)
{
	if (l.head == NULL)
		l.head = l.tail = p;
	else {
		p->next = l.head;
		l.head->prev = p;
		l.head = p;
	}
}

void chenSau(list& l, node* q, node* p)
{
	if (q != NULL)
	{
		node* t = q->next;
		p->next = t;
		q->next = p;
		p->prev = q;
		if(t != NULL)
			t->prev = p;
		if (q == l.head)
			l.tail = p;
	}
	else chenDau(l, p);
}

void chenTruoc(list& l, node* q, node* p)
{
	if (q != NULL)
	{
		p->next = q;
		q->prev = p;
		if (q->prev != NULL)
			q->prev->next = p;
		if (l.head == q)
			l.head = p;
	}
	else chenCuoi(l, p);
}

sach *nhapSach()
{
	sach* book = new sach;
	cin.ignore();
	cout << "Nhap ten sach: ";
	gets_s(book->tenSach);
	cout << "Nhap ten tac gia: ";
	gets_s(book->tenTacGia);
	cout << "Nhap nam xuat ban: ";
	cin >> book->namXuatBan;
	return book;
}


void danhSachChenCuoi(list& l)
{
	int n;
	cout << "Nhap so luong phan tu cua danh sach: ";
	cin >> n;
	createList(l);
	for (int i = 1; i <= n; i++)
	{
		cout << "Nhap thong tin sach thu: " << i << endl;
		chenCuoi(l, getNode(nhapSach()));
	}
}

void inDanhSach(list l)
{
	int j = 1;
	for (node* i = l.head; i != NULL; i = i->next)
	{
		cout << "Thong tin sach thu: " << j << endl;
		cout << "Ten sach: " << i->data->tenSach << endl;
		cout << "Ten tac gia: " << i->data->tenTacGia << endl;
		cout << "Nam xuat ban: " << i->data->namXuatBan << endl;
		j++;
		cout << endl;
	}
}

void inThongTin(node* p)
{
	if (p == NULL) {
		cout << "Khong co sach trong du lieu" << endl;
		exit(1);
	}
	cout << "Thong tin sach da tim duoc: " << endl;
	cout << "Ten sach: " << p->data->tenSach << endl;
	cout << "Ten tac gia: " << p->data->tenTacGia << endl;
	cout << "Nam xuat ban: " << p->data->namXuatBan << endl;
	cout << endl;
}

node* timKiem(list l, char sachCanTim[])
{
	node* p = l.head;
	while (p != NULL && strcmp(p->data->tenSach, sachCanTim) != 0)
		p = p->next;
	return p;
}

void giaiPhong(list &l) {
	node* p;
	while (l.head != NULL)
	{
		p = l.head;
		l.head = l.head->next;
		delete p;
	}
}

int main()
{
	list l;
	danhSachChenCuoi(l);
	inDanhSach(l);

	cout << "Nhap sach muon tim kiem: ";
	cin.ignore();
	char sachCanTim[50];
	gets_s(sachCanTim);

	node* sachTimDuoc = timKiem(l, sachCanTim);

	cout << endl;
	
	inThongTin(sachTimDuoc);

	//fflush(stdin);
	//cout << "Nhap sach muon sua: ";
	//char tenSachMuonSua[50];
	//gets_s(tenSachMuonSua);

	//node* sachMuonSua = timKiem(l, tenSachMuonSua);

	cout << "Nhap sach can chen phia sau: ";
	char sachTruoc[50];
	gets_s(sachTruoc);

	cout << "Nhap thong tin sach can chen: \n Nhan Enter" << endl;

	node* nodeTruoc = timKiem(l, sachTruoc);

	chenTruoc(l, nodeTruoc, getNode(nhapSach()));

	cout << endl;

	inDanhSach(l);

	giaiPhong(l);
	return 0;
}