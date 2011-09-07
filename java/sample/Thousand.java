import java.lang.*;

class Thousand {
    public static void main (String [] args) {
        for (int i = 1; i <= 1000; i ++) {
            for (int j = i, n = 0; j <= 1000 && n <= 1000; j ++) {
                n += j;
                if (n == 1000) {
                    System.out.println(i + "から" + j);
                    break;
                }
            }
        }
        // -----------------------------------------------------------
        int first = 1;
        int last = 2;
        int sum = first + last;
        while (first <= 1000) {
            if (sum < 1000) {
                last ++;
                sum += last;
            } else {
                if (sum == 1000) {
                    System.out.println("from " + first + " to " + last);
                }
                sum -= first;
                first ++;
            }
        }
    }
}
