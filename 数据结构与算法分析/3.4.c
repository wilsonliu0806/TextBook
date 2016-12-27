#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define FatalError printf
struct Node
{
    ElementType Element;
    Position Next;
};
List MakeEmpty(List L){
    if(L!= NULL)
        DeleteList(L);
    L = malloc(sizeof(struct Node));
    if(L == NULL)
        FatalError("Out of Memeory!");
    L->Next = NULL;
    return L;
}
int IsEmpty(List L)
{
    return L->Next == NULL;
}
int IsLast(Position P,List L)
{
    return P->Next == NULL;
}
Position Find(ElementType X,List L)
{
    Position P;
    P = L->Next;
    while(P!=NULL && P->Element!=X){
        P = P->Next;
    }
    return P;
}
void Delete(ElementType X,List L)
{
    Position P,TmpCell;
    P = FindPrevious(X,L);
    if(!IsLast(P,L)){
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
}
void DeleteList(List L)
{
    Position P;
    P = L->Next;
    L->Next = NULL;
    while(P!=NULL){
        free(P);
        P = P->Next;
    }
}
Position FindPrevious(ElementType X,List L)
{
    Position P;
    P = L;
    while(P->Next!=NULL && P->Next->Element != X){
        P = P->Next;
    }
    return P;
}
void Insert(ElementType X,List L,Position P)
{
    Position TmpCell;
    TmpCell = malloc(sizeof(struct Node));
    if(TmpCell == NULL){
        FatalError("Out of Space");
        return;
    }
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

List ListInterSec(List L1,List L2)
{
    List Result;
    Position L1Pos,L2Pos,ResultPos;
    L1Pos = First(L1);L2Pos = First(L2);
    Result = MakeEmpty(NULL);
    ResultPos = First(Result);
    while(L1Pos!=NULL&&L2Pos!=NULL)
    {
        if(L1Pos->Element < L2Pos->Element)
            L1Pos = Next(L1Pos,L1);
        else if(L1Pos->Element > L2Pos->Element)
            L2Pos = Next(L2Pos,L2);
        else{
            Insert(L1Pos->Element,Result,ResultPos);
            L1 = Next(L1Pos,L1);L2 = Next(L2Pos,L2);
            ResultPos = Next(ResultPos,Result);
        }
    }
    return Result;
}
int main(){
    List L = malloc(sizeof(struct Node));
    if(L == NULL){
        return 1;
    }else{
        L->Next = NULL;
    }
    Insert(0,L,L);
    return 0;
}
