#ifndef INSTRUCTIVE_H
#define INSTRUCTIVE_H

/** * @brief True linked list struct, can match different data type with same linked list.
 * Default is Circular doubly linked list.
 */
struct list_head
{
    struct list_head *m_prev;
    struct list_head *m_next;
};

typedef struct list_head list_head;

/**
 * @brief Calculate struct datamember offset with struct address.
 *
 */
#define offsetof(type, member)          (unsigned long)&((type *)0)->member

/**
 * @brief Calculate struct head address, by member address, struct type, struct datamember;
 *  Head address = Member Address - Member Offset
 */
#define container_of(ptr, type, member) (type *)((char *)(ptr) - offsetof(type, member))

// List macro
#define LIST_HEAD_INIT(name)            {&(name), &(name)}
#define LIST_HEAD(name)                 list_head name = LIST_HEAD_INIT(name)
#define LIST_ENTRY(node, type, member)  container_of(node, type, member)
#define LIST_for_each(pos, head)        for (pos = (head)->m_next; pos != (head); pos = pos->m_next)
#define LIST_for_each_safe(pos, head, n) \
    for (pos = (head)->m_next, n = pos->m_next; pos != (head); pos = n, n = pos->m_next)

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief If In C-style, Just create a node struct include that `list_head`
     * @tparam T
     */

    /**
     * @brief Init a single node doubly circular list.
     *
     * @param _list
     */
    void ins_init(list_head *_list);
    /**
     * @brief Insert a node After current list node.
     *
     * @param _list insert pos
     * @param _node
     */
    void insert_after(list_head *_list, list_head *_node);

    /**
     * @brief Insert a node Before current list node.
     *
     * @param _list insert pos
     * @param _node
     */
    void insert_before(list_head *_list, list_head *_node);
    void ins_remove(list_head *_node);
    int  isempty(list_head *_list);
    void ins_clear(list_head *_list);
    int  getlen(list_head *_list);

    typedef struct data1
    {
        int       m_id;
        list_head m_list;
    } data1;

    typedef struct data2
    {
        int       m_id;
        list_head m_list;
    } data2;

#ifdef __cplusplus
}
#endif

#endif