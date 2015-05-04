#include <iostream>
#include <memory>
#include <random>
#include <forward_list>
#include <vector>
#include <cassert>
struct Node {
  int val_;
  std::shared_ptr<Node> next;
  Node() : val_(0), next(nullptr) {}
  Node(int val) : val_(val) 
  {
  }
  Node(int val, Node* new_Node) : val_(val), next(new_Node)
  {
  }
};

/// Quinn
int len_q(Node* head);
Node* intersect_point(Node* first1, Node* first2);

int len_q(Node* head) {
  int i = 0;
  while (head != nullptr) {
    head = head->next.get();
    ++i;
  }
  return i;
}

Node* intersect_point(Node* first1, Node* first2) {
  int len1 = len_q(first1);
  int len2 = len_q(first2);

  if (len1 > len2) {
    for (int i = 0; i < abs(len1 - len2); ++i)
      first1 = first1->next.get();
  }
  else {
    for (int i = 0; i < abs(len1 - len2); ++i)
      first2 = first2->next.get();
  }
  while (first1 != first2) {
    first1 = first1->next.get();
    first2 = first2->next.get();
  }
  return first1;
}

// Jeremy high
/* This is probably uglier than it needs to be */
Node* intersect(Node* head1, Node* head2) {
  if (head1 == head2) {
    return head1;
  }

  auto l1 = head1, 
       l2 = head2;

  unsigned int count1 = 1, 
               count2 = 1;


  while (l1->next.get() != nullptr) {
    l1 = l1->next.get();
    ++count1;
  }
  while (l2->next.get() != nullptr) {
    l2 = l2->next.get();
    ++count2;
  }

  l1 = head1;
  l2 = head2;

  while (count1 > count2) {
    l1 = l1->next.get();
    --count1;
  }

  while (count2 > count1) {
    l2 = l2->next.get();
    --count2;
  }

  /* Assuming there is always an intersection */
  while (l1 != l2) {
    l1=l1->next.get();
    l2=l2->next.get();
  }

  return l1;
}


// Chris bennett
struct Node* doMath(struct Node* l1Start, struct Node* l2Start)
{
  struct Node *p = l1Start;
  struct Node *p2 = l2Start;
  int countL1=0, countL2=0;
  //Count list 1 N
  while (p)
  {
    ++countL1;
    p = p->next.get();
  }
  //Count list 2 N
  while (p2)
  {
    ++countL2;
    p2 = p2->next.get();
  }
  int dif = abs(countL1 - countL2);
  struct Node *l1P=l1Start, *l2P=l2Start;
  //N
  //Accelerate list 1 or 2 by the diference in list lengths
  if (countL1 > countL2)
    for (int i = 0; i < dif; ++i) l1P = l1P->next.get();
  else
    for (int i = 0; i < dif; ++i) l2P = l2P->next.get();
                             //Compare each list till match
  while (l1P != l2P)
    l1P = l1P->next.get(), l2P = l2P->next.get();
                                  //3N complexity (1)space
  return l1P;
}

// David
Node* find_node(Node* h1, Node* h2);
int len(Node* h);

int len(Node* h) {
    int l = 0;
    while (h != nullptr) {
        ++l;
        h = h->next.get();
    }
    return l;
}

Node* find_node(Node* h1, Node* h2) {
    int l1 = len(h1);
    int l2 = len(h2);

    if (l1 > l2) {
        for (int i = 0; i < l1-l2; ++i)
            h1 = h1->next.get();
    } else if (l1 < l2) {
        for (int i = 0; i < l2-l1; ++i)
            h2 = h2->next.get();
    }

    while (h1->next.get() != h2->next.get() && h1->next.get()!= nullptr && h2->next.get() != nullptr) {
        h1 = h1->next.get();
        h2 = h2->next.get();
    }

    if (h1->next.get() == nullptr || h2->next.get() == nullptr)
        return nullptr;

    return h1->next.get();
}


int main() {
  std::mt19937 generator;
  std::uniform_int_distribution<int> dist_N(2,60);
  int j = 1;
  while (j) 
  {
    std::cout << "test case " << j << std::endl;
    ++j;
    int size_a = dist_N(generator);
    int size_b = dist_N(generator);
    int size_c = dist_N(generator);
    std::shared_ptr<Node> head_a(new Node(dist_N(generator), nullptr));
    std::shared_ptr<Node> head_b(new Node(dist_N(generator), nullptr));
    std::shared_ptr<Node> curr_a(head_a, head_a.get());
    std::shared_ptr<Node> curr_b(head_b, head_b.get());
    for (int i = 1; i < size_a; ++i) {
      curr_a->next.reset(new Node(dist_N(generator), nullptr));
      curr_a = std::shared_ptr<Node>(curr_a->next,curr_a->next.get());
    }
    for (int i = 1; i < size_b; ++i) {
      curr_b->next.reset(new Node(dist_N(generator), nullptr));
      curr_b = std::shared_ptr<Node>(curr_b->next,curr_b->next.get());
    }
    std::shared_ptr<Node> head_c(nullptr);
    for (int i = 0; i < size_c; ++i) {
      curr_a->next.reset(new Node(dist_N(generator), nullptr));
      curr_b->next = std::shared_ptr<Node>(curr_a->next,curr_a->next.get());
      if (i == 0) {
        head_c = std::shared_ptr<Node>(curr_b->next,curr_b->next.get());
      }
      curr_a = std::shared_ptr<Node>(curr_a->next,curr_a->next.get());
      curr_b = std::shared_ptr<Node>(curr_b->next,curr_b->next.get());
    }
    std::shared_ptr<Node> merged_a(nullptr), merged_b(nullptr);
    for (std::shared_ptr<Node> curr(head_a, head_a.get()); curr->next != nullptr; curr = std::shared_ptr<Node>(curr->next, curr->next.get())) {
      if (curr.get() == head_c.get()) {
        merged_a = std::shared_ptr<Node>(curr, curr.get());
      } 
    }
    for (std::shared_ptr<Node> curr(head_b, head_b.get()); curr->next != nullptr; curr = std::shared_ptr<Node>(curr->next, curr->next.get())) {
      if (curr.get() == head_c.get()) {
        merged_b = std::shared_ptr<Node>(curr, curr.get());
      } 
    }
    while (merged_a->next.get() != nullptr || merged_b->next.get() != nullptr) {
      assert(merged_a.get() == merged_b.get());
      merged_a = std::shared_ptr<Node>(merged_a->next, merged_a->next.get());
      merged_b = std::shared_ptr<Node>(merged_b->next, merged_b->next.get());
    }
    // Test user code.
    assert(head_c.get() == find_node(head_a.get(), head_b.get()));
  }
  return 0;
}
