#-*- coding: utf-8 -*-

def partition(a,p,r):
    i = p-1
    x = a[r]
    for j in range(p,r):
        if(a[j]<=x):
            i=i+1
            a[i],a[j] = a[j],a[i]
    i = i+1
    a[i],a[r] = a[r],a[i]
    return i

def quicksort(a,p,r):
    if(p<r):
        q = partition(a,p,r)
        quicksort(a,p,q-1)
        quicksort(a,q+1,r)
