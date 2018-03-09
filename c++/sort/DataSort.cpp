//
// Created by Hong,Jian on 2018/2/25.
//

#include <cstdio>
#include <stack>

using namespace std;
/**
 * 交换指针指向的存储的值
 * @param i
 * @param j
 */
void SwapVal (int* i, int *j) {
    int temp = *j;
    *j = *i;
    *i = temp;
}

/**
 * 输出数组内容
 * @param arr
 * @param size
 */
void print (int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d,", arr[i]);
    }
}

/**
 * 直接插入排序
 * 将一个记录插入到已排序好的有序表中，从而得到一个新，记录数增1的有序表。即：先将序列的第1个记录看成是一个有序的子序
 * 列，然后从第2个记录逐个进行插入，直至整个序列有序为止。
 * 如果碰见一个和插入元素相等的，那么插入元素把想插入的元素放
 * 在相等元素的后面。所以，相等元素的前后顺序没有改变，从原无序序列出去的顺序就是排好序后的顺序，所以插入排序是稳定的。
 *
 * 时间复杂度 O(n^2)
 *
 * @param arr
 * @param size
 */
void StraightInsertionSort (int arr[], int size) {
    int j;
    for (int i = 1; i < size ; ++i) {
        j = i;
        for (; j > 0; --j) {
            if (arr[j-1] > arr[j]) {
                SwapVal(&arr[j-1], &arr[j]);
            } else {
                break;
            }
        }
    }
}

/**
 *
 * @param arr
 * @param size
 * @param d
 */
void ShellSort (int arr[], int size, int d) {
    int j;
    for (int i = d; i < size; i = i + d) {
        j = i;
        for (; j > 0; j -= d) {
            if (arr[j-d] > arr[j]) {
                SwapVal(&arr[j-d], &arr[j]);
            } else {
                break;
            }
        }
    }
}

/**
 * 希尔排序
 * 是直接插入排序的改进版本，原理接近于分组排序。
 * 不稳定
 *
 * 时间 O(nlogn)
 *
 * @param arr
 * @param size
 * @param d 分组步长
 */
void ShellInsertSort (int arr[], int size, int d) {
    int dk = size/d;
    while (dk >= 1) {
        ShellSort(arr, size, dk);
        dk = dk/d;
    }
}

/**
 * 简单选择排序
 * 在要排序的一组数中，选出最小（或者最大）的一个数与第1个位置的数交换；然后在剩下的数当中再找最小（或者最大）的与第2个位置的数交换，
 * 依次类推，直到第n-1个元素（倒数第二个数）和第n个元素（最后一个数）比较为止。
 * 稳定
 *
 * 时间复杂度 O(n^2)
 *
 * @param arr
 * @param size
 */
