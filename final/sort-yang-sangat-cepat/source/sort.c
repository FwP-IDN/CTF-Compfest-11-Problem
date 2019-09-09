void sort(int arr[], int low, int high, long long int *call){
    *call = *call + 1;
    if (*call >= 150000){
        return;
    }
    int pivot, i, j, temp;
    if (low < high){
        pivot = low;
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        i = low;
        j = high;
        while (i < j){
            while (arr[i] <= arr[pivot] && i <= high){
                i++;
            }
            while (arr[j] > arr[pivot] && j >= low){
                j--;
            }
            if (i < j){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[j];
        arr[j] = arr[pivot];
        arr[pivot] = temp;
        sort(arr, low, j - 1, call);
        sort(arr, j + 1, high, call);
    }
}