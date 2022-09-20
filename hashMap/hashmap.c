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

Hashmap* init_hashmap();//创建hashmap
unsigned int hash(K key);//hash方法进行散列
void put(Hashmap*, K, V);//在HashMap中添加元素(头插法，允许存在重复元素，并且无序)
V get(Hashmap*, K);//获取key对应value
void displayHashMap(Hashmap*);
void distroy(Hashmap*);


unsigned int hash(K s)
{//哈希函数
    unsigned int h = 0;
    for (; *s; s++)
        h = *s + h * 31;//将整个字符串按照特定关系转化为一个整数，然后对hash长度取余
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
    if (head->next == NULL) return -1;//如果为空返回-1
    return head->next->val;//返回对应的val
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