void SimpleSelectionSort (int arr[], int size) {
    int min;
    for (int i = 0; i < size; ++i) {
        min = i;
        for (int j = i; j < size; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (i != min) {
            SwapVal(&arr[i], &arr[min]);
        }
    }
}

/**
 * 堆调整
 * @param arr
 * @param i    待调整节点的位置
 */
void HeapAdjust (int arr[], int i, int size) {
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;
    if (right < size && arr[left] < arr[right]) {
        SwapVal(&arr[left], &arr[right]);
    }

    if (arr[i] < arr[left]) {
        SwapVal(&arr[i], &arr[left]);
    }
}

/**
 * 替换根节点后，做一个向下的shift
 */
void HeapShift (int arr[], int i, int size) {
    int left    = i * 2 + 1;
    int right   = i * 2 + 2;

    if (right < size && arr[left] < arr[right]) {
        SwapVal(&arr[left], &arr[right]);
    }

    if (arr[left] > arr[i]) {
        SwapVal(&arr[left], &arr[i]);
    }

    if (left * 2 + 1> size) {
        return;
    }

    if (arr[left * 2 + 1] > arr[left]) {
        HeapShift(arr, left, size);
    }
}

/**
 * 构建堆，这里构建一个最大堆
 * 输入数组当作一个完全二叉树进行处理
 *
 * O(nlogn)
 *
 * @param arr
 * @param size
 */
void InitHeap (int arr[], int size) {
    int i = size/2 -  1;
    while (i >= 0) {
        HeapAdjust(arr, i, size);

        i--;
    }
}

/**
 * 输出堆排序后数据
 * @param arr
 * @param size
 */
void printHeap (int arr[], int size) {
    if (size <= 2) {
        if (arr[0] < arr[1]) {
            SwapVal(&arr[0], &arr[1]);
        }
        printf("%d, %d", arr[0], arr[1]);
        return;
    }

    while (size > 2) {
        printf("%d,", arr[0]);
        arr[0] = arr[size-1];
        size --;

        HeapShift(arr, 0, size);
    }

    if (arr[0] < arr[1]) {
        SwapVal(&arr[0], &arr[1]);
    }
    printf("%d, %d", arr[0], arr[1]);
}

/**
 * 快排一趟子过程
 *
 * O(nlogn)
 *
 * @param arr
 * @param left
 * @param right
 */
int Partition (int arr[], int left, int right) {
    int key = arr[left];
    while (left < right) {
        while (left < right) {
            if (arr[right] < key) {
                break;
            }
            right--;
        }

        arr[left] = arr[right];

        while (left < right) {
            if (arr[left] > key) {
                break;
            }
            left++;
        }

        arr[right] = arr[left];
    }

    arr[left] = key;
    return left;
}

/**
 * 递归实现快速排序
 *
 * @param arr
 * @param left
 * @param right
 */
void QuickSortRecursive (int arr[], int left, int right) {
    if (left >= right || left < 0 || arr == NULL) {
        return;
    }

    int par = Partition(arr, left, right);

    if (left < par) {
        QuickSortRecursive(arr, left, par - 1);
    }

    if (right > par) {
        QuickSortRecursive(arr, par + 1, right);
    }
}

/**
 * 非递归实现快排
 *
 * @param arr
 * @param left
 * @param right
 */
void QuickSortNonRecursive (int arr[], int left, int right) {
    stack<int> s;

     if (left > right || left < 0 || arr == NULL) {
        return;
    }

    s.push(right);
    s.push(left);
    int t_left, t_right, par;

    while (! s.empty()) {
        t_left = s.top();
        s.pop();
        t_right = s.top();
        s.pop();

        par = Partition(arr, t_left, t_right);

        if (t_left < par) {
            s.push(par - 1);
            s.push(left);
        }

        if (t_right > par) {
            s.push(right);
            s.push(par + 1);
        }
    }
}

/**
 * 归并排序merge的子过程,暴力型 空间复杂度O(1) 做法
 *
 * @param arr
 * @param start   第一个有序集head
 * @param end     第一个有序集end
 * @param start2  第二个有序集head
 * @param end2    第二个有序集end
 */
void MergeWithMoreShift (int arr[], int start, int end, int start2, int end2) {
    int i = start;
    int j;
    int k;
    while (i <= end) {
        j = start2;
        while (j <= end2) {
            if (arr[i] > arr[j]) {
                SwapVal(&arr[i], &arr[j]);
                //对第二个序列进行一遍重筛，如果使用二分查找，来确定应该插入的位置，时间复杂度优化上会更加合理
                k = j;
                while (k <= end2) {
                    if (arr[j] > arr[k]) {
                        SwapVal(&arr[j], &arr[k]);
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }
}

/**
 * 数组取反交换位置
 *
 * @param arr
 * @param left
 * @param right
 */
void reverse (int* arr, int left, int right) {
    while (left <= right) {
        SwapVal(&arr[left++], &arr[right--]);
    }
}

/**
 * 手摇算法
 *
 * @param arr
 * @param left
 * @param mid
 * @param right
 */
void HandRoll (int* arr, int left, int mid, int right) {
    reverse(arr, left, mid);
    reverse(arr, mid + 1, right);
    reverse(arr, left, right);
}

/**
 *
 * 归并merge过程
 *
 * @param arr
 * @param start
 * @param mid
 * @param end
 * @param temp
 */
void MergeSort (int arr[], int start, int mid, int end, int temp[]) {
    int start2 = mid + 1;
    int start1 = start;
    int t = start;
    while (start1 <= mid && start2 <= end) {
        if (arr[start1] <= arr[start2]) {
            temp[t++] = arr[start1++];
        } else {
            temp[t++] = arr[start2++];
        }
    }

    //组合未拼接完的数据
    while (start1 <= mid) {
        temp[t++] = arr[start1++];
    }

    while (start2 <= end) {
        temp[t++] = arr[start2++];
    }

    while (start <= end) {
        arr[start] = temp[start];
        start++;
    }
}

/**
 * 递归归并
 * O(nlogn)
 *
 * @param arr
 * @param start
 * @param end
 * @param temp
 */
void MergeSortRecursive (int arr[], int start, int end, int temp[]) {
    if (start >= end || arr == NULL) {
        return;
    }

    int mid = (start + end) / 2;
    MergeSortRecursive(arr, start, mid, temp);
    MergeSortRecursive(arr, mid + 1, end, temp);
    MergeSort(arr, start, mid, end, temp);
}

int main () {
    int a[8] = {1, 4, 2, 3, 2, 7, 1, 6};
    //int a[8] = {1, 2, 3, 4, 5, 4, 3, 2};
    //int a[8] = {2, 2, 2, 2, 4, 4, 4, 4};

    //直接插入排序
//    StraightInsertionSort(a, 8);
//    print(a, 8);

    //希尔排序
//    ShellInsertSort(a, 8, 2);
//    print(a, 8);

    //简单选择排序
//    SimpleSelectionSort(a, 8);
//    print(a, 8);

    //堆排序
//    InitHeap(a, 8);
//    printHeap(a, 8);

    //快速排序
    //QuickSortRecursive(a, 0, 7);
//    QuickSortNonRecursive(a, 0, 7);
//    print(a, 8);

    //归并排序
    int b[8];
    MergeSortRecursive(a, 0, 7, b);
    print(b, 8);

    return 0;
}