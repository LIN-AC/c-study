#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 100

typedef char* K;
typedef int   V;

typedef struct node {
    K key;
    V val;
    struct node* next;
}Node;

typedef struct hash_table {
    Node* table[HASHSIZE];
}Hashmap;

Hashmap* init_hashmap();//����hashmap
unsigned int hash(K key);//hash��������ɢ��
void put(Hashmap*, K, V);//��HashMap�����Ԫ��(ͷ�巨����������ظ�Ԫ�أ���������)
V get(Hashmap*, K);//��ȡkey��Ӧvalue
void displayHashMap(Hashmap*);
void distroy(Hashmap*);


unsigned int hash(K s)
{//��ϣ����
    unsigned int h = 0;
    for (; *s; s++)
        h = *s + h * 31;//�������ַ��������ض���ϵת��Ϊһ��������Ȼ���hash����ȡ��
    return h % HASHSIZE;
}

Hashmap* init_hashmap() {
    Hashmap* hashmap = (Hashmap*)calloc(1,sizeof(Hashmap));
    if (hashmap == NULL) {
        puts("create false");
        return;
    }
    return hashmap;
}
void put(Hashmap* hashmap, K key, V val) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return;
    node->key = key;
    node->val = val;
    int hashval = hash(key);
    Node* head = hashmap->table[hashval];
    if (head == NULL) {
        head = (Node*)malloc(sizeof(Node));
        head->next = NULL;
        hashmap->table[hashval] = head;
    }
    node->next = head->next;
    head->next = node;
}
V get(Hashmap* hashmap, K key) {
    Node* head = hashmap->table[hash(key)];
    while (head->next->key != key && head->next != NULL) {
        head = head->next;
    }
    if (head->next == NULL) return -1;//���Ϊ�շ���-1
    return head->next->val;//���ض�Ӧ��val
}
void displayHashmap(Hashmap* hashmap) {
    Node* p;
    for (int i = 0; i < HASHSIZE; i++) {
        if (hashmap->table[i] != NULL) {
            p = hashmap->table[i];
            printf("\nhashvalue: %d (", i);
            for (; p->next != NULL; p = p->next)
                printf(" (%s.%d) ", p->key, p->val);
            printf(")\n");
        }
    }
}

void distroy(Hashmap* hashmap) {
    Node *head, *temp;
    for (int i = 0; i < HASHSIZE; i++) {

        if (hashmap->table[i] != NULL) {
            head = hashmap->table[i];
            while (head != NULL) {
                temp = head->next;
                free(head->key);
                free(head);
                head = temp;
            }
        }
    }
}

int main() {
    Hashmap* hashmap = init_hashmap();
    put(hashmap, "zhang", 3);
    put(hashmap, "li", 4);
    put(hashmap, "wang", 5);
    put(hashmap, "zhao", 6);

    V val = get(hashmap, "li");
    printf("%d", val);
    return 0;
}