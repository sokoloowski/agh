public class Lab3Z1 {
    public static void main(String[] args) {
        int [] arr = { 4, 8, 1, 5, 9, 2, 3 };
        quickSort(arr);

    }
    public static void quickSort(int arr[]) {
        quickSort(arr, 0, arr.length-1);
    }
    public void quickSort(int arr[], int begin, int end) {
        if (begin < end) {
            int index = partition(arr, ..., ...);
            quickSort(arr, begin, ...-1);
            quickSort(arr, ...+1, ...);
        }
    }
    private static int partition(int arr[], int begin, int end) {
        int pivot = arr[end];
        int i = ...);
        for (int j = ...; j < ...; ...) {
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[...];
                arr[...] = arr[...];
                arr[...] = temp;
            }
        }
        int temp = arr[i+1];
        arr[i+1] = arr[end];
        arr[end] = temp;
        return ...;
    }

}